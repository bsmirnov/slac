<?php
/**
 * @file
 * slac_ssp.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function slac_ssp_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_simplesamlphp_auth_activate';
  $strongarm->value = '1';
  $export['stanford_simplesamlphp_auth_activate'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_simplesamlphp_auth_allowdefaultlogin';
  $strongarm->value = '1';
  $export['stanford_simplesamlphp_auth_allowdefaultlogin'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_simplesamlphp_auth_allowsetdrupalpwd';
  $strongarm->value = 0;
  $export['stanford_simplesamlphp_auth_allowsetdrupalpwd'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_simplesamlphp_auth_authsource';
  $strongarm->value = 'default-sp';
  $export['stanford_simplesamlphp_auth_authsource'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_simplesamlphp_auth_autoenablesaml';
  $strongarm->value = '1';
  $export['stanford_simplesamlphp_auth_autoenablesaml'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_simplesamlphp_auth_installdir';
  $strongarm->value = '//code/private/simplesamlphp';
  $export['stanford_simplesamlphp_auth_installdir'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_simplesamlphp_auth_mailattr';
  $strongarm->value = 'mail';
  $export['stanford_simplesamlphp_auth_mailattr'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_simplesamlphp_auth_registerusers';
  $strongarm->value = '1';
  $export['stanford_simplesamlphp_auth_registerusers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_simplesamlphp_auth_unique_id';
  $strongarm->value = 'eduPersonPrincipalName';
  $export['stanford_simplesamlphp_auth_unique_id'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_simplesamlphp_auth_user_name';
  $strongarm->value = 'eduPersonPrincipalName';
  $export['stanford_simplesamlphp_auth_user_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_simplesamlphp_auth_user_register_original';
  $strongarm->value = 2;
  $export['stanford_simplesamlphp_auth_user_register_original'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_auth_restrictions';
  $strongarm->value = 'any';
  $export['stanford_ssp_auth_restrictions'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_auth_restriction_group';
  $strongarm->value = '';
  $export['stanford_ssp_auth_restriction_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_auth_restriction_sunet';
  $strongarm->value = '';
  $export['stanford_ssp_auth_restriction_sunet'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_auth_role_map';
  $strongarm->value = 'reassign';
  $export['stanford_ssp_auth_role_map'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_automagic_login';
  $strongarm->value = '1';
  $export['stanford_ssp_automagic_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_force_https';
  $strongarm->value = 0;
  $export['stanford_ssp_force_https'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_format_entitlements';
  $strongarm->value = 0;
  $export['stanford_ssp_format_entitlements'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_prevent_cache';
  $strongarm->value = 0;
  $export['stanford_ssp_prevent_cache'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_redirect_on_login';
  $strongarm->value = '';
  $export['stanford_ssp_redirect_on_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_role_map_source';
  $strongarm->value = 'entitlement';
  $export['stanford_ssp_role_map_source'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_show_local_login';
  $strongarm->value = 0;
  $export['stanford_ssp_show_local_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_show_sso_login';
  $strongarm->value = '1';
  $export['stanford_ssp_show_sso_login'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_workgroup_api_cert';
  $strongarm->value = '/etc/pki/tls/certs/stanford_ssp.cert';
  $export['stanford_ssp_workgroup_api_cert'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'stanford_ssp_workgroup_api_key';
  $strongarm->value = '/etc/pki/tls/certs/stanford_ssp.key';
  $export['stanford_ssp_workgroup_api_key'] = $strongarm;

  return $export;
}
