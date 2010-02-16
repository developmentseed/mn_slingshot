<?php

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _slingshotsms_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_feeds_importer_default().
 */
function _slingshotsms_feeds_importer_default() {
  $export = array();
  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'slingshot';
  $feeds_importer->config = array(
    'name' => 'Slingshot',
    'description' => 'Imports items from SMS',
    'fetcher' => array(
      'plugin_key' => 'FeedsSlingshotFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_keyauth' => FALSE,
        'keyauth_public' => '',
        'subscription_period' => 86400,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsSyndicationParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'book',
        'update_existing' => 0,
        'expire' => -1,
        'mappings' => array(),
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 0,
  );

  $export['slingshot'] = $feeds_importer;
  return $export;
}
