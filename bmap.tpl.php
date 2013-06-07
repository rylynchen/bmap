<div class="<?php echo $classes; ?>">
  <?php echo render($content['x']); ?>
  <?php echo render($content['y']); ?>
  <?php echo render($content['field_bmap_address']); ?>
  <?php echo render($content['field_bmap_name']); ?>
  <?php echo render($content['field_bmap_description']); ?>
  <?php echo theme('bmap_field_map', array('points' => array($bmap))); ?>
</div>