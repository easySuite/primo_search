<?php
/**
 * @file
 * primo_search.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function primo_search_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'primo_search_carousel_items';
  $strongarm->value = '20';
  $export['primo_search_carousel_items'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'primo_search_host';
  $strongarm->value = 'http://www.minibib.dk/X';
  $export['primo_search_host'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'primo_search_lib_url';
  $strongarm->value = 'http://minibib.hosted.exlibrisgroup.com/primo_library/libweb/action/display.do';
  $export['primo_search_lib_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'primo_search_page_items';
  $strongarm->value = '50';
  $export['primo_search_page_items'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'primo_search_subjects';
  $strongarm->value = array(
    0 => array(
      'name' => 'Recent books',
      'index' => '0',
    ),
    1 => array(
      'name' => 'Management',
      'index' => '001',
    ),
    2 => array(
      'name' => 'Jura',
      'index' => '002',
    ),
    3 => array(
      'name' => 'Politics',
      'index' => '003',
    ),
    4 => array(
      'name' => 'Economy',
      'index' => '004',
    ),
    5 => array(
      'name' => 'Organization and Leadership',
      'index' => '005',
    ),
    6 => array(
      'name' => 'Other Literature',
      'index' => '006',
    ),
    'more' => 'Add another one',
  );
  $export['primo_search_subjects'] = $strongarm;

  return $export;
}
