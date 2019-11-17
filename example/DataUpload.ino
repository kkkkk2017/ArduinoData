#define TX 4
#define RX 5
#define LedPin 13
#include <DTran.h>
#include <SoftwareSerial.h>

String url="myarduinosite.tk";
String request="/upload.php";
String params[3];

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

  params[0] = "lag=" + String(random(-100, 100));
  params[1] = "lon=" + String(random(-100, 100));
  params[2] = "time=" + String(random(0,24+1)) + ":" + String(random(0,60+1)) + " GMT+9";
 
  delay(100);
  dtran.decodeParameter(params);
  
  delay(500);
  dtran.sendHTTP(url, request);
}

void loop(){
   dtran.updateSerial();

}

