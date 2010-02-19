<?php
// $Id$

/**
 * @file
 * CTools plugins declarations.
 */

/**
 * Break out for feeds_feed_plugins().
 */
function _mn_slingshot_feeds_plugins() {
  $path = drupal_get_path('module', 'mn_slingshot') .'/includes';

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
  $info['FeedsSlingshotParser'] = array(
    'name' => 'Slingshot parser',
    'description' => 'Parse SMS Data from Slingshot.',
    'handler' => array(
      'parent' => 'FeedsParser',
      'class' => 'FeedsSlingshotParser',
      'file' => 'FeedsSlingshotParser.inc',
      'path' => $path,
    ),
  );
  return $info;
}

