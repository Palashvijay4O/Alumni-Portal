<?php // node template ?>

<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="node-container">
    <?php if ($display_submitted): ?>
      <div class="submitted-info">
      <?php print t('posted by'); ?>
      <span class="node-name"><?php print $name; ?></span>
      <?php print t('on'); ?>
      <span class="node-date"><?php print $date; ?></span>
      <?php if(!$node->status): ?>
        <span class="node-status-unpublished"><?php print t('unpublished'); ?></span>
      <?php endif; ?>
      </div>
    <?php endif; ?>

    <?php print $user_picture; ?>

    <div class="nodecontent"<?php print $content_attributes; ?>>
      <?php
         hide($content['comments']);
         hide($content['links']);
      ?>
      <?php print render($title_prefix); ?>
      <?php if (!$page): ?>
        <h2<?php print $title_attributes; ?>>
          <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
        </h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print render($content); ?>
    </div>
    <?php if($content['links']): ?>
      <div class="links-container">
        <?php print render($content['links']); ?>
      </div>
    <?php endif; ?>
    <?php if (!$teaser): ?>
      <div class="clearfix">
        <?php print render($content['comments']); ?>
      </div>
    <?php endif; ?>
  </div><!--end node container-->
</div><!--end node-->