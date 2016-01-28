<?php
/**
 * @file
 *   Define main result as a highlighted book.
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Primo Search Results'),
  'description' => t('Display primo search results.'),
  'category' => t('Widgets'),
  'render callback' => 'primo_search_items',
);

/**
 * Render primo search panel.
 */
function primo_search_items($subtype, $conf, $args, $contexts) {
  $primo_link = variable_get('primo_search_host', '');
  $ps = new PrimoSearchService($primo_link);

  // Prepare arguments for most recent items.
  $arg_keys = array('001', '002', '003', '004', '005', '006');
  $request = implode('+OR+', $arg_keys);
  $arg = '0';
  if (isset($args[0]) && $args[0] != '0') {
    $request = $args[0];
    $arg = $args[0];
  }
  // Prepare parameters for find query.
  $find_params = array(
    'code' => 'wtv',
    'base' => 'dabdab',
    'request' => check_plain($request),
  );
  $find = $ps->findPrimoItems($find_params);

  // Prepare parameters for present query.
  $set_count = variable_get('primo_search_set_count', 50);
  $present_params = array(
    'format' => 'marc',
    'set_no' => $find->set_number,
    'set_entry' => '000000001-' . $set_count,
  );
  $items = $ps->presentPrimoItems($present_params);

  // Get the first item, as the main one.
  $main_item = array_shift($items);
  $form = drupal_get_form('primo_search_select_form', $arg);

  $params = array(
    'category' => $form['requests']['#options'][$arg],
    'image_style' => 'primo_main',
  );
  // Theme the main item.
  $output = _primo_search_theme_item($main_item, $params);

  // Render select form.
  $output .= drupal_render($form);

  // Theme primo search items.
  $params['image_style'] = 'primo_thumb';
  $output .= _primo_search_theme_grid($items, $params);

  // Prepare block content to the output.
  $block = new stdClass();
  $block->content = $output;

  return $block;
}

/**
 * Select list to choose the books category.
 */
function primo_search_select_form($form, &$form_state, $arg) {
  $options = array(
    '0'   => t('Recent books'),
    '001' => t('Management'),
    '002' => t('Jura'),
    '003' => t('Politics'),
    '004' => t('Economy'),
    '005' => t('Organization and Leadership'),
    '006' => t('Other Literature'),
  );
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
 * Filter primo search fields from primo object.
 *
 * @param $fields
 *   Primo object.
 *
 * @return array
 *   Array of book info fields ready to be rendered.
 */
function _primo_search_filter_fields($fields) {
  $item = array();
  foreach ($fields->varfield as $field) {
    $subfield = $field->subfield;
    switch ($field->attributes()->id) {
      case '021':
        $isbn = (string) $subfield[0];
        $isbn = $isbn = str_replace('-', '', $isbn);
        $item['isbn'] = $isbn;
        $item['image'] = _primo_search_download_cover($isbn);
        break;
      case '245':
        $item['title'] = (string) $subfield[0];
        break;
      case '250':
        $item['udg'] = (string) $subfield[0];
        break;
      case '300':
        $item['pages'] = (string) $subfield;
        break;
      case '700':
        $item['author_name'] = (string) $subfield[1];
        $item['author_surname'] = (string) $subfield[0];
        break;
      case '710':
        $item['institution'] = (string) $subfield[0];
        break;
    }
  }

  return $item;
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
  $field = _primo_search_filter_fields($item['attributes']);

  $image_path = (isset($field['image']) && $field['image']) ? $field['image'] : drupal_get_path('module', 'primo_search') . '/img/default.png';
  $image = theme_primo_image(array('style_name' => $params['image_style'], 'path' => $image_path));
  $link = _primo_search_title_link($item['doc_number']);
  $themed_item = theme(
    'primo_search_item',
    array(
      'title' => !empty($field['title']) ? $field['title'] : FALSE,
      'title_link' => $link,
      'image' => $image,
      'category' => $params['category'],
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
