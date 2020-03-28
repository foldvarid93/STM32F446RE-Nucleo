/*********************************************************************/
#ifndef EXTENSIONBOARD_H
#define EXTENSIONBOARD_H
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "crc.h"
#include "GUI.h"
#include "S6D04D1.h"

/*********************************************************************/
/*********************************************************************/
void BoardInit(void);
void InitEncoder(void);
void InitPWM(void);
uint8_t ReadIOExpander(void);
void WriteIOExpander(uint8_t);
void SetBackLightPWM(uint16_t);
void SetHBridgePWM(uint16_t);
void InitPCF8574(void);
/*********************************************************************/
#endif
/*********************************************************************/
