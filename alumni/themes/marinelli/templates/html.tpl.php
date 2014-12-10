<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN" "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>"
<?php print $rdf_namespaces; ?>>

	<head profile="<?php print $grddl_profile; ?>"><!--start head section-->
	  <?php print $head; ?>
	  <title><?php print $head_title; ?></title>
	  <?php print $styles; ?>
	  <?php print $scripts; ?>
	</head>
	<!--[if lt IE 7 ]> <body class="marinelli ie6 <?php print $classes; ?>"> <![endif]-->
    <!--[if IE 7 ]>    <body class="marinelli ie7 <?php print $classes; ?>"> <![endif]-->
    <!--[if IE 8 ]>    <body class="marinelli ie8 <?php print $classes; ?>"> <![endif]-->
    <!--[if IE 9 ]>    <body class="marinelli ie9 <?php print $classes; ?>"> <![endif]-->
    <!--[if gt IE 9]>  <body class="marinelli <?php print $classes; ?>"> <![endif]-->
    <!--[if !IE]><!--> <body class="marinelli <?php print $classes; ?>"> <!--<![endif]-->
	  <div id="skip-link">
	    <a href="#content" title="<?php print t('Jump to the main content of this page'); ?>" class="element-invisible"><?php print t('Jump to Content'); ?></a>
	  </div>
	  <?php print $page_top; ?>
	  <?php print $page; ?>
	  <?php print $page_bottom; ?>
	</body><!--end body-->
</html>