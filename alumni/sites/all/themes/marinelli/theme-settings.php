<?php // $Id$
include_once 'template.php';

/**
 * Advanced theme settings.
 */
function marinelli_form_system_theme_settings_alter(&$form, $form_state) {
  // fieldgroups
  $form['breadcrumb'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Breadcrumb Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['layout'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Layout Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['menu'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Primary menu settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['accessibility'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Accessibility and code semantics settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['text_vars'] = array(
    '#type' => 'fieldset', 
    '#title' => t('String settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  
  $form['css3'] = array(
    '#type' => 'fieldset', 
    '#title' => t('css3 settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );  

  $form['banner'] = array(
    '#type' => 'fieldset',
    '#title' => t('Banner managment'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Breadcrumb elements
  $form['breadcrumb']['breadcrumb_title'] = array(
    '#type' => 'select',
    '#title' => t('Breadcrumb title'),
    '#description' => t('Do you want to show the title of the page in the breadcrumb?'),
    '#options' => array(
      0 => t('No'),
      1 => t('Yes'),
    ),
    '#default_value' => theme_get_setting('breadcrumb_title'),
  );

  $form['breadcrumb']['breadcrumb_title_length'] = array(
    '#type' => 'select',
    '#title' => t('Title length'),
    '#description' => t('The title in the breadcrumb will be truncated after this number of character'),
    '#options' => array(
      10 => 10,
      20 => 20,
      30 => 30,
      40 => 40,
      50 => 50,
      60 => 60,
      70 => 70,
      80 => 90,
      100 => 100,
    ),
    '#default_value' => theme_get_setting('breadcrumb_title_length'),
  );

  // Layout elements
  $form['layout']['layout_width'] = array(
    '#type' => 'select',
    '#title' => t('Layout width'),
    '#description' => t('1048px layout could show <strong>horizontal bars </strong> with lower resolutions...but honestly i think we are ready to make a wider web...'),
    '#options' => array(
      1 => t('Fixed, 1048px width'),
      2 => t('Fixed, 988px width'),
    ),
    '#default_value' => theme_get_setting('layout_width'),
  );

  $form['layout']['layout_type'] = array(
    '#type' => 'select',
    '#title' => t('Layout Type'),
    '#description' => t('Choose a layout type'),
    '#options' => array(
      1 => t('Content on the left'),
      2 => t('Content in the middle'),
      3 => t('Content on the right'),
    ),
    '#default_value' => theme_get_setting('layout_type'),
  );
  
  /* TO DO: sidebar width
  
  $form['layout']['sidebar_width'] = array(
    '#type' => 'select',
    '#title' => t('Sidebar Width'),
    '#description' => t('Choose a width for the sidebars. The extact size depend on the full layout width (988px or 1048px). The <strong>small size</strong> is 138px or 148px, the <strong>medium size</strong> is 217px or 232px, the <strong>large size</strong> is 296px or 316px'),
    '#options' => array(
      2 => t('Small'),
      3 => t('Medium'),
      4 => t('Large'),
    ),
    '#default_value' => theme_get_setting('sidebar_width'),
  );
  
  */
  
  $form['layout']['blocks'] = array(
    '#type' => 'select',
    '#title' => t('Do you want to hide block title for the external blocks?'),
    '#description' => t('If you choose yes, block title will show only for sidebar blocks. The title will be hidden in all the other blocks (but not removed from source)'),
    '#options' => array(
	    1 => t('YES'),
	    2 => t('NO'),
    ),
    
    '#default_value' => theme_get_setting('blocks'),
  );
  
  // Menu elements
  $form['menu']['menu_type'] = array(
    '#type' => 'select',
    '#title' => t('Which kind of primary links do you want to use?'),
    '#description' => t('Classic one-level primary links, or mega drop-down menu'),
    '#options' => array(
      1 => t('Classic Primary Links'),
      2 => t('Mega Drop Down'),
    ),
    '#default_value' => theme_get_setting('menu_type'),
  );
  
  $form['menu']['menu_element'] = array(
    '#type' => 'select',
    '#title' => t('Megamenu Source'),
    '#description' => t('Choose a menu to render as megamenu'),
    '#options' => menu_get_menus(),
    '#default_value' => theme_get_setting('menu_element'),
  );

  $form['menu']['menu_alt_class'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Alt class (mega menu only)'),
    '#description' => t('On which occurency of primary links would you like to put the alt class?'),
    '#options' => array(
      0 => t('none'),
      1 => 1,
      2 => 2,
      3 => 3,
      4 => 4,
      5 => 5,
      6 => 6,
      7 => 7,
      8 => 8,
      9 => 9,
      10 => 10,
      11 => 11,
      12 => 12,
    ),
    '#suffix' => '<strong>' . t('The alt class will open the mega menu on the left') . '</strong>',
    '#default_value' => theme_get_setting('menu_alt_class'),
  );
  
  // accessibility and code semantics settings
  
  $form['accessibility']['outside_tags'] = array(
    '#type' => 'select',
    '#title' => t('Do you want to use p tag for all the section titles that come before main site content?'),
    '#description' => t('If you choose yes, the theme will try to comply WCAG2 headings specifications by using the p tag instead of h2 for all the section title tags that come before the main content (for example banner title and top region block titles) '),
    '#options' => array(
	    0 => t('NO'),
	    1 => t('YES'),
    ),
    
    '#default_value' => theme_get_setting('outside_tags'),
  );
  
  $form['accessibility']['title_tags'] = array(
    '#type' => 'select',
    '#title' => t('Do you want to use h1 and h2 tags for site title and site slogan on the front page?'),
    '#description' => t('If you choose NO, the theme will force the p tag for title and slogan in every page. This might help with WCAG2 headings specification if you front page has the page title'),
    '#options' => array(
	    0 => t('YES'),
	    1 => t('NO'),
    ),
    
    '#default_value' => theme_get_setting('title_tags'),
  );
  
  $form['accessibility']['menu_headings'] = array(
    '#type' => 'select',
    '#title' => t('Which tag do you want to use for menu section titles?'),
    '#description' => t('Using headings will improve screen-reader based navigation, however you will fail Wcag2 headings order raccomandations'),
    '#options' => array(
      1 => t('only <li>'),
      2 => t('<h2> for first level and <h3> for megamenu sections'),
    ),
    '#default_value' => theme_get_setting('menu_headings'),
  );
  
  // text vars
  
   $form['text_vars']['sticky_text'] = array(
    '#type' => 'textfield',
    '#title' => t('text of the sticky icon'),
    '#default_value' => theme_get_setting('sticky_text')
  );
  
   $form['text_vars']['bartext'] = array(
    '#type' => 'textfield',
    '#title' => t('text of the top bar slide button'),
    '#default_value' => theme_get_setting('bartext')
  );
  
   $form['text_vars']['bartext2'] = array(
    '#type' => 'textfield',
    '#title' => t('text of opened top bar slide button'),
    '#default_value' => theme_get_setting('bartext2')
  );

  // css3 elements
  $form['css3']['css'] = array(
    '#type' => 'select',
    '#title' => t('Do you want to use css3 effects?'),
    '#description' => t('With css3 you can have some additional css-based styles such as rounded corners and text shadows. This effects work only with some browsers. <strong>With css3 enabled you will probably fail css validation</strong>'),
    '#options' => array(
      1 => t('Css3 On'),
      2 => t('Css3 Off'),
    ),
    '#default_value' => theme_get_setting('css'),
  );
  
  $form['css3']['css_typo'] = array(
    '#type' => 'select',
    '#title' => t('Do you want to use css3 font face embedding?'),
    '#description' => t('With this option enabled we can use css3 nice fonts (Loading fonts may slow down page loading) <strong>You need to enable css3 to use this feature</strong>'),
    '#options' => array(
      1 => t('Font face OFF'),
      2 => t('Font Face ON'),
    ),
    '#default_value' => theme_get_setting('css_typo'),
  );

  // Banners elements
  $form['banner']['configuration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Banner configuration'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['banner']['configuration']['banner_usage'] = array(
    '#type' => 'select',
    '#options' => array(
      1 => t('Marinelli banners'),
      0 => t('Drupal region (advertise)')
     ),
    '#title' => t('Do you want to use Marinelli banners or a classic drupal region?'),
    '#default_value' => theme_get_setting('banner_usage'),
  );

  $form['banner']['configuration']['banner_effect'] = array(
    '#type' => 'select',
    '#options' => array(
      'fade' => t('fade'),
      'scrollRight' => t('scrollRight'),
      'scrollLeft' => t('scrollLeft'),
      'scrollUp' => t('scrollUp'),
      'scrollDown' => t('scrollDown'),
      'turnLeft' => t('turnLeft'),
      'fadeZoom' => t('fadeZoom'),
      'curtainX' => t('curtainX'),
      'wipe' => t('wipe'),
       /* TO DO other options*/
     ),
    '#title' => t('Choose the effect of your banner'),
    '#default_value' => theme_get_setting('banner_effect'),
  );

  $form['banner']['configuration']['banner_speed'] = array(
    '#type' => 'textfield',
    '#size' => 4,
    '#title' => t('Choose the  rotation speed (milliseconds, default is 1000)'),
    '#default_value' => theme_get_setting('banner_speed'),
  );

  $form['banner']['configuration']['banner_delay'] = array(
    '#type' => 'textfield',
    '#size' => 4,
    '#title' => t('Choose the banner delay (milliseconds, default is 4000)'),
    '#default_value' => theme_get_setting('banner_delay'),
  );

  $form['banner']['configuration']['banner_pause'] = array(
    '#type' => 'select',
    '#options' => array(
      0 => t('No'),
      1 => t('Yes'),
     ),
    '#title' => t('Pause on hover? default is YES'),
    '#default_value' => theme_get_setting('banner_pause'),
  );

  $form['banner']['configuration']['banner_showtext'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to show title and description over the banner?'),
    '#default_value' => theme_get_setting('banner_showtext'),
    '#options' => array(
      0 => t('No'),
      1 => t('Yes'),
    )
  );

  $form['banner']['configuration']['banner_shownavigation'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want to show the banner navigation over the banner?'),
    '#default_value' => theme_get_setting('banner_shownavigation'),
    '#options' => array(
      0 => t('No'),
      1 => t('Yes'),
    )
  );

  // Image upload section ======================================================
  $banners = marinelli_get_banners();
  
  $form['banner']['images'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Banner images'),
    '#weight' => 2,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  $i = 0;
  foreach ($banners as $image_data) {
    $form['banner']['images'][$i] = array(
      '#type' => 'fieldset',
      '#title' => t('Image !number: !title', array('!number' => $i + 1, '!title' => $image_data['image_title'])),
      '#weight' => $i,
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#tree' => TRUE,
      // Add image config form to $form
      'image' => _marinelli_banner_form($image_data),
    );

    $i++;
  }

  $form['banner']['image_upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload a new banner'),
    '#weight' => $i,
  );

  $form['#submit'][]   = 'marinelli_settings_submit';
  return $form;
}

/**
 * Save settings data.
 */
function marinelli_settings_submit($form, &$form_state) {
  $settings = array();

  // Update image field
  foreach ($form_state['input']['images'] as $image) {
    if (is_array($image)) {
      $image = $image['image'];
      
      if ($image['image_delete']) {
        // Delete banner file
        file_unmanaged_delete($image['image_path']);
        // Delete banner thumbnail file
        file_unmanaged_delete($image['image_thumb']);
      } else {
        // Update image
        $settings[] = $image;
      }
    }
  }
  
  // Check for a new uploaded file, and use that if available.
  if ($file = file_save_upload('image_upload')) {
    $file->status = FILE_STATUS_PERMANENT;
    if ($image = _marinelli_save_image($file)) {
      // Put new image into settings
      $settings[] = $image;
    }
  }

  // Save settings
  marinelli_set_banners($settings);
}

/**
 * Check if folder is available or create it.
 *
 * @param <string> $dir
 *    Folder to check
 */
function _marinelli_check_dir($dir) {
  // Normalize directory name
  $dir = file_stream_wrapper_uri_normalize($dir);

  // Create directory (if not exist)
  file_prepare_directory($dir,  FILE_CREATE_DIRECTORY);
}

/**
 * Save file uploaded by user and generate setting to save.
 *
 * @param <file> $file
 *    File uploaded from user
 *
 * @param <string> $banner_folder
 *    Folder where save image
 *
 * @param <string> $banner_thumb_folder
 *    Folder where save image thumbnail
 *
 * @return <array>
 *    Array with file data.
 *    FALSE on error.
 */
function _marinelli_save_image($file, $banner_folder = 'public://banner/', $banner_thumb_folder = 'public://banner/thumb/') {
  // Check directory and create it (if not exist)
  _marinelli_check_dir($banner_folder);
  _marinelli_check_dir($banner_thumb_folder);

  $parts = pathinfo($file->filename);
  $destination = $banner_folder . $parts['basename'];
  $setting = array();

  $file->status = FILE_STATUS_PERMANENT;
  
  // Copy temporary image into banner folder
  if ($img = file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
    // Generate image thumb
    $image = image_load($destination);
    $small_img = image_scale($image, 300, 100);
    $image->source = $banner_thumb_folder . $parts['basename'];
    image_save($image);

    // Set image info
    $setting['image_path'] = $destination;
    $setting['image_thumb'] = $image->source;
    $setting['image_title'] = '';
    $setting['image_description'] = '';
    $setting['image_url'] = '<front>';
    $setting['image_weight'] = 0;
    $setting['image_published'] = FALSE;
    $setting['image_visibility'] = '*';

    return $setting;
  }
  
  return FALSE;
}

/**
 * Provvide default installation settings for marinelli.
 */
function _marinelli_install() {
  // Deafault data
  $file = new stdClass;
  $banners = array();
  // Source base for images
  
  $src_base_path = drupal_get_path('theme', 'marinelli');
  $default_banners = theme_get_setting('default_banners');
  
  // Put all image as banners
  foreach ($default_banners as $i => $data) {
    $file->uri = $src_base_path . '/' . $data['image_path'];
    $file->filename = $file->uri;

    $banner = _marinelli_save_image($file);
    unset($data['image_path']);
    $banner = array_merge($banner, $data);
    $banners[$i] = $banner;
  }

  // Save banner data
  marinelli_set_banners($banners);

  // Flag theme is installed
  variable_set('theme_marinelli_first_install', FALSE);
}

/**
 * Generate form to mange banner informations
 *
 * @param <array> $image_data
 *    Array with image data
 *
 * @return <array>
 *    Form to manage image informations
 */
function _marinelli_banner_form($image_data) {
    $img_form = array();

    // Image preview
    $img_form['image_preview'] = array(
      '#markup' => theme('image', array('path' => $image_data['image_thumb'])),
    );

    // Image path
    $img_form['image_path'] = array(
      '#type' => 'hidden',
      '#value' => $image_data['image_path'],
    );

    // Thumbnail path
    $img_form['image_thumb'] = array(
      '#type' => 'hidden',
      '#value' => $image_data['image_thumb'],
    );

    // Image title
    $img_form['image_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => $image_data['image_title'],
    );

    // Image description
    $img_form['image_description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => $image_data['image_description'],
    );

    // Link url
    $img_form['image_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Url'),
      '#default_value' => $image_data['image_url'],
    );

    // Image visibility
    $img_form['image_visibility'] = array(
      '#type' => 'textarea',
      '#title' => t('Visibility'),
      '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
      '#default_value' => $image_data['image_visibility'],
    );

    // Image weight
    $img_form['image_weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $image_data['image_weight'],
    );

    // Image is published
    $img_form['image_published'] = array(
      '#type' => 'checkbox',
      '#title' => t('Published'),
      '#default_value' => $image_data['image_published'],
    );

    // Delete image
    $img_form['image_delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete image.'),
      '#default_value' => FALSE,
    );

    return $img_form;
}
