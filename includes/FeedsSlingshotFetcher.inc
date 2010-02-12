<?php

feeds_include_library('PushSubscriber.inc', 'PushSubscriber');

/**
 * Publish/Subscribe fetcher. Supports at the moment only PubSubHubbub (PuSH).
 */
class FeedsSlingshotFetcher extends FeedsHTTPFetcher {

  /**
   * Implementation of FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    // Handle fat ping if present, otherwise pass up to HTTP fetcher.
    if ($raw = feeds_push_subscriber($this->id, $source->feed_nid)->receive()) {
      return new FeedsImportBatch($source_config['source'], NULL, $raw);
    }
    return parent::fetch($source);
  }

  /**
   * Override sourceSave() - subscribe to hub.
   */
  public function sourceSave(FeedsSource $source) {
    $this->subscribe($source);
  }

  /**
   * Override sourceDelete() - unsubscribe from hub.
   */
  public function sourceDelete(FeedsSource $source) {
    $this->unsubscribe($source);
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
    $period = drupal_map_assoc(array(0, 900, 1800, 3600, 10800, 21600, 43200, 86400, 259200, 604800, 2419200), 'format_interval');
    $period[FEEDS_SCHEDULE_NEVER] = t('Never renew');
    $period[0] = t('Renew as often as possible');
    $form['subscription_period'] = array(
      '#type' => 'select',
      '#title' => t('Renew subscription after'),
      '#options' => $period,
      '#description' => t('This is the minimum time that must elapse before a subscription is renewed.'),
      '#default_value' => $this->config['subscription_period'],
    );
    return $form;
  }

  /**
   * Verify a PubSubHubbub subscription request.
   */
  public function pushVerifySubscriptionRequest($verify_fields, $feed_nid) {
    feeds_push_subscriber($this->id, $feed_nid)->verifySubscriptionRequest($verify_fields);
  }
}

/**
 * Create a PubSubHubbub subscriber.
 *
 * @return PushSubscriber
 *   A PushSubscriber object.
 */
function feeds_push_subscriber($id, $subscriber_id) {
  return PushSubscriber::instance($id, $subscriber_id, PuSHSubscriptions::instance());
}
