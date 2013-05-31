<?php

/**
 * Implements hook_views_default_views().
 */
function bmap_views_default_views() {
  $view = new view();
  $view->name = 'bmaps';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'bmap';
  $view->human_name = 'Bmaps';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'bid' => 'bid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'bid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Bmap: Bmap ID */
  $handler->display->display_options['fields']['bid']['id'] = 'bid';
  $handler->display->display_options['fields']['bid']['table'] = 'bmap';
  $handler->display->display_options['fields']['bid']['field'] = 'bid';
  /* Field: Bmap: Name */
  $handler->display->display_options['fields']['field_bmap_name']['id'] = 'field_bmap_name';
  $handler->display->display_options['fields']['field_bmap_name']['table'] = 'field_data_field_bmap_name';
  $handler->display->display_options['fields']['field_bmap_name']['field'] = 'field_bmap_name';
  $handler->display->display_options['fields']['field_bmap_name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_bmap_name']['alter']['path'] = 'bmap/[bid]';
  $handler->display->display_options['fields']['field_bmap_name']['alter']['target'] = '_blank';
  /* Field: Bmap: Addess */
  $handler->display->display_options['fields']['field_bmap_address']['id'] = 'field_bmap_address';
  $handler->display->display_options['fields']['field_bmap_address']['table'] = 'field_data_field_bmap_address';
  $handler->display->display_options['fields']['field_bmap_address']['field'] = 'field_bmap_address';
  /* Field: Bmap: X */
  $handler->display->display_options['fields']['x']['id'] = 'x';
  $handler->display->display_options['fields']['x']['table'] = 'bmap';
  $handler->display->display_options['fields']['x']['field'] = 'x';
  /* Field: Bmap: Y */
  $handler->display->display_options['fields']['y']['id'] = 'y';
  $handler->display->display_options['fields']['y']['table'] = 'bmap';
  $handler->display->display_options['fields']['y']['field'] = 'y';
  /* Field: Bmap: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'bmap';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';
  $handler->display->display_options['fields']['operations']['label'] = 'Operations';
  /* Filter criterion: Bmap: Name (field_bmap_name) */
  $handler->display->display_options['filters']['field_bmap_name_value']['id'] = 'field_bmap_name_value';
  $handler->display->display_options['filters']['field_bmap_name_value']['table'] = 'field_data_field_bmap_name';
  $handler->display->display_options['filters']['field_bmap_name_value']['field'] = 'field_bmap_name_value';
  $handler->display->display_options['filters']['field_bmap_name_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_bmap_name_value']['expose']['operator_id'] = 'field_bmap_name_value_op';
  $handler->display->display_options['filters']['field_bmap_name_value']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['field_bmap_name_value']['expose']['operator'] = 'field_bmap_name_value_op';
  $handler->display->display_options['filters']['field_bmap_name_value']['expose']['identifier'] = 'field_bmap_name_value';
  $handler->display->display_options['filters']['field_bmap_name_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $views[$view->name] = $view;
  return $views;
}