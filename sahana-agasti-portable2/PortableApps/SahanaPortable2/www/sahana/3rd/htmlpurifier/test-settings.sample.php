<?php

// ATTENTION! DO NOT EDIT THIS FILE!
// This file is necessary to run the unit tests and profiling scripts.
// Please copy it to 'test-settings.php' and make the necessary edits.

// Some of these scripts run a long time, so it is recommended that you
// turn off the time limit
set_time_limit(0);

// Turning off output buffering will prevent mysterious errors from core dumps
@ob_end_flush();

// Where is SimpleTest located?
$simpletest_location = '/path/to/simpletest/';

// How many times should profiling scripts iterate over the function? More runs 
// means more accurate results, but they'll take longer to perform.
$GLOBALS['HTMLPurifierTest']['Runs'] = 2;

