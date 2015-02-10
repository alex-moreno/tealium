<?php
/**
 * @file
 * Tealium Module Tests.
 */

/**
 * PHPunit Tealium.
 *
 * To run :
 *
 * phpunit --coverage-clover reports/clover.xml --coverage-html reports/html
 * --log-junit reports/junit.xml -c /www/b2b/releases/20150123124021/profiles/b2bprofile/modules/shared/tealium/phpunit.xml.dist
 *
 * @group Tealium
 */
class TeaiumModuleTest extends \PHPUnit_Framework_TestCase {

  /**
   * Test valid Tealium values.
   *
   * @dataProvider getValidTealiumValues
   */
  public function testValidTealiumValue($value) {
    $result = tealium_is_valid_value($value);
    $this->assertTrue($result);
  }

  /**
   * Test valid Tealium values.
   *
   * @dataProvider getInvalidTealiumValues
   */
  public function testInvalidTealiumValue($value) {
    $result = tealium_is_valid_value($value);
    $this->assertFalse($result);
  }

  /**
   * Valid values for Tealium.
   */
  function getValidTealiumValues() {
    return array(
      array(0),
      array(1),
      array(99999999),
      array("0"),
      array('0'),
      array('front'),
      array('TAGVALUE'),
      array('TAG VALUE WITH SPACES'),
      array('<tags_in_values>'),
    );
  }
  /**
   * Invalid values for Tealium.
   */
  function getInvalidTealiumValues() {
    return array(
      array(NULL),
      array(''),
      array(FALSE),
      array(TRUE),
    );
  }
}