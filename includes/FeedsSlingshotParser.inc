<?php

/**
 * Parses a given file as a CSV file.
 */
class FeedsSlingshotParser extends ExtractorSyndicationParser {

  /**
  * Parses a raw string and returns a Feed object from it.
  */
  public function parse(FeedsFetcherResult $fetcherResult, FeedsSource $source) {
    $items = array();

    // Parse post request
    // Test with
    // curl -d "sender=202-330-3006&timestamp=`date +%s`&text=Lorem%20Ipsum%20Chicago" http://example.com/slingshot/post/[node id]
    $items[] = array(
      'title' => $fetcherResult->value['sender'],
      'timestamp' => time(),
      'description' => $fetcherResult->value['text'],
    );

    // Return result.
    return new FeedsParserResult(array('items' => $items));
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
    return parent::getMappingSources() + $sources;
  }
}