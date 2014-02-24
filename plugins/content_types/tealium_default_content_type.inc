<?php
/**
 * @file
 * CTools content plugin for default data points.
 * This CTools content plugin can be used in journeys which employees
 * panels.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'single' => TRUE,
  'title' => t('Tealium  Data Point form'),
  'category' => t('RMG Tealium'),
  'edit form' => 'tealium_default_content_type_render_content_type_edit_form',
  'render callback' => 'tealium_default_content_type_render',
  'content_types' => 'tealium_default_content_type',
  'description' => t('Renders Tealium data points.'),
  'icon' => 'tealium.icon.png',
  'all contexts' => TRUE,
);

/**
 * Set plugin default Tealium variables.
 */
function tealium_default_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $default_data_points = _rmg_tealium_get_default_data_points_from_context();
  // Add the data points to the conf.
  $conf = array_replace($conf, $default_data_points);

  if (!empty($conf)) {
    foreach ($conf as $key => $value) {
      $value = ctools_context_keyword_substitute($value, array(), $context);
      if (!empty($value) && in_array($key, $default_data_points)) {
        rmg_tealium_tag_notify($key, $value);
      }
    }

    return $block;
  }
}

/**
 * Returns an edit form for custom type settings.
 * @see _rmg_tealium_content_type_render_content_type_edit_form_submit()
 * @ingroup forms
 */
function tealium_default_content_type_render_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $default_data_points = _rmg_tealium_get_default_data_points_from_context();

  if (!empty($default_data_points)) {
    foreach ($default_data_points as $default_data_point) {
      $form[$default_data_point] = array(
        '#type' => 'textfield',
        '#title' => t($default_data_point),
        '#default_value' => isset($conf[$default_data_point]) ? $conf[$default_data_point] : '',
        '#description' => t('Tealium @data_point.', array('@data_point' => $default_data_point)),
      );
    }
  }

  return $form;
}

/**
 * Form submission handler for tealium_default_content_type_render_content_type_edit_form().
 */
function tealium_default_content_type_render_content_type_edit_form_submit(&$form, &$form_state) {
  // Get data points.
  $default_data_points = _rmg_tealium_get_default_data_points_from_context();

  // Map the values.
  if (!empty($default_data_points)) {
    foreach ($default_data_points as $default_data_point) {
      $form_state['conf'][$default_data_point] = $form_state['values'][$default_data_point];
    }
  }
}

/**
 * Tealium Data points for applications.
 *
 * @return array
 *   Return the data points.
 */
function _rmg_tealium_get_default_data_points_from_context() {
  $defined_context_data_points = _rmg_tealium_get_default_data_points();

  if (!empty($defined_context_data_points)) {
    return array_keys($defined_context_data_points);
  }

  return array();
}

/**
 * Tealium Data points for application.
 *
 * @return array
 *   Return the data points
 */
function _rmg_tealium_get_default_data_points() {
  return array(
    'pageName' => t('Custom page name if you need to override the one set site wide.'),
    'pageApplicationName' => t('pageApplicationName Tealium Data point'),
    'pageApplicationStep' => t('pageApplicationStep Tealium Data point'),
    'productName' => t('productName Tealium Data point'),
    'productCategory' => t('productCategory Tealium Data point'),
    'productSubcategory' => t('productSubcategory Tealium Data point'),
    'productPrice' => t('productPrice Tealium Data point'),
    'productQuantity' => t('productQuantity Tealium Data point'),
    'productAttributes' => t('productAttributes Tealium Data point'),
    'pageTemplate' => t('pageTemplate Tealium Data point'),
    'transactionID' => t('transactionID Tealium Data point'),
    'transactionTotal' => t('transactionTotal Tealium Data point'),
    'transactionPaymentType' => t('transactionPaymentType Tealium Data point'),
    'transactionCurrency' => t('transactionCurrency Tealium Data point'),
    'conversionType' => t('Ex: Redelivery'),
    'conversionID' => t('Ex: CLEO Reference Number'),
    'conversionProduct' => t('Conversion product name. Ex: Redelivery'),
    'conversionAttributes' => t('An array of conversion attributes as key value pairs.'),
    'pageErrorType' => t('Type of the error message. Ex: Payment validation. Do not use this to set Form Validation Errors'),
    'pageErrorMessage' => t('Error message. Ex: Payment failed. Do not use this to set Form Validation Errors'),
  );
}
