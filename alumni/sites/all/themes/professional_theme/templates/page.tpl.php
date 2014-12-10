<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/garland.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to main-menu administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 */
?>

<div id="wrapper">
  <header id="header" role="banner">
    <?php if ($logo): ?><div id="logo"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>"/></a></div><?php endif; ?>
    <?php if ($site_name): ?><h1 id="site-title"><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a></h1><?php endif; ?>
    <?php if ($site_slogan): ?><div id="site-description"><?php print $site_slogan; ?></div><?php endif; ?>
    <div class="clear"></div>
	<?php
		/* Disable Main menu if unchecked */
		if ($main_menu == TRUE):
	?>
    <nav id="main-menu"  role="navigation">
      <a class="nav-toggle" href="#"><?php print t("Navigation"); ?></a>
      <div class="menu-navigation-container">
        <?php
        if (module_exists('i18n_menu')) {
			$main_menu_tree = i18n_menu_translated_tree(variable_get('menu_main_links_source', 'main-menu'));
        } else {
			$main_menu_tree = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
        }
			print drupal_render($main_menu_tree);
		?>
      </div>
      <div class="clear"></div>
    </nav>
	<?php endif;?><!-- end main-menu -->
  </header>


  <div id="container">

    <?php if ($is_front || theme_get_setting('slideshow_all')): ?>
      <?php if (theme_get_setting('slideshow_display')): ?>
        <!-- Slides -->
        <?php
        $slide1_head = check_plain(theme_get_setting('slide1_head'));
        $slide1_desc = filter_xss_admin(theme_get_setting('slide1_desc'));
        $slide1_url = check_plain(theme_get_setting('slide1_url'));
        $slide1_img = check_plain(theme_get_setting('slide1_image_url'));
        $slide_alt = check_plain(theme_get_setting('slide_alt'));

        $slide2_head = check_plain(theme_get_setting('slide2_head'));
        $slide2_desc = filter_xss_admin(theme_get_setting('slide2_desc'));
        $slide2_url = check_plain(theme_get_setting('slide2_url'));
        $slide2_img = check_plain(theme_get_setting('slide2_image_url'));
        $slide2_alt = check_plain(theme_get_setting('slide2_alt'));

        $slide3_head = check_plain(theme_get_setting('slide3_head'));
        $slide3_desc = filter_xss_admin(theme_get_setting('slide3_desc'));
        $slide3_url = check_plain(theme_get_setting('slide3_url'));
        $slide3_img = check_plain(theme_get_setting('slide3_image_url'));
        $slide3_alt = check_plain(theme_get_setting('slide3_alt'));

        // Default values in case the alt text is not populated.
        if ($slide_alt == ""):
          $slide_alt = "slider image 1";
        endif;
        if ($slide2_alt == ""):
          $slide2_alt = "slider image 2";
        endif;
        if ($slide3_alt == ""):
          $slide3_alt = "slider image 3";
        endif;
        ?>
    <section id="slider">
    <ul class="slides">
      <li>
        <article class="post">
        <div class="entry-container">
          <header class="entry-header">
            <h2 class="entry-title"><a href="<?php print url($slide1_url); ?>"><?php print $slide1_head; ?></a></h2>
          </header><!-- .entry-header -->
          <div class="entry-summary">
                <?php print $slide1_desc; ?>
          </div><!-- .entry-summary -->
          <div class="clear"></div>
        </div><!-- .entry-container -->
            <a href="<?php print url($slide1_url); ?>">
	    <?php if($slide1_img != '') { ?>
            <img src="<?php print $slide1_img; ?>" class="slide-image" alt="<?php print $slide_alt; ?>" /> </a>
            <?php } else { ?>
            <img src="<?php print base_path() . drupal_get_path('theme', 'professional_theme') . '/images/slide-image-1.jpg'; ?>" class="slide-image" alt="<?php print $slide_alt; ?>" /></a>
        <?php } ?>
	<div class="clear"></div>
        </article>
      </li>

      <li>
        <article class="post">
        <div class="entry-container">
          <header class="entry-header">
            <h2 class="entry-title"><a href="<?php print url($slide2_url); ?>"><?php print $slide2_head; ?></a></h2>
          </header><!-- .entry-header -->
          <div class="entry-summary">
                <?php print $slide2_desc; ?>
          </div><!-- .entry-summary -->
          <div class="clear"></div>
        </div><!-- .entry-container -->
            <a href="<?php print url($slide2_url); ?>">
		<?php if($slide2_img != '') { ?>
            	<img src="<?php print $slide2_img; ?>" class="slide-image" alt="<?php print $slide2_alt; ?>" /> </a>
		<?php } else { ?>
            <img src="<?php print base_path() . drupal_get_path('theme', 'professional_theme') . '/images/slide-image-2.jpg'; ?>" class="slide-image" alt="<?php print $slide2_alt; ?>"  /></a>
        	<?php } ?>
	<div class="clear"></div>
        </article>
      </li>

      <li>
        <article class="post">
        <div class="entry-container">
          <header class="entry-header">
            <h2 class="entry-title"><a href="<?php print url($slide3_url); ?>"><?php print $slide3_head; ?></a></h2>
          </header><!-- .entry-header -->
          <div class="entry-summary">
                <?php print $slide3_desc; ?>
          </div><!-- .entry-summary -->
          <div class="clear"></div>
        </div><!-- .entry-container -->
            <a href="<?php print url($slide3_url); ?>">
		<?php if($slide3_img != '') { ?>
            <img src="<?php print $slide3_img; ?>" class="slide-image" alt="<?php print $slide3_alt; ?>" /> </a>
		<?php } else { ?>
            <img src="<?php print base_path() . drupal_get_path('theme', 'professional_theme') . '/images/slide-image-3.jpg'; ?>" class="slide-image" alt="<?php print $slide3_alt; ?>" /></a>
		<?php } ?>
         <div class="clear"></div>
        </article>
      </li>
    </ul>
    </section>
       <?php endif; ?>
    <?php endif; ?>


   <?php if ($page['header']): ?>
   <div id="head">
    <?php print render($page['header']); ?>
   </div>
   <div class="clear"></div>
   <?php endif; ?>

    <div class="content-sidebar-wrap">

    <div id="content">
      <?php if (theme_get_setting('breadcrumbs')): ?><div id="breadcrumbs"><?php if ($breadcrumb): print $breadcrumb; endif;?></div><?php endif; ?>
      <section id="post-content" role="main">
        <?php print $messages; ?>
        <?php if ($page['content_top']): ?><div id="content_top"><?php print render($page['content_top']); ?></div><?php endif; ?>
        <?php print render($title_prefix); ?>
        <?php if ($title): ?><h1 class="page-title"><?php print $title; ?></h1><?php endif; ?>
        <?php print render($title_suffix); ?>
        <?php if (!empty($tabs['#primary'])): ?><div class="tabs-wrapper"><?php print render($tabs); ?></div><?php endif; ?>
        <?php print render($page['help']); ?>
        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        <?php print render($page['content']); ?>
      </section> <!-- /#main -->
    </div>

    <?php if ($page['sidebar_first']): ?>
      <aside id="sidebar-first" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>

    </div>

    <?php if ($page['sidebar_second']): ?>
      <aside id="sidebar-second" role="complementary">
        <?php print render($page['sidebar_second']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>

  <div class="clear"></div>

  <?php if ($page['footer']): ?>
   <div id="foot">
     <?php print render($page['footer']) ?>
   </div>
   <?php endif; ?>
  </div>



  <div id="footer">
    <?php if ($page['footer_first'] || $page['footer_second'] || $page['footer_third']): ?>
      <div id="footer-area" class="clearfix">
        <?php if ($page['footer_first']): ?>
        <div class="column"><?php print render($page['footer_first']); ?></div>
        <?php endif; ?>
        <?php if ($page['footer_second']): ?>
        <div class="column"><?php print render($page['footer_second']); ?></div>
        <?php endif; ?>
        <?php if ($page['footer_third']): ?>
        <div class="column"><?php print render($page['footer_third']); ?></div>
        <?php endif; ?>
      </div>
    <?php endif; ?>

    <div id="copyright">
    <!--Remove  -->
    <?php if (!theme_get_setting('remove_copyright')){ ?>
    <?php if (!theme_get_setting('copyright_override')){?>
      <p class="copyright"><?php print t('Copyright'); ?> &copy; <?php echo date("Y"); ?>, <?php print check_plain(theme_get_setting('copywrite_holder')) ?></p>
    <?php } else {?>
       <?php echo check_plain(theme_get_setting('copyright_override'));?>
    <?php } ?>
    <?php } ?>
    <!--Remove Theme Credit by Setting -->
    <?php if (!theme_get_setting('display_theme_credit')): ?>
      <p class="credits"> <?php print t('Theme Originally Created by'); ?>  <a href="http://www.devsaran.com">Devsaran</a></p>
    <?php endif; ?>
    <div class="clear"></div>
    </div>
  </div>
</div>
