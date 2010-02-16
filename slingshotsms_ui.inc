<?php

define('PACKAGED_PUBLIC_KEY', '6d4c2ff9361f6a0f778794994af952defab4e1df');
define('PACKAGED_PUBLIC_KEY_NAME', 'Slingshot');

/**
 * @file
 * Minimal Slingshot UI
 */

/**
 * Filter keys to select the slingshot key
 */
function is_slingshot_key($key) {
  return $key['title'] == 'Slingshot';
}

/**
 * Main slingshot configuration form
 */
function slingshot_config_form() {
  global $base_root;
  keyauth_include();
  $all_keys = keyauth_all_keys();
  $slingshot_key = current(array_filter($all_keys, 'is_slingshot_key'));

  // Regenerate key on first pageload so that each installation
  // is secure
  if ($slingshot_key['private_key'] == PACKAGED_PRIVATE_KEY) {
    keyauth_save($slingshot_key);
    keyauth_regenerate($slingshot_key['public_key']);
    return slingshot_config_form();
  }

  // TODO derive correct node id
  $endpoint = $base_root . base_path() . 'slingshot/slingshot/4';
  $form = array();
  $form['slingshot_help'] = array(
    '#value' => '<p>SlingshotSMS Configuration: Copy and paste the 
    code below into slingshotsms.txt for your modem
    server</p>'
  );
  $form['slingshot_snippet'] = array(
    '#value' => "<textarea cols='80' rows='5'>
[hmac]
endpoint=$endpoint
public_key=$slingshot_key[public_key]
private_key=$slingshot_key[private_key]</textarea>"
  );
  // Make a system setting form and return
  return system_settings_form($form);
}
