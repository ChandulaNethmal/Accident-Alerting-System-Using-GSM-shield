# Accident-Alerting-System-Using-GSM-shield
This was a kind of basic project I have involved with one of my friend who was studying at a engineering education Institute. The target was an accident alerting system for a vehicle.    When the car getting closer to a vehicle alerting system gives a beep pulse sound to alert the driver. The driver can manually silent the alarm by separated push button switch. If the vehicle gets very closer (7cm as an example) system gives an emergency alarm to indicate an accident. The driver still can silence the alarm and ignore the incidence as a mistake by pressing the same button mentioned above within a minute.    Unless the driver presses the button within a minute system to consider this as an accident and sends SMS to the family and police with the GPS coordinates of the vehicle, time and information of the accident. Then it automatically makes a missed call to the family as the SMS do not give an urgent alert. however as my thoughts this method has a tedious part with sing an ultra sonic sensor. 

# Using SIM 808 GPRS, GSM, GPS  Arduino shield


SIM808 module is a GSM/GPS/BT three-in-one function module. It is based on the latest GSM/GPS/BT module SIM808 from 'SIMCOM', supports GSM/GPRS Quad-Band network and combines GPS technology for satellite navigation.It has high GPS receiver sensitivity with 22 tracking and 66 acquisition receiver channels. Besides, it supports A-GPS that available for indoor localization， and it also supports for Bluetooth 4.0.

The module is controlled by AT command via UART and supports 3.3V and 5V logical level.





There are two separated antennas for GSM and GPS. The bigger one is for the GPS and the other one is a GSM antenna. 

We must plug both of them as our application to the dedicated slot labeled on the shield. Some of the major parts of the shield can be understood using the image shown below. But it is another model of shield made by using the same SIM808 module.

Communication with the microcontroller
The SIM808 GPRS/GSM+GPS Shield is used UART (serial)protocol to communicate with an Arduino. Users can use jumpers to connect (RX,TX) of the shield to either Software Serial(D8,D7) or Hardware Serial(D1,D0) of the Arduino


# Turn on the SIM808  shield
There are two ways to turn on the SIM808 GPRS/GSM+GPS Shield.


1. Turn on through the power button . Press the the 'POWERKEY' for few seconds until Power-on indicator(Green/red) is on.

2. Turn on through the software.To turn on through software run the following code, the SIM808 will POWER on or POWER off after code run.

# Automatic Power down methods of SIM 808


Apart from normal manual power down through hardware or software, there are some automated procedures for safety and other facts involved the device. They are as follows,



1.  Over-voltage or Under-voltage Power Down: 


The module software monitors VBAT voltage constantly.

           1.If the voltage ≤ 3.5V, the following URC will be reported:

UNDER-VOLTAGE WARNNING

           2.If the voltage ≥ 4.3V, the following URC will be reported:

OVER-VOLTAGE WARNNING

          3.If the voltage < 3.4V, the following URC will be reported,and the module will be automativally powered down.

UNDER-VOLTAGE POWER DOWN

          4.If the voltage > 4.4V, the following URC will be reported,and the module will be automativally powered down.

OVER-VOLTAGE POWER DOWN



2. Over-temperature or Under-temperature Power Down: 

This will constantly monitor the temperature of the module.

①If the temperature > +80℃, the following URC will be reported:

+CMTE:1

②If the temperature < -30℃, the following URC will be reported:

+CMTE:-1

③If the temperature > +85℃, the following URC will be reported,and the module will be automativally powered down.

+CMTE:2

④If the temperature < -40℃, the following URC will be reported,and the module will be automativally powered down.

+CMTE:-2

Lets' Communicate with The device
Sim 808 is supported with AT commands for communication process with the user. We should send At commands as our purpose to execute it.

# Back to the project
Here I used an ultrasonic range sensor for detect the distance to the closest vehicle t our vehicle from front side. When the distance is getting lower than predefined alerting limit there is a buzzer for give an alarm. Unless driver bush a separated button for this on the dashboard , alarm sounds as long as distance is low. If the distance reduce to lower than 10cm for two minutes without a button press during this 2 minutes system recognize this as an accident and send a SMS to the predefined phone number 


