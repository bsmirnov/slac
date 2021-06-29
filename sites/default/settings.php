<?php

// Created at: 2021-06-15 15:36:47

/**
 * Added by Pantheon Migration Tool.
 * Includes Pantheon-specific configs.
 * All $conf[] variables should be added AFTER this include.
 * !!! Please do not remove while site is in migration process. !!!
 */
if (file_exists(__DIR__ . DIRECTORY_SEPARATOR . 'pmt.settings.php')) {
  require_once __DIR__ . DIRECTORY_SEPARATOR . 'pmt.settings.php';
}

/**
 * User custom configuration.
 */
$update_free_access = FALSE;

ini_set('session.gc_probability', 1);
ini_set('session.gc_divisor', 100);
ini_set('session.gc_maxlifetime', 200000);
ini_set('session.cookie_lifetime', 2000000);

$conf['404_fast_paths_exclude'] = '/\/(?:styles)|(?:system\/files)\/|(?:sitemap.txt)|(?:robots.txt)/';
$conf['404_fast_paths'] = '/\.(?:txt|png|gif|jpe?g|css|js|ico|swf|flv|cgi|bat|pl|dll|exe|asp)$/i';
$conf['404_fast_html'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN" "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL "@path" was not found on this server.</p></body></html>';

if (function_exists('drupal_fast_404')) {
  drupal_fast_404();
}

// Overrides for local development
// DO NOT REMOVE!
if (file_exists(__DIR__ . DIRECTORY_SEPARATOR . 'local.settings.php')) {
  require_once __DIR__ . DIRECTORY_SEPARATOR . 'local.settings.php';
}
$conf['cache_backends'][] = 'sites/all/modules/contrib/d8cache/d8cache-ac.cache.inc';
$conf['cache_class_cache_views_data'] = 'D8CacheAttachmentsCollector';
$conf['cache_class_cache_block'] = 'D8CacheAttachmentsCollector';
$conf['cache_class_cache_page'] = 'D8Cache';

# Provide universal absolute path to the installation.
$conf['simplesamlphp_auth_installdir'] = $_ENV['HOME'] .'/code/private/simplesamlphp';
