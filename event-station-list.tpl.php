<?php
/**
 * @file
 * Default implementation of an event station
 * 
 * Available variables:
 * -$name: the name of the event station
 * -$description: the description of the event station
 * -$esid: the identifier of the event station
 * -$event: the event associated with the event
 * -$guides: participants managing the event station
 * -$spots:  availability, available spots on the event station for managing participants
 * @todo  (loop to collect all fields?)
 * -$fields: fields added to the entity
 * 
 *  @see template_preprocess()
 *  @see template_process()
*/
?>
<div class='event-station-list'>
  <div class='event-station-list-label'></div>  
  

<?php if ($event_stations): ?>
  <?php  foreach ($event_stations as $event_station): ?>
  
<div class='event-station'> 
  <div class='event-station-label'></div> 
    <div class='event-station-name'> 
      <div class='event-station-name-label'></div> 
        <div class='event-station-name-value'>
      <?php if ($event_station['name']): ?>          
          <p>
          <strong><?php print $event_station['name']; ?></strong>
          </p>
      <?php endif;//$event_station['name'] ?>          
        </div>
    </div>
    <div class='event-station-description'> 
      <div class='event-station-description-label'></div>
      <div class='event-station-description-value'>
      <?php if ($event_station['description']): ?>        
        <p>
        <?php print $event_station['description']; ?>
        </p>
      <?php endif;//$event_station['description'] ?>        
      </div>
    </div>
    <div class='event-station-id'> 
      <div class='event-station-id-label'></div>
      <div class='event-station-id-value'>
      <?php if ($event_station['esid']): ?>        
        <p>
        <?php print $event_station['esid']; ?>          
        </p>
      <?php endif;//$event_station['esid'] ?>         
      </div>  
    </div>        
    <div class='event-station-event'> 
      <div class='event-station-event-label'></div>
            <div class='event-station-event-value'>
      <?php if ($event_station['event']): ?>              
              <p>
                <?php print $event_station['event']; ?>
              </p>
      <?php endif;//$event_station['event'] ?>              
           </div>
    </div>        
    <div class='event-station-guides'> 
      <div class='event-station-guides-label'></div>
      <div class='event-station-guides-value'>    
      <?php if ($event_station['guides']): ?>
             <p>
            <?php print $event_station['guides']; ?>
            </p>
      <?php endif;//$event_station['guides'] ?>
      </div> 
    </div>
    <div class='event-station-spots'> 
      <div class='event-station-spots-label'></div>
        <div class='event-station-spots-value'>
      <?php if ($event_station['spots']): ?>          
          <p>      
            <?php print $event_station['spots']; ?>
          </p>
     <?php endif;//$event_station['spots'] ?>          
      </div>
    </div>       
</div> <?php //event-station ?>      
    <?php endforeach;////$event_station ?>
 <?php endif;//$event_station ?>

</div>