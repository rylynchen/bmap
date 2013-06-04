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
  // $build['#markup'] = views_embed_view('bmaps', 'default');
  $view = views_get_view('bmaps', 'default');
  $view->override_url = $_GET['q'];
  return $view->preview();
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