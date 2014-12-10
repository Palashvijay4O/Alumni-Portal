<?php // page template ?>

<?php if($page['topbar']): ?>
  <!--start top bar-->
  <div id="topBar" class="outsidecontent">
    <div id="topBarContainer" class="<?php print $layout_width; ?>">
    <?php print render($page['topbar']); ?>
    </div>
  </div>

  <div id="topBarLink" class="outsidecontent<?php !$topRegion ? print " withoutTopRegion": print ""; ?>">
    <?php print $topbarlink; ?>
  </div>
  <!--end top bar-->
<?php endif; ?>

<!--start framework container-->
<div class="container_12 <?php print $layout_width; ?>" id="totalContainer">
  <?php if($topRegion): ?>
    <!--start top section-->
    <div id="top" class="outsidecontent">

      <?php if($page['utility_top']): ?>
        <!--start top utility box-->
        <div class="utility" id="topUtility">
          <?php print render($page['utility_top']); ?>
        </div>
        <!--end top utility box-->
      <?php endif; ?>
        
      <!--start branding-->
      <div id="branding">

        <?php if($logo): ?>
          <div id="logo-container">
            <?php print $imagelogo; ?>
          </div>
        <?php endif; ?>

        <?php if($site_name || $siteslogan ): ?>
          <!--start title and slogan-->
          <div id="title-slogan">
            <?php if($site_name): ?>
              <?php print $sitename; ?>
            <?php endif; ?>

            <?php if($site_slogan): ?>
              <?php print $siteslogan; ?>
            <?php endif; ?>
          </div>
          <!--end title and slogan-->
        <?php endif; ?>

      </div>
      <!--end branding-->

      <?php if($page['search']): ?>
        <!--start search-->
        <div id="search">
          <?php print render($page['search']); ?>
        </div>
        <!--end search-->
      <?php endif; ?>

    </div>
    <!--end top section-->
  <?php endif; ?>

  <?php if($mainmenu): ?>
    <!--start main menu-->
    <div id="navigation-primary" class="sitemenu">
      <?php print $mainmenu; ?>
    </div>
    <!--end main menu-->
  <?php endif; ?>

  <!--border start-->
  <div id="pageBorder" <?php print $noborder; ?>>
    <?php if ((!$usebanner && $page['advertise']) || ($usebanner && $banner_image)): ?>
      <!--start advertise section-->
      <div id="header-images" <?php print ($usebanner == 0) ? 'class="unlimited"' : ""; ?>>
        <?php if (!$usebanner): // Use drupal region ?>
          <?php print render($page['advertise']); ?>
        <?php elseif ($banner_image): // Use marinelli banners ?>
          <?php print $banner_text; ?>
          <?php print $banner_nav; ?>
          <?php print $banner_image; ?>
        <?php endif; ?>
      </div>
      <!--end advertise-->
    <?php endif; ?>
		
		<?php if ($secondary_menu): ?>
      <!--start secondary navigation-->
      <div id="navigation-secondary" class="sitemenu">
        <?php print theme('links', array('links' => $secondary_menu, 'attributes' => array('id' => 'secondary-menu', 'class' => array('links', 'clearfix', 'secondary-menu')))); ?>
      </div>
      <!--end secondary-navigation-->
    <?php endif; ?>

    <!-- start contentWrapper-->
    <div id="contentWrapper">
      <!--start breadcrumb -->
      <?php if($breadcrumb): ?>
        <div id="breadcrumb"><?php print $breadcrumb; ?></div>
      <?php endif; ?>
      <!-- end breadcrumb -->
		
			<?php if($page['overcontent']): ?>
        <!--start overcontent-->
        <div class="grid_12 outofContent" id="overContent">
          <?php print render($page['overcontent']); ?>
        </div>
        <!--end overContent-->
      <?php endif; ?>

      <!--start innercontent-->
			<div id="innerContent">

        <!--start main content-->
				<div class="<?php print marinelli_c_c($page['sidebar_first'], $page['sidebar_second'], $layoutType,$exception); ?>" id="siteContent">
					<?php if($page['overnode']): ?>
            <!--start overnode-->
            <div class="outofnode" id="overNode">
              <?php print render($page['overnode']); ?>
            </div>
            <!--end over node-->
					<?php endif; ?>
	   				
	   			<?php if ($page['highlight']): ?>
	   				<div id="highlight">
	   					<?php print render($page['highlight']); ?>
	   				</div>
          <?php endif; ?>
		           	
		      <?php print render($title_prefix); ?>

          <?php if ($title): ?>
            <h1 id="page-title"><?php print $title; ?></h1>
          <?php endif; ?>

          <?php print render($title_suffix); ?>
          <?php print $messages; ?>

          <?php if ($tabs): ?>
            <div class="tab-container">
              <?php print render($tabs); ?>
            </div>
          <?php endif; ?>

          <?php print render($page['help']); ?>

          <?php if ($action_links): ?>
            <ul class="action-links"><?php print render($action_links); ?></ul>
          <?php endif; ?>

          <!--start drupal content-->
          <div id="content">
            <?php print render($page['content']); ?>
          </div>
          <!--end drupal content-->

          <?php print $feed_icons ?>

          <?php if($page['undernode']): ?>
            <!--start undernode-->
            <div class="outofnode" id="underNode">
              <?php print render($page['undernode']); ?>
            </div>
            <!--end under node-->
          <?php endif; ?>

        </div>
        <!--end main content-->
	 			
          <?php if($page['sidebar_first'] && $page['sidebar_second'] && theme_get_setting('layout_type') != 2): ?>
          <div class="<?php print marinelli_w_c($layoutType); ?>" id="sidebarWrapper">
            <!--start oversidebars-->
	        	<?php if($page['oversidebars']): ?>
		    			<div class="outofsidebars grid_6 alpha omega" id="overSidebars">
                <?php print render($page['oversidebars']); ?>
              </div>
            <?php endif; ?>
            <!--end over sidebars-->
        <?php endif; ?>
		    		
		    <?php if($page['sidebar_first']): ?>
          <!--start first sidebar-->
          <div class="<?php print marinelli_s_c($page['sidebar_first'],$page['sidebar_second'],$layoutType,1); ?> sidebar" id="sidebar-first">
						<?php print render($page['sidebar_first']); ?>	
          </div>
          <!--end first sidebar-->
        <?php endif; ?>
		    
        <?php if($page['sidebar_second']): ?>
          <!--start second sidebar-->
          <div class="<?php print marinelli_s_c($page['sidebar_first'],$page['sidebar_second'],$layoutType,2); ?> sidebar" id="sidebar-second"><!--start second sidebar-->
            <?php print render($page['sidebar_second']); ?>
          </div>
          <!--end second sidebar-->
        <?php endif; ?>
						
						
				<?php if($page['sidebar_first'] && $page['sidebar_second'] && theme_get_setting('layout_type') != 2): ?>
          <?php if($page['undersidebars']): ?>
            <!--start undersidebars-->
            <div class="outofsidebars grid_6 alpha omega" id="underSidebars">
              <?php print render($page['undersidebars']); ?>
            </div>
            <!--end under sidebars-->
          <?php endif; ?>
          </div>
          <!--end sidebarWrapper-->
        <?php endif; ?>

      
      </div>
      <!--end innerContent-->


      <?php if($page['undercontent']): ?>
        <!--start underContent-->
				<div class="grid_12 outofContent" id="underContent">
          <?php print render($page['undercontent']); ?>
        </div>
        <!--end underContent-->
      <?php endif; ?>
    </div>
    <!--end contentWrapper-->

	</div>
  <!--close page border Wrapper-->

  <?php if($page['footer'] || $page['utility_bottom']): ?>
    <!--start footer-->
    <div id="footer" class="outsidecontent">
      <?php print render($page['footer']); ?>

      <?php if($page['utility_bottom']): ?>
        <!--start bottom utility box-->
        <div class="utility" id="bottomUtility">
          <?php print render($page['utility_bottom']); ?>
        </div>
        <!--end bottom utility box-->
      <?php endif; ?>
    </div>
    <!--end footer-->
  <?php endif; ?>

</div>
<!--end framework container-->
