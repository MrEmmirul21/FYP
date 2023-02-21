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
				echo "<tr>";
					echo "<td>" .$row['timestamp']. "</td>";

					$temperature = number_format((float)$row['temperature'], 2, '.', '');
					echo "<td>" .$temperature. "</td>";

					echo "<td>" .$row['turbidity']. "</td>";

					$acidity = number_format((float)$row['acidity'], 2, '.', '');
					echo "<td>" .$acidity. "</td>";

					echo "<td>" .$row['hash']. "</td>";

					$test = "temperature=".$temperature."&turbidity=".$row['turbidity']."&acidity=".$row['acidity'];

					if ($row['hash'] != sha1($test))
						echo "<th>".sha1($test)."</th>";
					else
						echo "<td>".sha1($test)."</td>";

				echo "</tr>";

				if ($row['hash'] != sha1($test))
					echo"<script language='javascript'>alert('Checksumming failed\nProbably data was changed');window.location='index.php';</script>";
		    }
		} 
		else
			echo "Error: " . mysqli_error($connection);
		?>
    </table>
</body>
</html>
