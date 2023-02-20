<?php
	$connection = mysqli_connect("localhost","root","","waterquality");

	if (!$connection)
		die('MySQL ERROR: ' . mysqli_connect_error());
	
	else 
		echo "Database connection succesfully <br/>";
?>