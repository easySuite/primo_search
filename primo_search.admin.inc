<?php
/**
 * @file
 * Define admin functions.
 */

/**
 * Configuration form for the Primo search.
 *
 * @return array admin form.
 */
function primo_search_admin_form() {
  $form = array();
  $form['primo_search'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Primo Search'),
  );
  $form['primo_search']['primo_search_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Primo Search Host'),
    '#description' => t('Primo search host, e.g. <em>http://www.minibib.dk/X</em>'),
    '#default_value' => variable_get('primo_search_host', ''),
  );
  $form['primo_search']['primo_search_lib_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Primo Search Library URL'),
    '#description' => t('Primo search library url to search the item at, e.g. <em>http://minibib.hosted.exlibrisgroup.com/primo_library/libweb/action/display.do</em>'),
    '#default_value' => variable_get('primo_search_lib_url', 'http://minibib.hosted.exlibrisgroup.com/primo_library/libweb/action/display.do'),
  );
  $form['primo_search']['primo_search_page_items'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of primo items on page'),
    '#descritpion' => t('How many items to fetch from server to be displayed on page'),
    '#default_value' => variable_get('primo_search_page_items', 50),
  );
  $form['primo_search']['primo_search_carousel_items'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of primo items on carousel'),
    '#descritpion' => t('How many items to fetch from server to be displayed on page'),
    '#default_value' => variable_get('primo_search_carousel_items', 20),
  );
  /**
   * TODO: Need to add form for the $options array values.
   * @see: primo_search_results_ajax, primo_search_select_form, _primo_search_theme_item, primo_search_carousel_render functions.
   */
  return system_settings_form($form);
}
