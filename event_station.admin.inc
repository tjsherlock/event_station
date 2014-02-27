<?php
/**
 * @file
 * Admin pages for videoentity.module.
 */

/**
 * Form for adding or editing a video entity.
 */
function event_station_form($form, &$form_state, $EventStation, $op = 'edit') {
    
  $form['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#default_value' => isset($EventStation->name) ? $EventStation->name : '',
    '#description' => t('Event Station title.'),
    '#required' => TRUE,
    '#weight' => -50,
  );

  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#description' => t('Description of the event station.'),
    '#default_value' => isset($EventStation->description) ? $EventStation->description : '',
    '#required' => TRUE,
    '#weight' => -40,
  );
  
    $form['spots'] = array(
      '#title' => t('Spots'),
      '#type' => 'textfield',
      '#description' => t('Spots available in the event station.'),
      '#default_value' => isset($EventStation->spots) ? $EventStation->spots : 1,
      '#weight' => -30,
  );
    
    $form['guides'] = array(
    '#title' => t('Guides'),
    '#type' => 'textfield',
    '#description' => t('Name of the guiding event participants.'),
    //'#default_value' => isset($EventStation->owner) ? $EventStation->owner : array('%name' => $account->name),
    '#default_value' => isset($EventStation->guides) ? $EventStation->guides : array(''),
    //'#autocomplete_path' => 'owner/autocomplete',
    '#weight' => -10,
  );

    //@todo: this should be a $user->name or $account->name.  Perhaps use autocomplete
     $form['owner'] = array(
    '#title' => t('Owner'),
    '#type' => 'textfield',
    '#description' => t('The user responsible for managing the station.  Initially, this is the station creator.'),
    //'#default_value' => isset($EventStation->owner) ? $EventStation->owner : array('%name' => $account->name),
    '#default_value' => isset($EventStation->owner) ? $EventStation->owner : event_station_accountname(),
    //'#autocomplete_path' => 'owner/autocomplete',
    '#weight' => -10,
  );
  $form['status'] = array(
    '#title' => t('This station is open.'),
    '#type' => 'checkbox',
    '#description' => t('Determines whether station is open or closed for registration.'),
    '#default_value' => isset($EventStation->status) ? $EventStation->status : '',    
    '#weight' => -8,
  );
  $form['visibility'] = array(
    '#title' => t('This station is visible.'),
    '#type' => 'checkbox',
    '#description' => t('Determines whether station is visible to registration users.'),
    '#default_value' => isset($EventStation->visibility) ? $EventStation->visibility : '',     
    '#weight' => -6,
  );
  $form['weight'] = array(
  '#type' => 'weight', 
  '#title' => t('Weight'), 
  '#default_value' => isset($EventStation->weight) ? $EventStation->weight : 0, 
  '#delta' => 10, 
  '#description' => t('Optional.  the heavier stations (e.g. 10) will sink to the bottom and the lighter stations (e.g. -10) will float to the top.'),
  '#weight' => -4,
    );
  
  field_attach_form('event_station', $EventStation, $form, $form_state);// inform entity controller of fields
    
  //not sure why 'EventStationAsset'
  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => isset($EventStationAsset->esid) ? t('Update event station asset') : t('Save event station asset'),
    ),
  );
  
  return $form;
}

/**
 * Validation form entity add/edit form.
 */
function event_station_form_validate($form, &$form_state) {
  if (isset($form_state['values']['spots']) && !is_numeric($form_state['values']['spots'])) {
    form_set_error('spots', t('Spots field must be an integer value.'));
  }
}

/**
 * Submit handler for entity add/edit form.
 */
function event_station_form_submit($form, &$form_state) {
  $EventStation = entity_ui_form_submit_build_entity($form, $form_state);
  $EventStation->save();
  drupal_set_message(t('@name event station has been saved.', array('@name' => $EventStation->name)));
  $form_state['redirect'] = 'admin/event_station';
}



/**
 * 
 *   Utilities
 * 
 */


/**
 * 
 * 
 * Make sure there is a valid userid  
 * 
 * 
 */
function event_station_accountname() {

    global $user;
    
    // The user object may not exist in all conditions, so 0 is substituted if needed.
    return isset($user->name) ? $user->name : 0;
}