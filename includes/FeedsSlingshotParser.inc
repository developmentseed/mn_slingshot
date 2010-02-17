<?php
// $Id$

/**
 * @file
 * Passthrough parser for SlingshotSMS
 */

/**
 * Parses a given file as a CSV file.
 */
class FeedsSlingshotParser extends FeedsParser {

  /**
  * Parses a raw string and returns a Feed object from it.
  */
  public function parse(FeedsImportBatch $batch, FeedsSource $source) {
    $items = array();
    $raw = $batch->getRaw();
   	$batch->addItem($raw[0]);
  }

  public function getMappingSources() {
    $sources =  array(
      'title' => array(
        'name' => t('Sender'),
        'description' => t('Phone number that sent the SMS'),
      ),
      'timestamp' => array(
        'name' => t('Timestamp'),
        'description' => t('Timestamp'),
      ),
      'description' => array(
        'name' => t('Message'),
        'description' => t('Full text of the SMS Message'),
      ),
    );
	  return $sources;
  }
}
