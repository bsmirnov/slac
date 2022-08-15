<?php

// Created at: 2021-06-15 15:37:11

/**
 * This is the setting file to dynamically create base_url for ACDN
originating requests.
 */
if (file_exists(__DIR__ . DIRECTORY_SEPARATOR . 'acdn.settings.php')) {
  require_once __DIR__ . DIRECTORY_SEPARATOR . 'acdn.settings.php';
}

/**
 * This file is added by Pantheon Migration Tool.
 * Includes Pantheon-specific configs.
 * !!! Do NOT EDIT or REMOVE this file while site is in migration process.!!!
 * AFTER SITE IS LIVE on Pantheon, feel free to merge configs below into main settings.php and remove this file.
 */

/**
 * Helpers
 */
$cli = (php_sapi_name() === 'cli');

// Settings
$profile = "slac_ext_org";
$install_profile = "slac_ext_org";
$conf['install_profile'] = 'slac_ext_org';
$conf['clean_url'] = 1;
$conf['aegir_api'] = 0;
$conf["slac_site_owner"] = 'jpham';
$conf["site_mail"] = 'noreply@slac.stanford.edu';

# Extra configuration from modules:
$conf["slac_role_mapping"] = array (
  'administrator' => 'drupal-11040-administrator',
  'manager' => 'drupal-11040-manager',
  'editor' => 'drupal-11040-editor',
  'site_member' => 'drupal-11040-site_member',
  'author' => 'drupal-11040-author',
);

// Sets redirection from old file paths /sites/*.stanford.edu/files/ to /sites/default/files/ directory.
if (php_sapi_name() != "cli") {
  $regexp = "/\/sites\/([A-Za-z0-9_\.]+)?stanford\.edu\/files\//i";

  if (($redirect = preg_replace($regexp, '/sites/default/files/', $_SERVER['REQUEST_URI'])) && ($redirect != $_SERVER['REQUEST_URI'])) {
    header('HTTP/1.0 301 Moved Permanently');
    header('Location: https://' . $_SERVER['HTTP_HOST'] . $redirect);

    // Name transaction "redirect" in New Relic for improved reporting (optional).
    if (extension_loaded('newrelic')) {
      newrelic_name_transaction("redirect");
    }

    exit();
  }
}

/**
 * Redirect for subpath.
 */
if (preg_match('/.*pantheonsite.io/', $_SERVER['HTTP_HOST']) === 1) {
  $redirect_path = "";
  if( strpos( $_SERVER['REQUEST_URI'], '/communications/' ) === 0){
    $redirect_path = 'https://' . $_SERVER['HTTP_HOST'] . str_replace('/communications/', '/', $_SERVER['REQUEST_URI']);
  }
  if($redirect_path != ""){
    if ( ( php_sapi_name() != "cli" ) ) {
      header( "HTTP/1.0 301 Moved Permanently");
      header( "Location: $redirect_path");
      exit();
    }
  }
}

/**
 * Pantheon-specific settings
 */
if (defined('PANTHEON_ENVIRONMENT')) {
  $variables = array (
  'domains' =>
  array (
    'canonical' => 'communications.int.slac.stanford.edu',
    'synonyms' =>
    array (
      0 => 'live-slac-internal-comms-d7.pantheonsite.io',
    ),
  ),
  'redis' => false,
);


  // If necessary, force redirect in to https
  if (isset($variables)) {
    if (array_key_exists('https', $variables) && $variables['https']) {
      if (!$cli && $_SERVER['HTTPS'] === 'OFF') {
        if (!isset($_SERVER['HTTP_X_SSL']) || (isset($_SERVER['HTTP_X_SSL']) && $_SERVER['HTTP_X_SSL'] != 'ON')) {
          header('HTTP/1.0 301 Moved Permanently');
          header('Location: https://'. $_SERVER['HTTP_HOST'] . $_SERVER['REQUEST_URI']);
          exit();
        }
      }
    }
  }

  // Extract Pantheon environmental configuration.
  extract(json_decode($_SERVER['PRESSFLOW_SETTINGS'], TRUE));

  if (array_key_exists('redis', $variables) && $variables['redis']) {
    // Set possible redis module paths.
    $redis_paths = array(
      implode(DIRECTORY_SEPARATOR, array('sites', 'default', 'modules', 'contrib', 'redis')),
      implode(DIRECTORY_SEPARATOR, array('sites', 'default', 'modules', 'redis')),
      implode(DIRECTORY_SEPARATOR, array('sites', 'all', 'modules', 'contrib', 'redis')),
      implode(DIRECTORY_SEPARATOR, array('sites', 'all', 'modules', 'redis')),
    );

    foreach ($redis_paths as $path) {
      if (is_dir($path)) {
        if (in_array('redis.autoload.inc', scandir($path)) && in_array('redis.lock.inc', scandir($path))) {
          $conf['redis_client_interface'] = 'PhpRedis';
          $conf['cache_backends'][] = $path . DIRECTORY_SEPARATOR . 'redis.autoload.inc';
          $conf['cache_default_class'] = 'Redis_Cache';
          $conf['cache_prefix'] = array('default' => 'pantheon-redis');
          $conf['cache_class_cache_form'] = 'DrupalDatabaseCache';
          $conf['lock_inc'] = $path . DIRECTORY_SEPARATOR . 'redis.lock.inc';

          break;
        }
      }
    }
  }

  if (PANTHEON_ENVIRONMENT != 'live') {
    // Place for settings for the non-live environment

    $conf['reroute_email_enable'] = 1;
  }

  if (PANTHEON_ENVIRONMENT == 'dev') {
    // Place for settings for the dev environment
  }

  if (PANTHEON_ENVIRONMENT == 'test') {
    // Place for settings for the test environment
  }

  if (PANTHEON_ENVIRONMENT == 'live') {
    // Place for settings for the live environment

    $conf['reroute_email_enable'] = 0;

    // Redirect to canonical domain
    if (isset($variables)) {
      if (isset($variables['domains']['canonical'])) {
        if (!$cli) {
          $location = false;

          // Get current protocol
          $protocol = 'http';

          if (array_key_exists('https', $variables) && $variables['https']) {
            if ((!empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off') || $_SERVER['SERVER_PORT'] == 443) {
              $protocol = 'https';
            }
          }

          // Default redirect
          $redirect = "$protocol://{$variables['domains']['canonical']}{$_SERVER['REQUEST_URI']}";

          if ($_SERVER['HTTP_HOST'] == $variables['domains']['canonical']) {
            $redirect = false;
          }

          if (isset($variables['domains']['synonyms']) && is_array($variables['domains']['synonyms'])) {
            if (in_array($_SERVER['HTTP_HOST'], $variables['domains']['synonyms'])) {
              $redirect = false;
            }
          }

          if ($redirect) {
            header("HTTP/1.0 301 Moved Permanently");
            header("Location: $redirect");
            exit();
          }
        }
      }
    }
  }

  foreach (array('dev', 'test', 'live') as $environment) {
    if (isset($variables['environments'][$environment]['conf']) && is_array($variables['environments'][$environment]['conf'])) {
      foreach ($variables['environments'][$environment]['conf'] as $variable => $value) {
        $conf[$variable] = $value;
      }
    }

    if (file_exists(__DIR__ . DIRECTORY_SEPARATOR . "files/private/settings/$environment.settings.php")) {
      require_once __DIR__ . DIRECTORY_SEPARATOR . "files/private/settings/$environment.settings.php";
    }
  }
}
