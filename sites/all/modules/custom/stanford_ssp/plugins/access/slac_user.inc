<?php

/**
 * @file
 * Plugin for controlling access based on the SLAC IdP session.
 */

$plugin = [
  'title' => t('SLAC user active'),
  'description' => t('Visible if a user is logged out of Drupal, but still logged in to Slac.'),
  'callback' => 'stanford_ssp_slac_user_access_check',
  'summary' => 'stanford_ssp_slac_user_access_summary',
];

/**
 * Check for access.
 */
function stanford_ssp_slac_user_access_check($config, $context) {
  stanford_simplesamlphp_auth_autoload();
  $saml = stanford_simplesamlphp_auth_get_saml_info();
  return user_is_anonymous() && isset($saml['source']) && $saml['source']->isAuthenticated();
}

/**
 * Provide a summary description.
 */
function stanford_ssp_slac_user_access_summary($config, $context) {
  return t('User is logged out of Drupal and logged into Slac IdP.');
}