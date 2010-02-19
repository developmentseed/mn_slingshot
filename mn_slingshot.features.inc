<?php
// $Id$

/**
 * Implementation of hook_ctools_plugin_api().
 */
function mn_slingshot_ctools_plugin_api() {
  module_load_include('inc', 'mn_slingshot', 'mn_slingshot.defaults');
  $args = func_get_args();
  return call_user_func_array('_mn_slingshot_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_feeds_importer_default().
 */
function mn_slingshot_feeds_importer_default() {
  module_load_include('inc', 'mn_slingshot', 'mn_slingshot.defaults');
  $args = func_get_args();
  return call_user_func_array('_mn_slingshot_feeds_importer_default', $args);
}

/**
 * Implementation of hook_keyauth_key_default().
 */
function mn_slingshot_keyauth_key_default() {
  module_load_include('inc', 'mn_slingshot', 'mn_slingshot.defaults');
  $args = func_get_args();
  return call_user_func_array('_mn_slingshot_keyauth_key_default', $args);
}

/**
 * Implementation of hook_node_info().
 */
function mn_slingshot_node_info() {
  module_load_include('inc', 'mn_slingshot', 'mn_slingshot.features.node');
  $args = func_get_args();
  return call_user_func_array('_mn_slingshot_node_info', $args);
}
