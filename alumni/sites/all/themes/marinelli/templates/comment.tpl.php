<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print $picture; ?>

  <div style="margin-left:<?php print $image_width; ?>px;" class="comment-content">
    <?php print render($title_prefix); ?>

    <?php if ($title): ?>
      <h3<?php print $title_attributes; ?>>
      <?php print $title; ?>
      <?php if ($new): ?>
        <span class="new"><?php print $new; ?></span>
      <?php endif; ?>
      </h3>
    <?php elseif ($new): ?>
      <div class="new"><?php print $new; ?></div>
    <?php endif; ?>

    <?php print render($title_suffix); ?>

    <div class="submitted">
      <?php print $permalink; ?>
      <?php print t('On'); ?>
      <strong><?php print $created; ?></strong>
    </div>

    <div class="comment-text"<?php print $content_attributes; ?>>
      <?php // We hide the comments and links now so that we can render them later.
      hide($content['links']);
      print render($content);
      ?>
        <div class="user-signature clearfix">
          <?php print t('By'); ?> <strong><?php print $author; ?></strong>
          <?php if ($signature): ?>
            --
            <?php print $signature; ?>
          <?php endif; ?>
        </div>
    </div>

    <?php print render($content['links']) ?>

    <div class="arrow-border"></div><!--make the triangle using css only-->
    <div class="arrow"></div>
  </div><!--end comment content-->
</div> <!-- end comment -->