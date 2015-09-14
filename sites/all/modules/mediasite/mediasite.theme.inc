<?php

/**
 * @file
 * Implements Mediasite theme functions.
 */

/**
 * Produces finished markup ready for inserting on the page.
 *
 * @param string $id
 *   A resource id.
 *
 * @param array $options
 *   An array of options.
 *   
 * @return string
 *   An HTML string that generates the output
 *   
 * @ingroup themeable
 */
function theme_mediasite_embed($options = array()) {
  $output = '';
  $server_root['root'] = variable_get('mediasite_server_root', '');
  $server_root['player'] = '/Viewer';
  
  // allow other modules to alter options
  drupal_alter('mediasite_options', $options);
  
  // check options
  if (empty($options['id'])) {
    return $output;
  }
  
  // build query
  $query = array(
    'peid' => $options['id'],
    'autoStart' => $options['autostart'],
    'viewerid' => $options['viewerid'],
    'w' => $options['width'],
    'h' => $options['height'],
    'username' => $options['username'],
  );
  
  // use defaults
  if (empty($query['viewerid'])) {
    $query['viewerid'] = variable_get('mediasite_default_viewer', '');
  }
  if (!is_numeric($query['w'])) {
    $query['w'] = variable_get('mediasite_default_width', '');
  }
  if (!is_numeric($query['h'])) {
    $query['h'] = variable_get('mediasite_default_height', '');
  }
  
  // determine if we should use html5
  if (module_exists('wurfl') && wurfl_devicecapability('html_preferred_dtd') == 'html5') {
    $query['html5'] = 'true';
  }
  
  // allow other modules to alter the query
  drupal_alter('mediasite_query', $query, $options);
  
  // get authentication ticket
  if ($options['auth'] != 'false') {
    $auth_ticket = mediasite_authentication_ticket($query['peid'], $query['username']);
    if ($auth_ticket) {
      $query['authTicket'] = $auth_ticket;
    }
  }
  
  // override server root
  if (!empty($options['host'])) {
    $server_root['root'] = $options['host'];
  }
  
  // allow other modules to alter root and player
  drupal_alter('mediasite_root', $server_root, $options);
  
  // check for thumbnail images
  $thumbnail = mediasite_thumbnail_image($query['peid']);
  
  // add placeholder image
  if (!empty($thumbnail['src']) && $options['useplaceholder'] == 'true') {
    drupal_add_js(drupal_get_path('module', 'mediasite') . '/mediasite.js');
    
    // build source string
    $query['mediasite_root'] = $server_root['root'];
    $query['mediasite_player'] = $server_root['player'];
    $src = '/mediasite-get-auth-ticket?' . http_build_query($query);
    
    $output = "<img height='" . $query['h'] . "' width='" . $query['w'] . "' rel='" . $src . "' src='" . $thumbnail['src'] . "' alt='" . $thumbnail['alt'] . "' class='mediasite-placeholder' />";
  }
  else {
    if (!empty($query['authTicket'])) {
      $GLOBALS['conf']['cache'] = FALSE;
    }
    
    // build source string
    $src = $server_root['root'] . $server_root['player'] . '?' . http_build_query($query);
    
    $output = "<iframe frameborder='0' height='" . $query['h'] . "' width='" . $query['w'] . "' src='" . $src . "' style='border: 0 none; background: white;'></iframe>";
  }
  
  return $output;
}