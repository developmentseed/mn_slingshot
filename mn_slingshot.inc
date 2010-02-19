<?php
// $Id$

/**
 * Implementation of hook_strongarm().
 */
function mn_slingshot_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE;
  $strongarm->api_version = 1;
  $strongarm->name = 'feeds_data_slingshot';
  $strongarm->value = 'feeds_data_syndication';
  $export['feeds_data_slingshot'] = $strongarm;
  return $export;
}

/**
 * Implementation of hook_enable().
 */
function mn_slingshot_enable() {
  // Create an example channel.
  $nid = db_result(
    db_query_range("SELECT nid FROM {node} WHERE type = 'slingshot_feed'", 0, 1)
  );
  if (!$nid) {
    global $user;
    $node = new stdClass();
    $node->uid = $user->uid;
    $node->title = "mn_slingshot";
    $node->type = 'slingshot_feed';
    $node->body = "The default mn_slingshot Feed";
    node_save($node);
    variable_set('mn_slingshot_feed_nid', $node->nid);
  }
}

/**
 * Implementation of hook_menu()
 */
function mn_slingshot_menu() {
  $items = array();

  // Slingshot Configuration Page
  $items['admin/settings/slingshot'] = array(
    'title' => 'Slingshot',
    'description' => 'Assistance for associating a mn_slingshot server',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('slingshot_config_form'),
    'access arguments' => array('access content'),
    'file' => 'mn_slingshot_ui.inc',
    'type' => MENU_NORMAL_ITEM
  );
  // Slingshot endpoints and callback for processing
  $items['slingshot/%mn_slingshot_slingshot_feed/%'] = array(
    'page callback' => 'mn_slingshot_receive',
    'page arguments' => array(1, 2),
    'access arguments' => array('access content'),
    'file' => 'mn_slingshot.inc',
    'type' => MENU_NORMAL_ITEM
  );
  return $items;
}

/**
 * Handle a mn_slingshot notification.
 * @param $importer
 *  FeedsImporter object
 * @param $feed_nid
 *  The node id of the feed node
 */
function mn_slingshot_receive($importer, $feed_nid = 0) {
  if ($importer->fetcher instanceof FeedsSlingshotFetcher) {
    // No subscription notification has ben sent, we are being notified.
    try {
      feeds_source($importer->id, $feed_nid)->import();
    }
    catch (Exception $e) {
      // In case of an error, respond with a 503 Service (temporary) unavailable.
      header('HTTP/1.1 503 "Not Found"', null, 503);
      exit();
    }
  }
}

/**
 * Menu loader for slingshot feeds
 * @param $feed_id
 *  Assumed to be the feed id
 */
function mn_slingshot_slingshot_feed_load($feed_id) {
  return feeds_importer($feed_id);
}

/**
 * Implementation of hook_feeds_importer_default().
 */
function mn_slingshot_feeds_plugins() {
  module_load_include('inc', 'mn_slingshot', 'mn_slingshot.plugins');
  $args = func_get_args();
  return call_user_func_array('_mn_slingshot_feeds_plugins', $args);
}

/**
  * Implementation of hook_views_default_views_alter().
  */
function mn_slingshot_views_default_views_alter(&$views) {
  // Add Slingshot Feeds to sidbar feed block
  $views['mn_feeds']->display['default']->display_options['filters']['type']['value'] = array(
    'feed' => 'feed',
    'slingshot_feed' => 'slingshot_feed',
  );
}
