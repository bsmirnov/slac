<?php
/**
 * @file
 * slac_ssp.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function slac_ssp_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
