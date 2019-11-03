<html>
<head>
    <title>delete empty data page</title>
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

    $sql = "DELETE FROM $usertable WHERE lag=' ' AND lon=' ' AND time=' '";
    if($dbconnect -> query($sql) != TRUE){
        echo "Error: " . $sql . "<br>" . $dbconnect->error;
    }


    $records = mysqli_query($dbconnect, $sql);

    echo "delete empty data";

    $dbconnect->close();
?>
</body>
</html>

