<?php

/**
 * @file
 * AGCDN domain masking settings.
 */

 if (isset($_SERVER['HTTP_X_HOST']) && isset($_SERVER['HTTP_X_MASKED_PATH'])) {
   $config['baseurlpath'] = 'https://' . $_SERVER['HTTP_X_HOST']  .':443'. $_SERVER['HTTP_X_MASKED_PATH'] . '/simplesaml/';
   $config['session.cookie.secure'] =  $_SERVER['HTTP_X_MASKED_PATH'],
 }
