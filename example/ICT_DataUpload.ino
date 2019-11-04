#define TX 4
#define RX 5
#define LedPin 13

#include <DTran.h>
#include <SoftwareSerial.h>

String url="http://myarduinosite.tk/";
String port="80";
String ip="52.65.219.251";
String post_request="POST /upload.php HTTP/1.1";
String get_request="GET /fetch.php HTTP/1.1";
String host="Host: myarduinosite.tk";
String type = "Content-Type: application/x-www-form-urlencoded; charset=UTF-8";
String len="Content-Length: ";
String params="lag=\"12:12212\"&lon=\"13:4321\"&time=\"11:00:08 PM\"";

SoftwareSerial mySerial = SoftwareSerial(TX, RX);
SoftwareSerial *ss = &mySerial;
DTran dtran = DTran();

void setup() {
  Serial.begin(4800);
  ss->begin(4800);

  digitalWrite(LedPin, LOW);
  
  dtran.begin(*ss);
  dtran.setBaudrate(4800);
  delay(500);
  
  if(dtran.sendHTTP(post_request, host, type, len, params)){
    delay(1000);
    digitalWrite(LedPin, HIGH);
    dtran.sendMessage();
  } else {
    digitalWrite(LedPin, LOW);
    Serial.println("Upload failed.");
    }
}

void loop(){
  dtran.updateSerial();
}

