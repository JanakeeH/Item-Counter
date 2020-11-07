

#define D4 eS_PORTC4
#define D5 eS_PORTC5
#define D6 eS_PORTC6
#define D7 eS_PORTC7
#define RS eS_PORTC0
#define EN eS_PORTC1

#include <avr/io.h>
#include "lcd.h"
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#define F_CPU 8000000UL		
#include <time.h>


int tallCount = 0;
int shortCount = 0;
char tallNum[5];
char shortNum[5];

int main(void)
{
	
	// Enable C ports.
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);
	DDRC = 0xff;
	DDRA = 0xff;
	DDRB = 0x00;
	PORTA = 0b00000001;
	Lcd4_Init();
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("   Welcome!!!   ");
	_delay_ms(1000);
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("    Power On    ");
	lightOn();
	_delay_ms(1000);
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("    Motor On    ");
	motorOn();
	itoa(tallCount, tallNum, 10);
	itoa(shortCount, shortNum, 10);
	
    while (1)
    {
		getCount();
    }
}


void motorOn(){
	PORTA &=~(1<<PINA0);
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Motor On");
	_delay_ms(2000);
}

void motorOff(){
	PORTA |=(1<<PINA0);
}

void lightOn(){
	PORTA |=(1<<PINA1);
}

void lightOff(){
	PORTA &=~(1<<PINA1);
}

void getCount(){
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Tall Count : ");
	Lcd4_Set_Cursor(1,13);
	Lcd4_Write_String(tallNum);
	Lcd4_Set_Cursor(2,0);
	Lcd4_Write_String("Short Count: ");
	Lcd4_Set_Cursor(2,13);
	Lcd4_Write_String(shortNum);
	_delay_ms(100);
	if(bit_is_clear(PINB,0)){
		while (bit_is_clear(PINB,0))
		{
			_delay_ms(1);
		}
		tallCount++;
		itoa(tallCount, tallNum, 10);
		
	}else if (bit_is_clear(PINB, 1)){
		while (bit_is_clear(PINB,1))
		{
			_delay_ms(1);
		}
		shortCount++;
		itoa(shortCount, shortNum, 10);
	}else{
		
	}
}