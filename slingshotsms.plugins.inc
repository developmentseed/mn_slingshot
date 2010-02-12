<?php
// $Id$

/**
 * @file
 * CTools plugins declarations.
 */

/**
 * Break out for feeds_feed_plugins().
 */
function _slingshotsms_feeds_plugins() {
  $path = drupal_get_path('module', 'slingshotsms') .'/includes';

  $info = array();

  $info['FeedsSlingshotFetcher'] = array(
    'name' => 'Slingshot Fetcher',
    'description' => 'Receive slingshot items',
    'handler' => array(
      'parent' => 'FeedsHTTPFetcher',
      'class' => 'FeedsSlingshotFetcher',
      'file' => 'FeedsSlingshotFetcher.inc',
      'path' => $path,
    ),
  );

  return $info;
}

