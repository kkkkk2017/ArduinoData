#include "DTran.h"
DTran::DTran(){
	_mySerial = 0;
}

void DTran::begin(Stream &port) {
	_mySerial = &port;
}

void DTran::setBaudrate(uint16_t baud) {
	_mySerial->println("AT+IPREX=" + baud);
	updateSerial();
	setUp();
}

void DTran::setUp(){
	Serial.println("Initializing...");
	delay(1000);

	//_mySerial->println("AT"); //Once the handshake test is successful, it will back to OK
	//updateSerial();
	//_mySerial->println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
	//updateSerial();
	//_mySerial->println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
	//updateSerial();
	//_mySerial->println("AT+CREG?"); //Check whether it has registered in the network
	//updateSerial();
	_mySerial->println("AT+CGSOCKCONT=1,\"IP\",\"telstra.wap\"");
	updateSerial();

	_mySerial->println("AT+CMGF=1");
	updateSerial();
	_mySerial->println("AT+CSOCKSETPN=1");
	updateSerial();
	//_mySerial->println("AT+SAPBR=3,1,\"APN\",\"telstra.wap\"");
	//updateSerial();
	//_mySerial->println("AT+SAPBR=1,1");
	//updateSerial();
 }


void DTran::sendMessage(){
	Serial.println("Sending the message");
	Serial.println("Enter a phone number to send: (including in \" \" )");
	String phone_number = "";
	String message = "";
	while (phone_number == "") {
		if (Serial.available()) {
			phone_number = Serial.readString();
		}
	}
	
	if (phone_number == "") {
		Serial.println("Phone number is empty");
	}
	else {
		_mySerial->println("AT+CMGS=" + phone_number);
		delay(100);
		Serial.println("Enter a message to send: ");
		while (message == "") {
			if (Serial.available()) {
				message = Serial.readString();
			}
		}
		_mySerial->println(message);
		_mySerial->write(0x1a);
	}

}

//bool DTran::sendHTTP(String request, String host, String type, String len, String params) {
//	_mySerial->println("AT+CHTTPSSTART");
//	updateSerial();
//	delay(1000);
//
//	_mySerial->println("AT+CHTTPSOPSE=\"myarduinosite.tk\", 80, 1");
//	updateSerial();
//	
//	_mySerial->println("AT+CHTTPSSEND="+ String(request.length()+host.length()+1) );
//	updateSerial();
//
//	_mySerial->println(request);
//	_mySerial->println(host);
//	_mySerial->write(0x1a);
//	//_mySerial->println(len + String(0));
//	updateSerial();
//
//	updateSerial();
//
//	_mySerial->println("AT+CHTTPSSEND");
//	updateSerial();
//	delay(300);
//	//_mySerial->println("AT+CHTTPSRECV?");
//	//updateSerial();
//
//	//closeHTTP();
//	return true;
//	//return strstr(replyBuffer, "ok") != 0 ;
//}

bool DTran::sendHTTP(String request, String host, String type, String len, String params) {
	_mySerial->println("AT+CHTTPACT=\"myarduinosite.tk\",80");
	delay(1000);
	updateSerial();
	delay(100);
	_mySerial->println(request);
	delay(1);
	_mySerial->println(host);
	delay(1);
	_mySerial->println(type);
	delay(1);
	_mySerial->println(len + String(255));
	delay(1);
	_mySerial->println();
	_mySerial->println(params);
	delay(1);
	_mySerial->write(0x1a);
	delay(1000);
	updateSerial();

	delay(1000);
	updateSerial();

	return true;
	//return strstr(replyBuffer, "ok") != 0 ;
}

void DTran::closeHTTP() {
	_mySerial->println("AT+CHTTPSCLSE");
	updateSerial();
	_mySerial->println("AT+CHTTPSSTOP");
	updateSerial();
}


void DTran::updateSerial()
{
	delay(500);
	for (int i = 0; i < sizeof(replyBuffer); i++) {
		replyBuffer[i] = 0;
	}

	while (Serial.available())
	{
		char b = Serial.read();
		if (b == '*') {
			_mySerial->write(0x1a);
		}
		else {
			_mySerial->write(b);
		}
	}

	int pos = 0;
	while (_mySerial->available())
	{
		char a = _mySerial->read();
		Serial.write(a);
		replyBuffer[pos] = a;
		pos += 1;
	}
}
