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
  $form['primo_search']['primo_search_host'] = array(
    '#type' => 'textfield',
    '#description' => t('Primo search host, e.g. <em>http://www.minibib.dk/X</em>'),
    '#default_value' => variable_get('primo_search_host', ''),
  );
  $form['primo_search']['primo_search_lib_url'] = array(
    '#type' => 'textfield',
    '#description' => t('Primo search library url to search the item at, e.g. <em>http://minibib.hosted.exlibrisgroup.com/primo_library/libweb/action/display.do</em>'),
    '#default_value' => variable_get('primo_search_lib_url', 'http://minibib.hosted.exlibrisgroup.com/primo_library/libweb/action/display.do'),
  );

  return system_settings_form($form);
}
