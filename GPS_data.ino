/*
Edited by Chandula N.
   st1,st2,date&time,longitude,latitude,altitude,

*/
#include <SoftwareSerial.h>
#define DEBUG true
SoftwareSerial mySerial(7, 8);
int Powerkey = 9;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(Powerkey, OUTPUT);   // initialize the digital pin as an output.
  power();
  getgps();
}

void loop() {
  sendData( "AT+CGNSINF", 1000, DEBUG);
}

void getgps(void) {
  sendData( "AT+CGNSPWR=1", 1000, DEBUG);
  sendData( "AT+CGPSINF=0", 1000, DEBUG);
}

void sendData(String command, const int timeout, boolean debug) {
  String response = "";
  mySerial.println(command);
  delay(5);
  if (debug) {
    long int time = millis();
    while ( (time + timeout) > millis()) {
      while (mySerial.available()) {
        response += char(mySerial.read());
      }
    }

    // Serial.print(response);
    int _1commaIndex = response.indexOf(',');
    int _2commaIndex = response.indexOf(',', _1commaIndex + 1);
    int _3commaIndex = response.indexOf(',', _2commaIndex + 1);
    int _4commaIndex = response.indexOf(',', _3commaIndex + 1);
    int _5commaIndex = response.indexOf(',', _4commaIndex + 1);
    String Lat = response.substring(_3commaIndex + 1, _4commaIndex);
    String Long = response.substring(_4commaIndex + 1, _5commaIndex);
    String Date = response.substring(_2commaIndex + 1, _2commaIndex + 9);
    String Time = response.substring(_2commaIndex + 9 , _3commaIndex );
    Date = Date.substring(0, 4) + "/" + Date.substring(4, 6) + "/" + Date.substring(6, 8);
    Time = (Time.substring(0, 2)) + "." + Time.substring(2, 4) + "." + Time.substring(4, 6);

    Serial.print("Lat:");
    Serial.println(Lat);
    Serial.print("Long:");
    Serial.println(Long);
    Serial.print("Date:");
    Serial.println(Date);
    Serial.print("Time:");
    Serial.println(Time);
    Serial.println();
  }
}
void power(void)            //Turn on thr sim808 
{
  digitalWrite(Powerkey, HIGH); 
  delay(1000);               // wait for 1 second
  digitalWrite(Powerkey, LOW);
}
