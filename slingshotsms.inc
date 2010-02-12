<?php

/**
 * @file
 * Pubsubhubbub subscriber library.
 */

/**
 * Pubsub subscriber.
 */
class SlingSubscriber {
  /**
   * Singleton.
   *
   * SlingSubscriber identifies a unique subscription by a domain and a numeric
   * id. The numeric id is assumed to e unique in its domain.
   *
   * @param $domain
   *   A string that identifies the domain in which $subscriber_id is unique.
   * @param $subscriber_id
   *   A numeric subscriber id.
   * @param PuSHSubscriptionsInterface $subscriptions
   *   An object to use for storing and loading subscriptions.
  public static function instance($domain, $subscriber_id, PuSHSubscriptionsInterface $subscriptions) {
    static $subscribers;
    if (!isset($subscriber[$domain][$subscriber_id])) {
      $subscriber = new SlingSubscriber($domain, $subscriber_id, $subscriptions);
    }
    return $subscriber;
  }
    protected function __construct($domain, $subscriber_id, PuSHSubscriptionsInterface $subscriptions) {
    $this->domain = $domain;
    $this->subscriber_id = $subscriber_id;
    $this->subscriptions = $subscriptions;
  }
   */

  /**
   * Receive a notification.
   */
  public function receive() {
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
      return file_get_contents('php://input');
    }
    return FALSE;
  }
}
