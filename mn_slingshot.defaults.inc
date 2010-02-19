<?php
// $Id$

/**
 * Helper to implementation of hook_ctools_plugin_api().
 */
function _mn_slingshot_ctools_plugin_api() {
  $args = func_get_args();
  $module = array_shift($args);
  $api = array_shift($args);
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => 1);
  }
  else if ($module == "keyauth" && $api == "keyauth_key_default") {
    return array("version" => 1);
  }
  else if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Helper to implementation of hook_feeds_importer_default().
 */
function _mn_slingshot_feeds_importer_default() {
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
      'plugin_key' => 'FeedsSlingshotParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsDataProcessor',
      'config' => array(
        'update_existing' => 0,
        'expire' => -1,
        'mappings' => array(
          '0' => array(
            'source' => 'timestamp',
            'target' => 'timestamp',
            'unique' => 0,
          ),
          '1' => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => 0,
          ),
          '2' => array(
            'source' => 'description',
            'target' => 'description',
            'unique' => FALSE,
          ),
        ),
      ),
    ),
    'content_type' => 'slingshot_feed',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 0,
  );

  $export['slingshot'] = $feeds_importer;
  return $export;
}

/**
 * Helper to implementation of hook_keyauth_key_default().
 */
function _mn_slingshot_keyauth_key_default() {
  $export = array();
  $keyauth_keys = new stdClass;
  $keyauth_keys->disabled = FALSE; /* Edit this to true to make a default keyauth_keys disabled initially */
  $keyauth_keys->api_version = 1;
  $keyauth_keys->title = 'Slingshot';
  $keyauth_keys->public_key = 'acf8b2bb295ccb58c1ad4e3a376a81cb';
  $keyauth_keys->private_key = 'cdb9381bfde2d9a14acf62c42345da5907b7aa14';

  $export['acf8b2bb295ccb58c1ad4e3a376a81cb'] = $keyauth_keys;
  return $export;
}
