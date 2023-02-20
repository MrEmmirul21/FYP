<html>
	<head>
		<style>
		table, th, td {
			border: 1px solid black;
			border-collapse: collapse;
		}
		table.center {
			margin-left: auto; 
			margin-right: auto;
		}
		tr{border-bottom: 1px solid #ddd}
		</style>
   </head>

<body>
   <h1>Water Quality Monitoring Web Sever</h1>

   <table class="centre" border="1" cellspacing="1" cellpadding="1">
		<tr>
			<th>&nbsp;Timestamp&nbsp;</th>
			<th>&nbsp;Temperature (°C)&nbsp;</th>
			<th>&nbsp;Turbidity (NTU)&nbsp;</th>
			<th>&nbsp;Acidity (pH)&nbsp;</th>
			<th>&nbsp;Water Condition Status&nbsp;</th>
			<th>&nbsp;Hash (SHA3-512)&nbsp;</th>
		</tr>
		
		<?php
        include("connect.php");
        $sql = "SELECT * FROM 'sensorreadings' ORDER BY 'seqnum' DESC";
        $result = mysqli_query($connection,$sql);
		echo $_POST['temperature'] . $_POST['turbidity'] . $_POST['acidity'];;
		
		if($result != false)
		{
			while($row = mysqli_fetch_array($result)) 
			{
				echo "<tr>";
					echo "<th>" .$row['seqnum'] . "</th>";
					echo "<th>" .$row['timestamp']. "</th>";
					echo "<th>" .$row['temperature']. "</th>";
					echo "<th>" .$row['acidity']. "</th>";
					echo "<th>" .$row['hash']. "</th>";
				echo "</tr>";
				
		    }
		} ?>
    </table>
</body>
</html>
