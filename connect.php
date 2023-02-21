<?php
	//$connection = mysqli_connect(hostname,username,password,database_name);
	$connection = mysqli_connect("localhost","root","","waterquality");

	if (!$connection)
		die('MySQL ERROR: ' . mysqli_connect_error());
	
?>
