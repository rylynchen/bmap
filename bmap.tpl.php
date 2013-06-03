<?php bmap_load_js_css(); ?>
<div class="<?php echo $classes; ?>">
  <?php echo render($content['x']); ?>
  <?php echo render($content['y']); ?>
  <?php echo render($content['field_bmap_address']); ?>
  <?php echo render($content['field_bmap_name']); ?>
  <?php echo render($content['field_bmap_description']); ?>
  <div style="width:<?php echo variable_get('bmap_preview_width', '100%'); ?>;height:<?php echo variable_get('bmap_preview_height', '500px'); ?> ;border:#ccc solid 1px;" id="<?php echo __BMAP_CONTAINER_ID__; ?>"></div>
  <?php
    $data = array(
      array(
        'x' => $bmap->x,
        'y' => $bmap->y,
        'name' => $bmap->field_bmap_name['und'][0]['value'],
        'description' => $bmap->field_bmap_description['und'][0]['value'],
      )
    );
    drupal_add_js(array('bmap' => array('data' => $data)), 'setting');
    drupal_add_js('jQuery(document).ready(function () { Drupal.bmap.phpSetData();Drupal.bmap.make(); });', array('type' => 'inline', 'scope' => 'footer'));
  ?>
</div>