<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying edit links
 * as fields
 */


class bmap_handler_edit_link_field extends bmap_handler_link_field {
  
  function construct() {
    parent::construct();
  }

  function render($values) {
    // Check access
    if (!user_access('edit bmap')) {
      return;
    }
    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    $bid = $values->{$this->aliases['bid']};
    return l($text, 'bmap/' . $bid . '/edit');
  }
}
