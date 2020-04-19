/*
 * app.c
 *
 *  Created on: Sep 16, 2019
 *      Author: Newname
 */
#include "MCAL/DIO.h"
#include "HAL/LCD.h"
#include "HAL/EKEY_PAD.h"
#include "macros.h"
#include "types.h"
#include "EBOOKS.h"
#include "EMEMBERS.h"
#include <util/delay.h>
#include "HAL/timer1.h"
#include "MCAL/method.h"

u8 location_before_timer = 0;

u8 counter = 0;
u8 seconds = 20, minutes = 58, hours = 11, crypt = 0;
u8 hide_me = 0;

void DISPLAY_OnDemand(char *str1, char *str2);
void APP(void);
void SECONDS_CALL (void);
void MINUTES_CALL (void);
void HOURS_CALL (void);

int main(void)
{
	LCD_vidInitialize();
	BOOKS_vidInitialize();
	LinkedList_vidInitialize();

	// Start timer and count till reaches 50 msec
	Timer1_vidInitialtize(8);

	// OCR is high to leave for ISR enough time for execution
	Timer1_vidSetOCRValue(50000);
	Timer1_setcallback(APP);

	hide_me = 1;

	LinkedList_vidInsertion("1", "Joey");
	LinkedList_vidInsertion("2", "John");
	LinkedList_vidInsertion("3", "Mark");
	LinkedList_vidInsertion("4", "Rose");
	LinkedList_vidInsertion("5", "Sarah");




	BOOKS_vidInsertion("0060832819", "The Zahir", 5);	//
	BOOKS_vidInsertion("0062315005", "The Alchemist", 5);		//
	BOOKS_vidInsertion("1509825428", "Bleak House", 5);		//
	BOOKS_vidInsertion("0141439675", "Hard times", 5);			//



	while(1)
	{
		hide_me = 1;
		LCD_vidClearOnDemand(1, 32);

		DISPLAY_OnDemand("1-INSER BOOK", "2-INSER MEMBER");

		DISPLAY_OnDemand("3-BORROW BOOK", "4-RETURN BOOK");

		DISPLAY_OnDemand("5-Show all books", "6-Show all members");

		DISPLAY_OnDemand("7-Member's INFO.", "                 ");

		LCD_String("OPERATION NO. :");
		LCD_vidGoTo(1, 2);
		hide_me = 0;

		KeyPad_vidInitialize();

		if(DEAD_SIGNAL_TERMINATE)
		{
			DEAD_SIGNAL_TERMINATE = 0;

			// Reset pointers to the head ot its linked list
			restart_vip();
			BOOKS_restart_vip();

			// Delete the whole data base
			LinkedList_u8DeleteEntire();
			BOOKS_u8DeleteEntire();
			break;
		}
	}
}

void DISPLAY_OnDemand(char *str1, char *str2)
{
	LCD_vidClearOnDemand(1, 32);
	// Display 1st string
	LCD_vidGoTo(1, 1);
	LCD_String(str1);
	// Display 2nd string
	LCD_vidGoTo(1, 2);
	LCD_String(str2);

	_delay_ms(1300);
	// Clear whole display
	LCD_vidClearOnDemand(1, 32);
}


void APP(void)
{
	_delay_us(10);
	counter++;
	// READ_FROM IR and assign to GLOBAL VAR. DATA

	// counter is low to let the function execute correctly without interrupting
	if(counter == 20)
	{
		location_before_timer = LCD_u8CurrentLocation_AC();

		// Variable used externally to connect timer with encrypting user input on screen
		crypt += counter;

		if(hide_me)
		{
			// Hide the clock
		}
		else
		{
			// READ_FROM IR and assign to GLOBAL VAR. DATA
			location_before_timer = LCD_u8CurrentLocation_AC();
		}

		SECONDS_CALL();

		// Reset counter
		counter = 0;
		LCD_vidInstruction(location_before_timer + (1<<7), write_operation, IR);

	}
}


void SECONDS_CALL (void)
{
	// Operation on fields are done first
	seconds++;
	if(seconds >= 60)
	{
		seconds = 0;
		minutes++;

		if(hide_me)
		{
			// Hide the clock
		}
		else
		{
			LCD_vidInstruction(0x4D + (1<<7), write_operation, IR);
			LCD_String(":");

			// 15 and 16 positions are for seconds
			LCD_vidInstruction(0x4E + (1<<7), write_operation, IR);
			// Type two zeros in seconds lane
			LCD_vidInstruction(0x30, write_operation, DR);
			LCD_vidInstruction(0x30, write_operation, DR);
		}
	}

	else if(seconds < 10)
	{
		// 15 and 16 positions are for seconds
		if(hide_me)
		{
			// Hide the clock
		}
		else
		{
			LCD_vidInstruction(0x4D + (1<<7), write_operation, IR);
			LCD_String(":");

			//LCD_vidGoTo(15, 1);
			LCD_vidInstruction(0x4E + (1<<7), write_operation, IR);
			// Type zero at the beginning then seconds
			LCD_vidInstruction(0x30, write_operation, DR);
			LCD_vidInstruction(seconds + 0x30, write_operation, DR);
		}
	}

	else
	{
		if(hide_me)
		{
			// Hide the clock
		}
		else
		{
			LCD_vidInstruction(0x4D + (1<<7), write_operation, IR);
			LCD_String(":");

			LCD_vidInstruction(0x4E + (1<<7), write_operation, IR);
			LCD_vidInstruction((seconds/10 + 0x30), write_operation, DR);
			LCD_vidInstruction((seconds%10 + 0x30), write_operation, DR);
		}
	}
	MINUTES_CALL();
}

void MINUTES_CALL (void)
{
	if(minutes >= 60)
	{
		minutes = 0;
		hours++;

		// Indication for minutes

		if(hide_me)
		{
			// Hide the clock
		}
		else
		{
			LCD_vidInstruction(0x4A + (1<<7), write_operation, IR);
			LCD_String(":");

			// 12 and 13 positions are  for minutes lane
			LCD_vidInstruction(0x4B + (1<<7), write_operation, IR);
			// Type two zeros
			LCD_vidInstruction(0x30, write_operation, DR);
			LCD_vidInstruction(0x30, write_operation, DR);
		}
	}
	else if(minutes < 10)
	{
		// Indication for minutes
		if(hide_me)
		{
			// Hide the clock
		}
		else
		{
			LCD_vidInstruction(0x4A + (1<<7), write_operation, IR);
			LCD_String(":");

			// 12 and 13 positions are  for minutes
			LCD_vidInstruction(0x4B + (1<<7), write_operation, IR);
			// Type zero at the beginning then minutes
			LCD_vidInstruction(0x30, write_operation, DR);
			LCD_vidInstruction(minutes + 0x30, write_operation, DR);
		}
	}
	else
	{
		if(hide_me)
		{
			// Hide the clock
		}
		else
		{
			LCD_vidInstruction(0x4A + (1<<7), write_operation, IR);
			LCD_String(":");

			// 12 and 13 positions are  for minutes
			LCD_vidInstruction(0x4B + (1<<7), write_operation, IR);
			LCD_vidInstruction((minutes/10 + 0x30), write_operation, DR);
			LCD_vidInstruction((minutes%10 + 0x30), write_operation, DR);
		}
	}
	HOURS_CALL();
}

void HOURS_CALL (void)
{
	if(hide_me)
	{

	}
	else
	{
		if(hours < 10)
		{
			// 9 and 10 positions are  for hours;
			LCD_vidInstruction(0x48 + (1<<7), write_operation, IR);
			LCD_vidInstruction(0x30, write_operation, DR);
			LCD_vidInstruction(hours + 0x30, write_operation, DR);
		}
		else
		{
			LCD_vidInstruction(0x48 + (1<<7), write_operation, IR);
			LCD_vidInstruction(hours / 10 + 0x30, write_operation, DR);
			LCD_vidInstruction(hours % 10 + 0x30, write_operation, DR);
		}
	}
}
