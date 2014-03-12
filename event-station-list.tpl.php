<?php
/**
 * @file
 * Default implementation of an event station
 * 
 * Available variables:
 * -$name: the name of the event station
 * -$description
 * -$esid
 * -$event
 * -$guides
 * -$spots:  (availability)
 * -$fields:  (loop to collect all fields?)
 * 
 *  @see template_preprocess()
 *  @see template_process()
*/
?>
<div class="event-station-list">
  <div class="event-station-list-label"></div>  
  

<?php if ($event_stations): ?>
  <?php  foreach ($event_stations as $event_station): ?>
  
<div class="event-station"> 
  <div class="event-station-label"></div> 
    <div class="event-station-name"> 
      <div class="event-station-name-label"></div> 
      <p>
      <strong><?php print $event_station['name']; ?></strong>
      </p>  
    </div>
    <div class="event-station-description"> 
      <div class="event-station-description-label"></div>  
        <p>
        <?php print $event_station['description']; ?>
        </p> 
    </div>
    <div class="event-station-id"> 
      <div class="event-station-id-label"></div>

        <p>
        <?php print $event_station['esid']; ?>
        </p>
    </div>        
    <div class="event-station-event"> 
      <div class="event-station-event-label"></div>
        <p>
          <?php print $event_station['event']; ?>
        </p>
    </div>        
    <div class="event-station-guides"> 
      <div class="event-station-guides-label"></div>
      
      <?php if ($event_station['guides']): ?>
         <?php foreach ($event_station['guides'] as $guide): ?>
        <p>
            <?php print $guide; ?>
        </p>
        <?php endforeach;//$event_station['guides'] ?>
      <?php endif;//$event_station['guides'] ?>
    </div>
    <div class="event-station-spots"> 
      <div class="event-station-spots-label"></div>
      <p>      
        <?php print $event_station['spots']; ?>
      </p>
    </div>       
</div> <?php //event-station ?>      
    <?php endforeach;////$event_station ?>
 <?php endif;//$event_station ?>

</div>