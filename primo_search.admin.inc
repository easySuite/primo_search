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
function primo_search_admin_form($form, &$form_state) {
  $form = array(
    '#tree' => TRUE,
  );
  $form['search'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Primo Search'),
  );
  $form['search']['primo_search_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Primo Search Host'),
    '#description' => t('Primo search host, e.g. <em>http://www.minibib.dk/X</em>'),
    '#default_value' => variable_get('primo_search_host', ''),
  );
  $form['search']['primo_search_lib_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Primo Search Library URL'),
    '#description' => t('Primo search library url to search the item at, e.g. <em>http://minibib.hosted.exlibrisgroup.com/primo_library/libweb/action/display.do</em>'),
    '#default_value' => variable_get('primo_search_lib_url', ''),
  );
  $form['search']['primo_search_page_items'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of primo items on page'),
    '#descritpion' => t('How many items to fetch from server to be displayed on page'),
    '#default_value' => variable_get('primo_search_page_items', 50),
  );
  $form['search']['primo_search_carousel_items'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of primo items on carousel'),
    '#descritpion' => t('How many items to fetch from server to be displayed on page'),
    '#default_value' => variable_get('primo_search_carousel_items', 20),
  );

  $form['subjects'] = array(
    '#prefix' => '<div id="primo-search-subjects-wrapper">',
    '#suffix' => '</div>',
    '#type' => 'fieldset',
    '#title' => t('Primo subjects'),
    '#theme' => 'primo_search_subjects_table',
    '#header' => array(
      t('Subject name'),
      t('Subject index'),
    ),
  );

  $subjects = variable_get('primo_search_subjects', array());
  if (!isset($form_state['subjects_count'])) {
    $form_state['subjects_count'] = empty($subjects) ? 1 : count($subjects);
  }
  $subjects_count = $form_state['subjects_count'];

  for ($i = 0; $i < $subjects_count; $i++) {
    $form['subjects'][$i]['name'] = array(
      '#type' => 'textfield',
      '#size'=> 30,
      '#default_value' => isset($subjects[$i]['name']) ? $subjects[$i]['name'] : '',
    );
    $form['subjects'][$i]['index'] = array(
      '#type' => 'textfield',
      '#size'=> 10,
      '#default_value' => isset($subjects[$i]['index']) ? $subjects[$i]['index'] : '',
    );
  }

  $form['subjects']['more'] = array(
    '#type' => 'submit',
    '#value' => t('Add another one'),
    '#ajax' => array(
      'callback' => 'primo_search_subjects_callback',
      'wrapper' => 'primo-search-subjects-wrapper',
    ),
    '#submit' => array('primo_search_subjects_more_submit'),
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Ajax callback for subjects display.
 */
function primo_search_subjects_callback(&$form, &$form_state) {
  return $form['subjects'];
}

/**
 * Re-draw table on add more button click.
 */
function primo_search_subjects_more_submit($form, &$form_state) {
  $form_state['subjects_count']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Save form values to variables.
 */
function primo_search_admin_form_submit($form, $form_state) {
  $subjects = $form_state['values']['subjects'];
  unset($subjects['more']);

  // Filter subjects before save.
  $subjects = array_filter($subjects, function($s) {
    return ($s['name'] != '') && ($s['index'] != '');
  });
  variable_set('primo_search_subjects', $subjects);

  foreach ($form_state['values']['search'] as $k => $v) {
    variable_set($k, $v);
  }
}
