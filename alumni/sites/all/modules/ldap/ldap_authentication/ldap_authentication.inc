<?php

/**
 * @file
 * ldap_authentication helper functions
 */

/**
  * helper function for ldap_authn_form_user_login_block_alter and ldap_authn_form_user_login_alter
  *
  * @todo if form is being generated on non https and is set in preferences, set warning and end form development
  */
function _ldap_authentication_login_form_alter(&$form, &$form_state, $form_id) {

  if (!$auth_conf = ldap_authentication_get_valid_conf()) {
    return;
  }
  elseif (!$auth_conf->hasEnabledAuthenticationServers()) {
    return;
  }

  /**
   *
   * add validate function to test for ldap authentication
   * should be placed after user_login_authenticate_validate
   * 1. user_login_name_validate
   * 2. user_login_authenticate_validate
   * 3. external authentication validate functions
   * 4. user_login_final_validate
   *
   * as articulated above user_login_default_validators() in user.module
   *
   * without any other external authentication modules, this array will start out as:
   *    array('user_login_name_validate', 'user_login_authenticate_validate', 'user_login_final_validate')
   */

  if (@in_array('user_login_authenticate_validate', $form['#validate'])) {
    $new_validation_sequence = array();
    foreach ($form['#validate'] as $validate_function_name) {
      if ($validate_function_name == 'user_login_authenticate_validate') {
        if ($auth_conf->authenticationMode == LDAP_AUTHENTICATION_MIXED) {
         // if mixed mode, allow drupal authentication first
          $new_validation_sequence[] = 'user_login_authenticate_validate';
          $new_validation_sequence[] = 'ldap_authentication_user_login_authenticate_validate';
        }
        elseif ($auth_conf->authenticationMode == LDAP_AUTHENTICATION_EXCLUSIVE) {
         // see drupal.org/node/1009990 and drupal.org/node/1022362 change back when fixed.
          $new_validation_sequence[] = 'user_login_authenticate_validate';
          $new_validation_sequence[] = 'ldap_authentication_user_login_authenticate_validate';
        }
        else { // misconfigured ldap authentication, restore to original validation sequence
        $new_validation_sequence[] = 'user_login_authenticate_validate';
        }
      }
      else {
        $new_validation_sequence[] = $validate_function_name;
      }
    }
  $form['#validate'] = $new_validation_sequence;
  }

  if ($form_id == 'user_login_block') {
    $user_register = variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL);
    $vars = array(
      'show_reset_pwd' => ldap_authentication_show_reset_pwd(),
      'auth_conf' => $auth_conf,
      );

    $form['links']['#markup'] = theme('ldap_authentication_user_login_block_links', $vars);
  }
  ldap_servers_disable_http_check($form);

  // Add help information for entering in username/password
  $auth_conf = ldap_authentication_get_valid_conf();
  if ($auth_conf) {
    if (isset($auth_conf->loginUIUsernameTxt)) {
      $form['name']['#description'] = t($auth_conf->loginUIUsernameTxt);
    }
    if (isset($auth_conf->loginUIPasswordTxt)) {
      $form['pass']['#description'] = t($auth_conf->loginUIPasswordTxt);
    }
  }
}



/**
  * alter user editing form (profile form) based on ldap authentication configuration
  *
  * @param array $form array from user profile
  * @param array $form_state from user profile
  *
  * @return NULL (alters $form by reference)
  */
function _ldap_authentication_form_user_profile_form_alter(&$form, $form_state) {
  // keep in mind admin may be editing another users profile form.  don't assume current global $user
  $auth_conf = ldap_authentication_get_valid_conf();
  if ($auth_conf && ldap_authentication_ldap_authenticated($form['#user'])) {
    if ($auth_conf->emailOption == LDAP_AUTHENTICATION_EMAIL_FIELD_REMOVE) {
      $form['account']['mail']['#type'] = 'hidden';
    }
    elseif ($auth_conf->emailOption == LDAP_AUTHENTICATION_EMAIL_FIELD_DISABLE) {
      $form['account']['mail']['#disabled'] = TRUE;
      $form['account']['mail']['#description'] = t('This email address is automatically set and may not be changed.');
    }
    elseif ($auth_conf->emailOption == LDAP_AUTHENTICATION_EMAIL_FIELD_ALLOW) {
      // email field is functional
    }

    if (!ldap_authentication_show_reset_pwd($form['#user'])) {
      $form['account']['current_pass']['#disabled'] = TRUE;
      if ($auth_conf->ldapUserHelpLinkUrl) {
        $form['account']['current_pass']['#description'] = l(t($auth_conf->ldapUserHelpLinkText), $auth_conf->ldapUserHelpLinkUrl);
      }
      else {
        $form['account']['current_pass']['#description'] = t('The password cannot be changed using this website');
      }
      $form['account']['pass']['#disabled'] = TRUE;
    }
  }
}


/**
  * user form validation will take care of username, pwd fields
  * this function validates ldap autentication specific issues
  * ldap authentication exclusively
  *
  * @param array $form_state array from user logon form
  * @return NULL (form_set_error() calls throw validation errors)
  */
function _ldap_authentication_user_login_authenticate_validate(&$form_state) {

  $detailed_watchdog_log = variable_get('ldap_help_watchdog_detail', 0);
  $authname = $form_state['values']['name']; // $name = $form_state['values']['name']; // patch 1599632
  $pass = $form_state['values']['pass'];

  /*
   * If a fake form state was passed into this function from
   * _ldap_authentication_user_login_sso(), there will be a value outside of the
   * form_state[values] array to let us know that we are not authenticating with
   * a password, but instead just looking up a username/dn in LDAP since the web
   * server already authenticated the user.
   */
  $sso_login = (isset($form_state['sso_login']) && $form_state['sso_login']) ? TRUE : FALSE;

  $watchdog_tokens = array('%username' => $authname); // $watchdog_tokens = array('%username' => $name); // patch 1599632
  if ($detailed_watchdog_log) {
    watchdog('ldap_authentication', '%username : Beginning authentification....', $watchdog_tokens, WATCHDOG_DEBUG);
  }

  if (!$auth_conf = ldap_authentication_get_valid_conf()) {
    watchdog('ldap_authentication', 'Failed to get valid ldap authentication configuration.', array(), WATCHDOG_ERROR);
    form_set_error('name', 'Server Error: Failed to get valid ldap authentication configuration.' . $error);
    return FALSE;
  }

 // if already succeeded at authentication, see if LDAP Exclusive is set
  if (isset($form_state['uid']) && is_numeric($form_state['uid'])) {
    if ($auth_conf->authenticationMode == LDAP_AUTHENTICATION_MIXED || $form_state['uid'] == 1) {
      if ($detailed_watchdog_log) {
      watchdog('ldap_authentication', '%username : Previously authenticated in mixed mode or uid=1', $watchdog_tokens, WATCHDOG_DEBUG);
      }
      return;  // already passed previous authentication validation
    }
    elseif ($auth_conf->authenticationMode == LDAP_AUTHENTICATION_EXCLUSIVE) {
      if ($detailed_watchdog_log) {
        watchdog('ldap_authentication', '%username : Previously authenticated in exclusive mode or uid is not 1.  Clear uid
        in form_state and attempt ldap authentication.',  $watchdog_tokens, WATCHDOG_DEBUG);
      }
      $form_state['uid'] = NULL;  // passed previous authentication, but only ldap should be used
    }
  }

  if (!$auth_conf->hasEnabledAuthenticationServers()) {
    watchdog('ldap_authentication',  'No LDAP servers configured.', array(), WATCHDOG_ERROR);
    form_set_error('name', 'Server Error:  No LDAP servers configured.');
  }

  if ($detailed_watchdog_log) {
    watchdog('ldap_authentication', '%username : user_load_by_name(%username)', $watchdog_tokens, WATCHDOG_DEBUG);
  }

  if (!($account = user_load_by_name($authname))) {
    $uid = db_query("SELECT uid FROM {authmap} WHERE authname = :authname AND module = 'ldap_user'", array(':authname' => $authname))->fetchColumn();
    $account = $uid ? user_load($uid) : FALSE;
  }

  if (is_object($account)) {
    if ($account->uid == 1) {
      if ($detailed_watchdog_log) {
        watchdog('ldap_authentication',  '%username : Drupal username maps to user 1, so do not authenticate with ldap', $watchdog_tokens, WATCHDOG_DEBUG);
      }
      return FALSE;  // user 1 must use drupal authentication
    }
    else {
      $account_exists = TRUE;
      $user_data = $account->data;
      $authmaps = user_get_authmaps($authname); // $authmaps = user_get_authmaps($name); // patch 1599632
      $ldap_authentication_authmap = isset($authmaps['ldap_user']);
      $no_authmaps = (boolean)(count($authmaps));
      if ($detailed_watchdog_log) {
        watchdog('ldap_authentication',  '%username : Drupal User Account found.  Continuing on to attempt ldap authentication', $watchdog_tokens, WATCHDOG_DEBUG);
      }
    }
  }
  else {  // account does not exist
    $account_exists = FALSE;
    if ($auth_conf->ldapUser->createLDAPAccounts == FALSE) {
      if ($detailed_watchdog_log) {
        watchdog('ldap_authentication', '%username : Drupal User Account not found and configuration is set to not create new accounts.', $watchdog_tokens, WATCHDOG_DEBUG);
      }
    }
    if ($detailed_watchdog_log) {
      watchdog('ldap_authentication', '%username : Existing Drupal User Account not found.  Continuing on to attempt ldap authentication', $watchdog_tokens, WATCHDOG_DEBUG);
    }
  }

  foreach ($auth_conf->enabledAuthenticationServers as $sid => $ldap_server) {
    $watchdog_tokens['%sid'] = $sid;
    $watchdog_tokens['%bind_method'] = $ldap_server->bind_method;
    if ($detailed_watchdog_log) {
      watchdog('ldap_authentication', '%username : Trying server %sid where bind_method = %bind_method', $watchdog_tokens, WATCHDOG_DEBUG);
    }

    // #1 CONNECT TO SERVER
    $authentication_result = LDAP_AUTHENTICATION_RESULT_FAIL_GENERIC;
    $result = $ldap_server->connect();
    if ($result != LDAP_SUCCESS) {
      $authentication_result = LDAP_AUTHENTICATION_RESULT_FAIL_CONNECT;
      $watchdog_tokens['%err_msg'] = $ldap_server->errorMsg('ldap');
      if ($detailed_watchdog_log) {
        watchdog('ldap_authentication',  '%username : Failed connecting to %sid.  Error: %err_msg', $watchdog_tokens, WATCHDOG_DEBUG);
      }
      $watchdog_tokens['%err_msg'] = NULL;
      continue; // next server, please
    }
    elseif ($detailed_watchdog_log) {
      watchdog('ldap_authentication',  '%username : Success at connecting to %sid', $watchdog_tokens, WATCHDOG_DEBUG);
    }

/**
  *
  LDAP_SERVERS_BIND_METHOD_SERVICE_ACCT => t('Service Account Bind.  Use credentials in following section to
  bind to ldap.  This option is usually a best practice. Service account is entered in next section.'),

  LDAP_SERVERS_BIND_METHOD_USER => t('Bind with Users Credentials.  Use users\' entered credentials
  to bind to LDAP.  This is only useful for modules that work during user logon such
  as ldap authentication and ldap authorization.  This option is not a best practice in most cases.
  The users dn must be of the form "cn=[username],[base dn]" for this option to work.'),

  LDAP_SERVERS_BIND_METHOD_ANON_USER => t('Anonymous Bind for search, then Bind with Users Credentials.
  Searches for user DN then uses users\' entered credentials to bind to LDAP.  This is only useful for
  modules that work during user logon such as ldap authentication and ldap authorization.
  The users dn must be discovered by an anonymous search for this option to work.'),

  LDAP_SERVERS_BIND_METHOD_ANON => t('Anonymous Bind. Use no credentials to bind to ldap server.
  Will not work on most ldaps.'),

  */

    $bind_success = FALSE;
    if ($ldap_server->bind_method == LDAP_SERVERS_BIND_METHOD_SERVICE_ACCT ||
        $ldap_server->bind_method == LDAP_SERVERS_BIND_METHOD_ANON_USER
        ) {
      $bind_success = ($ldap_server->bind() == LDAP_SUCCESS);
    }
    elseif ($ldap_server->bind_method == LDAP_SERVERS_BIND_METHOD_ANON) {
      $bind_success = ($ldap_server->bind(NULL, NULL, TRUE) == LDAP_SUCCESS);
    }
    elseif ($sso_login) {
      watchdog('ldap_authentication', 'Trying to use SSO with LDAP_SERVERS_BIND_METHOD_USER bind method.', $watchdog_tokens, WATCHDOG_ERROR);
    }
    elseif ($ldap_server->bind_method == LDAP_SERVERS_BIND_METHOD_USER && $sso_login == FALSE) {
      // with sso enabled this method of binding isn't valid
      foreach ($ldap_server->basedn as $basedn) {
        $search = array('%basedn', '%username');
        $transformname =  $ldap_server->userUsernameToLdapNameTransform($authname, $watchdog_tokens);
        $replace = array($basedn, $transformname);
        $userdn = str_replace($search, $replace, $ldap_server->user_dn_expression);
        $bind_success = ($ldap_server->bind($userdn, $pass) == LDAP_SUCCESS);
        if ($bind_success) {
          break;
        }
      }
    }
    else {
      watchdog('ldap_authentication', 'No bind method set in ldap_server->bind_method in _ldap_authentication_user_login_authenticate_validate.', $watchdog_tokens, WATCHDOG_ERROR);
    }

    if (!$bind_success) {
      if ($detailed_watchdog_log) {
        $watchdog_tokens['%err_text'] = $ldap_server->errorMsg('ldap');
        watchdog('ldap_authentication', '%username : Trying server %sid where bind_method = %bind_method.  Error: %err_text', $watchdog_tokens, WATCHDOG_DEBUG);
        $watchdog_tokens['%err_text'] = NULL;
      }
      $authentication_result = ($ldap_server->bind_method == LDAP_SERVERS_BIND_METHOD_USER) ? LDAP_AUTHENTICATION_RESULT_FAIL_CREDENTIALS : LDAP_AUTHENTICATION_RESULT_FAIL_BIND;
      continue; // if bind fails, onto next server
    }

    // #3 DOES USER EXIST IN SERVER'S LDAP
    if ($ldap_server->bind_method == LDAP_SERVERS_BIND_METHOD_ANON_USER) {
      $ldap_user = $ldap_server->userUserNameToExistingLdapEntry($authname);
    }
    elseif ($sso_login) {
      $ldap_user = $ldap_server->userUserNameToExistingLdapEntry($authname);
      if ($detailed_watchdog_log) {
        $watchdog_tokens['%result'] = var_export($result, TRUE);
        watchdog('ldap_authentication', '%username : attempting single sign-on
          login in bind_method of LDAP_SERVERS_BIND_METHOD_USER. Result of
          userUserNameToExistingLdapEntry: <pre>%result</pre>', $watchdog_tokens, WATCHDOG_DEBUG);
      }
    }
    else {
      $ldap_user = $ldap_server->userUserNameToExistingLdapEntry($authname);
    }

    if (!$ldap_user) {
      if ($detailed_watchdog_log) {
        $watchdog_tokens['%err_text'] = $ldap_server->errorMsg('ldap');
        watchdog('ldap_authentication', '%username : Trying server %sid where bind_method = %bind_method.  Error: %err_text', $watchdog_tokens, WATCHDOG_DEBUG);
        $watchdog_tokens['%err_text'] = NULL;
      }
      if ($ldap_server->ldapErrorNumber()) {
        $authentication_result = LDAP_AUTHENTICATION_RESULT_FAIL_SERVER;
        break;
      }
      $authentication_result = LDAP_AUTHENTICATION_RESULT_FAIL_FIND;
      continue; // next server, please
    }

    $watchdog_tokens['%dn'] = $ldap_user['dn'];
    $watchdog_tokens['%mail'] = $ldap_user['mail'];

    /**
    * #4 CHECK ALLOWED AND EXCLUDED LIST AND PHP FOR ALLOWED USERS
    */

    $allow = $auth_conf->allowUser($authname, $ldap_user, $account_exists);

    if (!$allow) {
      $authentication_result = LDAP_AUTHENTICATION_RESULT_FAIL_DISALLOWED;
      break;  // regardless of how many servers, disallowed user fails
    }

    /**
    * #5 TEST PASSWORD
    */
    $credentials_pass = FALSE;
    if ($sso_login) {
      /** If we have $sso_login passed in as true from the fake form state in
        * passed from _ldap_authentication_user_login_sso(), we will be relying
        * on the webserver for actually authenticating the user, either by NTLM
        * or user/password if configured as a fallback. Since the webserver has
        * already authenticated the user, and the web server only contains the
        * user's LDAP user name, instead of binding on the username/pass, we
        * simply look up the user's account in LDAP, and make sure it matches
        * what is contained in the global $_SERVER array populated by the web
        * server authentication.
        */
      $credentials_pass = (boolean)($ldap_user);
    }
    else {
      $credentials_pass = ($ldap_server->bind($ldap_user['dn'], $pass) == LDAP_SUCCESS);
    }
    if (!$credentials_pass) {
      if ($detailed_watchdog_log) {
        $watchdog_tokens['%err_text'] = $ldap_server->errorMsg('ldap');
        watchdog('ldap_authentication', '%username : Testing user credentials on server %sid where bind_method = %bind_method.  Error: %err_text', $watchdog_tokens, WATCHDOG_DEBUG);
        $watchdog_tokens['%err_text'] = NULL;
      }
      $authentication_result = LDAP_AUTHENTICATION_RESULT_FAIL_CREDENTIALS;
      continue; // next server, please
    }
    else {
      $authentication_result = LDAP_AUTHENTICATION_RESULT_SUCCESS;
      if ($ldap_server->bind_method == LDAP_SERVERS_BIND_METHOD_ANON_USER) {
        $ldap_user = $ldap_server->userUserNameToExistingLdapEntry($authname); // after successful bind, lookup user again to get private attributes
        $watchdog_tokens['%mail'] = $ldap_user['mail'];
      }
      if ($ldap_server->account_name_attr != '') {
        $accountname = $ldap_user['attr'][ldap_server_massage_text($ldap_server->account_name_attr, 'attr_name', LDAP_SERVER_MASSAGE_QUERY_ARRAY)][0];
      }
      else {
        $accountname = $authname;
      }
      $watchdog_tokens['%account_name_attr'] = $accountname;
      if ($ldap_server->account_name_attr != '') {
        $accountname = $ldap_user['attr'][ldap_server_massage_text($ldap_server->account_name_attr, 'attr_name', LDAP_SERVER_MASSAGE_QUERY_ARRAY)][0];
      }
      else {
        $accountname = $authname;
      }
      $watchdog_tokens['%account_name_attr'] = $accountname;
      if ($ldap_server->bind_method == LDAP_SERVERS_BIND_METHOD_SERVICE_ACCT ||
          $ldap_server->bind_method == LDAP_SERVERS_BIND_METHOD_ANON_USER) {
          $ldap_server->disconnect();
      }
      break; //success
    }

  }  // end loop through servers

  $watchdog_tokens['%result'] = $result;
  $watchdog_tokens['%auth_result'] = $authentication_result;
  $watchdog_tokens['%err_text'] =  _ldap_authentication_err_text($authentication_result) ;
  if ($detailed_watchdog_log) {
    watchdog('ldap_authentication',  '%username : Authentication result id=%result auth_result=%auth_result (%err_text)', $watchdog_tokens, WATCHDOG_DEBUG);
  }

  if ($authentication_result != LDAP_AUTHENTICATION_RESULT_SUCCESS) {
    $watchdog_tokens['%err_text'] =  _ldap_authentication_err_text($authentication_result);
  // fail scenario 1.  ldap auth exclusive and failed  throw error
    if ($auth_conf->authenticationMode == LDAP_AUTHENTICATION_EXCLUSIVE) {
      if ($detailed_watchdog_log) {
        watchdog('ldap_authentication', '%username : setting error because failed at ldap and
          LDAP_AUTHENTICATION_EXCLUSIVE is set to true.  So need to stop authentication of Drupal user that is not user 1.
          error message: %err_text', $watchdog_tokens, WATCHDOG_DEBUG);
      }
      form_set_error('name', $watchdog_tokens['%err_text']);
    }
    else {
   // fail scenario 2.  simply fails ldap.  return false.
   // don't show user message, may be using other authentication after this that may succeed.
    if ($detailed_watchdog_log) {
      watchdog('ldap_authentication',
        '%username : Failed ldap authentication.
        User may have authenticated successfully by other means in a mixed authentication site.
        LDAP Authentication Error #: %auth_result  error message: %err_text',
        $watchdog_tokens,
        WATCHDOG_DEBUG
        );
      }
    }
    return FALSE;
  }

  /**
   * case 0: account doesn't exist with $name used to logon,
   *  but puid exists in another user; that is username has changed
   *
   */

  $user_edit = array(); // array of attributes that are changing for existing users
  if (!$account_exists && isset($auth_conf->enabledAuthenticationServers[$ldap_user['sid']])) {
    $ldap_server = $auth_conf->enabledAuthenticationServers[$ldap_user['sid']];
    $puid = $ldap_server->userPuidFromLdapEntry($ldap_user['attr']);
    if ($puid) {
      $account = $ldap_server->userUserEntityFromPuid($puid);
      if ($account) {
        $account_exists = TRUE;
        $user_edit['name'] = $name;
        $account = user_save($account, $user_edit, 'ldap_user');
        user_set_authmaps($account, array("authname_ldap_user" => $name));
      }
    }
  }

  /**
   * case 1: previously drupal authenticated user authenticated successfully on ldap
   *
   */
  if (!$account_exists && ($account = user_load_by_name($accountname))) {
    user_set_authmaps($account, array('authname_ldap_user' => $authname));
    $account_exists = TRUE;
  }
  if (!$account_exists) {


    if ($account_with_same_email = user_load_by_mail($ldap_user['mail'])) {
      // dpm('account with same email');
      /**
       * username does not exist but email does.  Since user_external_login_register does not deal with
       * mail attribute and the email conflict error needs to be caught beforehand, need to throw error here
       */
      $watchdog_tokens['%duplicate_name'] = $account_with_same_email->name;
      watchdog('ldap_authentication', 'LDAP user with DN %dn has email address
        (%mail) conflict with a drupal user %duplicate_name', $watchdog_tokens, WATCHDOG_ERROR);
      drupal_set_message(t('Another user already exists in the system with the same email address. You should contact the system administrator in order to solve this conflict.'), 'error');
      return FALSE;
    }

    if (!$auth_conf->ldapUser->provisionEnabled(LDAP_USER_PROV_DIRECTION_TO_DRUPAL_USER, LDAP_USER_DRUPAL_USER_PROV_ON_AUTHENTICATE)) {
      watchdog('ldap_user', 'Drupal account for %authname does not exists and provisioning of Drupal accounts on authentication is not enabled', array('%authname' => $accountname));
      return FALSE;
    }

    /**
     *
     * new ldap_authentication provisioned account could let user_external_login_register create the account and set authmaps, but would need
     * to add mail and any other user->data data in hook_user_presave which would mean requerying ldap
     * or having a global variable.  At this point the account does not exist, so there is no
     * reason not to create it here.
     *
     * @todo create patch for user_external_login_register to deal with new external accounts
     *       a little tweak to add user->data and mail etc as parameters would make it more useful
     *       for external authentication modules
     */
    ldap_servers_module_load_include('inc', 'ldap_servers', 'ldap_servers.functions');

    // $ldap_user['sid'] = $sid;
    $account = NULL;
    $user_edit = array('name' => $authname, 'status' => 1);
    $user_register = variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL);
    if ($auth_conf->ldapUser->acctCreation == LDAP_AUTHENTICATION_ACCT_CREATION_USER_SETTINGS_FOR_LDAP && $user_register == USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL) {
      $user_edit['status'] = 0; // if admin approval required, set status to 1.
    }

    // don't pass in ldap user, because want to requery with correct attributes needed
    // this may be a case where efficiency dictates querying for all attributes
    $account = $auth_conf->ldapUser->provisionDrupalAccount($account, $user_edit, NULL, TRUE);
    if ($account === FALSE) {
      // need to throw error that account was not created so logging in is not happenning via ldap
    }
  }
  else {  // account already exists
    if ($ldap_authentication_authmap == FALSE) {
      if ($auth_conf->ldapUser->loginConflictResolve == LDAP_USER_CONFLICT_LOG) {
        if ($account_with_same_email = user_load_by_mail($ldap_user['mail'])) {
          $watchdog_tokens['%conflict_name'] = $account_with_same_email->name;
          watchdog('ldap_authentication', 'LDAP user with DN %dn has a naming conflict with a local drupal user %conflict_name', $watchdog_tokens, WATCHDOG_ERROR);
        }
        drupal_set_message(t('Another user already exists in the system with the same login name. You should contact the system administrator in order to solve this conflict.'), 'error');
        return FALSE;
      }
      else { // LDAP_authen.AC.disallow.ldap.drupal
      // add ldap_authentication authmap to user.  account name is fine here, though cn could be used
        user_set_authmaps($account, array('authname_ldap_user' => $authname));
        if ($detailed_watchdog_log) {
          watchdog('ldap_authentication', 'set authmap for %username authname_ldap_user', $watchdog_tokens, WATCHDOG_DEBUG);
        }
      }
    }


    /**
     * @todo.  mail, name, and all other attributes should be synched in this case.  need to
     * generalise this instead of dealing with mail and name individually.
     *
     *  $account = ldap_user_synch_drupal_account($ldap_user);
     */

    if ($account->mail != $ldap_user['mail'] && (
          $auth_conf->emailUpdate == LDAP_AUTHENTICATION_EMAIL_UPDATE_ON_LDAP_CHANGE_ENABLE_NOTIFY ||
          $auth_conf->emailUpdate == LDAP_AUTHENTICATION_EMAIL_UPDATE_ON_LDAP_CHANGE_ENABLE
          ))  {
      $user_edit['mail'] = $ldap_user['mail'];
    }

    if (count($user_edit)) {
      $watchdog_tokens['%username'] = $account->name;
      if (!$updated_account = user_save($account, $user_edit)) {
        watchdog('ldap_authentication', 'Failed to make changes to user %username updated %changed.', $watchdog_tokens,  WATCHDOG_ERROR);
      }
      elseif ($auth_conf->emailUpdate == LDAP_AUTHENTICATION_EMAIL_UPDATE_ON_LDAP_CHANGE_ENABLE_NOTIFY ) {
        if (isset($user_edit['mail'])) {
          $watchdog_tokens['%mail'] = $user_edit['mail'];
          drupal_set_message(t('Your e-mail has been updated to match your current account (%mail).', $watchdog_tokens), 'status');
        }
        if (isset($user_edit['name'])) {
          $watchdog_tokens['%new_username'] = $user_edit['name'];
          drupal_set_message(t('Your old account username %username has been updated to %new_username.', $watchdog_tokens), 'status');
        }
      }
    }
  }

  /**
  * we now have valid, ldap authenticated username with an account authmapped to ldap_authentication.
  * since user_external_login_register can't deal with user mail attribute and doesn't do much else, it is not
  * being used here.
  */

  /**
   * without doing the user_login_submit,
   * [#1009990]
   *
   */
  $fake_form_state = array('uid' => $account->uid);
  user_login_submit(array(), $fake_form_state);
  global $user;
  $form_state['uid'] = $user->uid;
  return $user;

}


/**
 * get human readable authentication error string
 *
 * @param int $error as LDAP_AUTHENTICATION_RESULT_* constant defined in ldap_authentication.module
 * @return string human readable error text
 */
function _ldap_authentication_err_text($error) {

  $msg = t('unknown error: ' . $error);
  switch ($error) {
    case LDAP_AUTHENTICATION_RESULT_FAIL_CONNECT:
    $msg = t('Failed to connect to ldap server');
    break;

    case LDAP_AUTHENTICATION_RESULT_FAIL_BIND:
    $msg = t('Failed to bind to ldap server');
    break;

    case LDAP_AUTHENTICATION_RESULT_FAIL_FIND:
    $msg =  t('Sorry, unrecognized username or password.');
    break;

    case LDAP_AUTHENTICATION_RESULT_FAIL_DISALLOWED:
    $msg = t('User disallowed');
    break;

    case LDAP_AUTHENTICATION_RESULT_FAIL_CREDENTIALS:
    $msg =  t('Sorry, unrecognized username or password.');
    break;

    case LDAP_AUTHENTICATION_RESULT_FAIL_GENERIC:
    $msg = t('Sorry, unrecognized username or password.');
    break;

    case LDAP_AUTHENTICATION_RESULT_FAIL_SERVER:
    $msg = t('Authentication Server or Configuration Error.');
    break;

  }

  return $msg;
}
