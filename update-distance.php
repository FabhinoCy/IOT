<?php
header('Access-Control-Allow-Origin: *');

$dsn = 'mysql:dbname=XXXXX;host=localhost';
$user = 'XXXXXX';
$password = 'XXXXXX';

$distance = $_POST['distance'];
$distance = filter_var($distance, FILTER_SANITIZE_STRING);

$instant = $_POST['instant'];

$bdd = new PDO($dsn, $user, $password);

if ($instant == 'true') {
    if ($distance === null) {
        return;
    }
    $request = "UPDATE `iot-final` SET `distance` = '$distance', `created_at` = NOW() WHERE `iot-final`.`id` = 1";
} else {
    $request = "INSERT INTO `iot-final` (`id`, `distance`, `created_at`) VALUES (NULL, '$distance', NOW())";
}

$bdd->query($request);
