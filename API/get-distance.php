<?php
header('Access-Control-Allow-Origin: *');

$dsn = 'mysql:dbname=XXXXX;host=localhost';
$user = 'XXXXX';
$password = 'XXXXX';

$bdd = new PDO($dsn, $user, $password);

$request = "SELECT * FROM `iot-final`";
$query = $bdd->query($request);
$result = $query->fetchAll(PDO::FETCH_ASSOC);

echo json_encode($result);