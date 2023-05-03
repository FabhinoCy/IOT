<?php

header('Access-Control-Allow-Origin: *');

$dsn = 'mysql:dbname=mmi20d07;host=localhost';
$user = 'mmi20d07';
$password = 'Password52$';

$bdd = new PDO($dsn, $user, $password);
$request = "SELECT * FROM iot where name='iot'";
$query = $bdd->query($request);

$result = $query->fetchAll();
$state = $result[0]['state'];

if ($state == 1) {
    $request = "UPDATE `iot` SET `state` = 0 WHERE `name` = 'laser'";
} else {
    $request = "UPDATE `iot` SET `state` = 1 WHERE `name` = 'laser'";
}

$bdd->query($request);
