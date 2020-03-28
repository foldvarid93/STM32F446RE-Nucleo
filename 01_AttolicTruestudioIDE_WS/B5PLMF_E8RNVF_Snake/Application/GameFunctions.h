/*
 * GameFunctions.h
 *
 *  Created on: 2017. nov. 25.
 *      Author: David
 */

#ifndef GAMEFUNCTIONS_H_
#define GAMEFUNCTIONS_H_

#include <stm32f4xx.h>
#include "stm32f429i_discovery.h"
#include "mytype.h"
#include "stdbool.h"
#include "stdio.h"
#include "math.h"
#include "gyroscope.h"
#include "touch.h"
#include "drawing.h"
#include "display.h"
#include "Common.h"

void Random(void);
void SnakeInitialization(void);
void Print(void);
void SnakeGame(void);

#endif /* GAMEFUNCTIONS_H_ */
