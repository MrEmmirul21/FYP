<html>
<head>
	<style>
		table, th {
			border: 1px solid black;
		}
		td {
			background-color: LightGray;
			border: collapse;
		}
		td.error {
			background-color: red;
			border: collapse;
		}
		table {
			margin-left: auto; 
			margin-right: auto;
		}
		h1 { text-align: center; }
		
	</style>
</head>

<body>
   <h1>Water Quality Monitoring Web Sever</h1>

   <table style="width:80%">
		<tr>
			<th>&nbsp;Timestamp&nbsp;</th>
			<th>&nbsp;Temperature (°C)&nbsp;</th>
			<th>&nbsp;Turbidity (NTU)&nbsp;</th>
			<th>&nbsp;Acidity (pH)&nbsp;</th>
			<th>&nbsp;Digest Value (SHA1)&nbsp;</th>
			<th>&nbsp;Checksum (SHA1)&nbsp;</th>
		</tr>
		
		<?php
        include("connect.php");
        $sql= "SELECT * FROM sensorreadings ORDER BY seqnum DESC";
        $result = mysqli_query($connection,$sql);
		
		if($result == true)
		{
			while($row = mysqli_fetch_array($result)) 
			{
				$timestamp = $row['timestamp'];
				$temperature = number_format((float)$row['temperature'], 2, '.', '');
				$turbidity = $row['turbidity'];
				$acidity = number_format((float)$row['acidity'], 2, '.', '');
                $hash = $row['hash'];
				$test = "temperature=".$temperature."&turbidity=".$turbidity."&acidity=".$acidity;

				if ($hash != sha1($test)) {
					echo "<tr>";
						echo "<td class='error'>" .$timestamp. "</td>";
						echo "<td class='error'>" .$temperature. "</td>";
						echo "<td class='error'>" .$turbidity. "</td>";
						echo "<td class='error'>" .$acidity. "</td>";
						echo "<td class='error'>" .$row['hash']. "</td>";
						echo "<td class='error'>" .sha1($test). "</td>";
					echo "</tr>";
				}
				else {
					echo "<tr>";
						echo "<td>" .$timestamp. "</td>";
						echo "<td>" .$temperature. "</td>";
						echo "<td>" .$turbidity. "</td>";
						echo "<td>" .$acidity. "</td>";
						echo "<td>" .$row['hash']. "</td>";
						echo "<td>" .sha1($test). "</td>";
				    echo "</tr>";
				}
		    }
		} 
		else
			echo "Error: " . mysqli_error($connection);
		?>
    </table>
</body>
</html>
