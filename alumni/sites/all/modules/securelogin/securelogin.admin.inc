<?php

/**
 * Admin settings form.
 */
function securelogin_admin() {
  global $base_secure_url;
  if (variable_get('https', FALSE)) {
    drupal_set_message(t('Secure Login module expects the Drupal <code>$conf[\'https\']</code> setting to be at its default value: <code>FALSE</code>. Because it is currently enabled, secure logins cannot be fully implemented because Drupal sets insecure session cookies during login to the secure site.'), 'warning');
  }
  $form['securelogin_base_url'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Secure base URL'),
    '#default_value' => variable_get('securelogin_base_url', NULL),
    '#description'   => t('The base URL for secure pages. Leave blank to allow Drupal to determine it automatically. It is not allowed to have a trailing slash; Drupal will add it for you. For example: %base_secure_url%. Note that in order for cookies to work, the hostnames in the secure base URL and the insecure base URL must be in the same domain as per the appropriate setting in <code>settings.php</code>, which you may need to modify.', array('%base_secure_url%' => $base_secure_url)),
  );
  $form['securelogin_secure_forms'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Redirect form pages to secure URL'),
    '#default_value' => variable_get('securelogin_secure_forms', TRUE),
    '#description'   => t('If enabled, any pages containing the forms enabled below will be redirected to the secure URL. Users can be assured that they are entering their private data on a secure URL, the contents of which have not been tampered with.'),
  );
  $form['required'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Required forms'),
    '#description'   => t('If enabled, the following forms will be submitted to the secure URL. These forms must be secured in order to implement basic secure login functionality.'),
  );
  $form['required']['securelogin_form_user_login'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('User login form'),
    '#default_value' => variable_get('securelogin_user_login', TRUE),
  );
  $form['required']['securelogin_form_user_login_block'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('User login block form'),
    '#default_value' => variable_get('securelogin_form_user_login_block', TRUE),
  );
  $form['required']['securelogin_form_user_pass_reset'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('User password reset form'),
    '#default_value' => variable_get('securelogin_form_user_pass_reset', TRUE),
  );
  $form['required']['securelogin_form_user_profile_form'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('User edit form'),
    '#default_value' => variable_get('securelogin_form_user_profile_form', TRUE),
  );
  $form['optional'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Optional forms'),
    '#description'   => t('Other forms accessible to anonymous users may optionally be secured. If enabled, the following forms will be submitted to the secure URL.'),
  );
  // Registration form is also a login form if e-mail verification is disabled.
  $register = variable_get('user_email_verification', TRUE) ? 'optional' : 'required';
  $form[$register]['securelogin_form_user_register_form'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('User registration form'),
    '#default_value' => variable_get('securelogin_form_user_register_form', TRUE),
  );
  $form['optional']['securelogin_form_user_pass'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('User password request form'),
    '#default_value' => variable_get('securelogin_form_user_pass', TRUE),
  );
  $form['optional']['securelogin_form_node_form'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Node form'),
    '#default_value' => variable_get('securelogin_form_node_form', TRUE),
  );
  $form['optional']['securelogin_form_contact_site_form'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Site contact form'),
    '#default_value' => variable_get('securelogin_form_contact_site_form', TRUE),
  );
  $form['optional']['securelogin_form_contact_personal_form'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Personal contact form'),
    '#default_value' => variable_get('securelogin_form_contact_personal_form', TRUE),
  );
  $form['optional']['securelogin_form_comment_form'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Comment form'),
    '#default_value' => variable_get('securelogin_form_comment_form', TRUE),
  );
  return system_settings_form($form);
}

/**
 * Admin settings form validation handler.
 */
function securelogin_admin_validate($form, &$form_state) {
  if (empty($form_state['values']['securelogin_base_url'])) {
    $form_state['values']['securelogin_base_url'] = NULL;
  }
  elseif (!valid_url($form_state['values']['securelogin_base_url'], TRUE)) {
    form_set_error('securelogin_base_url', t('The secure base URL must be a valid URL.'));
  }
  elseif (strtolower(parse_url($form_state['values']['securelogin_base_url'], PHP_URL_SCHEME)) !== 'https') {
    form_set_error('securelogin_base_url', t('The secure base URL must start with <em>https://</em>.'));
  }
}
