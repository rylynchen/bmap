<?php

/**
 * @file
 * Administration page for baidu map
 *
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
  return system_settings_form($form);
}