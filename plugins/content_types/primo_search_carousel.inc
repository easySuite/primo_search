<?php
/**
 * @file
 *   Define primo search carousel.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Primo Search Carousel.'),
  'description' => t('Display primo books as a carousel.'),
  'category' => t('Widgets'),
  'render callback' => 'primo_search_carousel_render',
);

function primo_search_carousel_render($subtype, $conf, $args, $contexts) {
  $options = array(
    '0'   => t('Recent books'),
    '001' => t('Management'),
    '002' => t('Jura'),
    '003' => t('Politics'),
    '004' => t('Economy'),
    '005' => t('Organization and Leadership'),
    '006' => t('Other Literature'),
  );
  // Theme primo search items.
  $params['image_style'] = 'primo_carousel_cover';
  $params['options'] = $options;
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
