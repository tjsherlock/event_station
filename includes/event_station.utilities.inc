<?php

/**
 * 
 *   Utilities
 * 
 */


/**
 * 
 * 
 * Make sure there is a valid userid  
 * 
 * 
 */
function event_station_userid() {

    global $user;
    
    // The user object may not exist in all conditions, so 0 is substituted if needed.
    return isset($user->uid) ? $user->uid : 0;
}

