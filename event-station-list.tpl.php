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

          <div class="event-station-header">
          <?php if ($event_station['name']): ?>
          <div class='event-station-name'> 
              <div class='event-station-name-label'></div> 
              <div class='event-station-name-value'>
                    <?php print $event_station['name']; ?>
              </div>
          </div>
          <?php endif;//$event_station['name'] ?>
            
            
          <?php if ($event_station['spots']): ?>
            <div class='event-station-spots'> 

            <div class='event-station-spots-label'>Available Positions:  

            </div>
                <div class='event-station-spots-value'>
                  <?php print $event_station['spots']; ?>
                </div>
          </div>
          <?php endif;//$event_station['spots'] ?>   
              
          </div><?php //event-station-header ?>

          
          <div class="event-station-body">
          <?php if ($event_station['description']): ?>
          <div class='event-station-description'> 
            <div class='event-station-description-label'></div>
            <div class='event-station-description-value'>
              <?php print $event_station['description']; ?> 
            </div>
          </div>
          <?php endif;//$event_station['description'] ?>




          <?php if ($event_station['guides']): ?>
          <div class='event-station-guides'> 
           <div class='event-station-guides-label'> Guides  </div>
            <div class='event-station-guides-value'>

                
                  <?php print $event_station['guides']; ?>
            </div> 
          </div>
          <?php endif;//$event_station['guides'] ?>    


          </div><?php //event-station-body ?>

          <div class="event-station-footer">
            
          <?php if ($event_station['event']): ?>
          <div class='event-station-event'> 
            <div class='event-station-event-label'>Event:  
 
           </div>
                 <div class='event-station-event-value'>
                      <?php print $event_station['event']; ?> 
                 </div>            
          </div>
          <?php endif;//$event_station['event'] ?> 
            
           <div class="event-station-subfooter">   
            <?php if ($event_station['esid']): ?>
            <div class='event-station-id'> 
              <div class='event-station-id-label'> Id:  </div>
              <div class='event-station-id-value'>
                <?php print $event_station['esid']; ?>          
              </div>  
            </div> 
             <?php endif;//$event_station['esid'] ?>

            <div class="event-station-dates">  
              <?php if ($event_station['created']): ?>
              <div class='event-station-created'> 
                <div class='event-station-created-label'> Created:  </div> 
                  <div class='event-station-created-value'>
                    <?php print $event_station['created']; ?>
                  </div>
              </div>
              <?php endif;//$event_station['name'] ?>

              <?php if ($event_station['changed']): ?>  
              <div class='event-station-changed'> 
                <div class='event-station-changed-label'> Updated:  </div> 
                  <div class='event-station-changed-value'>   
                    <?php print $event_station['changed']; ?>
                  </div>
              </div>
              <?php endif;//$event_station['name'] ?>
            </div> <?php //event-station-dates ?>
           </div> <?php //event-station-subfooter ?>  
          </div><?php //event-station-footer ?>
      </div> <?php //event-station ?> 
  
    <?php endforeach;////$event_station ?>
 <?php endif;//$event_station ?>

</div>