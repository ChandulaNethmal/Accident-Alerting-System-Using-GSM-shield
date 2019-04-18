# Accident-Alerting-System-Using-GSM-shield
This was a kind of basic project I have involved with one of my friend who was studying at a engineering education Institute. The target was an accident alerting system for a vehicle.    When the car getting closer to a vehicle alerting system gives a beep pulse sound to alert the driver. The driver can manually silent the alarm by separated push button switch. If the vehicle gets very closer (7cm as an example) system gives an emergency alarm to indicate an accident. The driver still can silence the alarm and ignore the incidence as a mistake by pressing the same button mentioned above within a minute.    Unless the driver presses the button within a minute system to consider this as an accident and sends SMS to the family and police with the GPS coordinates of the vehicle, time and information of the accident. Then it automatically makes a missed call to the family as the SMS do not give an urgent alert. however as my thoughts this method has a tedious part with sing an ultra sonic sensor. 

# Using SIM 808 GPRS, GSM, GPS  Arduino shield


SIM808 module is a GSM/GPS/BT three-in-one function module. It is based on the latest GSM/GPS/BT module SIM808 from 'SIMCOM', supports GSM/GPRS Quad-Band network and combines GPS technology for satellite navigation.It has high GPS receiver sensitivity with 22 tracking and 66 acquisition receiver channels. Besides, it supports A-GPS that available for indoor localization， and it also supports for Bluetooth 4.0.

The module is controlled by AT command via UART and supports 3.3V and 5V logical level.





There are two separated antennas for GSM and GPS. The bigger one is for the GPS and the other one is a GSM antenna. 

We must plug both of them as our application to the dedicated slot labeled on the shield. Some of the major parts of the shield can be understood using the image shown below. But it is another model of shield made by using the same SIM808 module.







# Turn on the SIM808  shield
There are two ways to turn on the SIM808 GPRS/GSM+GPS Shield.


1. Turn on through the power button . Press the the 'POWERKEY' for few seconds until Power-on indicator(Green/red) is on.

2. Turn on through the software.To turn on through software run the following code, the SIM808 will POWER on or POWER off after code run.
