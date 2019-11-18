Develop a C library for a 3G device for Arduino platform
=============================

A library for a 3G device to upload data on cloud for a Arduino platform. 

## Prerequisites
1. There should have a API(application programming interface) for uploading adn fecthing data. 
2. There should have a SIM card attahced in the Arudion Controller.
3. There should have a valid MySQL server on the cloud.

## Configuration

Change the API to fit current data:

	1.1 Copy the upload.php and give it a new name.
	
	1.2 Change the $dbusername, $dbpassword, $server, $dbname, $usertable to your database information.
	
	1.3 Change $lon, $lag, $time to the data attribute name that you need and change $_GET[your attribute name].
	
	1.4 Change the $sql to the INSERT SQL command to insert your data to your database table.
	
	1.5 Connect to your virtual web server (The example project is using Apache) and put the file under your websites directory.

## Use in Arduino program

To start up,

	1. Create the library object with:
		DTran dtran = DTran();
		
  	2. Put the software serial to begin with:
		dtran.begin(mySerial);
		This function passing the serial to the library so it can start the operations. 
		
  	3. Set the baud rate for the serial with:
		  dtran.setBaudrate(4800);
		  The baudrate can only set with 4800. 
  
  	4. Set up the controller with:
		setUp();
		This functino is doing the initial set up and checking the SIM card and network status.
To send SMS, 

	1. change the phone_number and message in the library and call sendMessage() function
	dtran.sendMessage();
	2. Or you can call the sendMessage(String phone_number, String message) with the phone number and the message.
	
To send HTTP request,
	1. The parameters are putted in a String array in a format "valuename=value"; String[] parameters;	
	2. call decodePrameter() function to decode your paramaters with passing the parameters then call sendHTTP() function with your url and reqeust page, for example,
	sendHTTP("myarduinosite.tk", "/upload.php");


