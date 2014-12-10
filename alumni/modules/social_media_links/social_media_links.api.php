<?php

/**
 * @file
 * API documentation for Social Media Links Block module.
 */

/**
 * Defines all platforms by the module.
 *
 * @return array
 *   An associative array whose keys define the key for the platform
 *   (social network) and contains information about the platform. Each
 *   platform description is itself an associative array, with the following
 *   key-value pairs:
 *   - title: (required) The name of the platform / social network.
 *   - base url: (required) The base url for the platform (prefix) to
 *     build the link:
 *     {base url} + {user value} = link url
 *     The base url will be shown on the configuration page before the
 *     input field.
 *   - link attributes:
 *   - image alt: A optional alternativ text that will be used for the icon
 *     alt attribute.
 */
function hook_social_media_links_platform_info() {
  $platforms = array();

  // A simple example for twitter.
  $platforms['twitter'] = array(
    'title' => t('Twitter'),
    'base url' => 'http://www.twitter.com/',
  );

  // A expample for Google+ with an alternative alt text.
  $platforms['googleplus'] = array(
    'title' => t('Google+'),
    'base url' => 'https://plus.google.com/',
    'image alt' => 'Google+ icon',
  );

  return $platforms;
}

/**
 * Change the platforms.
 *
 * @param array $platforms
 *   A associative array with the defined platforms.
 */
function hook_social_media_links_platform_info_alter(&$platforms) {
  // Change the title for Google Plus.
  $platforms['googleplus']['title'] = t('Google Plus');
}

/**
 * Defines the available iconsets.
 *
 * @return array
 *   An associative array whose keys define the key for the iconset
 *   and contains information about the icons for the platforms. Each
 *   iconset deinition is itself an associative array, with the
 *   following key-value pairs:
 *   - name: The name of the iconset.
 *   - publisher: The name of the publisher.
 *   - publisher url: The url for further informations about the iconset.
 *   - styles: The available sizes/styles for the iconset.
 *   - path callback: The name of the callback function that returns the
 *     image urls.
 *   - download url: The url to download the iconset.
 */
function hook_social_media_links_iconset_info() {
  // Simple example for a iconset definition.
  $icons['elegantthemes'] = array(
    'name' => 'Elegant Themes Icons',
    'publisher' => 'Elegant Themes',
    'publisher url' => 'http://www.elegantthemes.com/',
    'styles' => array(
      '32' => '32x32',
    ),
    'path callback' => 'social_media_links_path_elegantthemes',
    'download url' => 'http://www.elegantthemes.com/blog/resources/beautiful-free-social-media-icons',
  );

  return $icons;
}

/**
 * Change the iconset definitions.
 *
 * @param array $iconsets
 *   A associative array with the defined iconsets.
 */
function hook_social_media_links_iconset_info_alter(&$iconsets) {
  // Change the path callback for the elegantthemes.
  $iconsets['elegantthemes']['path callback'] = 'social_media_links_path_elegantthemes';
}
