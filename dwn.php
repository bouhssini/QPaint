<?php
$user_db='root';
$passwd_db='Maqraa17rootMaqraa17';
$host_db='localhost';
$db_mysql='maahad_hakiba';
$link = NULL;

$link = mysql_connect($host_db, $user_db, $passwd_db);	

$id_usr = 0;
$id_room = 0;

if (isset($_POST['id_usr']))  $id_usr = (int)$_POST['id_usr'];
if (isset($_POST['id_room']))  $id_room = (int)$_POST['id_room'];


?>