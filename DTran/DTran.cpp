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
}

void DTran::setUp(){
	Serial.println("Initializing...");
	delay(500);
	_mySerial->println("AT"); //Once the handshake test is successful, it will back to OK
	updateSerial();

	if (!checkReply("OK")) {
		Serial.println("Power off the 3G sheild and reset the Controller, Please.");
		status = false;
		return;
	}

	_mySerial->println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
	updateSerial();
	_mySerial->println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
	updateSerial();
	_mySerial->println("AT+CREG?"); //Check whether it has registered in the network
	updateSerial();
	_mySerial->println("AT+CMGF=1"); //Configure SMS mode
	updateSerial();
	_mySerial->println("AT+CGSOCKCONT=1,\"IP\",\"telstra.wap\""); //Set up the barrier profile
	updateSerial();
	_mySerial->println("AT+CSOCKSETPN=1");
	updateSerial();
 }

void DTran::sendMessage(String phone_number, String message){
	if (!status) {return;}
	Serial.println();
	Serial.println("Sending the message");
	_mySerial->println("AT+CMGS=\"" + phone_number + "\"");
	updateSerial();
	_mySerial->println(message);
	_mySerial->write(0x1a);
	updateSerial();

	delay(1000);
	bool result = checkReplyTimeout(2000, "OK");
	if (!result) {
		Serial.println(MESSAGE_SMS_FAILED);
		return;
	} 
}

/* This method can not be bool type, otehrwise the HTTP function does not sent
or the AT command does not work*/
void DTran::sendHTTP(String url, String request) {
	if (!status) {return;}

	updateSerial();
	delay(500);

	//open HTTP session
	_mySerial->println("AT+CHTTPACT=\""+ url + "\",80");

	//* important: update serial twice because there are two reponse 
	updateSerial();
	delay(300);
	updateSerial();

	bool result = checkReplyTimeout(3000, "REQUEST");

	if (!result) {
		Serial.println(MESSAGE_FAILED);
		digitalWrite(LEDPIN, HIGH);
		sendMessage(PHONE_NUMBER, MESSAGE_FAILED);
		return;
	}

	_mySerial->println("POST " + request + writeBuffer + " HTTP/1.1");
	delay(1);
	_mySerial->println("Host: " + url);
	delay(1);
	_mySerial->println("Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
	delay(1);
	_mySerial->println("Content-Length:" + String(255));
	delay(1);
	_mySerial->println();
	_mySerial->write(0x1a);

	updateSerial();
	result = checkReplyTimeout(10000, "ok");

	updateSerial();
	if (!result) {
		Serial.println(MESSAGE_UPLOAD_FAILED);
		digitalWrite(LEDPIN, HIGH);
		sendMessage(PHONE_NUMBER, MESSAGE_FAILED);
		return;
	}
	else {
		Serial.println();
		sendMessage(PHONE_NUMBER, MESSAGE_SUCCESS);
	}
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

bool DTran::reset() {
	Serial.println("Waiting for 3 seconds to reset...");
	delay(3000);
	Serial.println("Resetting...");
	_mySerial->println("AT+CRESET");
	updateSerial();
	while (!checkReply("PB DONE")) {
		updateSerial();
	}

	Serial.println("AT+CRESET?");
	updateSerial();
	return checkReply("OK");
}

bool DTran::checkReplyTimeout(int timeout, const char* expect) {
	delay(1000);
	Serial.println();
	bool result = false;
	while (timeout > 0) {
		Serial.println("Waiting ..... " + String(timeout / 500));
		updateSerial();
		if (checkReply(expect)) {
			result = true;
			break;
		}
		timeout -= 500;
	}
	return result;
}

bool DTran::checkReply(const char* expect) {
	return (strstr(replyBuffer, expect) != 0);
}

void DTran::decodeParameter(String params[]) {
	if (!status) { return; }
	for (int i = 0; i < sizeof(writeBuffer); i++) {
		writeBuffer[i] = 0;
	}
	writeBuffer[0] = '?';
	int pos = 1;
	for (int i=0; i <= sizeof(params); i++) {
		for (char a : params[i]) {
			if (a == ' ') {
				writeBuffer[pos] = '+';
			}
			else if (a == '+') {
				writeBuffer[pos] = '%';
				pos += 1;
				writeBuffer[pos] = '2';
				pos += 1;
				writeBuffer[pos] = 'B';
			}
			else {
				writeBuffer[pos] = a;
			}
			pos += 1;
		}
		if (i == sizeof(params)) { break; }
		writeBuffer[pos] = '&';
		pos += 1;
	}
}
