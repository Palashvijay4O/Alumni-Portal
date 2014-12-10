<?php
/**
* Implements hook_html_head_alter().
* This will overwrite the default meta character type tag with HTML5 version.
*/
function professional_theme_html_head_alter(&$head_elements) {
$head_elements['system_meta_content_type']['#attributes'] = array(
'charset' => 'utf-8'
);
}

/**
* Insert themed breadcrumb page navigation at top of the node content.
*/
function professional_theme_breadcrumb($variables) {
$breadcrumb = $variables['breadcrumb'];
if (!empty($breadcrumb)) {
// Use CSS to hide titile .element-invisible.
$output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';
// comment below line to hide current page to breadcrumb
$breadcrumb[] = drupal_get_title();
$output .= '<nav class="breadcrumb">' . implode(' » ', $breadcrumb) . '</nav>';
return $output;
}
}

/**
* Override or insert variables into the page template.
*/
function professional_theme_preprocess_page(&$vars) {
if (isset($vars['main_menu'])) {
$vars['main_menu'] = theme('links__system_main_menu', array(
'links' => $vars['main_menu'],
'attributes' => array(
'class' => array('links', 'main-menu', 'clearfix'),
),
'heading' => array(
'text' => t('Main menu'),
'level' => 'h2',
'class' => array('element-invisible'),
)
));
}
else {
$vars['main_menu'] = FALSE;
}
if (isset($vars['secondary_menu'])) {
$vars['secondary_menu'] = theme('links__system_secondary_menu', array(
'links' => $vars['secondary_menu'],
'attributes' => array(
'class' => array('links', 'secondary-menu', 'clearfix'),
),
'heading' => array(
'text' => t('Secondary menu'),
'level' => 'h2',
'class' => array('element-invisible'),
)
));
}
else {
$vars['secondary_menu'] = FALSE;
}
// Add javascript files for front-page jquery slideshow.
if (drupal_is_front_page() || theme_get_setting('slideshow_all')) {
$directory = drupal_get_path('theme', 'professional_theme');
drupal_add_js($directory . '/js/jquery.flexslider-min.js', array('group' => JS_THEME));
drupal_add_js($directory . '/js/slide.js', array('group' => JS_THEME));
}
// <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1"/>
$viewport = array(
'#type' => 'html_tag',
'#tag' => 'meta',
'#attributes' => array(
'name' =>  'viewport',
'content' =>  'width=device-width'
)
);
drupal_add_html_head($viewport, 'viewport');
}

/**
* Duplicate of theme_menu_local_tasks() but adds clearfix to tabs.
*/
function professional_theme_menu_local_tasks(&$variables) {
$output = '';

if (!empty($variables['primary'])) {
$variables['primary']['#prefix'] = '<h2 class="element-invisible">' . t('Primary tabs') . '</h2>';
$variables['primary']['#prefix'] .= '<ul class="tabs primary clearfix">';
$variables['primary']['#suffix'] = '</ul>';
$output .= drupal_render($variables['primary']);
}
if (!empty($variables['secondary'])) {
$variables['secondary']['#prefix'] = '<h2 class="element-invisible">' . t('Secondary tabs') . '</h2>';
$variables['secondary']['#prefix'] .= '<ul class="tabs secondary clearfix">';
$variables['secondary']['#suffix'] = '</ul>';
$output .= drupal_render($variables['secondary']);
}
return $output;
}

/**
* Override or insert variables into the node template.
*/
function professional_theme_preprocess_node(&$variables) {
$node = $variables['node'];
if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
$variables['classes_array'][] = 'node-full';
}
}
?>
<?php
function professional_theme_form_alter(&$form, &$form_state, $form_id) {
	if ($form_id == 'search_block_form') {
		$form['search_block_form']['#title'] = t('Search'); // Change the text on the label element
		$form['search_block_form']['#title_display'] = 'invisible'; // Toggle label visibilty
		$form['search_block_form']['#size'] = 10;  // define size of the textfield
		$form['search_block_form']['#default_value'] = t('Search'); // Set a default value for the textfield
		$form['actions']['submit']['#value'] = t('GO!'); // Change the text on the submit button
		$form['actions']['submit'] = array('#type' => 'image_button', '#src' => base_path() . path_to_theme() . '/images/search-button.png');
		// Add extra attributes to the text box
		$form['search_block_form']['#attributes']['onblur'] = "if (this.value == '') {this.value = 'Search';}";
		$form['search_block_form']['#attributes']['onfocus'] = "if (this.value == 'Search') {this.value = '';}";
		// Prevent user from searching the default text
		$form['#attributes']['onsubmit'] = "if(this.search_block_form.value=='Search'){ alert('Please enter a search'); return false; }";
		// Alternative (HTML5) placeholder attribute instead of using the javascript
		$form['search_block_form']['#attributes']['placeholder'] = t('Search');
	}
}
