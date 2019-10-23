#include "SMS_lib.h"
SMS_lib::SMS_lib(int baud){
  _baud=baud;
  Serial.begin(baud);
  ss.begin(baud);

  }

void SMS_lib::setUp(){
  ss.println("AT+CMGF=1");
  ss.println("AT+SAPBR=3,1,\"APN\",\"telstra.wap\"");
  delay(500);
  ss.println("AT+SAPBR=1,1");
  delay(500);
  ss.println("AT+HTTPINIT");
  delay(1000);
 }


void SMS_lib::sendMessage(String phone_number, String message){
	Serial.println("Sending the message");
  ss.println("AT+CMGS=\""+phone_number+"\"");
  delay(100);
  ss.println(message);
  ss.write(0x1a);
  
  }
