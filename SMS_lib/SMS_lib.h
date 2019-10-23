#ifndef SMS_lib_h
#define SMS_lib_h

#if (ARDUINO >= 100)
#include "Arduino.h" // for Arduino 1.0
#else
#include "WProgram.h" // for Arduino 23
#endif

#include <SoftwareSerial.h>

#define TX 4
#define TX 5

class SMS_lib
{
  public:
    SMS_lib(int baud);
    void setUp();
    void sendMessage(String phone_number, String message);
  private:
    int _baud;

	Software ss = new SoftwareSerial(TX, RX);
    
};




#endif
