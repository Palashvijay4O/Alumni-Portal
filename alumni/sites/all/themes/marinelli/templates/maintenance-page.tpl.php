<?php 

/* maintenance page */

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
</head>
<body class="<?php print $classes; ?>" id="maintenance-page">
	<div id="maintenance-page-container">
		<div id="maintenance-page-left">
			<div class="maintenance-page-panel">
			<?php 
					/* print the login form */
					
					$login = drupal_get_form("user_login");
					unset($login['openid_links']); // remove openid links
					unset($login['openid_identifier']);// remove openid option
					print drupal_render($login);
			?>
			</div>
		</div><!--end left-->
		<div id="maintenance-page-right">
			<div class="maintenance-page-panel">
				<?php if($site_name) :?>
				<h1><?php print $site_name; ?></h1>
				<?php endif; ?>
				<?php if($site_slogan) :?>
				<h2><?php print $site_slogan; ?></h2>
				<?php endif; ?>
        		<?php if ($title): ?><h3><?php print $title; ?></h3><?php endif; ?>
        		<?php print $content; ?>
       			<?php if ($messages): ?>
				<?php print $messages; ?>
				<?php endif; ?>
			</div>
		</div><!--end right-->
	</div><!--end container-->
</body>
</html>
