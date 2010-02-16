<?php

/**
 * @file
 * Pubsubhubbub subscriber library.
 */

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
      if(keyauth_verify(
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
    return new FeedsImportBatch($source_config['source'], NULL, $raw);
    //return parent::fetch($source);
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
    /*
    $form['subscription_period'] = array(
      '#type' => 'select',
      '#title' => t('Renew subscription after'),
      '#options' => $period,
      '#description' => t('This is the minimum time that must elapse before a subscription is renewed.'),
      '#default_value' => $this->config['subscription_period'],
    );
     */
    return $form;
  }
}
