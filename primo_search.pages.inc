<?php
/**
 * @file
 * Define proper functions for service and hooks integration.
 */

/**
 * Load primo items from service based on subject id.
 *
 * @param $subject_id
 *   Unique code that is passed to the primo find request.
 * @param $count
 *   How many items to request from service.
 *
 * @return array
 *   Array of primo raw items.
 */
function primo_search_get_items_by_subject($subject_id, $count = 50) {
  $primo_link = variable_get('primo_search_host', '');
  $items = array();

  try {
    $ps = new PrimoSearchService($primo_link);

    // Prepare parameters for find query.
    $find_params = array(
      'code' => 'wtv',
      'base' => 'dabdab',
      'request' => check_plain($subject_id),
    );
    $find = $ps->findPrimoItems($find_params);

    // Prepare parameters for present query.
    $present_params = array(
      'format' => 'marc',
      'set_no' => $find->set_number,
      'set_entry' => '000000001-' . $count,
    );
    $items = $ps->presentPrimoItems($present_params);

  }
  catch (Exception $e) {
    watchdog('primo_search', 'Unable to retrieve items from PRIMO SEARCH: %message', array('%message' => $e->getMessage()), WATCHDOG_ERROR);
  }

  return $items;
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
      case '592':
        $category = (string) $subfield[0];
        $category_arr = explode(' ', $category);
        $item['category'] = isset($category_arr[1]) ? $category_arr[1]: FALSE;
        break;
    }
  }

  return $item;
}

/**
 * Fetch the link to the primo item based on its doc_number.
 *
 * @param $doc_number
 *   Unique identifier of the item on service.
 *
 * @return string
 *   Url on the primo search site.
 */
function _primo_search_title_link($doc_number) {
  $query = 'DABPR' . $doc_number;
  $params = array(
    'mode' => 'Basic',
    'vl(freeText0)' => $query,
    'fn' => 'search',
    'doc' => $query,
    'scp.scps' => 'scope:(DABPR)',
    'vid' => 'DAB',
    'tab' => 'default_tab',
    'srt' => 'rank',
    'indx' => 1,
    'dscnt' => 0,
    'dum' => 'true',
  );
  $http_query = drupal_http_build_query($params);
  $bib_link = variable_get('primo_search_lib_url', '');

  $search_query = ($http_query && $bib_link) ? implode('?', array($bib_link, $http_query)) : '';

  return $search_query;
}

/**
 * Get url of the book cover form the ADDI service based on book isbn.
 *
 * @param $isbn
 *   isbn identifier of a book.
 *
 * @return mixed
 *   image url or FALSE if the cover image is missing.
 */
function _primo_search_cover_url($isbn) {
  $service = new AdditionalInformationService(variable_get('addi_wsdl_url'), variable_get('addi_username'), variable_get('addi_group'), variable_get('addi_password'));
  $info = $service->getByIsbn($isbn);
  $image = (!empty($info)) ? $info[$isbn] : FALSE;

  return ($image) ? $image->detailUrl : FALSE;
}

/**
 * Download cover image of the book based on the it's isbn identifier.
 *
 * @param $isbn
 *   isbn identifier.
 *
 * @return mixed
 *   File path or FALSE if image is not accessible.
 */
function _primo_search_download_cover($isbn) {
  $directory = file_default_scheme() . '://covers';

  // Build the destination folder tree if it doesn't already exist.
  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY || FILE_MODIFY_PERMISSIONS)) {
    watchdog('ting_covers', 'Failed to create directory: %directory', array('%directory' => $directory), WATCHDOG_ERROR);
    return FALSE;
  }
  $destination = $directory . DIRECTORY_SEPARATOR . $isbn . '.jpg';
  $retrieved_file = $destination;
  if (!is_file($destination)) {
    $retrieved_file = FALSE;
    $url = _primo_search_cover_url($isbn);
    if ($url) {
      $retrieved_file = system_retrieve_file($url, $destination, FALSE, FILE_EXISTS_REPLACE);
    }
  }
  return $retrieved_file;
}
