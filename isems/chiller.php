<?php
$servername = "localhost";
$username = "interlog";
$password = "interlog";
$mood = $_GET['mood'];
$dbname = "isems";
$conn = mysqli_connect($servername, $username, $password, $dbname);
// mengecek koneksi
if (!$conn) {
    die("Koneksi gagal: " . mysqli_connect_error());
}
echo "Koneksi berhasil";
$datenow = date('Y-m-d');

$sql = "INSERT INTO `chiller`(`teks`) VALUES (\"$mood\")";
$query = mysqli_query($conn,$sql); 
mysqli_close($conn);
?>
