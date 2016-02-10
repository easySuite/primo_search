<?php
/**
 * @file
 * Main functions to get the results from Primo Search service.
 */

class PrimoSearchService {
  // Service url.
  private $url;

  public function __construct($url) {
    if (!$url) {
      throw new Exception(t('Url is empty.'));
    }
    $this->url = $url;
  }

  /**
   * Find elements based on request.
   *
   * @param $params
   *   Contains default parameters for find query: code, base, request.
   *
   * @return \SimpleXMLElement
   *   Object of the number of the set and records.
   */
  public function findPrimoItems($params) {
    $params['op'] = 'find';
    return $this->getPrimoItems($params);
  }

  /**
   * Present/Load items based on set number returned from find request.
   *
   * @param $params
   *   Parameters that include set number of item and amount of items to load,
   *   contains default keys: format, set_no, set_entry.
   *
   * @return array
   *   Array of filtered items from service.
   */
  public function presentPrimoItems($params) {
    $params['op'] = 'present';
    $results = $this->getPrimoItems($params);

    $items = array();
    if ($results) {
      $items = $this->filterPrimoItems($results);
    }

    return $items;
  }

  /**
   * Unset unnecessary attributes of the XMLObject.
   *
   * @param $results
   *   XMLObject of the primo search result.
   *
   * @return array
   *   Filtered array of primo search result items.
   */
  private function filterPrimoItems($results) {
    $items = array();
    $i = 0;
    foreach ($results as $res) {
      $metadata = $res->metadata;
      $items[$i]['attributes'] = $metadata->oai_marc;

      $doc_number = $res->doc_number;
      if ($doc_number) {
        $items[$i]['doc_number'] = (string) $doc_number[0];
      }
      $i++;
    }

    // Unset the last element of array because it is the session id.
    array_pop($items);

    return $items;
  }

  /**
   * Build query based on parameters that are passed from outside of class.
   *
   * @param $params
   *   array of GET params for query.
   *
   * @return \SimpleXMLElement
   *   Object of Primo Search item based on operation key of the params array.
   */
  private function getPrimoItems($params) {
    $query = drupal_http_build_query($params);
    $request = implode('?', array($this->url, urldecode($query)));
    $response = drupal_http_request($request);
    $result = simplexml_load_string($response->data);

    return $result;
  }
}
