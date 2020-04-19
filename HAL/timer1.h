/*
 * timer1.h
 *
 *  Created on: Sep 7, 2019
 *      Author: Newname
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "../macros.h"
#include "../types.h"


void Timer1_vidInitialtize(u16 scale);
f32 Timer1_vidPreScaler(u16 scale);
void Timer1_vidSetOCRValue(u16 counts);
void Timer1_setcallback(void(*function)(void));


#endif /* TIMER1_H_ */
