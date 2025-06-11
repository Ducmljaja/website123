<?php
$servername = "localhost";
$username = "root"; // Thay đổi nếu bạn dùng tài khoản khác
$password = ""; // Thay đổi nếu có mật khẩu
$dbname = "shopdientu"; // Tên cơ sở dữ liệu của bạn

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
?>
