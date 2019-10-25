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
	void sendMessage(String phone_number, String message);
	bool sendHTTP(String request_string);
	void updateSerial();

private:
	Stream *_mySerial;

    
};




#endif
