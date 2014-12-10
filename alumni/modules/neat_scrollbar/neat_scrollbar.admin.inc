<?php
/**
 * @file
 * Implements Neat Scrollbar configuration settings.
 */

/**
 * Neat Scrollbar options & settings form.
 */
function neat_scrollbar_settings($form, &$form_state) {
  // Load default content settings.
  $content_defaults = array(
    'default_stylesheet' => TRUE,
    'nodes' => FALSE,
    'blocks' => FALSE,
    'vertical_css' => '',
    'horizontal_css' => '',
  );
  $content_settings = array_merge($content_defaults, variable_get('neat_scrollbar_content', array()));
  // Apply neat scrollbar to content.
  $form['neat_scrollbar_content'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Content & CSS Styling'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Provide a bit of help/explanation in context.
  $form['neat_scrollbar_content']['overview'] = array(
    '#type' => 'item',
    '#title' => t('Specify Default Content Types to receive Scrollbar Theming.'),
    '#description' => t('You can specify site-wide content to apply Scrollbar theming to.
                          Do not use this option if you only want to style individual pieces of content.
                          Choose <strong>Selective CSS Attributes</strong> below instead.'),
  );
  // Apply default stylesheet.
  $form['neat_scrollbar_content']['default_stylesheet'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t("Use this Module's Default Stylesheet"),
    '#description' => t('This will apply a height of 400px to site-wide content when selected below. 
                        This stylesheet can be left on and overridden using
                        the CSS classes <strong><em>.neat-scrollbar</em></strong> for nodes and <strong><em>.neat-scrollbar-blocks</em></strong> for main content blocks.
                        If switched off these classes can still be used (in your own stylesheet) if either of <strong><em>Apply to site-wide Node Body/Blocks</em></strong> below are active.'),
    '#default_value' => $content_settings['default_stylesheet'],
  );
  // Apply site-wide to node content.
  $form['neat_scrollbar_content']['nodes'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Apply to site-wide Node Body'),
    '#default_value' => $content_settings['nodes'],
    '#description' => t("Check this box if you want to apply Scrollbar theming to all nodes.
                          This will apply styling to the node body.  For this to work, your theme should correctly print the 
                          <em>\$classes</em> variable inside it's respective node div."),
  );
  // Apply site-wide to standard-blocks/content-blocks.
  $form['neat_scrollbar_content']['blocks'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Apply to site-wide Blocks'),
    '#default_value' => $content_settings['blocks'],
    '#description' => t('Check this box if you want to apply Scrollbar theming to all Blocks.'),
  );
  // Add selective css classes.
  $form['neat_scrollbar_content']['css_attributes'] = array(
    '#prefix' => '<hr />',
    '#type' => 'item',
    '#title' => t('Selective CSS Attributes'),
    '#description' => t("When specifying CSS attributes below, don't forget to insert the appropriate CSS styles in your theme's stylesheet for each custom class and ID.<br />
                         The following styles should be applied: <strong><em>height: ? px;</em></strong> <u>or</u> <strong><em>width: ? px;</em></strong> & <strong><em>overflow: hidden;</em></strong> for both.<br />
                         If the actual height (for vertical scrolling) or width (for horizontal scrolling) of the content is less than that specified in your stylesheet, the scrollbar will not show.<br /><br />"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Add text box for custom vertical scrollbar css attributes.
  $form['neat_scrollbar_content']['vertical_css'] = array(
    '#type' => 'textarea',
    '#title' => t('Vertical Scrollbar CSS Attributes'),
    '#description' => t("List of CSS attributes (classes or ID's) to receive Vertical Scrollbar theming.
                         Use lowercase text and separate each attribute with a comma."),
    '#default_value' => strtolower(preg_replace('/\s+/', '', $content_settings['vertical_css'])),
    '#rows' => 2,
    '#element_validate' => array('_neat_scrollbar_css_validate'),
  );
  // Add text box for custom horizontal scrollbar css attributes.
  $form['neat_scrollbar_content']['horizontal_css'] = array(
    '#type' => 'textarea',
    '#title' => t('Horizontal Scrollbar CSS Attributes'),
    '#description' => t("List of CSS attributes (classes or ID's) to receive Horizontal Scrollbar theming. Use lowercase text and separate each attribute with a comma."),
    '#default_value' => strtolower(preg_replace('/\s+/', '', $content_settings['horizontal_css'])),
    '#rows' => 2,
    '#element_validate' => array('_neat_scrollbar_css_validate'),
  );
  // Load defaults.
  $default_settings = array(
    'theme' => 'dark',
    'buttons' => TRUE,
    'round_dragger' => FALSE,
    'inertia' => 550,
    'autohide' => FALSE,
    'dragger_status' => TRUE,
    'mousewheel_status' => FALSE,
    'touch_status' => FALSE,
    'browser_resize' => TRUE,
    'content_resize' => FALSE,
    'autoscroll' => FALSE,
  );
  $settings = array_merge($default_settings, variable_get('neat_scrollbar_settings', array()));
  // Theming & Effects.
  $form['neat_scrollbar_settings'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Theming & Effects'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Add theme selection..
  $form['neat_scrollbar_settings']['theme'] = array(
    '#type' => 'select',
    '#title' => t('Neat Scrollbar Theme'),
    '#default_value' => $settings['theme'],
    '#options' => array(
      'dark' => t('dark'),
      'dark-2' => t('dark-2'),
      'dark-thick' => t('dark-thick'),
      'dark-thin' => t('dark-thin'),
      'light' => t('light'),
      'light-2' => t('light-2'),
      'light-thick' => t('light-thick'),
      'light-thin' => t('light-thin'),
    ),
    '#description' => t('Select a scrollbar theme.  Some <em>light</em> themes may make the Scrollbar difficult to see against a white background and vice-versa.<br />
                      Have a look at the <a href="@help">Available Themes</a> to help you decide which theme you prefer.',
        array('@help' => url('http://manos.malihu.gr/tuts/custom-scrollbar-plugin/scrollbar_themes_demo.html'))),
  );
  // Refine chosen theme with/without arrows/buttons.
  $form['neat_scrollbar_settings']['buttons'] = array(
    '#type' => 'checkbox',
    '#title' => t('Buttons/Arrows'),
    '#default_value' => $settings['buttons'],
    '#description' => t('Turn scroll buttons/arrows on or off.'),
  );
  // Refine chosen theme with/without round dragger.
  $form['neat_scrollbar_settings']['round_dragger'] = array(
    '#type' => 'checkbox',
    '#title' => t('Round Drag Bar'),
    '#default_value' => $settings['round_dragger'],
    '#description' => t('Use a circular dragger instead of a bar.'),
  );
  // Set the easing/inertia of scrollbar & content.
  $form['neat_scrollbar_settings']['inertia_easing'] = array(
    '#prefix' => '<hr />',
    '#type' => 'item',
    '#title' => t('Inertia & Easing'),
  );
  // Add input & validation against an effective useful range.
  $form['neat_scrollbar_settings']['inertia'] = array(
    '#type' => 'textfield',
    '#field_suffix' => t('range: 0 - 3000'),
    '#default_value' => $settings['inertia'],
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('This is the rate at which
                         the content continues to scroll after the scrollbar has been moved.<br />
                         This will also affect the resitance at which the content scrolls
                         when using the scroll buttons/arrows. (default:550)'),
    '#element_validate' => array('_neat_scrollbar_inertia_validate'),
  );
  // Various special FX.
  $form['neat_scrollbar_settings']['effects'] = array(
    '#prefix' => '<hr />',
    '#type' => 'item',
    '#title' => t('Other Options'),
  );
  // Autohide the scrollbar until it has focus/hover.
  $form['neat_scrollbar_settings']['autohide'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto Hide'),
    '#default_value' => $settings['autohide'],
    '#description' => t('Sets the scrollbar to auto-hide and appear again when hovered over. (default:off)'),
  );
  // Dragger - turn auto sizing on or off.
  $form['neat_scrollbar_settings']['dragger_status'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Dragger Auto-Size'),
    '#default_value' => $settings['dragger_status'],
    '#description' => t('Automatically size the Dragger bar in relation to content size. (default:on)'),
  );
  // Mouse wheel - enable scrolling using the mouse wheel.
  $form['neat_scrollbar_settings']['mousewheel_status'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Mouse Wheel On/Off'),
    '#default_value' => $settings['mousewheel_status'],
    '#description' => t('Allow scrolling of neat scrollbar enabled areas using the Mouse Wheel.<br />
                        Enabling this option will load the Mouse Wheel Library. (default:off)'),
  );
  // For mobiles/tablets - enable touch scrolling.
  $form['neat_scrollbar_settings']['touch_status'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Touch Screen Scroll'),
    '#default_value' => $settings['touch_status'],
    '#description' => t('Allow scrolling of neat scrollbar enabled areas for touch screen devices. (default:off)'),
  );
  // Load defaults.
  $adv_defaults = array(
    'browser_resize' => TRUE,
    'content_resize' => FALSE,
    'autoscroll' => FALSE,
  );
  $adv_settings = array_merge($adv_defaults, variable_get('neat_scrollbar_advanced_settings', array()));
  // Advanced settings & FX.
  $form['neat_scrollbar_advanced_settings'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Advanced Settings & Effects'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Resize scrollbar upon browser resize.
  $form['neat_scrollbar_advanced_settings']['browser_resize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Browser Resize'),
    '#default_value' => $adv_settings['browser_resize'],
    '#description' => t('Update scrollbar on browser resize.  Only switch off if using fixed content dimensions. (default:on)'),
  );
  // Resize scrollbar upon content resize.
  $form['neat_scrollbar_advanced_settings']['content_resize'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Content Resize'),
    '#default_value' => $adv_settings['content_resize'],
    '#description' => t('Update scrollbar on content resize. Use for dynamically changing content (and programmatic changes to content).<br />  
                         If on, this will cause the library script to check for changes every few milliseconds (possible performance considerations). (default:off)'),
  );
  // Set autoscroll on or off.
  $form['neat_scrollbar_advanced_settings']['autoscroll'] = array(
    '#prefix' => '<hr />',
    '#type' => 'checkbox',
    '#title' => t('Auto Scroll'),
    '#default_value' => $adv_settings['autoscroll'],
    '#description' => t('Sets the scrollbar to auto-scroll for elements that have focus e.g. when tabbing between textfields.<br />
                        For Drupal users, if you are wrapping content with forms (such as the comments form) within scrollbars, this should be left off
                        to avoid unusual behaviour.<br />
                        In addition, <strong><em>if</em></strong> your nodes have comment forms enabled, you should leave this 
                        <strong><em>off</em></strong> when using <strong><em>Apply to site-wide Node Body</em></strong>
                        under <strong><em>Content & CSS Styling</em></strong> above. (default:off)'),
  );
  // Allow developers to override settings while continuing to use this module's
  // libraries.
  $form['neat_scrollbar_override'] = array(
    '#type' => 'fieldset',
    '#title' => t('Disable Module Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['neat_scrollbar_override']['neat_scrollbar_switch'] = array(
    '#type' => 'checkbox',
    '#title' => t('Override The Above Settings'),
    '#default_value' => variable_get('neat_scrollbar_switch', FALSE),
    '#description' => t("Check this box if you want to disable the settings provided by this module.
                          Select only if you are a developer and want to use this module's libraries with your own custom CSS and JQuery.<br />
                          This will not effect the mousewheel library which can still be switched on or off under Theming & Effects above."),
  );
  return system_settings_form($form);
}
/**
 * Form validation for Neat Scrollbar inertia range.
 */
function _neat_scrollbar_inertia_validate($element, $form_state) {
  $form_inertia = intval($form_state['values']['neat_scrollbar_settings']['inertia']);
  if ($form_inertia > 3000) {
    form_set_error('neat_scrollbar_settings][inertia', t('This field requires a <strong><em>number</em></strong> up to 3000 - the default value is 550.<br />
                                                Please input an acceptable value or refresh/exit this page.')
    );
  }
}
/**
 * Implements validation callback for Neat Scrollbar form CSS inputs.
 */
function _neat_scrollbar_css_validate($element, $form_state) {
  // Ready variables.
  $vertical_css = $form_state['values']['neat_scrollbar_content']['vertical_css'];
  $horz_css = $form_state['values']['neat_scrollbar_content']['horizontal_css'];
  $regex = '#[\.\#]{1}[_a-zA-Z0-9-]+,{1}#';
  // Build regex & form validation for vertical & horizontal styles.
  // Unmatched entries will be parsed to an array.
  $vert_css_array = preg_split($regex, $vertical_css, -1, PREG_SPLIT_NO_EMPTY);
  $vert_unmatched = count($vert_css_array);
  $horz_css_array = preg_split($regex, $horz_css, -1, PREG_SPLIT_NO_EMPTY);
  $horz_unmatched = count($horz_css_array);
  // Return validation errors if any CSS input falls outside of matched regex.
  if ($vert_unmatched !== 0) {
    form_set_error('neat_scrollbar_content][vertical_css', t('Please ensure that each Vertical Scrollbar CSS Attribute starts with |<strong style="color: blue;"><em> . </em></strong>| or |<strong style="color: blue;"><em> # </em></strong>| 
                                                    and ends with a comma |<strong style="color: blue;"><em> , </em></strong>|.<br />
                                                    For example:  <strong style="color: blue;"><em>.node,#block,#region,</em></strong>')
    );
  }
  if ($horz_unmatched !== 0) {
    form_set_error('neat_scrollbar_content][horizontal_css', t('Please ensure that each Horizontal Scrollbar CSS Attributes starts with |<strong style="color: blue;"><em> . </em></strong>| or |<strong style="color: blue;"><em> # </em></strong>| 
                                                    and ends with a comma |<strong style="color: blue;"><em> , </em></strong>|.<br />
                                                    For example:  <strong style="color: blue;"><em>.node,#block,#region,</em></strong>')
    );
  }
}
