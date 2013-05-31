<?php

/**
 * Implements hook_views_data()
 */
function bmap_views_data_alter(&$data) {
  $data['bmap']['link_bmap'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the bmap.'),
      'handler' => 'bmap_handler_link_field',
    ),
  );
  $data['bmap']['edit_bmap'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the bmap.'),
      'handler' => 'bmap_handler_edit_link_field',
    ),
  );
  $data['bmap']['delete_bmap'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the bmap.'),
      'handler' => 'bmap_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows bmaps/bmap/%bmap_bid/op
  $data['bmap']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this bmap.'),
      'handler' => 'bmap_handler_bmap_operations_field',
    ),
  );
}