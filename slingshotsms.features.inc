<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function slingshotsms_ctools_plugin_api() {
  module_load_include('inc', 'slingshotsms', 'slingshotsms.defaults');
  $args = func_get_args();
  return call_user_func_array('_slingshotsms_ctools_plugin_api', $args);
}

/**
 * Implementation of hook_feeds_importer_default().
 */
function slingshotsms_feeds_importer_default() {
  module_load_include('inc', 'slingshotsms', 'slingshotsms.defaults');
  $args = func_get_args();
  return call_user_func_array('_slingshotsms_feeds_importer_default', $args);
}
