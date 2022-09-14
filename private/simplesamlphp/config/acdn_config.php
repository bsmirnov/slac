<?php

/**
 * @file
 * AGCDN domain masking settings.
 */

if (isset($_SERVER['HTTP_X_HOST']) && isset($_SERVER['HTTP_X_MASKED_PATH'])) {
  $config['baseurlpath'] = 'https://' . $_SERVER['HTTP_X_HOST']  . $_SERVER['HTTP_X_MASKED_PATH'] . '/simplesaml/';
}
