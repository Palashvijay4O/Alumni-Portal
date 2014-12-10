<?php
/**
 * @file
 * Field validation unique validator.
 *
 */
$plugin = array(
  'label' => t('Unique values'),
  'description' => t('Verifies that all values are unique in current entity or bundle.'),
  'handler' => array(
    'class' => 'field_validation_unique_validator',
  ),
);

class field_validation_unique_validator extends field_validation_validator {

  /**
   * Validate field. 
   */
  public function validate() {
    $flag = TRUE;
    $scope = $this->rule->settings['data'];
    $count = 0;
    foreach ($this->items as $delta1 => $item1) {
      if ($this->delta != $delta1) {
        if ($this->value == $item1[$this->rule->col]) {
          $flag = FALSE;
          break;
        }
      }
    }
    if ($flag) {
      $query = new EntityFieldQuery();
      if ($scope == 'global') {
      }
      elseif ($scope == 'entity') {
        $query->entityCondition('entity_type', $this->rule->entity_type);
      }
      elseif ($scope == 'bundle') {
        $query->entityCondition('entity_type', $this->rule->entity_type);
        $query->entityCondition('bundle', $this->rule->bundle);
      }

      list($id, $vid, $bundle) = entity_extract_ids($this->rule->entity_type, $this->entity);
      if ($this->rule->entity_type == 'user' && arg(0) =='user' && arg(2) =='edit' && empty($id)) {
        $id = arg(1);
      }
      if ($this->rule->entity_type == 'field_collection_item' && arg(0) == 'field-collection' && arg(3) =='edit' && empty($id)) {
        $id = arg(2); 
      }
      if (!empty($id)) {
        $query->entityCondition('entity_id', $id, '!=');
      }
      //Always bypass all access checkings.
      $query->addMetaData('account', user_load(1));
      $count = $query->fieldCondition($this->rule->field_name, $this->rule->col, $this->value)
        ->count()
        ->execute();
      if ($count) {
        $flag = FALSE;
      }

    }

    if (!$flag) {
      $token = array(
        '[count]' => $count,
      );
      $this->set_error($token);
    }
  }
  
  /**
   * Provide settings option
   */
  function settings_form(&$form, &$form_state) {
    $default_settings = $this->get_default_settings($form, $form_state);
    //print debug($default_settings);
    $form['settings']['data'] = array(
      '#title' => t('Scope of unique'),
      '#description' => t("Specify the scope of unique values, support: global, entity, bundle."),
      '#type' => 'select',
      '#options' => array(
        'global' => t('Global'),
        'entity' => t('Entity'),
        'bundle' => t('Bundle'),
      ),  
      '#default_value' => isset($default_settings['data']) ? $default_settings['data'] : '',
    );
    parent::settings_form($form, $form_state);
  }
  
  /**
   * Provide token help info for error message.
   */
  public function token_help() {
    $token_help = parent::token_help();
    $token_help += array(
      '[count]' => t('Count of duplicate'),
    );
    return $token_help;
  }
}