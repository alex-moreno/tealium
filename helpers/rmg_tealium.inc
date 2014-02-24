<?php
/**
 * @file
 * Helper functions to notify about Tealium tags and and retrieve the tag cloud.
 */
/**
 * Function that will be used to set Tealium Tags when they are fired.
 *
 * @param string $tealium_tag_key
 *   Tealium tag key. Ex: s.events
 *
 * @param string $tealium_tag_value
 *   Tealium Tag value.
 *
 * @param bool $merge
 *   Merge Value if exist.
 *
 * @param bool $is_session_based
 *   Set a flag so that will be returned on the tag cloud through out the
 *   session. Default will be boolean FALSE and the tag will return only on a
 *   request.
 *
 * @return void
 *   Does not return anything.
 */
function rmg_tealium_tag_notify($tealium_tag_key, $tealium_tag_value, $merge = FALSE, $is_session_based = FALSE) {
  // This is for the modules that sets json encoded strings on panels.
  if (is_array($tealium_tag_value) == FALSE) {
    $tealium_tag_value = (_rmg_tealium_is_json($tealium_tag_value)) ? json_decode($tealium_tag_value, TRUE) : trim($tealium_tag_value);
  }

  if(isset($tealium_tag_key) && isset($tealium_tag_value) && !empty($tealium_tag_key) && !empty($tealium_tag_value)){
    rmg_tealium_set_tag($tealium_tag_key, $tealium_tag_value);
  }

}

/**
 * Simple function to check whether a given string is JSON encoded.
 *
 * @param string $string
 *   String to check.
 *
 * @return bool
 *   Return whether it is a JSON endoded object or not.
 */
function _rmg_tealium_is_json($string) {
  json_decode($string);
  return (json_last_error() == JSON_ERROR_NONE);
}