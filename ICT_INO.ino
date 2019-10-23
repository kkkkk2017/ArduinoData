#define TX 4
#define RX 5
#define LedPin 13

#include <SMS_lib.h>
#include <SoftwareSerial.h>

SoftwareSerial ss = SoftwareSerial(TX, RX);
SMS_lib sms = SMS_lib();

char replybuffer[255];
char data[4] = "tim";

void setup() {
  Serial.begin(9600);
  // start at 4800 baud  
  ss.begin(4800);
  Serial.println("Initialze with 4800 baud");
  pinMode(LED_BUILTIN, OUTPUT);
  
  sms.Begin(mySerial);
  sms.setBaudrate(4800);
  
  //setUpHTTPS();
  setUp();
//  sendMessage();
  //delay(500);
}

void loop(){
  if(Serial.available() > 0){
//      String result;
//      result = Serial.readStringUntil('\n');
      //Serial.write(data,4);
      //delay(1000);
      char result[1];
      Serial.readBytesUntil('\n',result,1);
     // Serial.println(result);
      if(result[0] == 't'){
          digitalWrite(LED_BUILTIN, LOW);
        } else if(result[0] == 'f'){
          digitalWrite(LED_BUILTIN, HIGH); 
          sms.sendMessage("+61422540224", "Testing");
          delay(500);
          } else {
              //digitalWrite(LED_BUILTIN, HIGH); 
              //delay(1000);
              //digitalWrite(LED_BUILTIN, LOW); 
              //delay(1000);
        }
    }
}

void setUpHTTPS(){
  //SETUP
  ss.println("AT+CGDCONT=1,\"IP\",\"telstra.wap\",\"0.0.0.0\"");
  ss.println("AT+CGSOCKCONT=1,\"IP\",\"telstra.wap\"");
  ss.println("AT+CSOCKSETPN=1");
  delay(200);
  getHTTP();
}

void getHTTP(){
  Serial.println("Getting http");
  ss.println("AT+CHTTPSSTART");
  ss.println("AT+CHTTPSOPSE=\"arduinodb.cujeuqx7a1yr.ap-southeast-2.rds.amazonaws.com\",1433,1");
  delay(200);
  ss.println("AT+CHTTPSSEND=86");
  delay(200);
  ss.println("AT+CHTTPSRECV=4000");
  delay(200);
  ss.println("AT+HTTPACTION=0");
//  ss.println("AT+CHTTPSCLSE");
//  delay(200);
//  ss.println("AT+CHTTPSSTOP");
 }

