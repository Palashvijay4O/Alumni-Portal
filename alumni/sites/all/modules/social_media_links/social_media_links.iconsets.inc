<?php

/**
 * @file
 * Callbacks for the icon sets.
 */

/**
 * Register the default icon sets.
 *
 * @return array
 *   Array of icon sets.
 */
function social_media_links_social_media_links_iconset_info() {
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

  $icons['nouveller'] = array(
    'name' => 'Social Meida Bookmark Icon +',
    'publisher' => 'nouveller',
    'publisher url' => 'http://www.nouveller.com/',
    'path callback' => 'social_media_links_path_nouveller',
    'download url' => 'http://www.nouveller.com/general/free-social-media-bookmark-icon-pack-the-ever-growing-icon-set/',
    'styles' => array(
      '16' => '16x16',
      '32' => '32x32',
      'buttons' => '122x42',
    ),
  );

  $icons['themeid'] = array(
    'name' => 'themeiD 26 Social Media Icon Sets',
    'publisher' => 'themeiD',
    'publisher url' => 'http://themeid.com/',
    'download url' => 'http://themeid.com/26-free-social-media-icon-sets/',
    'path callback' => 'social_media_links_path_themeid',
    'styles' => array(
      '32' => '32x32',
    ),
  );

  $icons['webtoolkit'] = array(
    'name' => 'webtoolkit Icon Set',
    'publisher' => 'webtoolkit4.me',
    'publisher url' => 'http://webtoolkit4.me/',
    'download url' => 'http://webtoolkit4.me/2008/09/05/webtoolkit4me-releases-the-first-icon-set/',
    'path callback' => 'social_media_links_path_webtoolkit',
    'styles' => array(
      '24' => '24x24',
      '32' => '32x32',
      '48' => '48x48',
      '62' => '62x62',
    ),
  );

  return $icons;
}

/**
 * Callback with the informations about the elegantthemes icon set.
 *
 * @param string $platform
 *   Name of the platform for which the path is returned.
 *
 * @param string $style
 *   Size of the icons.
 *
 * @return string
 *   The image path.
 */
function social_media_links_path_elegantthemes($platform = 'twitter', $style = NULL) {
  $info = social_media_links_iconset('elegantthemes');

  switch ($platform) {
    case 'contact':
      $platform = 'email';
      break;
  }

  $path = isset($info['path']) ? $info['path'] . '/PNG/' . $platform . '.png' : '';

  return $path;
}

/**
 * Callback with the informations about the nouveller icon set.
 *
 * @param string $platform
 *   Name of the platform for which the path is returned.
 *
 * @param string $style
 *   Size of the icons.
 *
 * @return string
 *   The image path.
 */
function social_media_links_path_nouveller($platform = 'twitter', $style = '32') {
  $info = social_media_links_iconset('nouveller');

  switch ($platform) {
    case 'contact':
      $platform = 'email';
      break;
    case 'googleplus':
      $platform = 'google';
      break;
  }

  $path = isset($info['path']) ? $info['path'] . '/' . $style . '/' . $platform . '.png' : '';

  return $path;
}

/**
 * Callback with the informations about the themeiD icon set.
 *
 * @param string $platform
 *   Name of the platform for which the path is returned.
 *
 * @param string $style
 *   Size of the icons.
 *
 * @return string
 *   The image path.
 */
function social_media_links_path_themeid($platform = 'twitter', $style = '32') {
  $info = social_media_links_iconset('themeid');

  switch ($platform) {
    case 'contact':
      $platform = 'email';
      break;

    case 'googleplus':
      $platform = 'google';
      break;
  }

  $path = isset($info['path']) ? $info['path'] . '/' . $platform . '-icon.png' : '';

  return $path;
}

/**
 * Callback with the informations about the themeiD icon set.
 *
 * @param string $platform
 *   Name of the platform for which the path is returned.
 *
 * @param string $style
 *   Size of the icons.
 *
 * @return string
 *   The image path.
 */
function social_media_links_path_webtoolkit($platform = 'twitter', $style = '32') {
  $info = social_media_links_iconset('webtoolkit');

  switch ($platform) {
    case 'googleplus':
      $platform = 'google';
      break;
  }

  $path = isset($info['path']) ? $info['path'] . '/' . $style . 'x' . $style . '/' . $platform . '.png' : '';

  return $path;
}
