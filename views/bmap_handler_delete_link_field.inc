<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */


class bmap_handler_delete_link_field extends bmap_handler_link_field {

  function construct() {
    parent::construct();
  }

  function render($values) {
    // Check access
    if (!user_access('delete bmap')) {
      return;
    }
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $bid = $values->{$this->aliases['bid']};
    return l($text, 'bmap/' . $bid . '/delete');
  }
}
