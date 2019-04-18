#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8);

void setup()
{
mySerial.begin(9600); 
mySerial.print("\r");
delay(1000);                    //Wait for a second while the modem sends an "OK"
mySerial.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
delay(1000);


mySerial.print("AT+CMGS=\"+94123456789\"\r");    //Start accepting the text for the message
//to be sent to the number specified.
//Replace this number with the target mobile number.
delay(1000);
mySerial.print("Hello,World!\r");   //The text for the message
delay(1000);
mySerial.write(0x1A);  //Equivalent to sending Ctrl+Z 
}

void loop()
{
//We just want to send the SMS only once, so there is nothing in this loop.
