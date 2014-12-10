<?php

/**
 * @file
 * Defines the social media links widget for panels.
 */

$plugin = array(
  'title' => t('Social Media Links'),
  'description' => t('Create a Social Media Links widget.'),
  'category' => array('widgets', 0),
  'single' => FALSE,
  'admin info' => 'social_media_links_widget_admin_info',
  'edit form' => 'social_media_links_widget_form',
  'render callback' => 'social_media_links_widget_render',
);

/**
 * Callback to provide administrative info (the preview in panels when building a panel).
 */
function social_media_links_widget_admin_info($subtype, $conf, $context = NULL) {
  if (!empty($conf)) {
    $platform_infos = social_media_links_platforms();

    $active_platforms = array();
    foreach ($conf['platforms'] as $name => $platform) {
      if (!empty($platform['platform_value'])) {
        $active_platforms[] = $platform_infos[$name]['title'];
      }
    }

    $content = t('Activated Platforms: @platforms', array('@platforms' => implode(', ', $active_platforms)));
    $content .= '<br />' . t('Iconset: @iconset', array('@iconset' => $conf['icon_style']));

    $block = new stdClass();
    $block->title = $conf['override_title'] ? $conf['override_title_text'] : t('Follow Us');
    $block->content = $content;

    return $block;
  }
}

/**
 * Callback for the edit form.
*/
function social_media_links_widget_form($form, &$form_state) {
  $form += social_media_links_form($form_state['conf']);

  return $form;
}

/**
 * Submit callback for the edit form.
 */
function social_media_links_widget_form_submit($form, &$form_state) {
  foreach (element_children($form) as $key) {
    if (isset($form_state['values'][$key])) {
      $form_state['conf'][$key] = $form_state['values'][$key];
    }
  }
  if (isset($form_state['values']['icon_style'])) {
    $form_state['conf']['icon_style'] = $form_state['values']['icon_style'];
  }
}

function social_media_links_widget_render($subtype, $conf, $panel_args) {
  $block = new stdClass();

  $content = array(
    '#theme' => 'social_media_links_platforms',
    '#platform_values' => $conf['platforms'],
    '#icon_style' => $conf['icon_style'],
    '#appearance' => $conf['appearance'],
    '#link_attributes' => $conf['link_attributes'],
    '#attributes' => array(
      'class' => array('social-media-links', 'platforms'),
    ),
  );

  // Add css to the block.
  $content['#attached']['css'][] = drupal_get_path('module', 'social_media_links') . '/social_media_links.css';

  $block->title = $conf['override_title'] ? $conf['override_title_text'] : t('Follow Us');
  $block->content = $content;

  return $block;
}