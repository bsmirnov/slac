<?php
/**
 * @file
 * slac_ssp.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function slac_ssp_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer stanford_ssp'.
  $permissions['administer stanford_ssp'] = array(
    'name' => 'administer stanford_ssp',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'stanford_ssp',
  );

  return $permissions;
}
