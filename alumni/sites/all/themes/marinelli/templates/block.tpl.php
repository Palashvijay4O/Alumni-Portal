<?php
/**
 *  $blockhide hides title in blocks (see marinelli_preprocess_block in template.php and theme settings)
 *  $blocktag decides the tag to use for the block title (see theme settings)
 */
?>
<div id="block-<?php print $block->module . '-' . $block->delta; ?>" class="<?php print $blockhide; ?><?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print render($title_prefix); ?>
  <?php if (!empty($block->subject)): ?>
    <div class="block-title">
      <<?php print $blocktag; ?> class="title"<?php print $title_attributes; ?>><?php print $block->subject ?></<?php print $blocktag; ?>>
    </div>
  <?php endif;?>
  <?php print render($title_suffix); ?>
  <div class="content">
    <?php print $content; ?>
  </div>
</div> <!-- /block -->