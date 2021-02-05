# Arduino-Controlled-Fan
DC motor fan connected to an Arduino Mega 2560 who's speed can be either controlled by a potentiometer or by the temperature.
Manual mode uses a potentiometer and push button to control the fan while Auto mode uses a TMP36 temperature sensor to control the fan.<br/> 
A remote control is used to switch between the two modes.<br/>
In Manual mode a push button is used to turn the fan on and off and potentionmeter is used to control the speed.<br/>
In Auto mode the fan is turned on when the temperature is read to be a certain amount and fan speed increases as temperature increases from that point.<br/>
If temperature dips below that point, the fan turns off.<br/>
A red LED and a green LED are used to signify if the fan is off or on respectively.<br/>
A LCD screen shows the temperature being read in Fahrenheit and what mode the fan is currently in.<br/>
