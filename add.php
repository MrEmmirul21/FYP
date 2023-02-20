<?php
	include("connect.php");

	$temperature = $_POST["temperature"];
	$turbididty = $_POST["turbidity"];
	$acidity = $_POST["acidity"];
	$hash = $_POST["hash"];
	
	$sql = "INSERT INTO 'sensorreadings' ('temperature','turbidity','acidity','hash') VALUES ('$temperature','$turbididty','$acidity',.$hash')";
	echo "\nQuery: ".$sql;

	if (mysqli_query($connection, $sql))
		echo "Sensor readings  successfully";
	
	else 
		echo "\nError: ".mysqli_error($connection);

	mysqli_close($connection);
?>