<?php

/**
 * Implementation of hook_strongarm().
 */
function slingshotsms_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'feeds_data_slingshot';
  $strongarm->value = 'feeds_data_syndication';
  $export['feeds_data_slingshot'] = $strongarm;
  return $export;
}

/**
 * Implementation of hook_enable().
 */
function slingshotsms_enable() {
  // Create an example channel.
  $nid = db_result(db_query_range("SELECT nid FROM {node} WHERE type = 'slingshot_feed'", 0, 1));
  if (!$nid) {
    global $user;
    $node = new stdClass();
    $node->uid = $user->uid;
    $node->title = "SlingshotSMS";
    $node->type = 'slingshot_feed';
    $node->body = "The default SlingshotSMS Feed";
    node_save($node);
    variable_set('slingshotsms_feed_nid', $node->nid);
  }
}

/**
 * Implementation of hook_menu()
 */
function slingshotsms_menu() {
  $items = array();

  // Core OpenLayers settings pages.
  $items['admin/settings/slingshot'] = array(
    'title' => 'Slingshot',
    'description' => 'Assistance for associating a SlingshotSMS server',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('slingshot_config_form'),
    'access arguments' => array('access content'),
    'file' => 'slingshotsms_ui.inc',
    'type' => MENU_NORMAL_ITEM
  );
    // Layer type drilldown
  $items['admin/settings/openlayers/layers/add'] = array(
    'title' => 'Add',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('openlayers_ui_layers_types'),
    'access arguments' => array('administer openlayers'),
    'file' => 'includes/openlayers_ui.layers.inc',
    'type' => MENU_LOCAL_TASK,
    'weight' => -10,
  );

  // Core OpenLayers settings pages.
  $items['slingshot/%slingshotsms_slingshot_feed/%node'] = array(
    'page callback' => 'slingshotsms_receive',
    'page arguments' => array(1, 2),
    'access arguments' => array('access content'),
    'file' => 'slingshotsms.inc',
    'type' => MENU_NORMAL_ITEM
  );

  return $items;
}

/**
 * Handle a Slingshotsms notification.
 * @param $importer
 *  FeedsImporter object
 * @param $feed_nid
 *  The node id of the feed node
 */
function slingshotsms_receive($importer, $feed_nid = 0) {
  $feed_nid = 4;
  if ($importer->fetcher instanceof FeedsSlingshotFetcher) {
  // No subscription notification has ben sent, we are being notified.
    //try {
      feeds_source($importer->id, $feed_nid)->import();
    //}
    //catch (Exception $e) {
    //  // In case of an error, respond with a 503 Service (temporary) unavailable.
    //  header('HTTP/1.1 503 "Not Found"', null, 503);
    //  exit();
    //}
  }
}

/**
 * Menu loader for slingshot feeds
 * @param $feed_id
 *  Assumed to be the feed id
 */
function slingshotsms_node_load($nid) {
  return $nid;
}

/**
 * Menu loader for slingshot feeds
 * @param $feed_id
 *  Assumed to be the feed id
 */
function slingshotsms_slingshot_feed_load($feed_id) {
  return feeds_importer($feed_id);
}

/**
 * Implementation of hook_feeds_importer_default().
 */
function slingshotsms_feeds_plugins() {
  module_load_include('inc', 'slingshotsms', 'slingshotsms.plugins');
  $args = func_get_args();
  return call_user_func_array('_slingshotsms_feeds_plugins', $args);
}

/**
  * Implementation of hook_views_default_views_alter().
  */
function slingshotsms_views_default_views_alter(&$views) {
  // Add Slingshot Feeds to sidbar feed block
  $views['mn_feeds']->display['default']->display_options['filters']['type']['value'] = array(
    'feed' => 'feed',
    'slingshot_feed' => 'slingshot_feed',
  );
}
