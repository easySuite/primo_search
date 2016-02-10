<?php
/**
 * @file
 *   Define primo search carousel.
 */

module_load_include('inc', 'primo_search', 'pages');

$plugin = array(
  'single' => TRUE,
  'title' => t('Primo Search Carousel.'),
  'description' => t('Display primo books as a carousel.'),
  'category' => t('Widgets'),
  'render callback' => 'primo_search_carousel_render',
);

function primo_search_carousel_render($subtype, $conf, $args, $contexts) {
  $subjects = variable_get('primo_search_subjects', array());
  unset($subjects['more']);

  // Theme primo search items.
  $params['image_style'] = 'primo_carousel_cover';
  $params['options'] = $subjects;
  $output = _primo_search_theme_carousel($params);

  // Prepare block content to the output.
  $path = drupal_get_path('module', 'primo_search');
  $block = new stdClass();
  $block->content = array(
    '#markup' => $output,
    '#attached' => array(
      'css' => array(
        $path . '/css/primo_search.css',
        $path . '/css/jquery.rs.carousel.css',
      ),
      'js' => array(
        $path . '/js/jquery.rs.carousel.js',
        $path . '/js/primo_search.carousel.js',
      ),
    ),
  );

  return $block;
}

function _primo_search_theme_carousel($params) {
  $output = theme(
    'primo_search_carousel',
    array(
      'tabs' => $params['options'],
    )
  );

  return $output;
}
