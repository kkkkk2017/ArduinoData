#define TX 4
#define RX 5
#include <DTran.h>
#include <SoftwareSerial.h>

String url="myarduinosite.tk";
String request="/upload.php";
String phone_number = "+61422540224"
String params[3];

SoftwareSerial mySerial = SoftwareSerial(TX, RX);
SoftwareSerial *ss = &mySerial;
DTran dtran = DTran();
int attempt = 0;

void setup() {
  //begin both software serial
  Serial.begin(4800);
  ss->begin(4800);

  while(Serial.available());

  //passing the software serial into the library
  dtran.begin(*ss);
  //set up the baudrate 
  dtran.setBaudrate(4800);
  //do initial set up and check the status
  dtran.setUp();
}

void loop(){
  //empty the buffer
   dtran.updateSerial();

   //upload data for three times
   while(attempt < 3){
      Serial.println("Attempt ... " + String(attempt+1)); 

      //Insert the parameters to the params array. 
      params[0] = "lag=" + String(random(-100, 100));
      params[1] = "lon=" + String(random(-100, 100));
      params[2] = "time=" + String(random(0,24+1)) + ":" + String(random(0,60+1)) + " GMT+9";
      
      upload();
      attempt += 1;
      //delay the uploading for 5 seconds
      delay(5000);
    }   
}

//wrap decodeParameter() and sendHTTP() into a function so easy for use
void upload(){
  //decode the paratemers into the requet string
  delay(100);
  dtran.decodeParameter(params);

  //send the data with http request 
  //and it will send notification to the phone number
  delay(500);
  dtran.sendHTTP(url, request, phone_number);
}

