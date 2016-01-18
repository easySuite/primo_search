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
  $form['primo_search']['primo_search_institution'] = array(
    '#type' => 'textfield',
    '#description' => t('Primo search institution'),
    '#default_value' => variable_get('primo_search_institution', ''),
  );

  return system_settings_form($form);
}
