****Develop a C library for a 3G device for Arduino platform****

A library for a 3G device to upload data on cloud for a Arduino platform. 

**Prerequisites**
1. There should have a API for uploading adn fecthing data. 
2. There should have a SIM card attahced in the Arudion Controller.
3. There should have a valid SQL server on the cloud.

**Configuration**
1. Change the API to fit current data:

	1.1 Copy the upload.php and give it a new name.
	1.2 Change the $dbusername, $dbpassword, $server, $dbname, $usertable to your database information.
	1.3 Change $lon, $lag, $time to the data attribute name that you need and change $_GET[your attribute name].
	1.4 Change the $sql to the INSERT SQL command to insert your data to your database table.
	1.5 Connect to your virtual server and put the file under your websiets directory.
 
2. Build the POST request string in the library with following format([] is where you need to insert):

	POST [url] HTTP/1.1\r\nHost: [host]\r\nContent-Length: [data length]\r\n[data name]=[data value]&[data2 name]=[data2 value](if more than 1 data, and repeat &[data name]=[data value] if more).\r\n

**Use**

To start up,

	1. Create the library object with:
		SMS_lib sms = SMS_lib();
		
  	2. Put the software serial to begin with:
		sms.Begin(mySerial);
		
  	3. Set the baud rate for the serial with:
		sms.setBaudrate(4800);
  
  	4. Set up the controller with:
		setUp();
To send SMS, 

	call sendMessage() function with your phone number and the sending message as the function paramete, for example,
	sendMessage("+61xxxxxxxxx", "testing message");
	
To send HTTP request,

	call sendHTTP() function with your POST reqeust string, for example,
	sendHTTP("POST xxxxxxxxxxxxxxxxx");


