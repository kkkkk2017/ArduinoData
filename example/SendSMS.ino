#define TX 4
#define RX 5
#define LedPin 13
#include <DTran.h>
#include <SoftwareSerial.h>

String phone_number = "+61422540224";
String message = "This is a test message.";

SoftwareSerial mySerial = SoftwareSerial(TX, RX);
SoftwareSerial *ss = &mySerial;
DTran dtran = DTran();

void setup() {
  Serial.begin(4800);
  ss->begin(4800);

  digitalWrite(LedPin, LOW);
  while(Serial.available());
  
  dtran.begin(*ss);
  dtran.setBaudrate(4800);
  dtran.setUp();

  dtran.sendMessage(phone_number, message);
}

void loop(){
   dtran.updateSerial();

}

