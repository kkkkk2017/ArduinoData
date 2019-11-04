#ifndef DTran_h
#define DTran_h

#if (ARDUINO >= 100)
#include "Arduino.h" // for Arduino 1.0
#else
#include "WProgram.h" // for Arduino 23
#endif

#include <SoftwareSerial.h>

class DTran
{
  public:
	DTran();

	void begin(Stream &port);
	void setBaudrate(uint16_t baud);
	void setUp();
	void sendMessage();
	bool sendHTTP(String request, String host, String type, String len, String params);
	void updateSerial();
	void closeHTTP();

private:
	Stream *_mySerial;
	char replyBuffer[255];
    
};




#endif
