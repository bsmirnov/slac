<?php

/**
 * @file
 * Config forms.
 */

/**
 * The main landing page for the configuration form.
 *
 * @param array $form
 *   Form array.
 * @param array &$form_state
 *   Form state array.
 *
 * @return array
 *   The form array.
 */
function stanford_ssp_configuration_form(array $form, array &$form_state) {

  // Vertical Tab container.
  $form['togglers'] = array(
    '#type' => 'vertical_tabs',
    '#default_tab' => 'edit-general-config',
  );

  // Tab Groups.
  // ----------------------------------------------------------------.

  // Tab for the general options.
  $form['general-config'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Configuration'),
    '#collapsible' => TRUE,
    '#description' => "<h4>" . t('Here you can configure the general settings for the use of this module. Please read the descriptions of each option carefully as it is possible to lock yourself out of this website if improperly configured.') . "</h4>",
    '#group' => 'togglers',
  );

  // Tab for the user options.
  $form['user-config'] = array(
    '#type' => 'fieldset',
    '#title' => t('User Account Configuration'),
    '#collapsible' => TRUE,
    '#description' => t('Here you can configure the general settings for how global interactions happen with users.'),
    '#group' => 'togglers',
  );

  // Tab for the user options.
  $form['saml-config'] = array(
    '#type' => 'fieldset',
    '#title' => t('SAML Configuration'),
    '#collapsible' => TRUE,
    '#description' => t('SimpleSAMLPHP configuration options are set here.'),
    '#group' => 'togglers',
  );

  // General Config
  // ---------------------------------------------------------------.

  // Enables / Disables user authentication by simplesamlphp.
  $form['general-config']['stanford_simplesamlphp_auth_activate'] = array(
    '#type' => 'switch',
    '#title' => t('Enable authentication by SSO'),
    '#description' => t("Turn on to allow users to sign in to this website using single sign on. <br />Warning: Enabling before configuring this module could lock you out of your website."),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_activate', FALSE),
  );

  // Enables / Disables user authentication by Drupal.
  $form['general-config']['stanford_simplesamlphp_auth_allowdefaultlogin'] = array(
    '#type' => 'switch',
    '#title' => t('Allow authentication with local Drupal accounts'),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_allowdefaultlogin', TRUE),
    '#description' => t('Turn on if you want to let people log in with local Drupal accounts (Not SSO).'),
  );

  // Enables automatic login when hitting a 403.
  $form['general-config']['stanford_ssp_automagic_login'] = array(
    '#type' => 'switch',
    '#title' => t('Enable automatic login'),
    '#description' => t("Try to automatically authenticate the user if they are presented with a (403) access denied page."),
    '#default_value' => variable_get('stanford_ssp_automagic_login', TRUE),
  );

  // Force users to log in over HTTPS.
  $form['general-config']['stanford_ssp_force_https'] = array(
    '#type' => 'switch',
    '#title' => t('Force users to log in with HTTPS.'),
    '#default_value' => variable_get('stanford_ssp_force_https', FALSE),
    '#description' => t("Enforce that authentication and authenticated transactions happen over HTTPS. This should be enabled on production websites."),
  );

  // Reformat entitlements, replacing : with _.
  $form['general-config']['stanford_ssp_format_entitlements'] = array(
    '#type' => 'switch',
    '#title' => t('Reformat entitlements.'),
    '#default_value' => variable_get('stanford_ssp_format_entitlements', FALSE),
    '#description' => t("If your SP configuration reformats entitlements (e.g. stanford:stanford to stanford_stanford), enable this option."),
  );

  $form['general-config']['stanford_ssp_is_internal'] = array(
    '#type' => 'switch',
    '#title' => t('Internal site'),
    '#default_value' => variable_get('stanford_ssp_is_internal', FALSE),
    '#description' => t("Internal sites require users to login first. Enabling this will redirect all anonymous users to the SSO login."),
  );

  $form['general-config']['stanford_ssp_redirect_on_login'] = array(
    '#type' => 'textfield',
    '#title' => t('Redirect all users on successful login to this url.'),
    '#default_value' => variable_get('stanford_ssp_redirect_on_login', FALSE),
    '#description' => t("Force the redirect of all users to a specific url no matter where they logged in from. This should be entered as a relative url. eg: admin/config/stanford"),
  );

  // User Config
  // ------------------------------------------------------------------.

  // Auto create an account for users on auth.
  $form['user-config']['stanford_simplesamlphp_auth_registerusers'] = array(
    '#type' => 'switch',
    '#title' => t('Register users (i.e., auto-provisioning)'),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_registerusers', TRUE),
    '#description' => t("Automatically create an account for a new user on successful log in. Without this enabled only those with user accounts already created in this website can log in."),
  );

  // Connect existing user accounts.
  $form['user-config']['stanford_simplesamlphp_auth_autoenablesaml'] = array(
    '#type' => 'switch',
    '#title' => t('Automatically enable SSO authentication for existing users upon successful login. This will update existing accounts to be able to authenticate with SSO.'),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_autoenablesaml', FALSE),
  );

  // Prevent the default cache for auth users.
  $form['user-config']['stanford_ssp_prevent_cache'] = array(
    '#type' => 'switch',
    '#title' => t('Prevent the browser from caching pages for authenticated users.'),
    '#default_value' => variable_get('stanford_ssp_prevent_cache', FALSE),
    '#description' => t("Pages for logged in users can be dynamic and if the browser caches them, there could be stale information displayed."),
  );

  // Allow for both local passwords and SAML based auth.
  $form['user-config']['stanford_simplesamlphp_auth_allowsetdrupalpwd'] = array(
    '#type' => 'switch',
    '#title' => t('Allow SSO users to set Drupal passwords.'),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_allowsetdrupalpwd', FALSE),
    '#description' => t('Set this to ON if you want to let users set passwords for their local Drupal accounts. This will allow users to log in using either SSO or a local Drupal account password. Disabling this removes the password change fields from the user profile form.'),
    '#states' => array(
      'enabled' => array(
        ':input[name="stanford_simplesamlphp_auth_allowdefaultlogin"]' => array('checked' => TRUE),
      ),
    ),
  );

  // SAML Config
  // ------------------------------------------------------------------.

  $form['saml-config']['stanford_simplesamlphp_auth_installdir'] = array(
    '#type' => 'textfield',
    '#title' => t('Installation directory'),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_installdir', '/opt/simplesamlphp'),
    '#description' => t('The base directory of simpleSAMLphp. Absolute path with no trailing slash. default: /opt/simplesamlphp'),
  );

  $form['saml-config']['stanford_simplesamlphp_auth_authsource'] = array(
    '#type' => 'textfield',
    '#title' => t('Authenticaton source for this service provider'),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_authsource', 'default-sp'),
    '#description' => t('The name of the source to use from //config/authsources.php. default: default-sp'),
  );

  $form['saml-config']['stanford_simplesamlphp_auth_user_name'] = array(
    '#type' => 'textfield',
    '#title' => t("Which attribute should be used as user's name"),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_user_name', 'displayName'),
    '#description' => t('Example: <i>eduPersonPrincipalName</i> or <i>displayName</i><br />If the attribute is multivalued, the first value will be used.'),
    '#required' => TRUE,
  );

  $form['saml-config']['stanford_simplesamlphp_auth_unique_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Which attribute should be used as unique identifier for the user'),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_unique_id', 'eduPersonPrincipalName'),
    '#description' => t('Example: <i>eduPersonPrincipalName</i> or <i>eduPersonTargetedID</i><br />If the attribute is multivalued, the first value will be used.'),
    '#required' => TRUE,
  );

  $form['saml-config']['stanford_simplesamlphp_auth_mailattr'] = array(
    '#type' => 'textfield',
    '#title' => t('Which attribute from simpleSAMLphp should be used as user mail address'),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_mailattr', 'mail'),
    '#description' => t('Example: <i>mail</i><br />If the user attribute is multivalued, the first value will be used.'),
  );

  return system_settings_form($form);
}

/**
 * Authorization and authentication settings form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   The form array.
 */
function stanford_ssp_authorizations_form(array $form, array &$form_state) {

  // Vertical Tab container.
  $form['togglers'] = array(
    '#type' => 'vertical_tabs',
    '#default_tab' => 'edit-general-config',
  );

  // Tab Groups
  // ----------------------------------------------------------------.

  // Tab for the general options.
  $form['saml-config'] = array(
    '#type' => 'fieldset',
    '#title' => t('SSO Accounts'),
    '#collapsible' => TRUE,
    '#group' => 'togglers',
  );

  // Tab for the user options.
  $form['local-config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Local Drupal Accounts'),
    '#collapsible' => TRUE,
    '#group' => 'togglers',
  );

  // SSO AUTH CONFIG
  // -------------------------------------------------------------------.

  $options = array(
    'any' => t("Allow any valid SSO (SUNet) user."),
    'restrict' => t("Restrict access to specific users and groups."),
  );

  $form['saml-config']['stanford_ssp_auth_restrictions'] = array(
    '#type' => 'radios',
    '#title' => t('SSO Authorization Restrictions.'),
    '#default_value' => variable_get('stanford_ssp_auth_restrictions', 'any'),
    '#options' => $options,
  );

  $form['saml-config']['stanford_ssp_auth_restriction_sunet'] = array(
    '#type' => 'textfield',
    '#title' => t('Allowed SUNet IDs'),
    '#default_value' => variable_get('stanford_ssp_auth_restriction_sunet', ''),
    '#description' => t('A comma-separated list of SUNet IDs that should be allowed to login with simpleSAMLphp. If left blank, any valid SUNet ID user can login.'),
    '#states' => array(
      'visible' => array(
        ':input[name="stanford_ssp_auth_restrictions"]' => array('value' => 'restrict'),
      ),
    ),
  );

  $form['saml-config']['stanford_ssp_auth_restriction_group'] = array(
    '#type' => 'textfield',
    '#title' => t('Allowed Workgroups'),
    '#default_value' => variable_get('stanford_ssp_auth_restriction_group', ''),
    '#description' => t('A comma-separated list of Workgroups that should be allowed to login with simpleSAMLphp. If left blank, any workgroup can login.'),
    '#states' => array(
      'visible' => array(
        ':input[name="stanford_ssp_auth_restrictions"]' => array('value' => 'restrict'),
      ),
    ),
  );

  // LOCAL AUTH CONFIG
  // -------------------------------------------------------------------.

  $roles = user_roles(TRUE);
  $form['local-config']['stanford_simplesamlphp_auth_allowdefaultloginroles'] = array(
    '#type' => 'select',
    '#size' => 7,
    '#options' => $roles,
    '#multiple' => TRUE,
    '#title' => t('Which roles should be allowed to login with local accounts?'),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_allowdefaultloginroles', array()),
    '#description' => t('Roles that should be allowed to login without SSO. Examples are dev/admin roles.'),
  );

  $form['local-config']['stanford_simplesamlphp_auth_allowdefaultloginusers'] = array(
    '#type' => 'textfield',
    '#title' => t('Which users should be allowed to login with local accounts?'),
    '#default_value' => variable_get('stanford_simplesamlphp_auth_allowdefaultloginusers', ''),
    '#description' => t('Example: <i>1,2,3</i><br />A comma-separated list of user IDs that should be allowed to login without SSO. If left blank, all local accounts can login.'),
  );

  return system_settings_form($form);
}

/**
 * Role mapping form for mapping a role to an authenticated user.
 *
 * @param array $form
 *   The form array.
 * @param array &$form_state
 *   The form state array.
 *
 * @return array
 *   The form array.
 */
function stanford_ssp_role_mappings_form(array $form, array &$form_state) {

  $options = array(
    'none' => t("Do not adjust roles. Allow local administration of roles only."),
    'grant' => t("Grant new roles only. Will only add roles based on role assignments."),
    'reassign' => t("Re-evaluate roles on every log in. This will grant and remove roles."),
  );

  $form['stanford_ssp_auth_role_map'] = array(
    '#type' => 'radios',
    '#title' => 'Action to perform on successful authentication with SUNet ID',
    '#options' => $options,
    '#default_value' => variable_get("stanford_ssp_auth_role_map", 'none'),
  );

  $form['stanford_ssp_role_map_source'] = array(
    '#type' => 'radios',
    '#title' => 'Source to validate role mapping groups against.',
    '#options' => array(
      'workgroup' => t('Workgroup API'),
      'entitlement' => t('SAML attribute'),
    ),
    '#default_value' => variable_get("stanford_ssp_role_map_source", 'entitlement'),
  );

  // In order to make this request openssl has to be available to php.
  if (function_exists('openssl_get_cert_locations')) {
    // Add the SSL certificate paths.
    $openssl_defaults = openssl_get_cert_locations();
    $default_path = $openssl_defaults['default_cert_dir'];;
    $cert_filename = variable_get('stanford_ssp_workgroup_api_cert', $default_path . "/stanford_ssp.cert");
    $key_filename = variable_get('stanford_ssp_workgroup_api_key', $default_path . "/stanford_ssp.key");

    $form['stanford_ssp_workgroup_api_cert'] = array(
      '#type' => 'textfield',
      '#title' => 'Path to Workgroup API SSL Certificate.',
      '#default_value' => !empty($cert_filename) ? $cert_filename : $default_path . "/stanford_ssp.cert",
      '#description' => t('For more information on how to get a certificate please see: https://uit.stanford.edu/service/registry/certificates'),
      '#states' => array(
        'visible' => array(
          ':input[name="stanford_ssp_role_map_source"]' => array('value' => 'workgroup'),
        ),
      ),
    );

    $form['stanford_ssp_workgroup_api_key'] = array(
      '#type' => 'textfield',
      '#title' => 'Path to Workgroup API SSL Key.',
      '#default_value' => !empty($key_filename) ? $key_filename : $default_path . "/stanford_ssp.key",
      '#description' => t('For more information on how to get a key please see: https://uit.stanford.edu/service/registry/certificates'),
      '#states' => array(
        'visible' => array(
          ':input[name="stanford_ssp_role_map_source"]' => array('value' => 'workgroup'),
        ),
      ),
    );

  }
  // If OpenSSL is not available then we should inform the end user.
  else {
    $form['no_open_ssl'] = array(
      '#type' => 'container',
      '#states' => array(
        'visible' => array(
          ':input[name="stanford_ssp_role_map_source"]' => array('value' => 'workgroup'),
        ),
      ),
    );
    $form['no_open_ssl']['no_open_ssl_message'] = array(
      '#markup' => '<div class="messages message error"><h2>OpenSSL is not available. Please compile PHP with OpenSSL to use workgroup api validation.</h2></div>',
    );
  }

  // ROLE MAPPING FORM.
  $table = array();

  // Remove authenticated user has this will be defaulted to true.
  $roles = user_roles(TRUE);
  unset($roles[2]);

  $form['role_id'] = array(
    '#name' => 'role_id',
    '#type' => 'select',
    '#options' => $roles,
  );

  $form['entitlement'] = array(
    '#name' => 'entitlement',
    '#type' => 'textfield',
  );

  $form['new_submit'] = array(
    '#name' => 'new_submit',
    '#type' => 'submit',
    '#value' => t('Add Mapping'),
  );

  $table[] = array(
    drupal_render($form['role_id']),
    drupal_render($form['entitlement']),
    drupal_render($form['new_submit']),
  );

  $header = array(
    t('Drupal Role'),
    t('Workgroup (e.g. helpdesk:consultants)'),
    t('Action'),
  );

  $rolemaps = variable_get("stanford_simplesamlphp_auth_rolepopulation", "");
  if (!empty($rolemaps)) {
    $xp = explode("|", $rolemaps);
    foreach ($xp as $index => $rule) {
      $button_id = 'remove_warid_' . $index;
      $form[$button_id] = array(
        '#name' => $button_id,
        '#type' => 'submit',
        '#value' => t('Remove Mapping'),
        '#submit' => array('stanford_ssp_remove_waird'),
      );

      // Special hidden element.
      $form[$button_id . "_value"] = array(
        '#type' => 'value',
        '#value' => $index,
      );

      // Something went wrong.
      if (empty($rule)) {
        drupal_set_message(t('Empty rule string. Please remove it below.'), 'error');
        watchdog('stanford_ssp', 'Empty rule string. Please navigate to !link and delete it.', array('!link' => l(t('role mappings'), 'admin/config/stanford/stanford_ssp/role-mappings')), WATCHDOG_ERROR);
        $row = [
          "<span style=\"color:red\">Broken or missing rule.</span>",
          "<span style=\"color:red\">Broken Rule. Remove me.</span>",
          drupal_render($form[$button_id]),
        ];
        $table[] = $row;
        continue;
      }

      // $rule = rid:expression.
      $bits = explode(':', $rule, 2);
      $role = user_role_load($bits[0]);
      $eval = str_getcsv($bits[1]);

      $row = array($role->name, $eval[2], drupal_render($form[$button_id]));
      $table[] = $row;
    }
  }

  $form['add_roles'] = array(
    '#markup' => theme('table', array(
      'header' => $header,
      'rows' => $table,
      'attributes' => array(
        "class" => array(
          'add-roles-table',
        ),
      ),
    )),
    // Unfortunately states don't work here so we added a bit of JS to account
    // for the loss.
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'stanford_ssp') . '/js/stanford_ssp.js',
      ),
    ),
  );

  // END ROLE MAPPING FORM.
  $form["#submit"][] = "stanford_ssp_role_mappings_form_submit";
  $form["#validate"][] = "stanford_ssp_role_mappings_form_validate";
  return system_settings_form($form);
}

/**
 * The login block and forms form form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   The form array.
 */
function stanford_ssp_login_block_forms_form(array $form, array &$form_state) {

  $form['stanford_ssp_show_local_login'] = array(
    '#type' => 'switch',
    '#title' => t('Show the local login form on the user page'),
    '#default_value' => variable_get('stanford_ssp_show_local_login', TRUE),
    '#description' => t("Turn on to show the local Drupal account login option on the !link.", array("!link" => l(t("user page"), "user"))),
  );

  $form['stanford_ssp_show_sso_login'] = array(
    '#type' => 'switch',
    '#title' => t('Show the SSO login link on user page'),
    '#default_value' => variable_get('stanford_ssp_show_sso_login', TRUE),
    '#description' => t("Turn on to show the SSO login link on the !link.", array("!link" => l(t("user page"), "user"))),
  );

  $form['stanford_ssp_sso_link_text'] = array(
    '#type' => 'textfield',
    '#title' => t('SSO login link text'),
    '#default_value' => variable_get('stanford_ssp_sso_link_text', t("Log in with your SUNet ID ??")),
    '#description' => t("Override the link text for the SSO login link on the !link.", array("!link" => l(t("user page"), "user"))),
  );

  return system_settings_form($form);
}

/**
 * Add a new SSO user account.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 *
 * @return array
 *   The form array.
 */
function stanford_ssp_add_sso_user(array $form, array &$form_state) {

  $form['sunetid'] = array(
    '#type' => 'textfield',
    '#title' => t('SUNetID'),
    '#description' => t('Enter the SUNetID of the user you wish to add.'),
    '#required' => TRUE,
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t("If you wish to specify the user's preferred name (instead of sunetid@stanford.edu), enter it here."),
  );

  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Address'),
    '#description' => t('If you wish to specify an alternate email address (instead of sunetid@stanford.edu), enter it here.'),
  );

  // Remove authenticated user has this will be defaulted to true.
  $roles = user_roles(TRUE);
  unset($roles[2]);

  // Only show the option if there is an option.
  if (!empty($roles)) {
    $form["roles"] = array(
      '#title' => "Roles",
      '#description' => t("Add roles to the new user account."),
      '#type' => 'select',
      '#options' => $roles,
      '#default_value' => array(1),
      '#multiple' => TRUE,
      '#size' => 7,
    );
  }

  if (variable_get("stanford_simplesamlphp_auth_allowsetdrupalpwd", FALSE)) {
    $form['pass'] = array(
      '#type' => 'password_confirm',
      '#size' => 25,
    );
  }

  $form['notify'] = array(
    '#type' => 'checkbox',
    '#title' => t('Notify user of new account'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add SSO User'),
  );

  return $form;
}

/**
 * ***************************************************************
 * VALIDATE FUNCTIONS
 * ***************************************************************
 */

/**
 * Validation function for stanford_ssp_configuration_form().
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function stanford_ssp_configuration_form_validate(array $form, array &$form_state) {
  $values = $form_state['values'];

  // Prevent both ssp and local login options from being disabled.
  if ($values["stanford_simplesamlphp_auth_activate"] === 0 && $values["stanford_simplesamlphp_auth_allowdefaultlogin"] === 0) {
    form_set_error('stanford_simplesamlphp_auth_allowdefaultlogin');
    form_set_error('stanford_simplesamlphp_auth_activate', t("Both SSO and Local log in cannot be disabled or you will lock yourself out of your site. Please enable one."));
  }

}

/**
 * Validation function for Add WebAuth User form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function stanford_ssp_add_sso_user_validate(array $form, array &$form_state) {

  $sunet = strtolower(trim(check_plain($form_state['values']['sunetid'])));

  // Make sure there isn't an entry in the authmap table.
  $authname = $sunet;

  // user_get_authmaps returns 0 if there are no authmaps,
  // or a keyed array if there are authmap entries.
  $authmaps = user_get_authmaps($authname);

  if ((($authmaps) !== 0) && isset($authmaps['authname_stanford_simplesamlphp_auth']) && ($authmaps['authname_stanford_simplesamlphp_auth'] == $authname)) {
    form_set_error('sunetid', t('Could not create user. Authname %s already exists. Has the user already been created with a different username but the same SUNetID?', ["%s" => $authname]));
  }

  // If no name is specified, use the default name (sunetid + @stanford.edu).
  $name = trim(check_plain($form_state['values']['name']));
  if (empty($name)) {
    $name = $authname;
  }

  // Check that there is no user with the same name.
  if (user_load_by_name($name)) {
    form_set_error('name', t('Could not create user. Username %s already exists.', ['%s' => $name]));
  }

  // If no email was specified, we'll use the default (sunetid + @stanford.edu).
  $default_email = $sunet . '@stanford.edu';
  $email = strtolower(trim($form_state['values']['email']));

  if (!empty($email) && !valid_email_address($email)) {
    form_set_error('email', t('The e-mail address %email is not valid.', ['%email' => $email]));
  }

  if (empty($email)) {
    $email = $default_email;
  }

  // Check that there is no user with the same email
  // Drupal will let us create the user with a duplicate email, but
  // the user will run into issues when making changes to their profile.
  if (user_load_by_mail($email)) {
    form_set_error('email', t('Could not create user. Email %email already in use.', ['%email' => $email]));
  }

  // Check that the sunet doesn't already exist.
  $suuser = stanford_ssp_user_load_by_sunetid($sunet);
  if ($suuser) {
    form_set_error("sunetid", t("A user with that sunetid already exists."));
  }

}

/**
 * Validation hook for stanford_ssp_authorizations_form.
 */
function stanford_ssp_authorizations_form_validate(&$form, &$form_state) {
  $values = $form_state["values"];
  $workgroups = stanford_ssp_format_entitlement($values['stanford_ssp_auth_restriction_group']);
  form_set_value($form['saml-config']['stanford_ssp_auth_restriction_group'], $workgroups, $form_state);
}

/**
 * ***************************************************************
 * SUBMIT FUNCTIONS
 * ***************************************************************
 */

/**
 * Submit handler for stanford_ssp_add_sso_user form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function stanford_ssp_add_sso_user_submit(array &$form, array &$form_state) {

  // Sunet.
  $sunet = strtolower(trim(check_plain($form_state['values']['sunetid'])));
  $authname = $sunet;

  // If no name is specified, use the default name (sunetid + @stanford.edu).
  $name = trim(check_plain($form_state['values']['name']));
  if (empty($name)) {
    $name = $authname;
  }

  // Email and default.
  $default_email = $sunet . '@stanford.edu';
  $email = strtolower(trim($form_state['values']['email']));
  if (empty($email)) {
    $email = $default_email;
  }

  $account = new stdClass();
  $account->is_new = TRUE;
  $account->name = $name;
  $account->pass = user_password();
  $account->mail = $email;
  $account->init = $sunet . '@stanford.edu';
  $account->status = TRUE;
  $roles = array(
    DRUPAL_AUTHENTICATED_RID => TRUE,
  );

  // Add in roles from config form.
  $config_roles = array_keys($form_state["values"]["roles"]);
  foreach ($config_roles as $rid) {
    $roles[$rid] = TRUE;
  }

  $account->roles = $roles;
  $account->timezone = variable_get('date_default_timezone', date_default_timezone_get());
  $account = user_save($account);

  // Account was not created.
  if (!isset($account->uid)) {
    drupal_set_message(t("User account creation went wrong. Please try again."), "error");
    return;
  }

  // Add an authmap to the authmap table.
  user_set_authmaps($account, array('authname_stanford_simplesamlphp_auth' => $authname));
  watchdog('Stanford SSP', 'Created user: %user', array('%user' => $name));
  $message = t('Successfully created SSO account for %user', array('%user' => $name));
  drupal_set_message($message);

  // Was the notify checkbox checked?
  if ($form_state["values"]["notify"] && $account) {
    global $language;
    drupal_mail('stanford_ssp', 'new_account', $account->mail, $language, ['account' => $account, 'user' => $account]);
    drupal_set_message(t("Email sent to user"), "status");
  }

  // Save the sunetid to the db.
  $record = array(
    'sunet' => $sunet,
    'uid' => $account->uid,
  );

  drupal_write_record("stanford_ssp_sunetid", $record);
}

/**
 * Implements hook_mail().
 */
function stanford_ssp_mail($key, &$message, $params) {

  if ($key !== "new_account") {
    return;
  }

  $language = $message['language'];
  $langcode = isset($language->language) ? $language->language : NULL;
  $subject = t('An administrator created an account for you on the [site:name] website', array(), array('langcode' => $langcode));
  $body = t("[user:name],

An account has been created for you on the [site:name] website. You may now log in with your SUNetID by clicking this link or copying and pasting it to your browser:

[site:url]sso/login?goto=user

Sincerely,

[site:name] web team", array(), array('langcode' => $langcode));

  $subject = token_replace($subject, $params,
    array(
      'language' => $language,
      'callback' => 'user_mail_tokens',
      'sanitize' => FALSE,
      'clear' => TRUE,
    )
  );
  $body = token_replace($body, $params,
    array(
      'language' => $language,
      'callback' => 'user_mail_tokens',
      'sanitize' => FALSE,
      'clear' => TRUE,
    )
  );

  $message['subject'] = $subject;
  $message['body'][] = $body;

}

/**
 * Implements hook_form_submit().
 */
function stanford_ssp_role_mappings_form_submit(array $form, array &$form_state) {

  $entitlement = $form_state['values']['entitlement'];
  $role = $form_state['values']['role_id'];

  $entitlement = stanford_ssp_format_entitlement($entitlement);

  // The silly save button could trigger this if there is not a value.
  if (!empty($entitlement) && !empty($role)) {
    stanford_ssp_map_entitlement_to_role($entitlement, $role);
  }

}

/**
 * Validate the workgroup against the api if that mapping is available.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function stanford_ssp_role_mappings_form_validate(array $form, array $form_state) {

  // Only validate if the api setting is set.
  $values = $form_state['values'];
  if ($values['stanford_ssp_role_map_source'] !== "workgroup") {
    return;
  }

  // If we were sent a new entitlement validate it.
  if (empty($values['entitlement'])) {
    return;
  }

  $group = $values['entitlement'];
  try {
    stanford_ssp_fetch_from_workgroup_api($group);
  }
  catch (Exception $e) {
    form_set_error('entitlement', t('Invalid workgroup.'));
  }
}

/**
 * Maps an entitlement to a role.
 *
 * @param string $entitlement
 *   A value in eduPersonEntitlement, e.g., helpdesk:consultants.
 * @param mixed $role
 *   Either the role id or a name.
 */
function stanford_ssp_map_entitlement_to_role($entitlement, $role) {
  $entitlement = check_plain($entitlement);

  // Look up rid.
  $role_object = FALSE;
  if (is_numeric($role)) {
    $role_object = user_role_load($role);
  }
  elseif (is_scalar($role)) {
    $role_object = user_role_load_by_name($role);
  }

  if (!$role_object) {
    drupal_set_message(t('No role exists with the name "@role"', array('@role' => $role)), 'error');
  }
  else {
    $rid = $role_object->rid;
    // Look up current role mapping, if any.
    $role_mapping = variable_get('stanford_simplesamlphp_auth_rolepopulation');
    if (!empty($role_mapping)) {
      $role_mapping .= "|";
    }
    // Add our mapping.
    $role_mapping .= $rid . ":eduPersonEntitlement,=," . $entitlement;

    // Save our mapping.
    variable_set('stanford_simplesamlphp_auth_rolepopulation', $role_mapping);
    $message = t('Mapped the "@entitlement" entitlement to the "@role" role.', array('@entitlement' => $entitlement, '@role' => $role_object->name));
    drupal_set_message($message);
    watchdog('stanford_ssp', $message);
  }
}

/**
 * Remove waird formatting.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form state array.
 */
function stanford_ssp_remove_waird(array $form, array &$form_state) {
  $trigger = $form_state["triggering_element"]['#name'];
  $index = $form_state['values'][$trigger . "_value"];
  $rolemaps = variable_get("stanford_simplesamlphp_auth_rolepopulation", array());
  $xp = explode("|", $rolemaps);
  if (isset($xp[$index])) {
    unset($xp[$index]);
  }
  $imp = implode("|", $xp);
  variable_set("stanford_simplesamlphp_auth_rolepopulation", $imp);
  drupal_set_message(t("Role mapping was removed"));
}
