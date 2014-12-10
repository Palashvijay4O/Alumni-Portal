<?php

/**
 * @file
 * Callbacks for the platforms.
 */

/**
 * Register the default platforms.
 *
 * @return array
 *   List with the default supported platforms.
 */
function social_media_links_social_media_links_platform_info() {
  $platforms['facebook'] = array(
    'title' => t('Facebook'),
    'base url' => 'https://www.facebook.com/',
  );

  $platforms['twitter'] = array(
    'title' => t('Twitter'),
    'base url' => 'http://www.twitter.com/',
  );

  $platforms['googleplus'] = array(
    'title' => t('Google+'),
    'base url' => 'https://plus.google.com/',
    'image alt' => 'Google+ icon',
  );

  $platforms['linkedin'] = array(
    'title' => t('LinkedIn'),
    'base url' => 'http://www.linkedin.com/',
  );

  $platforms['pinterest'] = array(
    'title' => t('Pinterest'),
    'base url' => 'http://www.pinterest.com',
  );

  $platforms['vimeo'] = array(
    'title' => t('Vimeo'),
    'base url' => 'http://www.vimeo.com/',
  );

  $platforms['youtube'] = array(
    'title' => t('YouTube'),
    'base url' => 'http://www.youtube.com/user/',
  );

  $platforms['rss'] = array(
    'title' => t('RSS'),
    'base url' => url(NULL, array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
  );

  $platforms['contact'] = array(
    'title' => t('Contact'),
    'base url' => url(NULL, array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
    'link attributes' => FALSE,
  );

  $platforms['email'] = array(
    'title' => t('E-Mail'),
    'base url' => '',
    'url callback' => 'social_media_links_email_url',
    'link attributes' => FALSE,
  );

  return $platforms;
}

/**
 * Callback function to generate the correct url for e-mail links.
 */
function social_media_links_email_url($base_url, $platform_value) {
  if (valid_email_address($platform_value)) {
    return 'mailto:' . $platform_value;
  }
  return FALSE;
}
