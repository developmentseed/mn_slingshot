<?php
// $Id$

/**
 * @file
 * Passthrough fetcher for SlingshotSMS
 */

class FeedsSlingshotBatch extends FeedsImportBatch {
  /**
   * Constructor.
   *
   * Either $url or $file_path must be given.
   */
  public function __construct($url = NULL, $file_path = NULL, $raw = NULL) {
    $this->url = $url;
    $this->file_path = $file_path;
    $this->raw = $raw;
    $this->items = array();
  }
}

/**
 * POST fetcher. Based off of PuSH
 */
class FeedsSlingshotFetcher extends FeedsHTTPFetcher {

  /**
   * Receive a notification.
   */
  public function receive() {
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
      keyauth_include();
      $post_input = file_get_contents('php://input');
      $query_variables = array();
      parse_str($post_input, $query_variables);
      if (keyauth_verify(
        "acf8b2bb295ccb58c1ad4e3a376a81cb", 
        $query_variables['message'], 
        $query_variables['nonce'],
        $query_variables['timestamp'],
        $query_variables['hash'])) {
          $item = array();
          parse_str($query_variables['message'], $item);
          return array($item);
      }
    }
    return FALSE;
  }

  /**
   * Implementation of FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    $raw = $this->receive();
    return new FeedsSlingshotBatch($source_config['source'], NULL, $raw);
  }

  /**
   * Return defaults for configuration.
   */
  public function configDefaults() {
    $defaults = parent::configDefaults();
    return $defaults + array(
      'subscription_period' => 3600*24, // Renew subscription in 24 hours.
    );
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = parent::configForm($form_state);
    return $form;
  }
}
