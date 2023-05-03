<?php
header('Access-Control-Allow-Origin: *');

$dsn = 'mysql:dbname=iot;host=localhost';
$user = 'root';
$password = '';

$bdd = new PDO($dsn, $user, $password);
$request = "INSERT INTO `toto` (`id`, `distance`) VALUES (NULL, '2')";

$bdd->query($request);