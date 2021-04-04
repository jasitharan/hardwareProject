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
#define OXY_SENSOR 0b00000010
#define HEART_SENSOR 0b00000001
#define ECG_SENSOR 0b00000011



int age = 0;  // Age
int gender = 0;  // Gender
int num = 0;

char key;



void getAge();
void getGender();
void sensor();
void sensorInstruction(char *c);


void pushSensor(int n);
void pullSensor(int n);


int main(void)
{
	
	keypad_init();
	
	i2c_init();
	i2c_start();
	i2c_write(0x70);
	lcd_init();
	
	lcd_clear();			/* Clear LCD */
	_delay_ms(100);
	lcd_1stline();
	lcd_msg("WELCOME...." );
	_delay_ms(50);
	lcd_2ndline();
	lcd_msg("Mobile Medi Box");
	_delay_ms(150);
	 lcd_clear();
	_delay_ms(50);


	
	//while (1)
	//{
		
     	getAge();                         // For Getting Age
		getGender();                      // For Getting Gender
	    sensor();                         // For Sensor Selection And Functions
	//}
	
}



void getAge()
{
	
	lcd_clear();
	lcd_msg("AGE: ");
	_delay_ms(100);
	lcd_2ndline();
	while(1){
		key = waiting_for_keypress();
		
		 if (key == BTN_OK) {
			 age = num;
			 _delay_ms(50);
			 break;
		 }
		
		lcd_dwr(keypad_get_number(key));
		num *= 10;      // num = 0 initial value
		num += keypad_get_number(key)-48;
		
		delay(500);
	}
	
}


  void getGender()
  {
	  lcd_clear();
	  lcd_msg("Gender: ");
	  lcd_2ndline();
	  lcd_msg("0.Male 1.Female");
	  key = waiting_for_keypress();
	  delay(500);
	  if (key == BTN_0) gender = 0;
	  if (key == BTN_1) gender = 1;
	  _delay_ms(50);
	  lcd_clear();
  }
  
 
  
  void sensor()
  {
	  lcd_msg("Select: ");
	  lcd_2ndline();
	  lcd_msg("0.T 1.O 2.E 3.H");
	  key = waiting_for_keypress();
	  switch(key)
	  {
		  case BTN_0:
		  sensorInstruction("Place Your Finger");
		  // Push The Sensor code
		//  pushSensor(TEMP_SENSOR);
		  
		  // Temperature Sensor Code 
		  
		  
		//  _delay_ms(10000);
//		  pushSensor(TEMP_SENSOR);
		  break;
		  case BTN_1:
		  sensorInstruction("PlaceYourThump");
		  // Push The Sensor code
		//  pushSensor(OXY_SENSOR);
		  // Oxygen Saturation Code
		  
		 //  _delay_ms(10000);
		//   pushSensor(OXY_SENSOR);
		  break;
		  case BTN_2:
		  sensorInstruction("PlaceYourThump");
		  // Push The Sensor code
		//  pushSensor(ECG_SENSOR);
		  
		  // ECG Code
		  
		  
		//   _delay_ms(10000);
		 //  pushSensor(ECG_SENSOR);
		  break;
		  case BTN_3:
		  sensorInstruction("Putitonyourchest");
		  // Push The Sensor code
		 // pushSensor(HEART_SENSOR);
		  
		  // Heart Rate Code
		  
		  
		//   _delay_ms(10000);
		 //  pushSensor(HEART_SENSOR);
		  break;
	      default:
		  lcd_clear();
		  lcd_msg("Wrong input");
		  _delay_ms(100);
		 //continue;
		  break;
	  }
  }
  
  void sensorInstruction(char *c)
  {
	  lcd_clear();
	  lcd_msg(c);
	  _delay_ms(50);
  }
  
  

  
  /*
  
  void pushSensor(int n)
  {
	 PORTD = n;
	 DDRD |= 0b00100011;
     TCCR1A |= 1<<WGM11 | 1<<COM1A1;
     TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10 | 1<<CS11;
     ICR1 = 2499;

     OCR1A = 65;	/* Set servo shaft at -90° position */
	 /*
    _delay_ms(1500);
     OCR1A = 175;	/* Set servo shaft at 0° position */
	 /*
    _delay_ms(1500);
     OCR1A = 300;	/* Set servo at +90° position */
	 /*
    _delay_ms(1500);
	  
  }

  void pullSensor(int n)
  {
	  
	  PORTD = n;
	  DDRD |= 0b00100011;
	  TCCR1A |= 1<<WGM11 | 1<<COM1A1;
	  TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS10 | 1<<CS11;
	  ICR1 = 2499;

	  OCR1A = 65;	/* Set servo shaft at -90° position */
	  /*
	  _delay_ms(1500);
	  
  }
  
  */
	  
	  
	  
	  
	  
	 