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

  _mySerial->println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  _mySerial->println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  _mySerial->println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  _mySerial->println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  _mySerial->println("AT+CGSOCKCONT=1,\"IP\",\"telstra.wap\"");
  updateSerial();

  _mySerial->println("AT+CMGF=1");
  updateSerial();
  _mySerial->println("AT+SAPBR=3,1,\"APN\",\"telstra.wap\"");
  updateSerial();
  _mySerial->println("AT+SAPBR=1,1");
  updateSerial();
 }


void DTran::sendMessage(String phone_number, String message){
	Serial.println("Sending the message");
	_mySerial->println("AT+CMGS=\"" + phone_number + "\"");
	delay(100);
	_mySerial->println(message);
	_mySerial->write(0x1a);
}

bool DTran::sendHTTP(String request_string) {
	_mySerial->println("AT+CHTTPACT=\"myarduinosite.tk\",80");
	delay(1000);
	updateSerial();
	delay(100);
	_mySerial->println(request_string);
	_mySerial->write(0x1a);
	updateSerial();
	delay(1000);
	return true;
}


void DTran::updateSerial()
{
	delay(500);
	while (Serial.available())
	{
		_mySerial->write(Serial.read());//Forward what Serial received to Software Serial Port
	}
	while (_mySerial->available())
	{
		Serial.write(_mySerial->read());//Forward what Software Serial received to Serial Port
	}
}
