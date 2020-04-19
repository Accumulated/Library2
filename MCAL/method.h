/*
 * method.h
 *
 *  Created on: Sep 4, 2019
 *      Author: Newname
 */

#ifndef METHOD_H_
#define METHOD_H_

#include "DIO.h"
/*GLOBAL INTERRUPT FLAG in SREG*/
#define I_G_flag	7	// Bit #7 in SREG

// Another way of implementation (better implementation)
/*#define ISR(vector_No)	\
	void __vector_##(vector_No) (void) __attribute__(signal);	\
	void __vector_##(vector_No) (void)*/
/*
#define ISR(x)	void __vector_##x (void) __attribute__(signal); \
					void __vector_##x (void)*/

#  define ISR(vector)            \
    void __vector_##vector (void) __attribute__ ((signal)); \
    void __vector_##vector (void)


/*EXTERNAL HARDWARE INTERRUPT PIN in GICR*/
#define INT0_BIT	6	// Bit #6 in GICR
#define INT1_BIT	7	// Bit #7 in GICR
#define INT2_BIT	5	// Bit #5 in GICR


/*INICATIONS FOR triggering either edge or level in MCUCR, MCUCSR*/
#define ISC00_BIT	0	// Bit #0 in MCUCR
#define ISC01_BIT	1	// Bit #1 in MCUCR
#define ISC10_BIT	2	// Bit #2 in MCUCR
#define ISC11_BIT	3	// Bit #3 in MCUCR
#define ISC2_BIT	6	// Bit #6 in MCUCSR


/*VECTOR TABLE*/


/* Control */
#define ENABLE	1
#define DISABLE	0



void INTERRUPT_vidGlobalEnable(u8 MODE);
void INTERRUPT_vidSetInterrupt(u8 PIN_NAME);
void INTERRUPT_vidclrInterrupt(u8 PIN_NAME);
void INTERRUPT_vidSetMCUPin(u8 pin_name);
void INTERRUPT_vidClrMCUPin(u8 pin_name);










#endif /* METHOD_H_ */
