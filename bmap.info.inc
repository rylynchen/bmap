<?php

/**
 * @file
 * Provides Entity metadata integration.
 */

/**
 * Extend the defaults.
 */
class BmapMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['x'] = array(
      'label' => t('X'),
      'description' => t('The bmap coordinate x.'),
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer bmap',
      'schema field' => 'x',
    );
    $properties['y'] = array(
      'label' => t('Y'),
      'description' => t('The bmap coordinate y.'),
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer bmap',
      'schema field' => 'y',
    );
    return $info;
  }
}