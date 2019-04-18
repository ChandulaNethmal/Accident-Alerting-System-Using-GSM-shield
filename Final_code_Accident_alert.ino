//Chandula-Nethmal

#include <SoftwareSerial.h>
#define DEBUG true
SoftwareSerial mySerial(7, 8);

int timeout = 5000; // timeout in millisecs

int counter = 0;
String Longit = "", Latit = "", Time1 = "", Date1 = "";
int Echo = 4; //SENSOR ECHO
int Trig = 5; //SENSOR TRIG

int buzzer = 11;
int sw = 6;
int Powerkey = 9;
int Distance = 0;
int counter2 = 0;
int counter3 = 0;

int  Accident_level = 10;   // 2nd level in cm
int Safty_Distance = 30;  // 1st level in cm

void setup()
{
  mySerial.begin(9600);  //Default serial port setting for the GPRS modem is 19200bps 8-N-1
  Serial.begin(9600);
  pinMode(Powerkey, OUTPUT);   // initialize the digital pin as an output.
  power();
  pinMode(sw, INPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  getgps();

}

void loop()
{
  counter=0;
  counter2 = 0;
  //sendData( "AT+CGNSINF", 1000, DEBUG);
  Distance = Distance_test();
  Serial.print("Distamce:");
  Serial.println(Distance);
  while (Distance <= Safty_Distance) {
    while ((Distance <= Safty_Distance) && (Distance > Accident_level) && (counter2 == 0))  {
      Distance = Distance_test();
      Serial.print("You are getting closer");
      Serial.print("Distamce:");
      Serial.println(Distance);
      Buzz1();
      if (digitalRead(sw) == HIGH) {
        counter2 = 1;
      }
    }
    Distance = Distance_test();
    Serial.print("Distamce:");
    Serial.println(Distance);
    counter3 = 0;
    int timestart = 0;
    while ( Distance <= Accident_level) {
      Distance =  Distance_test();
      Serial.print("Distamce:");
      Serial.println(Distance);
      timestart = millis();
      while ((millis() <= (timestart + timeout)) && (counter3 == 0 || counter3 == 2) && (Distance <= Accident_level)) {
        Serial.print("You are in crashing level");
        Distance =  Distance_test();
        Serial.print("Distamce:");
        Serial.println(Distance);
        if (digitalRead(sw) == HIGH) {
          counter3 = 1;
        }
        else (counter3 = 2);
        Buzz2();
      }
      if ( (counter3 == 2) && (millis() > (timestart + timeout))) {            // Put the timeout period as (timestart + "timeout")
        while ((Longit == "")  or ( Latit == "" ) or  (Date1.substring(0, 4) != "2017" )) {
          sendData( "AT+CGNSINF", 1000, DEBUG);
          Serial.println("This is an urgent messege sent by SIM 808 accident alerting system. Your car has faced an accident at " + Longit + " ," + Latit + " coordinates on " + Date1 + "  at the time in GMT " + Time1 + " . \r");
        }
        sendData( "AT+CGNSINF", 1000, DEBUG);
        Serial.println("Making a call");
        call();
        delay(6000);
        Serial.println("sending a sms");
        sendSMS();
        Serial.print("This is an urgent messege sent by SIM 808 accident alerting system. Your car has faced an accident at " + Longit + " ," + Latit + " coordinates on " + Date1 + "  at the time in GMT " + Time1 + " . \r");
        counter3 =0;
        counter=0;
        counter2 = 0;
        
      }

    }
  }
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

    //Serial.print("Lat:");
    Longit = Long;
    Latit = Lat;
    Time1 = Time;
    Date1 = Date;
  }
}
int Distance_test()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig , LOW);
  float Fdistance = pulseIn(Echo , HIGH);
  delay(10);

  Fdistance = Fdistance / 29 / 2;
  return (int)Fdistance;
}
int Buzz1() {
  analogWrite(buzzer, 235), delay(500);
  analogWrite(buzzer, 0), delay(300);
}
void Buzz2() {
  analogWrite(buzzer, 255), delay(200);
  analogWrite(buzzer, 0), delay(150);
}
void sendSMS() {
  //sendData( "AT+CGNSINF", 1000, DEBUG);
  if ( Longit != ""  && Latit != "" &&  (Date1.substring(0, 4) == "2017" ) &&  counter == 0) {
    Serial.print("This is an urgent messege sent by SIM 808 accident alerting system. Your car has faced an accident at " + Longit + " ," + Latit + " coordinates on " + Date1 + "  at the time in GMT " + Time1 + " . \r");
    mySerial.print("\r");
    delay(1000);                    //Wait for a second while the modem sends an "OK"
    mySerial.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
    delay(1000);
    Serial.print("Time out");
    //mySerial.print("AT+CSCA=\"+919032055002\"\r");  //Setting for the SMS Message center number,
    //delay(1000);                                  //uncomment only if required and replace with
    //the message center number obtained from
    //your GSM service provider.
    //Note that when specifying a tring of characters
    // " is entered as \"

    mySerial.print("AT+CMGS=\"0711662691\"\r");    // Youy family number
    //to be sent to the number specified.
    //Replace this number with the target mobile number.
    delay(1000);
    mySerial.print("This is an urgent messege sent by Dad's car alerting system. Your car has faced an accident at " + Longit + " ," + Latit + " coordinates on " + Date1 + "  at the time in GMT " + Time1 + " . \r"); //The text for the message
    counter = 1;
    delay(1000);
    mySerial.write(0x1A);  //Equivalent to sending Ctrl+Z
  }
}

void power(void)
{
  digitalWrite(Powerkey, HIGH);
  delay(1000);               // wait for 1 second
  digitalWrite(Powerkey, LOW);
}

void call() {   //Making a call
  mySerial.println("ATD0711662691;"); // The number you want to dial ("ATD'your num';")

  if (mySerial.available())

    Serial.print((unsigned char)mySerial.read());


  delay(10000);
  delay(10000);

  mySerial.println("ATH"); //End the call.
  if (mySerial.available())

    Serial.print((unsigned char)mySerial.read());
}
