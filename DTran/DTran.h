#ifndef DTran_h
#define DTran_h

#if (ARDUINO >= 100)
#include "Arduino.h" // for Arduino 1.0
#else
#include "WProgram.h" // for Arduino 23
#endif

#include <SoftwareSerial.h>

#define LEDPIN 13

//Customise the phone number and message
#define PHONE_NUMBER "+61422540224"
#define MESSAGE_SUCCESS "Data Uploaded"
#define MESSAGE_FAILED "HTTP Failed"
#define MESSAGE_UPLOAD_FAILED "Upload Failed"
#define MESSAGE_SMS_FAILED "SMS Failed"


class DTran
{
  public:
	DTran();

	void begin(Stream &port);
	void setBaudrate(uint16_t baud);
	void setUp();
	void sendMessage(String phone_number, String message);
//attend three time if failed
	void sendHTTP(String url, String request);

	void updateSerial();
	bool reset();
	bool checkReplyTimeout(int timeout, const char* expect);
	bool checkReply(const char* expect);
	void decodeParameter(String params[]);

private:
	Stream *_mySerial;
	char replyBuffer[255];
	char writeBuffer[255];
	bool status = true;
    
};




#endif
