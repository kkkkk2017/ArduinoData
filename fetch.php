<html>
<head>
    <title>fetch data page</title>
</head>
<body>
<?php

    $dbusername = "admin";
    $dbpassword = "12345678";
    $server = "testdb.cujeuqx7a1yr.ap-southeast-2.rds.amazonaws.com";
    $dbname="demo";
    $usertable= "test";

    $dbconnect = mysqli_connect($server, $dbusername, $dbpassword);
    if(!$dbconnect){
        DIE ('Unable to connect to database! Please try again later.');
    }

    $dbselect = mysqli_select_db($dbconnect, $dbname);
    if(!$dbselect){
        DIE ('Unable to get the database! Please try again later.');
    }

    $sql = "SELECT * FROM $usertable";
    if($dbconnect -> query($sql) != TRUE){
        echo "Error: " . $sql . "<br>" . $dbconnect->error;
    }


    $records = mysqli_query($dbconnect, $sql);
    $json_array = array();

    if ($records->num_rows > 0) {
        // output data of each row
        while($row = $records->fetch_assoc()) {
            echo "lag: " . $row["lag"]. " - lon: " . $row["lon"]. "- time: " . $row["time"]. "<br>";
        }
    } else {
        echo "0 results";
    }

    $dbconnect->close();
?>
</body>
</html>

