<?php

/**
 * @file
 * Configuration settings for Mediasite.
 */
 
/**
 * Returns a form definition for the admin settings page.
 */
function mediasite_admin_settings_form($form_state) {
  $form['mediasite_server_root'] = array(
    '#type' => 'textfield',
    '#title' => t('Mediasite Server Root'),
    '#default_value' => variable_get('mediasite_server_root', ''),
    '#maxlength' => 255,
    '#description' => t('The URL of the mediasite root'),
    '#required' => TRUE,
  );
  
  $form['mediasite_services_api_loication'] = array(
    '#type' => 'textfield',
    '#title' => t('Mediasite Services/API Location'),
    '#default_value' => variable_get('mediasite_services_api_loication', ''),
    '#maxlength' => 255,
    '#description' => t('The URL of the services/api location.'),
    '#required' => TRUE,
  );
  
  $form['mediasite_ticket_lifetime'] = array(
    '#type' => 'textfield',
    '#title' => t('Ticket Lifetime'),
    '#default_value' => variable_get('mediasite_ticket_lifetime', 30),
    '#field_suffix' => ' minutes',
    '#maxlength' => 255,
    '#description' => t('How long to keep a ticket'),
    '#required' => TRUE,
  );
  
  $form['mediasite_default_viewer'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Viewer'),
    '#default_value' => variable_get('mediasite_default_viewer', ''),
    '#maxlength' => 255,
    '#description' => t('Mediasite Viewer ID to use if no viewerid specified'),
    '#required' => TRUE,
  );
  
  $form['mediasite_default_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Width'),
    '#default_value' => variable_get('mediasite_default_width', 650),
    '#maxlength' => 255,
    '#description' => t('Mediasite Width to use if no width specified'),
    '#required' => TRUE,
  );
  
  $form['mediasite_default_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Height'),
    '#default_value' => variable_get('mediasite_default_height', 500),
    '#maxlength' => 255,
    '#description' => t('Mediasite Height to use if no height specified'),
    '#required' => TRUE,
  );
  
  $form['mediasite_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Mediasite User Name'),
    '#default_value' => variable_get('mediasite_user', ''),
    '#maxlength' => 255,
    '#description' => t('The admin user for mediasite'),
    '#required' => TRUE,
  );
  
  $form['mediasite_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Mediasite Password'),
    '#default_value' => '',
    '#maxlength' => 255,
    '#description' => t('The admin password for mediasite'),
/*     '#required' => TRUE, */
  );
  
  $form['mediasite_version'] = array(
    '#type' => 'select',
    '#title' => t('Mediasite Server Version'),
    '#default_value' => variable_get('mediasite_version', 5),
    '#options' => array(
      6 => '6.0',
      5 => '5.5',
    ),
    '#required' => TRUE,
  );
  
  $form['#submit'][] = 'mediasite_admin_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Admin Settings Submit Function.
 */
function mediasite_admin_settings_form_submit($form, &$form_state) {
  if (empty($form_state['values']['mediasite_password'])) {
    $form_state['values']['mediasite_password'] = variable_get('mediasite_password', '');
  }
}