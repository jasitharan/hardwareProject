/*
 * MobiKit.c
 *
 * Created: 11/8/2020 3:49:30 PM
 * Author : jasitharan
 */ 

#define F_CPU 8000000UL // Define CPU Frequency 8MHz
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "keypad.h"
#include "i2c.h"
#include "LCD_I2C.h"


// Servo Motors Pins
#define TEMP_SENSOR 0b00000000
#define OXY_SENSOR 0b00000001
#define HEART_SENSOR 0b00000011
#define ECG_SENSOR 0b00000010
#define MEDI_BOX1 0b00000100
#define MEDI_BOX2 0b00000101
#define MEDI_BOX3 0b00000110


int age = 0;  // Age
int gender = 0;  // Gender
int num = 0;
char *p_number;


char key;



void getAge();
void getGender();
void sensor();
void sensorInstruction(char *c);
void getPhoneNumber();


void pushSensor();
void pullSensor();


int main(void)
{
	
	keypad_init();
	
	i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	
	lcd_clear();			/* Clear LCD */
	_delay_ms(200);
	lcd_1stline();
	lcd_msg("WELCOME...." );
	_delay_ms(1000);
	lcd_2ndline();
	lcd_msg("Mobile Medi Box");
	_delay_ms(1000);



	
	//while (1)
	//{
		
     	getAge();                         // For Getting Age
		getGender();                      // For Getting Gender
		getPhoneNumber();
	    sensor();                         // For Sensor Selection And Functions
	//}
	
}



void getAge()
{
	
	lcd_clear();
	_delay_ms(500);
	lcd_msg("AGE: ");
	_delay_ms(500);
	lcd_2ndline();
	while(1){
		key = waiting_for_keypress();
		
		 if (key == BTN_OK) {
			 age = num;
			 _delay_ms(500);
			 break;
		 }
		
		lcd_dwr(keypad_get_number(key));
		num *= 10;      // num = 0 initial value
		num += keypad_get_number(key)-48;
		
		delay(8500);
	}
	
}


  void getGender()
  {
	  lcd_clear();
	  _delay_ms(500);
	  lcd_msg("Gender: ");
	  lcd_2ndline();
	  lcd_msg("0.Male 1.Female");
	  key = waiting_for_keypress();
	  if (key == BTN_0) gender = 0;
	  if (key == BTN_1) gender = 1;
	  lcd_clear();
  }
  
  
   void getPhoneNumber()
   {
	   int n = 0;
	   _delay_ms(500);
	   lcd_msg("Phone Number: ");
	   lcd_2ndline();
	   while(1){
		   if (n == 10) break;
	       key = waiting_for_keypress();
		   lcd_dwr(keypad_get_number(key));
	       p_number[n] = key;
		   delay(8500);
	       n++;
	   }
	  
	   lcd_clear();
	   _delay_ms(50);
   }
 
  
  void sensor()
  {
	   _delay_ms(750);
	  lcd_msg("Select: ");
	  lcd_2ndline();
	  lcd_msg("0.T 1.O 2.E 3.H");
	  key = waiting_for_keypress();
	  switch(key)
	  {
		  case BTN_0:
		  sensorInstruction("PlaceYourFinger");
		  // Push The Sensor code
		 pushSensor(TEMP_SENSOR);
		 // _delay_ms(5000);
		  //pushSensor(GSM_SENSOR);
		  // Temperature Sensor Code 
		  
		  
		 //_delay_ms(10000);
        //  pullSensor(TEMP_SENSOR);
		//  pullSensor(GSM_SENSOR);
		  break;
		  case BTN_1:
		  sensorInstruction("PlaceYourThump");
		  // Push The Sensor code
		 pushSensor(OXY_SENSOR);
		  // Oxygen Saturation Code
		 //  _delay_ms(5000);
	//	   pushSensor(GSM_SENSOR);
		  
		 //  _delay_ms(10000);
		//   pushSensor(OXY_SENSOR);
	//	_delay_ms(10000);
	//	pullSensor(OXY_SENSOR);
		  break;
		  case BTN_2:
		  sensorInstruction("PlaceYourThump");
		  // Push The Sensor code
		pushSensor(ECG_SENSOR);
		  
		  // ECG Code
		  
		  
	//	 _delay_ms(10000);
		 // pushSensor(ECG_SENSOR);
		 //_delay_ms(10000);
	//	 pullSensor(ECG_SENSOR);
		  break;
		  case BTN_3:
		  sensorInstruction("Putitonyourchest");
		  // Push The Sensor code
		  pushSensor(HEART_SENSOR);
		  
		  // Heart Rate Code
		  
		  
		// _delay_ms(10000);
		// pushSensor(HEART_SENSOR);
	//	 _delay_ms(10000);
	//	 pullSensor(HEART_SENSOR);
		  break;
	      default:
		  lcd_clear();
		  _delay_ms(500);
		  lcd_msg("Wrong input");
		  _delay_ms(1000);
		 //continue;
		  break;
	  }
  }
  
  void sensorInstruction(char *c)
  {
	  lcd_clear();
	   _delay_ms(750);
	  lcd_msg(c);
	  _delay_ms(500);
  }
  
  

  
	  

  void pushSensor(int n)
  {
	  
	 PORTD = n; 
	  
	 //Configure TIMER1
	 TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	 TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

	 ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).

	 DDRD|=(1<<PD4)|(1<<PD5);   //PWM Pins as Out


	 OCR1A=500;  //180 degree
		  
  }
  

	  
	  
void pullSensor(int n)
{
	 PORTD = n;
	 OCR1A=249;   //0 degree
}