#include <SoftwareSerial.h>

void SIM900power()
{
  pinMode(6, OUTPUT); 
  digitalWrite(11,LOW);
  delay(10000);

}

//Create software serial object to communicate with SIM900
SoftwareSerial mySerial(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8
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
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();

}

void loop()
{
  if (millis() - startTime > 29450){  
    //Wake();
    SendSMS("\"+923002824728\"", "Aoun");
    startTime = millis(); 
    //Sleep();   
  }
  
}


void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

void Sleep(){
  pinMode(9, HIGH);
  delay(5);
  mySerial.println("AT+CSCLK=1");
  updateSerial();
  delay(10);
  pinMode(9, LOW);
}

void Wake(){
  pinMode(9, HIGH);
  delay(5);
  mySerial.println("");
  mySerial.println("AT+CSCLK=0");
  delay(10);
  pinMode(9, LOW);
  
  
}


void SendSMS(String number, String content) {
    delay(10);
    mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
    updateSerial();
    //mySerial.println("AT+CMGS=\"+923002824728\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    mySerial.println("AT+CMGS="+number);//change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial();
    mySerial.print(content); //text content
    updateSerial();
    mySerial.write(26);
}
