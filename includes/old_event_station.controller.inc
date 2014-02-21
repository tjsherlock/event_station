<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 * EntityExampleBasicControllerInterface definition.
 *
 * We create an interface here because anyone could come along and
 * use hook_entity_info_alter() to change our controller class.
 * We want to let them know what methods our class needs in order
 * to function with the rest of the module, so here's a handy list.
 *
 * @see hook_entity_info_alter()
 */

interface EventStationControllerInterface
  extends DrupalEntityControllerInterface {
  public function create();
  public function save($entity);
  public function delete($entity);
}


class EventStationController extends EntityAPIController //DrupalDefaultEntityController
implements EventStationControllerInterface {
    
    
  
    
    
    public function create() {
        $entity = new stdClass();
        $entity->type = 'event_station';
        $entity->esid = 0;
        $entity->is_new = 1;// tjs 2013Dec10
        $entity->bundle_type = 'event_station';// tjs 2013Dec23 was even_station_bundle
        $entity->title = '';
        $entity->description = '';
        $entity->event = '';
        $entity->spots = 0;//array
        $entity->volunteers = array();
        $entity->weight = 0;
        $entity->owner = 0;
        $entity->status = TRUE;
        $entity->visibility = TRUE;
        $entity->created = NULL;
        $entity->changed = NULL;
        return $entity;
    }
    
    
    
    /*public function save($eventstation) {
        drupal_write_record('event_station', $eventstation);
        field_attach_insert('event_station', $eventstation);
        module_invoke_all('entity_insert', 'event_station', $eventstation);
        return $eventstation;
    }*/
    
    
    
     /**
   * Saves the custom fields using drupal_write_record()
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    // If our entity has no basic_id, then we need to give it a
    // time of creation.
    /*if (empty($entity->esid)) {
      $entity->created = time();
    }*/
    
     if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;
    }
    
    $entity->changed = REQUEST_TIME;
    //return parent::save($entity, $transaction);
    
    
    // Invoke hook_entity_presave().
    module_invoke_all('event_station_presave', $entity, 'event_station');
    // The 'primary_keys' argument determines whether this will be an insert
    // or an update. So if the entity already has an ID, we'll specify
    // basic_id as the key.
    
    if(isset($entity->esid)){
        $exists = 'exists';
    }
    else{
        $doesnt_exit = 'doesnt exist';
    }
    
    $primary_keys = (isset($entity->esid) ? 'esid' : array());
    // Write out the entity record.
    drupal_write_record('event_station', $entity, $primary_keys);
    // We're going to invoke either hook_entity_update() or
    // hook_entity_insert(), depending on whether or not this is a
    // new entity. We'll just store the name of hook_entity_insert()
    // and change it if we need to.
    $invocation = 'event_station_insert';
    // Now we need to either insert or update the fields which are
    // attached to this entity. We use the same primary_keys logic
    // to determine whether to update or insert, and which hook we
    // need to invoke.
    if (empty($primary_keys)) {
      field_attach_insert('event_station', $entity);
    }
    else {
      field_attach_update('event_station', $entity);
      $invocation = 'event_station_update';
    }
    // Invoke either hook_entity_update() or hook_entity_insert().
    module_invoke_all($invocation, $entity, 'event_station');
    return $entity;
  }
  
  
  
  /**
   * Override the save method.
   */
 /* public function save($entity, DatabaseTransaction $transaction = NULL) {
    if (isset($entity->is_new)) {
      $entity->created = REQUEST_TIME;
    }

    $entity->changed = REQUEST_TIME;
    return parent::save($entity, $transaction);
  }*/

  /**
   * Delete a single entity.
   *
   * Really a convenience function for delete_multiple().
   */
  public function delete($entity) {
    $this->delete_multiple(array($entity));
  }

  /**
   * Delete one or more entity_example_basic entities.
   *
   * Deletion is unfortunately not supported in the base
   * DrupalDefaultEntityController class.
   *
   * @param $basic_ids
   *   An array of entity IDs or a single numeric ID.
   */
  public function delete_multiple($entities) {
    $esids = array();
    if (!empty($entities)) {
      $transaction = db_transaction();
      try {
        foreach ($entities as $entity) {
          // Invoke hook_entity_delete().
          module_invoke_all('event_station_delete', $entity, 'event_station');
          field_attach_delete('event_station', $entity);
          $esids[] = $entity->basic_id;
        }
        db_delete('event_station')
          ->condition('esid', $esids, 'IN')
          ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('event_station', $e);
        throw $e;
      }
    }
  }
  
  
  /**
 * @todo implement function
 * 
 */
public function get_default_event_station(){
    
    
}


  /**
   * Overridden.
   * @see DrupalDefaultEntityController#load($ids, $conditions)
   *
   * In contrast to the parent implementation we factor out query execution, so
   * fetching can be further customized easily.
   */
  public function load($ids = array(), $conditions = array()) {
    $entities = array();

    // Revisions are not statically cached, and require a different query to
    // other conditions, so separate the revision id into its own variable.
    if ($this->revisionKey && isset($conditions[$this->revisionKey])) {
      $revision_id = $conditions[$this->revisionKey];
      unset($conditions[$this->revisionKey]);
    }
    else {
      $revision_id = FALSE;
    }

    // Create a new variable which is either a prepared version of the $ids
    // array for later comparison with the entity cache, or FALSE if no $ids
    // were passed. The $ids array is reduced as items are loaded from cache,
    // and we need to know if it's empty for this reason to avoid querying the
    // database when all requested entities are loaded from cache.
    $passed_ids = !empty($ids) ? array_flip($ids) : FALSE;

    // Try to load entities from the static cache.
    if ($this->cache && !$revision_id) {
      $entities = $this->cacheGet($ids, $conditions);
      // If any entities were loaded, remove them from the ids still to load.
      if ($passed_ids) {
        $ids = array_keys(array_diff_key($passed_ids, $entities));
      }
    }

    // Support the entitycache module if activated.
    if (!empty($this->entityInfo['entity cache']) && !$revision_id && $ids && !$conditions) {
      $cached_entities = EntityCacheControllerHelper::entityCacheGet($this, $ids, $conditions);
      // If any entities were loaded, remove them from the ids still to load.
      $ids = array_diff($ids, array_keys($cached_entities));
      $entities += $cached_entities;

      // Add loaded entities to the static cache if we are not loading a
      // revision.
      if ($this->cache && !empty($cached_entities) && !$revision_id) {
        $this->cacheSet($cached_entities);
      }
    }

    // Load any remaining entities from the database. This is the case if $ids
    // is set to FALSE (so we load all entities), if there are any ids left to
    // load or if loading a revision.
    if (!($this->cacheComplete && $ids === FALSE && !$conditions) && ($ids === FALSE || $ids || $revision_id)) {
      $queried_entities = array();
      foreach ($this->query($ids, $conditions, $revision_id) as $record) {
        // Skip entities already retrieved from cache.
        if (isset($entities[$record->{$this->idKey}])) {
          continue;
        }

        // For DB-based entities take care of serialized columns.
        if (!empty($this->entityInfo['base table'])) {
          $schema = drupal_get_schema($this->entityInfo['base table']);

          foreach ($schema['fields'] as $field => $info) {
            if (!empty($info['serialize']) && isset($record->$field)) {
              $record->$field = unserialize($record->$field);
              // Support automatic merging of 'data' fields into the entity.
              if (!empty($info['merge']) && is_array($record->$field)) {
                foreach ($record->$field as $key => $value) {
                  $record->$key = $value;
                }
                unset($record->$field);
              }
            }
          }
        }

        $queried_entities[$record->{$this->idKey}] = $record;
      }
    }

    // Pass all entities loaded from the database through $this->attachLoad(),
    // which attaches fields (if supported by the entity type) and calls the
    // entity type specific load callback, for example hook_node_load().
    if (!empty($queried_entities)) {
      $this->attachLoad($queried_entities, $revision_id);
      $entities += $queried_entities;
    }

    // Entitycache module support: Add entities to the entity cache if we are
    // not loading a revision.
    if (!empty($this->entityInfo['entity cache']) && !empty($queried_entities) && !$revision_id) {
      EntityCacheControllerHelper::entityCacheSet($this, $queried_entities);
    }

    if ($this->cache) {
      // Add entities to the cache if we are not loading a revision.
      if (!empty($queried_entities) && !$revision_id) {
        $this->cacheSet($queried_entities);

        // Remember if we have cached all entities now.
        if (!$conditions && $ids === FALSE) {
          $this->cacheComplete = TRUE;
        }
      }
    }
    // Ensure that the returned array is ordered the same as the original
    // $ids array if this was passed in and remove any invalid ids.
    if ($passed_ids && $passed_ids = array_intersect_key($passed_ids, $entities)) {
      foreach ($passed_ids as $id => $value) {
        $passed_ids[$id] = $entities[$id];
      }
      $entities = $passed_ids;
    }
    return $entities;
  }




  /**
   * Overridden to support passing numeric ids as well as names as $ids.
   */
  /*public function load($ids = array(), $conditions = array()) {
    $entities = array();

    // Only do something if loaded by names.
    if (!$ids || $this->nameKey == $this->idKey || is_numeric(reset($ids))) {
      return parent::load($ids, $conditions);
    }

    // Revisions are not statically cached, and require a different query to
    // other conditions, so separate the revision id into its own variable.
    if ($this->revisionKey && isset($conditions[$this->revisionKey])) {
      $revision_id = $conditions[$this->revisionKey];
      unset($conditions[$this->revisionKey]);
    }
    else {
      $revision_id = FALSE;
    }
    $passed_ids = !empty($ids) ? array_flip($ids) : FALSE;

    // Care about the static cache.
    if ($this->cache && !$revision_id) {
      $entities = $this->cacheGetByName($ids, $conditions);
    }
    // If any entities were loaded, remove them from the ids still to load.
    if ($entities) {
      $ids = array_keys(array_diff_key($passed_ids, $entities));
    }

    $entities_by_id = parent::load($ids, $conditions);
    $entities += entity_key_array_by_property($entities_by_id, $this->nameKey);

    // Ensure that the returned array is keyed by numeric id and ordered the
    // same as the original $ids array and remove any invalid ids.
    $return = array();
    foreach ($passed_ids as $name => $value) {
      if (isset($entities[$name])) {
        $return[$entities[$name]->{$this->idKey}] = $entities[$name];
      }
    }
    return $return;
  }*/

}



