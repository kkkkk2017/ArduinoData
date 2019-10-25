#define TX 4
#define RX 5
#define LedPin 13

#include <DTran.h>
#include <SoftwareSerial.h>

String url="http://myarduinosite.tk/";
String port="80";
String request="POST /upload.php HTTP/1.1\r\n";
String host="Host: myarduinosite.tk\r\n";
String len="Content-Length: ";
String params="lag=\"9.099743\"&lon=\"33.215467\"&time=\"11:00:08 PM\"";

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
  
  String conStr = request+host+len+params.length()+" \r\n\r\n"+params; 
  if(dtran.sendHTTP(conStr)){
    delay(1000);
    digitalWrite(LedPin, HIGH);
    dtran.sendMessage("+61422540224", "Hi! This is a testing message.");
  } else {
    digitalWrite(LedPin, LOW);
    Serial.println("Upload failed.");
    }
}

void loop(){
  dtran.updateSerial();
}

