<?php

/**
 * @file File with the Class definition FlagDrupalToolKit.
 */

/**
 * Contains several methods to be used with Flag module.
 *
 * @package em_drupal_toolkit
 */
class FlagDrupalToolKit {

  /**
   * Give the users that has flagged a entity. This is a wrapper of
   * flag_get_entity_flags
   *
   * @param  string $entity_type The type of entity that will be checked for users.       Usually 'node'
   * @param  int $entity_id Entity Id that we're checking.
   * @param  string $flag_name   Flag type.
   * @return [type]              [description]
   */
  public static function getUsersFlaggedContent($entity_type, $entity_id,
    $flag_name = NULL) {

    $users_flagged = array();
    // Flag module isn't a dependency, we've to be sure that it's enabled.
    if (module_exists('flag')) {
      $users_flagged = flag_get_entity_flags($entity_type, $entity_id, $flag_name);
    }

    return $users_flagged;
  }

  /**
   * Retrieve the number of people that a user given is following
   *
   * @param  int $uid User uid that flagged the content
   * @return int Count of entities flaged by a user.
   */
  public static function getFollowingCount($uid) {
    //Get the fid for follow_user machine name
    $query = db_select('flag', 'f');
    $query->fields('f', array('fid'));
    $query->condition('name', 'follow_user');
    $fid = $query->execute()->fetchField(0);

    $query = db_select('flagging', 'f');
    $query->fields('f', array('flagging_id'));
    $query->condition('fid', $fid);
    $query->condition('uid', $uid);

    $count = $query->execute()->rowCount();

    return $count;
  }

  /**
   * Return the number of users that flaged a entity
   *
   * @param  int $uid User id that is flagged.
   * @return int Count of users that flaged a content.
   */
  public static function getFollowersCount($uid) {
    //Get the fid for follow_user machine name
    $query = db_select('flag', 'f');
    $query->fields('f', array('fid'));
    $query->condition('name', 'follow_user');
    $fid = $query->execute()->fetchField(0);

    $query = db_select('flagging', 'f');
    $query->fields('f', array('flagging_id'));
    $query->condition('fid', $fid);
    $query->condition('entity_id', $uid);

    $count = $query->execute()->rowCount();

    return $count;
  }

}

