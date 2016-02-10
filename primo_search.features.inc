<?php
/**
 * @file
 * primo_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function primo_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function primo_search_image_default_styles() {
  $styles = array();

  // Exported image style: primo_carousel_cover.
  $styles['primo_carousel_cover'] = array(
    'name' => 'primo_carousel_cover',
    'label' => 'Primo Carousel Cover',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 135,
          'height' => 196,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: primo_main.
  $styles['primo_main'] = array(
    'name' => 'primo_main',
    'label' => 'Primo Main',
    'effects' => array(
      3 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 140,
          'height' => 196,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: primo_thumb.
  $styles['primo_thumb'] = array(
    'name' => 'primo_thumb',
    'label' => 'Primo Thumb',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 70,
          'height' => 98,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
