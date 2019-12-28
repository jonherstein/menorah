<?php

// Get the contents of the JSON file 
$strJsonFileContents = file_get_contents("chanukah.json");
$array = json_decode($strJsonFileContents, true);

if(time()<strtotime($array["1"]))
    echo "0";
if(time()>=strtotime($array["1"]) and time()<strtotime($array["2"]))
    echo "1";
if(time()>=strtotime($array["2"]) and time()<strtotime($array["3"]))
    echo "2";
if(time()>=strtotime($array["3"]) and time()<strtotime($array["4"]))
    echo "3";
if(time()>=strtotime($array["4"]) and time()<strtotime($array["5"]))
    echo "4";
if(time()>=strtotime($array["5"]) and time()<strtotime($array["6"]))
    echo "5";
if(time()>=strtotime($array["6"]) and time()<strtotime($array["7"]))
    echo "6";
if(time()>=strtotime($array["7"]) and time()<strtotime($array["8"]))
    echo "7";
if(time()>=strtotime($array["8"]))
    echo "8";

?>
