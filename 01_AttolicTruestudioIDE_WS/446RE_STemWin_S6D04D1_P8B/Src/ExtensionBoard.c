#include "ExtensionBoard.h"
/*********************************************************************/
//Author: Dávid Földvári
//github: foldvarid93
//Version: 1.0
//HW Version: 1.0
/*********************************************************************/
//board initialization
/*********************************************************************/
void BoardInit(void){
	//Timer
	InitEncoder();//initialize encoder input and timer
	InitPWM();//LCD backlight and H-bridge PWM init
	SetHBridgePWM(100);//H bridge PWM signal
	//I2C
	MX_I2C3_Init();//init I2C3 I2C peripheral
	InitPCF8574();//init port extension I2C slave
	//SPI

	//LCD
	MX_CRC_Init();//need for GUI
	GUI_Init();//init gui
	GUI_Clear();//
	//Analog

	//Uart

}
/*********************************************************************/
//Timer
/*********************************************************************/
void InitEncoder(void){
	MX_TIM3_Init();
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	TIM3->CNT=0x7FFF;
}
/*********************************************************************/
void InitPWM(void){
	MX_TIM2_Init();
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1|TIM_CHANNEL_2);
}
/*********************************************************************/
void SetBackLightPWM(uint16_t value){
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = value;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}
/*********************************************************************/
void SetHBridgePWM(uint16_t value){
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = value;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}
/*********************************************************************/
/*********************************************************************/
//I2C
/*********************************************************************/
void InitPCF8574(void){
	uint8_t data=0B10011111;
	HAL_I2C_Master_Transmit(&hi2c3,0x40,&data,1,100);
}
/*********************************************************************/
uint8_t ReadIOExpander(void){
	uint8_t data;
	HAL_I2C_Master_Receive(&hi2c3,0x41,&data,1,100);
	return data;
}
/*********************************************************************/
void WriteIOExpander(uint8_t value){
	uint8_t data=value;
	data|=0B10011111;
	HAL_I2C_Master_Transmit(&hi2c3,0x40,&data,1,100);
}
/*********************************************************************/
void InitMPU6050(void){

}
/*********************************************************************/
void InitLM75(void){

}
/*********************************************************************/
void InitBME280(void){

}
/*********************************************************************/
//SPI
/*********************************************************************/
void ShiftRegister4094(void){

}
/*********************************************************************/

/*********************************************************************/
//Analog
/*********************************************************************/
void LightSensorTEMT6000(void){

}
/*********************************************************************/
void CurrentSensorACS712(void){

}
/*********************************************************************/
void CurrentSensorVNH7100BAS(void){

}
/*********************************************************************/

/*********************************************************************/
//UART
/*********************************************************************/
void ESP8266(void){

}
/*********************************************************************/
