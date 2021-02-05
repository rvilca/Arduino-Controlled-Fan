#include <LiquidCrystal.h>
#include <IRremote.h>

const int rs = A3, en = A2, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int BUTTON = 3;
const int LED_ON = 5;
const int LED_OFF = 4;
int BUTTONstate = 0;
bool motor_state = false;
const byte CONTROL = 6;
int manualvalue = 0;
int autovalue = 0;
int celsius = 0;
int fahrenheit = 0;
bool mode = false; //manual = false, auto = true
int RECV_PIN = 11;

//IR Library stuff
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // initialize the serial communications:
  Serial.begin(9600);
  irrecv.enableIRIn();
  
  pinMode(BUTTON, INPUT);
  pinMode(LED_ON, OUTPUT);
  pinMode(LED_OFF, OUTPUT);
  pinMode(CONTROL, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop()
{
  if (irrecv.decode(&results)) {//irrecv.decode(&results) returns true if anything is recieved, and stores info in varible results
    unsigned int value = results.value; //Get the value of results as an unsigned int, so we can use switch case
    switch (value)
    {
      case 255: 
      mode=!mode;
      motor_state = false;
    }
    
    irrecv.resume(); // Receive the next value
  }    
 
  celsius = map(((analogRead(A1) - 20) * 3.04), 0, 1023, -40, 125);
  fahrenheit = ((celsius * 9) / 5 + 32);   
  
  if (mode == false)
  { 
    BUTTONstate = digitalRead(BUTTON);
   
   	if (BUTTONstate == HIGH)
  	{
    	Serial.println("CLICK");
    	motor_state = !motor_state;
  	} 
  	else
    {}
  
  	if (motor_state == true)
  	{
    	manualvalue = map(analogRead(A0), 0, 1023,77, 255); 
      digitalWrite(LED_ON, HIGH);
    	digitalWrite(LED_OFF, LOW);
  		analogWrite(CONTROL, manualvalue);
      
      Serial.print("Potentiometer = ");     
  		Serial.print(analogRead(A0));
  		Serial.print(" , Motor = ");
  		Serial.println(manualvalue);
  	} 
  	else
    {
      digitalWrite(LED_ON, LOW);
    	digitalWrite(LED_OFF, HIGH);
    	analogWrite(CONTROL, 0);
      
      Serial.print("Potentiometer = ");     
  		Serial.print("0");
  		Serial.print(" , Motor = ");
  		Serial.println("0");
	}
  }
  else
  { 
  	if (fahrenheit >= 90)
    {
    	motor_state = true;
    	autovalue = map(fahrenheit, 90, 110,77, 255);
    
   		if(fahrenheit >= 110)
    	{
     		autovalue = 255;
    	}
    } 
    else
    {
    	motor_state = false;
      	autovalue = 0;
    }
  
    if (motor_state == true)
    {
    	digitalWrite(LED_ON, HIGH);
    	digitalWrite(LED_OFF, LOW);
  		analogWrite(CONTROL, autovalue);
    } 
    else
    {
    	digitalWrite(LED_ON, LOW);
    	digitalWrite(LED_OFF, HIGH);
    	analogWrite(CONTROL, 0);
	}
   
   	Serial.print("Temperature = ");     
  	Serial.print(fahrenheit);
  
  	Serial.print(" , Motor = ");
  	Serial.println(autovalue);
  }

  delay(1000);
  lcd.clear();
  
  lcd.setCursor(0, 0);
  
  if (mode == false)
  {
  	lcd.print("Mode: Manual");
  }
  else
  {
    lcd.print("Mode: Auto");
  }
   
  lcd.setCursor(0, 1);
  lcd.print("Temp = ");
  lcd.print(fahrenheit);
  
}
