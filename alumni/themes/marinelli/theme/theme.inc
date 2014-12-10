<?php // $Id$

/**
 * Overrides of theme implementations
 */
function marinelli_theme() {
  return array(
    'custom_links' => array( // function that renders classic primary menu with <h2> 
      'variables' => array('links' => NULL, 'attributes' => NULL, 'heading' => NULL),
    ),
    'mega_menu' => array(
      'variables' => array('menu' => NULL),
    ),
    'mbanner_text' => array(
      // 'variables' => array('text' => NULL),
    ),
    'mbanner_nav'  => array(
      'variables' => array('prev' => NULL, 'next' => NULL),
    ),
  );
}

/**
 * Custom primary menu with <h2> for each item
 */
function marinelli_custom_links($variables) {
  global $language_url;
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  $output = '';

  if (count($links) > 0) {
    $output = '';

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);

      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
          && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      $output .= '<li' . drupal_attributes(array('class' => $class)) . '><h2>';

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</h2></li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * Mega drop down primary links.
 *
 * param <array> $menu
 *   Full array of main menu
 *
 * return string
 *   Html with mega menu to printo into page
 */
function marinelli_mega_menu($variables) {
  drupal_add_js(path_to_theme() . '/js/hoverintent/hoverintent.js');
  drupal_add_js(path_to_theme() . '/js/menu/marinelli_menu.js');

  $menu   = $variables['menu'];
  $alt    = theme_get_setting('menu_alt_class');
  $output = '<ul class="megamenu-1">'; // open list

  $count_main_links = 1;

  foreach ($menu as $key => $value) {
    if ($value['link']['hidden'] != 1) { // check if the link is hidden
      $id = 'menu-main-title-' . $value['link']['mlid']; // give an unique id for better styling
      $options = array();
      if (isset($value['link']['options']['attributes']['title'])) {
        $options = array('attributes' => array('title' => $value['link']['options']['attributes']['title']));
      }

      if (theme_get_setting('menu_headings') == 1) { // first level markup (li or h2)
        $output .= '<li class="megamenu-li-first-level" id="' . $id . '">' . l($value['link']['link_title'], $value['link']['href'], $options);
      }
      elseif (theme_get_setting('menu_headings') == 2) {
        // use <h2>, according to http://drupal.org/node/561750
        $output .= '<li class="megamenu-li-first-level" id="' . $id . '"><h2>' . l($value['link']['link_title'], $value['link']['href'], $options) . '</h2>';
      }

      $class = "";
      $altclass = "";

      if (in_array($count_main_links, $alt)) { // add the alt class based on theme settings
        $altclass = " alt";
      }

      switch (count($value['below'])) { // choose mega class (div width based on the numbers of columns)
        case 1:
          $class = 'one-col' . $altclass;
          break;
        case 2:
          $class = 'two-col' . $altclass;
          break;
        case 3:
          $class = 'three-col' . $altclass;
          break;
        case 4:
          $class = 'four-col' . $altclass;
          break;
        case 5:
          $class = 'five-col' . $altclass;
          break;
        case 6:
          $class = 'six-col' . $altclass;
          break;
      }

      if (count($value['below']) > 0 ) { // check if we have children
        $output .= '<div class="mega ' . $class . '">'; // open div mega
        $output .= '<div class="megamenuWrapper">'; // open div megamenuWrapper

        foreach ($value['below'] as $key2 => $value2) {
          if ($value2['below']) {
            $output .= '<div class="menu-section">'; // open div menusection
          }

          $id = 'menu-section-title-' . $value2['link']['mlid']; // give an unique id for better styling
          $options = array('class' => array('menu-section-link'));
          if (isset($value2['link']['options']['attributes']['title'])) {
            $options['attributes'] = array('title' => $value2['link']['options']['attributes']['title']);
          }
          
          if (theme_get_setting('menu_headings') == 1) { // && $value2['below']) { // use a list
            $output .= '<ul class="megamenu-section">'; // open section list

            if ($value2['link']['hidden'] != 1) { // check if the link is hidden
              $output .= '<li class="menu-section-title" id="' . $id . '">' . l($value2['link']['link_title'], $value2['link']['href'], $options);
            }
          }
          elseif (theme_get_setting('menu_headings') == 2) { //  && $value2['below']) { // use <h3>
            if ($value2['link']['hidden'] != 1) { // check if the link is hidden
              $output .= '<h3>' . l($value2['link']['link_title'], $value2['link']['href'], $options) . '</h3>';
            }
          }

          if ($value2['below']) {
            $output .= '<ul class="megamenu-2">'; // open 2nd level list

            foreach ($value2['below'] as $key3 => $value3) {
              $options = array('class' => array('menu-leaf-link'));
              if (isset($value3['link']['options']['attributes']['title'])) {
                $options['attributes'] = array('title' => $value3['link']['options']['attributes']['title']);
              }

              if ($value3['link']['hidden'] != 1) { // check if the link is hidden
                $output .= '<li class="menu-leaf-list">' . l($value3['link']['link_title'], $value3['link']['href'], $options) . '</li>'; // 2nd level <li>
              }
            } // end third foreach

            $output .= '</ul>'; // close 2nd level <ul>

            if (theme_get_setting('menu_headings') == 1) { // close the list only if we use <li>
              $output .= '</li>'; // close 2ndlevel <li>
              $output .= '</ul>'; // close section <ul>
            }

            $output .= '</div>'; // close <div> menu-section
          }
        } // end second foreach

        $output .= '</div>'; // close <div> megamenuWrapper
        $output .= '<div class="closepanel"><span class="close-panel" title="close this panel">' . t('close this panel') . '</span></div>';
        $output .= '</div>'; // close <div> mega
      } // end check for children

      $output .= '</li>'; // close first level <li>
      $count_main_links++;
    } // end check if link is hidden
  } //end first foreach

  $output .= '</ul>'; // close first level <ul>

  return $output;
}

function marinelli_mbanner_text() {
  $banner_text  =  '<div id="header-image-text" class="marinelli-hide-no-js">';
  $banner_text .=  '<div id="header-image-text-data">';
  $banner_text .=  '<'.OUTTAG.' id="header-image-title"><a href="#" class="bannerlink" title="'.t('See this content').'">title</a></'.OUTTAG.'>';
  $banner_text .=  '<p id="header-image-description"><a href="#" class="bannerlink" title="'.t('See this content').'">description</a></p>';
  $banner_text .=  '</div>';
  $banner_text .=  '</div>';

  return $banner_text;
}

function marinelli_mbanner_nav($variables) {
  $banner_navigation  = '<div id="header-image-navigation" class="marinelli-hide-no-js">';
  $banner_navigation .= '<a href="#" id="header-image-prev" title="' . $variables['prev'] . '">&lsaquo;</a>';
  $banner_navigation .= '<a href="#" id="header-image-next" title="' . $variables['next'] . '">&rsaquo;</a>';
  $banner_navigation .= '</div>';

  return $banner_navigation;
}