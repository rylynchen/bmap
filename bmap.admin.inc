<?php

/**
 * Administration page for baidu map
 */
function bmap_settings() {
  $form = array();
  $form['bmap_info'] = array(
    '#type' => 'item',
    '#markup' => '<div id="scroll-to-top-prev-container">Apply the key from <a target="_blank" href="http://developer.baidu.com/map/jshome.htm">Baidu Map API</a></div>',
  );
  $form['bmap_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Key'),
    '#default_value' => variable_get('bmap_key', ''),
  );
  $form['bmap_preview_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Preview map width'),
    '#default_value' => variable_get('bmap_preview_width', ''),
  );
  $form['bmap_preview_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Preview map height'),
    '#default_value' => variable_get('bmap_preview_height', ''),
  );
  return system_settings_form($form);
}

/**
 * Display bmap admin page
 */
function bmap_manage() {
  $build['#markup'] = t('Bmap manage');
  return $build;
}

/**
 * Returns a bmap submission form.
 */
function bmap_add() {
  $bmap = entity_get_controller('bmap')->create();
  $output = drupal_get_form('bmap_form', $bmap);
  return $output;
}

/**
 * The bmap edit form.
 */
function bmap_form($form, &$form_state, $bmap) {
  // Save the bmap for later, incase we need it.
  $form['#bmap'] = $bmap;
  $form_state['bmap'] = $bmap;
  $form['bid'] = array(
    '#type' => 'value',
    '#value' => isset($bmap->bid) ? $bmap->bid : NULL,
  );
  $form['info'] = array(
    '#markup' => '<div> You can get X/Y from <a target="_blank" href="http://api.map.baidu.com/lbsapi/getpoint/index.html">Baidu Map</a></div>',
    '#weight' => -30,
  ); 
  $form['x'] = array(
    '#type' => 'textfield',
    '#title' => t('X'),
    '#maxlength' => 60,
    '#default_value' => !empty($bmap->x) ? $bmap->x : '',
    '#attributes' => array('class' => array('bmap_form_x')),
    '#weight' => -20,
    '#required' => TRUE,
  );
  $form['y'] = array(
    '#type' => 'textfield',
    '#title' => t('Y'),
    '#maxlength' => 60,
    '#default_value' => !empty($bmap->y) ? $bmap->y : '',
    '#attributes' => array('class' => array('bmap_form_y')),
    '#weight' => -10,
    '#required' => TRUE,
  );
  // Add the field related form elements.
  field_attach_form('bmap', $bmap, $form, $form_state);
  $form['get_xy'] = array(
    '#type' => 'submit',
    '#value' => t('Get X/Y by address'),
    '#executes_submit_callback' => FALSE,
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => 'bmap_get_xy_callback',
      'progress' => array(
        'type' => 'throbber',
        'message' => '',
      ), 
    ),
    '#weight' => 0,
  );
  $form['preview'] = array(
    '#type' => 'submit',
    '#value' => t('Preview'),
    '#executes_submit_callback' => FALSE,
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => 'bmap_preview_callback',
      'progress' => array(
        'type' => 'throbber',
        'message' => '',
      ),
    ),
    '#weight' => 30,
  );
  $form['map'] = array(
    '#markup' => '<div style="width:'.variable_get('bmap_preview_width', '100%').';height:'.variable_get('bmap_preview_height', '500px').';border:#ccc solid 1px;" id="'.__BMAP_CONTAINER_ID__.'"></div>',
    '#weight' => 35,
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 40
  );
  if (!empty($bmap->bid)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('bmap_form_submit_delete'),
    );    
  }
  $form['#validate'][] = 'bmap_form_validate';
  $form['#submit'][] = 'bmap_form_submit';
  // attached js & css
  $form['#attached']['css'] = array(
    'http://api.map.baidu.com/library/SearchInfoWindow/1.5/src/SearchInfoWindow_min.css' => array('type' => 'external'),
    drupal_get_path('module', 'bmap').'/bmap.css' => array('type' => 'file'),
  );
  $form['#attached']['js'] = array(
    'http://api.map.baidu.com/api?v=1.5&ak='.variable_get('bmap_key', '') => array('type' => 'external'),
    'http://api.map.baidu.com/library/SearchInfoWindow/1.5/src/SearchInfoWindow_min.js' => array('type' => 'external'),
    array('data' => array('bmap' => array('container' => __BMAP_CONTAINER_ID__)), 'type' => 'setting'),
    array('data' => drupal_get_path('module', 'bmap').'/bmap.js', 'scope' => 'footer')
  );
  if (isset($bmap->bid)) {
    $data = array(
      array(
        'x' => $bmap->x,
        'y' => $bmap->y,
        'name' => $bmap->field_bmap_name['und'][0]['value'],
        'description' => $bmap->field_bmap_description['und'][0]['value'],
      )
    );
    $form['#attached']['js'][] = array('data' => array('bmap' => array('data' => $data)), 'type' => 'setting');
    $form['#attached']['js'][] = array('data' => 'jQuery(document).ready(function () { Drupal.bmap.phpSetData();Drupal.bmap.make(); });', 'type' => 'inline');
  }
  return $form;
}

/**
 * Bmap form get x/y handler.
 */
function bmap_get_xy_callback($form, $form_state) {
  $commands[] = array(
    'command' => 'bmapGetXY',
    'data' => $form_state['values']['field_bmap_address']['und'][0]['value'],
  );
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Bmap form preview handler.
 */
function bmap_preview_callback($form, $form_state) {
  $data = array(
    array(
      'x' => $form_state['values']['x'],
      'y' => $form_state['values']['y'],
      'name' => $form_state['values']['field_bmap_name']['und'][0]['value'],
      'description' => $form_state['values']['field_bmap_description']['und'][0]['value'],
    )
  );
  $commands[] = array(
    'command' => 'bmapPreview',
    'data' => $data,
  );
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Bmap form validate handler.
 */
function bmap_form_validate($form, &$form_state) {
  $bmap = $form_state['bmap'];
  // Notify field widgets to validate their data.
  field_attach_form_validate('bmap', $bmap, $form, $form_state);
  if (!is_numeric($form_state['values']['x'])) {
    form_set_error('x', t('X must be a number.'));
  }
  if (!is_numeric($form_state['values']['y'])) {
    form_set_error('y', t('Y must be a number.'));
  }
}

/**
 * Bmap form submit handler.
 */
function bmap_form_submit($form, &$form_state) {
  $bmap = &$form_state['bmap'];
  $bmap->bid = $form_state['values']['bid'];
  $bmap->x = $form_state['values']['x'];
  $bmap->y = $form_state['values']['y'];
  // Notify field widgets.
  field_attach_submit('bmap', $bmap, $form, $form_state);
  // Save the bmap
  bmap_save($bmap);
  drupal_set_message(t('Bmap saved.'));
  $form_state['redirect'] = 'bmap/'.$bmap->bid;
}

/**
 * Bmap view page.
 */
function bmap_page_view($bmap, $view_mode = 'full') {
  $build = $bmap->view($view_mode);
  if ($view_mode == 'full') {
    $build['bmap'][$bmap->bid]['x'] = array(
      '#markup' => '<div class="field field-type-text field-label-above"><div class="field-label">X:</div><div class="field-items"><div class="field-item even">'.filter_xss($bmap->x).'</div></div></div>',
      '#weight' => -20,
    );
    $build['bmap'][$bmap->bid]['y'] = array(
      '#markup' => '<div class="field field-type-text field-label-above"><div class="field-label">Y:</div><div class="field-items"><div class="field-item even">'.filter_xss($bmap->y).'</div></div></div>',
      '#weight' => -10,
    );
  }
  return $build;
}

/**
 * Bmap edit page.
 */
function bmap_page_edit($bmap) {
  return drupal_get_form('bmap_form', $bmap);
}

/**
 * Bmap form submit handler for the delete button.
 */
function bmap_form_submit_delete($form, &$form_state) {
  $bmap = $form_state['bmap'];
  $form_state['redirect'] = 'bmap/'.$bmap->bid.'/delete';
}

/**
 * Confirm form for deleting a bmap.
 */
function bmap_delete_confirm_form($form, &$form_state, $bmap) {
  $form_state += array('bmap' => $bmap);
  $confirm_question = t('Are you sure you want to delete bmap for X:%x, Y:%y ?', array('%x' => $bmap->x, '%y' => $bmap->y));
  return confirm_form($form, $confirm_question, 'bmap/'.$bmap->bid);
}

/**
 * Bmap delete confirm form submit handler.
 */
function bmap_delete_confirm_form_submit($form, &$form_state) {
  $bmap = $form_state['bmap'];
  $bmap->delete();
  drupal_set_message(t('Delete bmap for X: %x , Y: %y .', array('%x' => $bmap->x, '%y' => $bmap->y)));
  $form_state['redirect'] = 'admin/structure/bmap';
}