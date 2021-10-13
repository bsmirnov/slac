
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

if (in_array($_ENV['PANTHEON_ENVIRONMENT'], $environments) && (isset($_SERVER['HTTP_ORIG_HOST']))) {
  $base_url = "https://" . $_SERVER['HTTP_ORIG_HOST'];
  if (isset($_SERVER['HTTP_X_MASKED_PATH'])) {
    $base_url = $base_url . $_SERVER['HTTP_X_MASKED_PATH'];
    $_SERVER['HTTP_HOST'] = $_SERVER['HTTP_ORIG_HOST'] . $_SERVER['HTTP_X_MASKED_PATH'];
  }
}
