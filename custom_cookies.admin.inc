<?php
/**
 * @file
 * This file provides administration form for the module.
 */

/**
 * Provides form for cookie control popup.
 */
function custom_cookies_admin_form($form_state) {

  global $language;
  $ln = $language->language;
  $popup_settings = custom_cookies_get_settings();
  $form['custom_cookies_' . $ln] = array (
    '#type'  => 'item',
    '#tree'   => TRUE,
  );

  if (module_exists('locale')) {
    $form['custom_cookies_' . $ln]['#title'] = t('Editing settings for the %language language.', array('%language' => $language->name));
  }

  $form['custom_cookies_' . $ln]['popup_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable popup'),
    '#default_value' => isset($popup_settings['popup_enabled']) ? $popup_settings['popup_enabled'] : 0,
  );

  if (module_exists('geoip')){
    $form['custom_cookies_' . $ln]['eu_only'] = array(
      '#type' => 'checkbox',
      '#title' => t('Only display popup in EU countries (using the <a href="http://drupal.org/project/geoip">geoip</a> module)'),
      '#default_value' => isset($popup_settings['eu_only']) ? $popup_settings['eu_only'] : 0,
    );
  }

  $form['custom_cookies_' . $ln]['popup_position'] = array(
    '#type' => 'checkbox',
    '#title' => t('Place the pop-up at the top of the website'),
    '#default_value' => isset($popup_settings['popup_position']) ? $popup_settings['popup_position'] : 0,
    '#description' => t('By default the pop-up appears at the bottom of the website. Tick this box if you want it to appear at the top'),
  );

  $form['custom_cookies_' . $ln]['popup_info'] = array(
    '#type' => 'text_format',
    '#title' => t('Popup message - requests consent'),
    '#default_value' => isset($popup_settings['popup_info']['value']) ? $popup_settings['popup_info']['value'] : '',
    '#required' => TRUE,
    '#format' => isset($popup_settings['popup_info']['format']) ? $popup_settings['popup_info']['format'] : NULL,
  );

  $form['custom_cookies_' . $ln]['popup_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Privacy policy link'),
    '#default_value' => isset($popup_settings['popup_link']) ? $popup_settings['popup_link'] : '',
    '#size' => 60,
    '#maxlength' => 220,
    '#required' => TRUE,
    '#description' => t('Enter link to your privacy policy or other page that will explain cookies to your users. For external links prepend http://'),
  );

  $form['custom_cookies_' . $ln]['popup_delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Popup time delay in miliseconds'),
    '#default_value' => isset($popup_settings['popup_delay']) ? $popup_settings['popup_delay'] : 500,
    '#size' => 5,
    '#maxlength' => 5,
    '#required' => TRUE,
  );

  $form_color_picker_type = 'textfield';

  $form['custom_cookies_' . $ln]['popup_bg_hex'] = array(
    '#type' => $form_color_picker_type,
    '#title' => t('Background Color'),
    '#default_value' => isset($popup_settings['popup_bg_hex']) ? $popup_settings['popup_bg_hex'] : '343434', 
    '#description' => t('Change the background color of the popup. Provide HEX value without the #'),
  );
  
  $form['custom_cookies_' . $ln]['popup_text_hex'] = array(
    '#type' => $form_color_picker_type,
    '#title' => t('Text Color'),
    '#default_value' => isset($popup_settings['popup_text_hex']) ? $popup_settings['popup_text_hex'] : 'ffffff',
    '#description' => t('Change the text color of the popup. Provide HEX value without the #'),
  );

  return system_settings_form($form);
}

/**
 * Validates form for cookie controll popup.
 */
function custom_cookies_admin_form_validate($form, &$form_state) {
  global $language;
  $ln = $language-> language;
  if (!preg_match('/^[1-9][0-9]{0,4}$/', $form_state['values']['custom_cookies_' . $ln]['popup_delay'])) {
    form_set_error('custom_cookies_popup_delay', t('Delay must be an integer value.'));
  }
}
