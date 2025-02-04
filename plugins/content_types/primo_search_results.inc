<?php
/**
 * @file
 *   Define main result as a highlighted book.
 */

module_load_include('inc', 'primo_search', 'pages');

$plugin = array(
  'single' => TRUE,
  'title' => t('Primo Search Results'),
  'description' => t('Display primo search results.'),
  'category' => t('Widgets'),
  'render callback' => 'primo_search_items_render',
);

/**
 * Render primo search panel.
 */
function primo_search_items_render($subtype, $conf, $args, $contexts) {
  $subjects = variable_get('primo_search_subjects', array());
  unset($subjects['more']);
  $arg_keys = array();
  foreach ($subjects as $subject) {
    $arg_keys[$subject['index']] = $subject['name'];
  }

  // Prepare arguments for most recent items.
  $keys = array_slice(array_keys($arg_keys), 1);
  $request = implode('+OR+', $keys);
  $arg = '0';
  if (isset($args[0]) && $args[0] != '0') {
    $request = $args[0];
    $arg = $args[0];
  }
  $count = variable_get('primo_search_page_items', 50);
  $items = primo_search_get_items_by_subject($request, $count);
  $output = '';

  if (!empty($items)) {
    // Get the first item, as the main one.
    $main_item = array_shift($items);
    $form = drupal_get_form('primo_search_select_form', $arg, $arg_keys);

    $params = array(
      'image_style' => 'primo_main',
      'options' => $arg_keys,
    );
    // Theme the main item.
    $output = _primo_search_theme_item($main_item, $params);

    // Render select form.
    $output .= drupal_render($form);

    // Theme primo search items.
    $params['image_style'] = 'primo_thumb';
    $params['options'] = $arg_keys;
    $output .= _primo_search_theme_grid($items, $params);
  }

  // Prepare block content to the output.
  $block = new stdClass();
  $block->content = $output;

  return $block;
}

/**
 * Select list to choose the books category.
 */
function primo_search_select_form($form, &$form_state, $arg, $options) {
  $path = drupal_get_path('module', 'primo_search');
  $form['requests'] = array(
    '#type' => 'select',
    '#title' => t('Sort by subject'),
    '#options' => $options,
    '#default_value' => $arg,
    '#attributes' => array(
      'id' => array('primo_search_select'),
    ),
    '#attached' => array(
      'js' => array(
        $path . '/js/primo_search.js',
      ),
      'css' => array(
        $path . '/css/primo_search.css',
      ),
    ),
  );

  return $form;
}

/**
 * Theme function of a book item.
 *
 * @param $item
 *   Array of book fields to the themed.
 *
 * @param $params
 *   Parameters used for themming: image_style, category.
 *
 * @return string
 *   Rendered string.
 */
function _primo_search_theme_item($item, $params) {
  $options = $params['options'];

  $field = _primo_search_filter_fields($item['attributes']);

  if ($field['category']) {
    $category = $options[$field['category']];
  }
  else {
    $category = array_pop($options);
  }

  $image_path = (isset($field['image']) && $field['image']) ? $field['image'] : drupal_get_path('module', 'primo_search') . '/img/default.png';
  $image = theme_primo_image(array('style_name' => $params['image_style'], 'path' => $image_path));
  $link = _primo_search_title_link($item['doc_number']);
  $themed_item = theme(
    'primo_search_item',
    array(
      'title' => !empty($field['title']) ? $field['title'] : FALSE,
      'title_link' => $link,
      'image' => $image,
      'category' => t($category),
      'author_name' => !empty($field['author_name']) ? $field['author_name'] : FALSE,
      'author_surname' => !empty($field['author_surname']) ? $field['author_surname'] : FALSE,
      'udg' => !empty($field['udg']) ? $field['udg'] : FALSE,
      'pages' => !empty($field['pages']) ? $field['pages'] : FALSE,
      'institution' => !empty($field['institution']) ? $field['institution'] : FALSE,
      'isbn' => !empty($field['isbn']) ? $field['isbn'] : FALSE,
    )
  );
  return $themed_item;
}

/**
 * Theme items as grid for search results region.
 *
 * @param $items
 *   Array of themed items.
 *
 * @param $category
 *   Items category.
 *
 * @return string
 *   Themed grid block.
 */
function _primo_search_theme_grid($items, $category) {
  $elements = array();
  foreach ($items as $item) {
    $elements[] = _primo_search_theme_item($item, $category);
  }
  return theme('primo_search_grid', array('elements' => $elements));
}
