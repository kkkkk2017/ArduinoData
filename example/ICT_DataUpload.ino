#define TX 4
#define RX 5
#define LedPin 13

#include <DTran.h>
#include <SoftwareSerial.h>

String url="myarduinosite.tk";
String request="/upload.php";
String params[] = {"lag=43.13423412", "lon=-0.4232","time=11:00 PM GMT+9"};

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
  
  delay(100);
  dtran.decodeParameter(params);
  
  delay(500);
  dtran.sendHTTP(url, request);
}

void loop(){
   dtran.updateSerial();

}

