<?php
/**
 * node teaser template
 * if you want to use custom teaser templates based on node types
 * just copy this file and rename it
 * for example: node--page--teaser.tpl.php for page teasers
 */
?>

<div class="teaser-container <?php print $classes; ?>"<?php print $attributes; ?>>
	<div class="teaser-content">
		<h2 class="teaser-title">
		<?php print l($title, 'node/'.$nid, array('html'=>TRUE)); ?>
		<?php if($sticky): ?>
			<span class="teaser-sticky"><?php print t($sticky_text); ?></span>
		<?php endif; ?>
		</h2>
		<?php if ($display_submitted): ?>
			<div class="teaser-created">
				<div class="teaser-created-month">
					<?php print t(date('M',$node->created)); ?>
				</div>
				<div class="teaser-created-day">
					<?php print date('d',$node->created); ?>
				</div>			
			</div>
		<?php endif; ?>
			<div class="teaser-text">
			<?php 
        		hide($content['comments']);
        		hide($content['links']);
				hide($content['field_tags']); // hide tags
				print render($content);
      		?>
      		</div>
	</div>
  <div class="teaser-meta">
  <?php if ($display_submitted): ?>
    <strong class="teaser-author"><?php print t('Posted By'); ?></strong> <?php print $name; ?>
  <?php endif; ?>
    <span class="teaser-readmore"><?php print l(t('read more'), 'node/' . $nid, array('attributes' => array('class' => t('node-readmore-link')))); ?></span>
  </div>
</div><!--end teaser container-->