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
  'orig-host',
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
  if (isset($_SERVER['HTTP_ORIG_HOST'])) {
    $_SERVER['HTTP_HOST'] = $_SERVER['HTTP_ORIG_HOST'];
  }

  // Now also handle subpath stuff.
  if (isset($_SERVER['HTTP_X_MASKED_PATH'])) {
    $base_url = "https://" . $_SERVER['HTTP_HOST'] . $_SERVER['HTTP_X_MASKED_PATH'];
    $base_path = $_SERVER['HTTP_X_MASKED_PATH'];
    $_SERVER['HTTP_HOST'] = $_SERVER['HTTP_ORIG_HOST'] . $_SERVER['HTTP_X_MASKED_PATH'];
    $cookie_domain = $_SERVER['HTTP_ORIG_HOST'];
  }
}