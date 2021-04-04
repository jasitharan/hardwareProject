/*
 * keypad.c
 *
 * Created: 4/4/2021 1:34:48 AM
 *  Author: jasitharan
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define BTN_0 0x13
#define BTN_1 0x08
#define BTN_2 0x09
#define BTN_3 0x10
#define BTN_4 0x04
#define BTN_5 0x05
#define BTN_6 0x06
#define BTN_7 0x00
#define BTN_8 0x01
#define BTN_9 0x02
#define BTN_OK 0x14

char database[4][4]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x012,0x13,0x14,0x15};


char search();
int r1=0,c1=0;int x=0;


void keypad_init(){
	DDRB=0xf0;
	PORTB=0x0f;
}


char search()
{
	x= x & 0x0F;
	if(x==0x0E)
	return database[r1][0];
	
	if(x==0x0D)
	return database[r1][1];
	
	if(x==0x0B)
	return database[r1][2];
	
	if(x==0x07)
	return database[r1][3];
	
	return 'n';
}

char waiting_for_keypress()
{
	
	while(1)
	{
		while(1)
		{
			x=PINB;
			if(x!=0x0f)
			{
				break;
			}
			
		}
		
		PORTB=0xEF;
		x=PINB;
		if(x!=0XEF)
		{
			r1=0;
			if(search() != 'n') break;
		}
		PORTB=0xDF;
		x=PINB;
		if(x!=0XDF)
		{
			r1=1;
			if(search() != 'n') break;
		}
		PORTB=0xBF;
		x=PINB;
		if(x!=0XBF)
		{
			r1=2;
			if(search() != 'n') break;
		}
		PORTB=0x7F;
		x=PINB;
		if(x!=0X7F)
		{
			r1=3;
			if(search() != 'n') break;
		}
	}
	
	return search();
}

char keypad_get_number(int key)
{
	switch(key)
	{
		case BTN_0: return 48;  // 0
		case BTN_1: return 49;  // 1
		case BTN_2: return 50;  // 2
		case BTN_3: return 51;  // 3
		case BTN_4: return 52;   // 4
		case BTN_5: return 53;   // 5
		case BTN_6: return 54;  // 6
	    case BTN_7: return 55;  // 7
		case BTN_8: return 56;  // 8
		case BTN_9: return 57;  // 9
		default: return -1;
	}
}