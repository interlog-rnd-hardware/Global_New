<?php
  include("function.php");
   
  $conn = databaseConnect();
 
  if(isset($_GET['message']))
  {
    echo $_GET['message'];
    echo "<br>";
    echo "<br>";
  }
  $sql = "SELECT * FROM arduino_data";
  $result = $conn->query($sql);
 
  echo "<html>";
  echo "<head>";
  echo "<meta http-equiv='refresh' content='10'>";
  echo "</head>";
  echo "<body>";
  echo "Arduino Data";
  echo "<table border='1'>";
  echo "<tr>";
  echo "<td width='50'>id</td><td width='100'>Variabel</td><td width='200'>Nilai</td>";
  echo "</tr>";
  if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
      echo "<tr>";
      echo "<td>".$row["id"]."</td><td>".$row["variabel"]."</td><td>".$row["nilai"]. "</td>";
      echo "</tr>";
    }
  } else {
    echo "<td colspan='3'>";
    echo("tidak ada hasil");
    echo "</td>";
  }
  echo "</table>";
   
  echo "<form action='dariBrowser.php' method=GET>";
  echo "<input type='hidden' name='aksi' value='hapus'><br>";
  echo "<input type='submit' value='Hapus semua data'>";
  echo "</form>";
 
  echo "<br>Kirim data ke Arduino<br>";
  echo "<form action='dariBrowser.php' method=GET>";
  echo "Nama variabel:<br><input type='text' name='variabel'><br>";
  echo "Nilai:<br><input type='text' name='nilai'><br>";
  echo "<input type='submit' value='Kirim'>";
  echo "</form>";
  echo "</body>";
  echo "</html>";
 
  $conn->close();
?> 