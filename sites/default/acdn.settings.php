<?php

/**
 * @file
 * AGCDN domain masking settings.
 */

/**
 * @var Array $varyHeaders
 * Headers that will be accessed for domain masking.
 */
$varyHeaders = [
  'x-host',
  'x-masked-path',
];

/**
 * @var Array $environments
 * Enviroments to monitor for AGCDN connections.
 */
$environments = array(
  'dev',
  'test',
  'live',
);

$varyString = implode(', ', $varyHeaders);
header("Vary: ${varyString}", FALSE);

if (isset($_ENV['PANTHEON_ENVIRONMENT']) && php_sapi_name() != 'cli') {
  // HTTP_ORIG_HOST is still present but is deprecated in favor of HTTP_X_HOST
  if (isset($_SERVER['HTTP_X_HOST'])) {
    $_SERVER['HTTP_HOST'] = $_SERVER['HTTP_X_HOST'];

  }

  // Now also handle subpath stuff.
  if (isset($_SERVER['HTTP_X_MASKED_PATH'])) {
    $base_url = "https://" . $_SERVER['HTTP_HOST'] . $_SERVER['HTTP_X_MASKED_PATH'];
    $base_path = $_SERVER['HTTP_X_MASKED_PATH'];

    # set cookie path to the value of HTTP_X_MASKED_PATH to avoid collision if parent name uses the same cookie name
    $cookieParams = session_get_cookie_params(); 
    session_set_cookie_params($cookieParams['lifetime'], $_SERVER['HTTP_X_MASK_PAST'], $cookieParams['domain'], $cookieParams['secure'], $cookieParams['httponly'], $cookieParams['samesite']);
  }
}
