<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _slingshotsms_node_info() {
  $items = array(
    'slingshot_feed' => array(
      'name' => t('Slingshot Feed'),
      'module' => 'features',
      'description' => t(''),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
    ),
  );
  return $items;
}
