<?php bmap_load_js_css(); ?>
<div class="field"><div class="field-label">Map:</div></div>
<div style="width:<?php echo variable_get('bmap_preview_width', '100%'); ?>;height:<?php echo variable_get('bmap_preview_height', '500px'); ?> ;border:#ccc solid 1px;" id="<?php echo __BMAP_CONTAINER_ID__; ?>"></div>
<?php
	$data = array();
	foreach($points as $point) {
	  $wrapper = entity_metadata_wrapper('bmap', $point);
	  $data[$point->bid] = array(
	    'x' => $wrapper->x->value(),
	    'y' => $wrapper->y->value(),
	    'name' => $wrapper->field_bmap_name->raw(),
	    'description' => $wrapper->field_bmap_description->raw(),
	  );
	}
	drupal_add_js(array('bmap' => array('data' => $data)), 'setting');
	drupal_add_js('jQuery(document).ready(function () { Drupal.bmap.phpSetData();Drupal.bmap.make(); });', array('type' => 'inline', 'scope' => 'footer'));
?>