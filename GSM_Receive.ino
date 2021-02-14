#include <SoftwareSerial.h>

void SIM900power()
{
  pinMode(11, OUTPUT); 
  digitalWrite(11,LOW);
  delay(10000);

}

//Create software serial object to communicate with SIM900
SoftwareSerial mySerial(9, 10); //SIM900 Tx & Rx is connected to Arduino #9 & #10
float startTime = millis();

void setup()
{
  SIM900power();
  //pinMode(9, OUTPUT);
  
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  //Begin serial communication with Arduino and SIM900
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Handshaking with SIM900
  delay(500);
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  delay(500);
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  delay(500);
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  delay(500);
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(500);
  mySerial.println("AT+CNMI=2,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  delay(500);
  Serial.println("Done!");
}

void loop()
{
 updateSerial();  
}


void updateSerial()
{
  delay(500);

  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
