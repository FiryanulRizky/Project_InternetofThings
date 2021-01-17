<?php
  include("function.php");
   
  $conn = databaseConnect();
   
    $sql = 'SELECT id, variabel, nilai 
    FROM browser_data';
    
$query = mysqli_query($conn, $sql);

if (!$query) {
  die ('SQL Error: ' . mysqli_error($conn));
}
    
while ($row = mysqli_fetch_array($query))
{
  echo '[Data ke-'.$row['id'].', Nama = '.$row['variabel'].', Nilai = '.$row['nilai'].'], ';
}

// Apakah kita perlu menjalankan fungsi mysqli_free_result() ini? baca bagian VII
mysqli_free_result($query);

// Apakah kita perlu menjalankan fungsi mysqli_close() ini? baca bagian VII
mysqli_close($conn);
?> 