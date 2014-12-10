<?php

/**
 * @file
 * Implements Nano Scrollbar configuration settings.
 */

/**
 * Nano Scrollbar options & settings form.
 */
function nano_scrollbar_settings($form, &$form_state) {
  // Load default content settings.
  $content_defaults = array(
    'default_stylesheet' => TRUE,
    'nodes' => FALSE,
    'blocks' => FALSE,
    'vertical_css' => '',
  );
  $content_settings = array_merge($content_defaults, variable_get('nano_scrollbar_content', array()));
  // Apply nano scrollbar to content.
  $form['nano_scrollbar_content'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Content & CSS Styling'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  // Provide a bit of help/explanation in context.
  $form['nano_scrollbar_content']['overview'] = array(
    '#type' => 'item',
    '#title' => t('Specify Default Content Types to receive Scrollbar Theming.'),
    '#description' => t('You can specify site-wide content to apply Scrollbar theming to.
                          Do not use this option if you only want to style individual pieces of content.
                          Choose <strong>Selective CSS Attributes</strong> below instead.'),
  );
  // Apply default stylesheet.
  $form['nano_scrollbar_content']['default_stylesheet'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t("Use this Module's Default Stylesheet"),
    '#description' => t('This will apply a height of 400px to site-wide content when selected below. 
                        This stylesheet can be left on and overridden using
                        the CSS classes <strong><em>.nano-scrollbar</em></strong> for nodes and <strong><em>.nano-scrollbar-blocks</em></strong> for main content blocks.
                        If switched off these classes can still be used (in your own stylesheet) if either of <strong><em>Apply to site-wide Node Body/Blocks</em></strong> below are active.'),
    '#default_value' => $content_settings['default_stylesheet'],
  );
  // Apply site-wide to node content.
  $form['nano_scrollbar_content']['nodes'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Apply to site-wide Node Body'),
    '#default_value' => $content_settings['nodes'],
    '#description' => t("Check this box if you want to apply Scrollbar theming to all nodes.
                          This will apply styling to the node body.  For this to work, your theme should correctly print the 
                          <em>\$classes</em> variable inside it's respective node div."),
  );
  // Apply site-wide to standard-blocks/content-blocks.
  $form['nano_scrollbar_content']['blocks'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Apply to site-wide Blocks'),
    '#default_value' => $content_settings['blocks'],
    '#description' => t('Check this box if you want to apply Scrollbar theming to all Blocks.'),
  );
  // Add text box for custom vertical scrollbar css attributes.
  $form['nano_scrollbar_content']['vertical_css'] = array(
    '#type' => 'textarea',
    '#title' => t('CSS Attributes'),
    '#description' => t("List of CSS attributes (classes or ID's) to receive Vertical Scrollbar theming.
                         Use lowercase text and separate each attribute with a comma(<b>.custom-drupal-content-class,</b>). When specifying custom CSS attributes below, don't forget to insert the appropriate CSS styles in your theme's stylesheet for each custom class and ID. The following styles should be applied: height: ? px; or & overflow: hidden; for both. EitherIf the actual height (for vertical scrolling) of the content is less than that specified in your stylesheet, the scrollbar will not show and <b>please follow the instructions given in the link https://drupal.org/node/2219577</b>."),
    '#default_value' => strtolower(preg_replace('/\s+/', '', $content_settings['vertical_css'])),
    '#rows' => 2,
    '#element_validate' => array('_nano_scrollbar_css_validate'),
  );
  // Load defaults.
  $default_settings = array(
    'alwaysvisible' => FALSE,
    'scrollpos' => FALSE,
    'flashdelay' => 1500,
    'prevtpagescroll' => FALSE,
    'disableResize' => FALSE,
    'iOSNativeScrolling' => FALSE,
    'flash' => FALSE,
    'destroy' => FALSE,
    'stop' => FALSE,
    'mobile_browser' => FALSE,
  );
  $settings = array_merge($default_settings, variable_get('nano_scrollbar_settings', array()));
  // Theming & Effects.
  $form['nano_scrollbar_settings'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Settings & Effects'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Turn scroll autovisible on or off.
  $form['nano_scrollbar_settings']['alwaysvisible'] = array(
    '#type' => 'checkbox',
    '#title' => t('Always Visible'),
    '#default_value' => $settings['alwaysvisible'],
    '#description' => t('Sets the scrollbar always visible and appear again when hovered over. (default:false)'),
  );
  // Specify scroll position to top or bottom.
  $form['nano_scrollbar_settings']['scrollpos'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Scroll Position Top/Bottom'),
    '#default_value' => $settings['scrollpos'],
    '#description' => t('Set the position of scroll on page load. (default:"top")<br/>Enabling this option will set the position to bottom'),
  );
  // Specify flash delay.
  $form['nano_scrollbar_settings']['flashdelay'] = array(
    '#prefix' => '<hr />',
    '#type' => 'textfield',
    '#size' => 25,
    '#maxlength' => 25,
    '#title' => t('Flash Delay'),
    '#default_value' => $settings['flashdelay'],
    '#description' => t('Set to specify the scrollbar hide delay in milliseconds if you have enabled the flash option. (default:1500)'),
    '#element_validate' => array('_nano_scrollbar_flashdelay_validate'),
  );
  // Disbale page scroll.
  $form['nano_scrollbar_settings']['prevtpagescroll'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Prevent Page Scrolling'),
    '#default_value' => $settings['prevtpagescroll'],
    '#description' => t('Enable this option to prevent page scrolling when top or bottom inside the content div is reached.(default:false)'),
  );
  // Disable resize.
  $form['nano_scrollbar_settings']['disableResize'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Disable Resize'),
    '#default_value' => $settings['disableResize'],
    '#description' => t('Enable this option to disable the resize from Nano Scroller. Useful if you want total control of the resize event. If you set this option to true remember to call the reset method so that the scroll do not have strange behavior.(default:false)'),
  );
  // Enable iOSNativeScrolling.
  $form['nano_scrollbar_settings']['iOSNativeScrolling'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Enable iOSNativeScrolling'),
    '#default_value' => $settings['iOSNativeScrolling'],
    '#description' => t('Enable this option if you want to use native scrolling in iOS 5+. This will disable your custom nanoScroller scrollbar in iOS 5+ <br/>and use the native one instead. While the native iOS scrollbar usually works much better, there could possibly be bugs in certain situations.(default:false)'),
  );
  // Enable Flash.
  $form['nano_scrollbar_settings']['flash'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Flash On/Off'),
    '#default_value' => $settings['flash'],
    '#description' => t('To flash the scrollbar gadget for an amount of time defined in plugin settings (defaults to 1,5s).<br/>Useful if you want to show the user (e.g. on pageload) that there is more content waiting for him. (default:off)'),
  );
  // Enable Destroy.
  $form['nano_scrollbar_settings']['destroy'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Destroy On/Off'),
    '#default_value' => $settings['destroy'],
    '#description' => t("Destroys nanoScroller and restores browser's native scrollbar. (default:off)"),
  );
  // Enable Stop.
  $form['nano_scrollbar_settings']['stop'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Stop On/Off'),
    '#default_value' => $settings['stop'],
    '#description' => t('To stop the operation. This option will tell the plugin to disable all event bindings and hide the gadget scrollbar from the UI. (default:off)'),
  );
  // Enable Mobile browser support.
  $form['nano_scrollbar_settings']['mobile_browser'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Mobile Browser Support On/Off'),
    '#default_value' => $settings['mobile_browser'],
    '#description' => t('To make nanoscroller work on many mobile devices. (default:off)'),
  );
  return system_settings_form($form);
}

/**
 * Implements validation callback for nano Scrollbar form CSS inputs.
 */
function _nano_scrollbar_css_validate($element, $form_state) {
  // Ready variables.
  $vertical_css = $form_state['values']['nano_scrollbar_content']['vertical_css'];
  $regex = '#[\.\#]{1}[_a-zA-Z0-9-]+,{1}#';
  // Build regex & form validation for vertical & horizontal styles.
  // Unmatched entries will be parsed to an array.
  $vert_css_array = preg_split($regex, $vertical_css, -1, PREG_SPLIT_NO_EMPTY);
  $vert_unmatched = count($vert_css_array);
  // Return validation errors if any CSS input falls outside of matched regex.
  if ($vert_unmatched !== 0) {
    form_set_error('nano_scrollbar_content][vertical_css', t('Please ensure that each Vertical Scrollbar CSS Attribute starts with |<strong style="color: blue;"><em> . </em></strong>| or |<strong style="color: blue;"><em> # </em></strong>| and ends with a comma |<strong style="color: blue;"><em> , </em></strong>|. For example:  <strong style="color: blue;"><em>.node,#block,#region,</em></strong>')
    );
  }
}

/**
 * Implements validation callback for nano Scrollbar form flashdelay input.
 */
function _nano_scrollbar_flashdelay_validate($element, $form_state) {
  // Ready variables.
  $flash_delay_value = $form_state['values']['nano_scrollbar_settings']['flashdelay'];
  // Build regex & form validation for flash delay.
  if (!preg_match('/^[0-9]+$/', $flash_delay_value)) {
    form_set_error('nano_scrollbar_settings[flashdelay]', t('Flash Delay accepts only numeric value.'));
  }
}
