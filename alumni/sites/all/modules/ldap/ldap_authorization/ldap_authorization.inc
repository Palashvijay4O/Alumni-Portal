<?php

/**
 * @file
 *  bulk of authorization code executed to determine a users authorizations
 */

function ldap_authorization_help_watchdog() {  // remove after testing

  $path =  drupal_get_path("module", "ldap_help");
  $_content = "";
  if (module_exists('dblog')) {
    include_once(drupal_get_path('module', 'dblog') . '/dblog.admin.inc');
    $_SESSION['dblog_overview_filter']['type'] = Array('ldap' => 'ldap');
    $_content .= "<h3>" . t('LDAP Watchdog Errors and Notifications') . "</h3>";
    $overview = dblog_overview();
    $_content .= render($overview);

    $_content .= l(t('...more watchdog'), 'admin/reports/dblog');
  }
  else {
    $_content .= "<h3>" . t('LDAP Help Watchdog Errors and Notifications') . "</h3>";
    $_content .= 'This feature requires <code>Database logging</code> module to be turned on. ';
    $_content .= l(t('Module enable page'), 'admin/build/modules');
  }


  return $_content;
}


/**
 * return all desired authorizations for a given user
 *
 * @param object $user
 *
 * @param string $op =
 *   set -- grant authorizations (store in db) and return authorizations
 *   test_query -- don't grant authorization, just query and return authorizations.  assume user is ldap authenticated and exists
 *   query -- don't grant authorization, just query and return authorizations
 *
 * @param string $consumer_type e.g. drupal_roles
 * @param string $context  'logon', 'test_if_authorizations_granted'
 *
 * @return
 *
 *   LDAP_AUTHORIZATION_NO_LDAP_SERVERS if no servers configured
 *   LDAP_AUTHORIZATION_LDAP_ERROR if ldap error
 *   TRUE if servers configured but no roles derived from ldap
 *   array of potential authorizations (user may or may not already have these)
 *
 *   by reference $user->data[<consumer_type>][<authorization_id>] = array();
 *      e.g.   $var['drupal_role']['content_admin'] = array('rid' => 4)
 *      e.g.   $var['og_membership']['bakers club'] = array('expires' => '01/01/2012');
 *
 */


function _ldap_authorizations_user_authorizations(&$user, $op, $consumer_type, $context) {
  $debug = FALSE;
  $detailed_watchdog_log = variable_get('ldap_help_watchdog_detail', 0);
  $authorizations = array();
  $notifications = array();
  $watchdog_tokens = array('%username' => $user->name);
  $consumers = ldap_authorization_get_consumers($consumer_type, TRUE, FALSE);

  $servers = ldap_servers_get_servers(NULL, 'enabled', TRUE);

  /**
   * user 1 not used in ldap authorization.  this is a design decision.
   */
  if (property_exists($user, 'uid') && $user->uid == 1) {
    if ($detailed_watchdog_log) {
      watchdog('ldap_authorization', '%username : ldap_authorization not applied to user 1', $watchdog_tokens, WATCHDOG_DEBUG);
    }
    $notifications['all'] = LDAP_AUTHORIZATION_NOT_APPLY_USER_1;
    foreach ($consumers as $consumer_type => $consumer) {
      $authorizations[$consumer_type] = array();
    }
    return array($authorizations, $notifications);
  }

  /**
   * determine if user is ldap authenticated
   */
  if ($context == 'test_if_authorizations_granted' || ($op == 'test_query' && @$user->ldap_test == TRUE)) {
    $ldap_authenticated = $user->ldap_authenticated;  // property 'ldap_authenticated' only exists for fake user objects submitted from testing form
  }
  else {
    $ldap_authenticated = (boolean)(module_exists('ldap_authentication') && ldap_authentication_ldap_authenticated($user));
  }
  //debug("_ldap_authorizations_user_authorizations" . $user->name .",ldap_authenticated=$ldap_authenticated");
  $watchdog_tokens['%ldap_authenticated'] = ($ldap_authenticated) ? 'yes' : 'no';

  foreach ($consumers as $consumer_type => $consumer) {
  //  dpm($consumer);
    $authorizations[$consumer_type] = array();
    /**
    * each consumer type has only one consumer conf and each consumer conf has only one ldap server id (sid)
    * so there is a one-to-one-to-one relationship between:
    *   - consumer object ($consumer),
    *   - server object ($ldap_server),
    *   - and consumer conf object.
    *
    */

    $consumer = ldap_authorization_get_consumer_object($consumer_type);
    if (!$consumer->consumerConf->status) {
      continue;
    }
    $proposed_ldap_authorizations = array();
    $watchdog_tokens['%consumer_type'] = $consumer_type;
    $watchdog_tokens['%sid'] = $consumer->consumerConf->sid;

    if (! is_object($consumer->consumerConf)) {
      if ($detailed_watchdog_log) {
        watchdog('ldap_authorization', '%username : consumer type  %consumer_type has no
          configuration set.', $watchdog_tokens, WATCHDOG_DEBUG);
      }
      continue;
    }

    if ($detailed_watchdog_log) {
      watchdog('ldap_authorization', '%username : testing with
         consumer type %consumer_type. ldap authenticated=%ldap_authenticated', $watchdog_tokens, WATCHDOG_DEBUG);
    }
    if ($debug) {
      debug(t('%username : testing with consumer type %consumer_type. ldap authenticated=%ldap_authenticated'), $watchdog_tokens);
    }
   // dpm("context=$context,ldap_authenticated=$ldap_authenticated");
    if ($context == 'logon' && !$consumer->consumerConf->synchOnLogon) {
      $notifications[$consumer_type][] = LDAP_AUTHORIZATION_MAP_NOT_CONF_FOR_LOGON;
      if ($detailed_watchdog_log) {
        watchdog('ldap_authorization', '%username : %consumer_type not set to run on user logon.', $watchdog_tokens, WATCHDOG_DEBUG);
      }
      continue;
    }

    if ($consumer->consumerConf->onlyApplyToLdapAuthenticated  && !$ldap_authenticated  && $op != 'test_query') {
      if ($detailed_watchdog_log) {
        watchdog('ldap_authorization', '%username : not used because it is set to be applied only to ldap authenticated users.
            %username  is not ldap authenticated.', $watchdog_tokens, WATCHDOG_DEBUG);
      }
      $notifications[$consumer_type][] = LDAP_AUTHORIZATION_USER_NOT_LDAP_AUTHENTICATED;
      continue;
    }

    $consumer_sid = $consumer->consumerConf->searchAll ? NULL : $consumer->consumerConf->sid;
    $ldap_user = ldap_servers_get_user_ldap_data($user, $consumer_sid, 'ldap_authorization__' . $consumer_type);

    if (!$ldap_user) {
      $notifications[$consumer_type][] = LDAP_AUTHORIZATION_USER_LDAP_NOT_FOUND;
      if ($detailed_watchdog_log) {
        watchdog('ldap_authorization', '%username : %consumer_type ldap user not found.', $watchdog_tokens, WATCHDOG_DEBUG);
      }
      continue;
    }

    if (! isset($servers[$consumer->consumerConf->sid])) {
      $notifications[$consumer_type][] = LDAP_AUTHORIZATION_SERVER_CONFIG_NOT_FOUND;
      if ($detailed_watchdog_log) {
        watchdog('ldap_authorization', '%username : %consumer_type ldap server %sid not enabled or found.', $watchdog_tokens, WATCHDOG_DEBUG);
      }
      continue;
    }

    $ldap_server = $consumer->consumerConf->server;
//    dpm('ldap_server'); dpm($ldap_server);
    /**
     * 1. first just need to figure out what authz_ids are generated for this consumer type/mapping configuration
     *
     * goal here is simply to build an array of authorizations for this ldap authz mapping
     * $proposed_ldap_authorizations[<authorization id>] = properties associative array or empty array
     *  e.g.  $proposed_ldap_authorizations['admin'] = array()
     *
     * the authorization ids may represent drupal roles, organic groups, civicrm groups, etc.
     * these mappings are a function of:
     *   -  drupal user entry, $user
     *   -  $ldap_user. see README.developers.txt for structure
     *   -  an ldap server configuration, $ldap_server
     *   -  a mapping configuration ($consumer_conf)
     */

    if ($detailed_watchdog_log || $debug) {
      $_proposed_ldap_authorizations_pre_hook_maps_alter = is_array($proposed_ldap_authorizations) ? $proposed_ldap_authorizations : array();
      $watchdog_tokens['%proposed_authorizations_pre_hook'] = join(', ', $_proposed_ldap_authorizations_pre_hook_maps_alter);
      watchdog('ldap_authorization', '%username : initial proposed authorization before mapps_alter_invoke %consumer_type: %proposed_authorizations_pre_hook.',
        $watchdog_tokens, WATCHDOG_DEBUG);
    }

    ldap_authorization_maps_alter_invoke($user, $ldap_user, $ldap_server, $consumer->consumerConf, $proposed_ldap_authorizations, $op);

    /** make sure keys of array are lower case and values are mixed case
      and strip to first attribute is configured
    */
    foreach ($proposed_ldap_authorizations as $key => $authorization_id) {
      if ($consumer->consumerConf->useFirstAttrAsGroupId) {
        $attr_parts = ldap_explode_dn($authorization_id, 0);
        if (count($attr_parts) > 0) {
          $first_part = explode('=', $attr_parts[0]);
          if (count($first_part) > 1) {
            $authorization_id = ldap_pear_unescape_dn_value(trim($first_part[1]));
          }
        }
      }
      $proposed_ldap_authorizations[drupal_strtolower($key)] = $authorization_id;
      if ($key != drupal_strtolower($key)) {
        unset($proposed_ldap_authorizations[$key]);
      }
    }

    if ($op == 'test_query') {
      $_SESSION['ldap_authorization_test_query']['useFirstAttrAsGroupId'] = $proposed_ldap_authorizations;
    }

    if ($detailed_watchdog_log || $debug) {
      $_proposed_ldap_authorizations = is_array($proposed_ldap_authorizations) ? $proposed_ldap_authorizations : array();
      $watchdog_tokens['%proposed_authorizations'] = join(', ', $_proposed_ldap_authorizations);
    }
    if ($detailed_watchdog_log) {
      watchdog('ldap_authorization', '%username : initial proposed authorization for %consumer_type: %proposed_authorizations.',
        $watchdog_tokens, WATCHDOG_DEBUG);
    }
    if ($debug) {
      debug(t('%username : initial proposed authorization for %consumer_type: %proposed_authorizations.',
        $watchdog_tokens));
    }



    /**
     * 2.  filter can be both a whitelist and a mapping of an ldap results to an authorization id.
     * goal of this step is to generate $filtered_ldap_authorizations[$consumer_type]
     * an array of filtered and mapped authorization ids
     */

    $filtered_ldap_authorizations = array();

    if ($consumer->consumerConf->useMappingsAsFilter) { // filter + map
      foreach ($consumer->consumerConf->normalizedMappings as $mapping_filter) {
        $map_from = $mapping_filter[0];
        $map_to = $mapping_filter[1];
        if (isset($proposed_ldap_authorizations[drupal_strtolower($map_from)])) {
          $filtered_ldap_authorizations[drupal_strtolower($map_to)] = $map_to;
        }
      }
    }
    else { // only map
      $_authorizations = array_values($proposed_ldap_authorizations);
      if (is_array($consumer->consumerConf->mappings) && is_array($proposed_ldap_authorizations)) {
        foreach ($consumer->consumerConf->mappings as $mapping_filter) {
          $map_from = $mapping_filter[0];
          $map_to = $mapping_filter[1];
          $map_from_key = array_search(drupal_strtolower($map_from), array_keys($proposed_ldap_authorizations));
          if ($map_from_key !== FALSE) {
            // remove non mapped authorization
            $_authorizations = array_diff($_authorizations, array($map_from));
            $_authorizations = array_diff($_authorizations, array(drupal_strtolower($map_from)));
            // add mapped authorization
            $_authorizations[] = $map_to;
            // remove map from;
          }
        }
      }
      foreach ($_authorizations as $i => $authorization_id) {
        $filtered_ldap_authorizations[drupal_strtolower($authorization_id)] = $authorization_id;
      }
    }

    $watchdog_tokens['%filtered_ldap_authorizations'] = join(', ', array_keys($filtered_ldap_authorizations));
    if ($detailed_watchdog_log) {
      watchdog('ldap_authorization', '%username : filtered authorization for %consumer_type: %filtered_ldap_authorizations.',
        $watchdog_tokens, WATCHDOG_DEBUG);
    }
    if ($debug) {
      debug(t('%username : filtered authorization for %consumer_type: %filtered_ldap_authorizations.',
        $watchdog_tokens));
    }

    if ($op == 'test_query') {
      $_SESSION['ldap_authorization_test_query']['post mappings'] = $filtered_ldap_authorizations;
    }

    /**
     * 3. third, grant any proposed authorizations not already granted
     */

    if ($op == 'test_query') {
      $_SESSION['ldap_authorization_test_query']['tokens'] = $watchdog_tokens;
    }
    if ($op == 'set') {
      _ldap_authorizations_user_authorizations_set($user, $consumer, $filtered_ldap_authorizations, $ldap_user, $watchdog_tokens);
    }

    $authorizations[$consumer_type] = $filtered_ldap_authorizations;
  } //  end foreach $consumers

  return array($authorizations, $notifications);

}
/**
 * @param object $user is a drupal user account object, need not be current user
 * @param object $consumer is instance of an authorization consumer class
 *   such as LdapAuthorizationConsumerDrupalRole
 * @param associative array of lower case authorization ids as keys and
 *    mixed case strings as values $filtered_ldap_authorizations
 *   all authorization ids a user is granted via ldap authorization configuration
 * @param object $ldap_entry is users ldap entry.  mapping of drupal user to
 *   ldap entry is stored in ldap_server configuration
 *
 * returns nothing
 */

function _ldap_authorizations_user_authorizations_set(&$user, $consumer, $filtered_ldap_authorizations, &$ldap_entry, $watchdog_tokens) {

  $detailed_watchdog_log = variable_get('ldap_help_watchdog_detail', 0);
  ldap_authorization_cleanse_empty_og_fields($user);

  /**
   * A.  Determine what authorizations have been granted in the past by ldap authorization
   */

  if (isset($user->data['ldap_authorizations'][$consumer->consumerType])
      && is_array($user->data['ldap_authorizations'][$consumer->consumerType])) {
    $user_auth_data = $user->data['ldap_authorizations'][$consumer->consumerType];
    $initial_existing_ldap_authorizations = array_keys($user_auth_data);
  }
  else {
    $user_auth_data = array();
    $initial_existing_ldap_authorizations = array();
  }

  $watchdog_tokens['%initial'] = join(', ', $initial_existing_ldap_authorizations);
  $grants_lcase = array_keys($filtered_ldap_authorizations);
  $watchdog_tokens['%filtered_ldap_authorizations'] = join(', ', array_values($filtered_ldap_authorizations));
   /**
   * B. if regrantLdapProvisioned is false, $grants_lcase array should only be new authorizations
   */
  // if regranting disabled, filter off previously granted roles
  if ($consumer->consumerConf->regrantLdapProvisioned === FALSE) {
    $grants_lcase = array_diff(array_keys($filtered_ldap_authorizations), $initial_existing_ldap_authorizations);
  }
  $watchdog_tokens['%grants1'] = join(', ', $grants_lcase);

   /**
   * C.  query or create existing authorization consumer ids (drupal roles, og groups etc.)
   */

  $consumer_containers_existing = $consumer->availableConsumerIDs();
  $consumer_containers_existing_lcase = array_keys($consumer_containers_existing);
  $containers_needed_lcase = array_diff($grants_lcase, $consumer_containers_existing);

  $containers_needed_assoc = array();
  foreach ($containers_needed_lcase as $i => $container_needed_lcase) {
    $containers_needed_assoc[$container_needed_lcase] = $filtered_ldap_authorizations[$container_needed_lcase];
  }

  $watchdog_tokens['%consumer_containers_initial'] = (count($consumer_containers_existing)) ? join(', ', $consumer_containers_existing) :  t('none');
  $watchdog_tokens['%consumer_containers_needed'] =  (count($containers_needed_lcase)) ?  join(', ', $containers_needed_lcase) :  t('none');

  if (count($containers_needed_lcase) > 0) {
    if ($consumer->consumerConf->createConsumers) {
      $consumer->createConsumers($containers_needed_assoc);
      $consumer_containers_existing = $consumer->availableConsumerIDs();  // requery in case of failure
      $consumer_containers_existing_lcase = array_keys($consumer_containers_existing);
    }
    else {
      $grants_lcase = array_diff($grants_lcase, $containers_needed_lcase);  // filter off consumer ids that don't exist and can't be created
    }
  }


  $watchdog_tokens['%consumer_containers_final'] = join(', ', $consumer_containers_existing);

   /**
   * D.  Only grant authorization consumer ids that exist
   */


  $watchdog_tokens['%consumer_containers_existing'] = (count($consumer_containers_existing)) ? join(', ', $consumer_containers_existing) :  t('none');
  $watchdog_tokens['%grants_pre_intersect'] = (count($grants_lcase)) ? join(', ', $grants_lcase) :  t('none');
  $grants_lcase = array_intersect($consumer_containers_existing_lcase, $grants_lcase);
  $watchdog_tokens['%grants_post_intersect'] = (count($grants_lcase)) ? join(', ', $grants_lcase) :  t('none');

  $grants = array(); // keys are lcase, values are mixed case
  foreach ($grants_lcase as $i => $grant_lcase) {
    $grants[$grant_lcase] = $consumer_containers_existing[$grant_lcase];
  }
  /**
   * E. Do grants
   */

  $consumer->authorizationGrant($user, $user_auth_data, $grants, $ldap_entry, FALSE);

  /**
   *  3.F take away any authorizations not in proposed authorization,
   *      but previously granted by ldap
   */
  $watchdog_tokens['%revokes'] = t('none');

  if ($consumer->consumerConf->revokeLdapProvisioned) {
    $revokes_lcase = array_diff($initial_existing_ldap_authorizations,
      array_keys($filtered_ldap_authorizations));

    if (count($revokes_lcase)) {
      $revokes = array(); // keys are lcase, values are mixed case
      foreach ($revokes_lcase as $i => $revoke_lcase) {
        $revokes[$revoke_lcase] = $consumer_containers_existing[$revoke_lcase];
      }
      $consumer->authorizationRevoke($user, $user_auth_data, $revokes, $ldap_entry, FALSE);
      $watchdog_tokens['%revokes'] = join(', ', $revokes_lcase);
    }
  }
  //print_r($user_auth_data); die();
  $watchdog_tokens['%user_data'] = print_r($user_auth_data, TRUE);


  /**
   *  3.G  save user object and user data
   *  note $user object is passed by reference into this function
   */

  $uid = $user->uid;
  $user_edit['data']['ldap_authorizations'][$consumer->consumerType] = $user_auth_data;
  $user = user_save($user, $user_edit);

  $watchdog_tokens['%user_obj_data_ldap_authorizations'] = print_r($user->data, TRUE);


  if ($detailed_watchdog_log) {
    watchdog('ldap_authorization', '%username : user_authorizations_set results for %consumer_type:
      <hr/>1. Initial existing authorizations:  %initial
      <hr/>1. Filtered Authorizations: %filtered_ldap_authorizations
      <hr/>2. After filtering off previously granted authorizations: %grants1
      <hr/>3. All available existing authorization ids: %consumer_containers_initial
      <hr/>4. authorization ids that need to be created: %consumer_containers_needed
      <hr/>5. consumer containers existing after create call (or non-call if og): %consumer_containers_final
      <hr/>6a. consumer_containers_existing: %consumer_containers_existing
      <hr/>6b. grants_pre_intersect: %grants_pre_intersect
      <hr/>6c. grants_post_intersect: %grants_post_intersect
      <hr/>7. revokes passed to authorizationRevoke(): %revokes
      <hr/>8. user auth data after save for %consumer_type: %user_data
      <hr/>9. user->data[ldap_authorizations] after save: <pre>%user_obj_data_ldap_authorizations</pre>
      ', $watchdog_tokens, WATCHDOG_DEBUG);
  }

}

function _ldap_authorization_ldap_authorization_maps_alter(&$user, &$user_ldap_entry, &$ldap_server, &$consumer_conf, &$authz_ids, $op) {

  $detailed_watchdog_log = variable_get('ldap_help_watchdog_detail', 0);
  $watchdog_tokens = array();

  // groups extracted from user's DN. such as ou=IT => group = "IT"
  $derive_from_dn_authorizations = array();
  if ($rdn_values = $consumer_conf->server->groupUserMembershipsFromDn($user)) {
    $derive_from_dn_authorizations = array_combine($rdn_values, $rdn_values);
  }
  else {
    $derive_from_dn_authorizations = array();
  }
  if ($op == 'test_query') {
    $_SESSION['ldap_authorization_test_query']['maps']['Derive from DN'] = ($rdn_values) ? $derive_from_dn_authorizations : t('disabled');
  }

  // traditional groups (dns)
  $group_dns = $consumer_conf->server->groupMembershipsFromUser($user, 'group_dns');
  if (count($group_dns)) {
    $group_dns = array_unique($group_dns);

  }
  if ($op == 'test_query') {
    $_SESSION['ldap_authorization_test_query']['maps']['Groups DNs'] = $group_dns;
  }

  $values = array_merge($derive_from_dn_authorizations, $group_dns);
  $values = array_unique($values);
  $authz_ids = (count($values)) ? array_combine($values, $values) : array();
  if ($detailed_watchdog_log) {
    $watchdog_tokens['%username'] = $user->name;
    $watchdog_tokens['%ldap_server'] = $ldap_server->sid;
    $watchdog_tokens['%deriveFromDn'] = join(', ', $derive_from_dn_authorizations);
    $watchdog_tokens['%deriveFromGroups'] = join(', ', $group_dns);
    $watchdog_tokens['%authz_ids'] =  join(', ', array_keys($authz_ids));

    watchdog('ldap_authorization', '%username :_ldap_authorization_ldap_authorization_maps_alter:
      <hr/>deriveFromDn authorization ids: %deriveFromDn
      <hr/>deriveFromAttr authorization ids: %deriveFromGroups
      <hr/>merged authz_ids authorization ids: %authz_ids
      ',
      $watchdog_tokens, WATCHDOG_DEBUG);
  }

}
