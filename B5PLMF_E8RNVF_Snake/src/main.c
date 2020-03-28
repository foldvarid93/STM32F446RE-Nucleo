/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <stm32f4xx.h>
#include "GameFunctions.h"

static void SystemClock_Config(void);
/**************************************************************************/
#define N 32
#define M 24

int16_t Field[N][M];//N=y,M=x
int16_t x,y;
uint8_t Dir,Length, Game, FoodColor;
bool LastTouchState=false,NewTouchState=true;
uint16_t TimeTick=0, TimerVar=0;
const uint32_t Colors[6]={0xFFFF0000,0xFF00FF00,0xFF0000FF,0xFFFFFF33,0xFFFF9999,0xFF66FFFF};

void ChangeDir(void){
	Pixel p;
	if(Dir==2||Dir==0){
		p.y=DRV_TS_GetY();
		if(p.y<160){
			Dir=1;
		}
		if(p.y>=160){
			Dir=3;
		}
	}
	else if(Dir==3||Dir==1){
		p.x=DRV_TS_GetX();
		if(p.x<120){
			Dir=2;
		}
		if(p.x>=120){
			Dir=0;
		}
	}
}
/*******************************************/
void StartWindow(void){
	Pixel pix={120,160};
	char string[]={"Hello. :)"};
	DRV_Display_Clear();
	DRV_Display_WriteStringAt(pix, &string[0], ALIGN_Center);
	DRV_Display_SwitchBuffer();

}
/*******************************************/
void GameOverWindow(void){
	Pixel pix={120,160};
	char string[]={"Game Over:( Touch!:)"};
	DRV_Display_WriteStringAt(pix, &string[0], ALIGN_Center);
	DRV_Display_SwitchBuffer();
}
/*******************************************/
bool TouchSensing(void){
	if (DRV_TS_IsTouchDetected()) {
		NewTouchState=true;
	}
	else{
		NewTouchState=false;
	}
	if(LastTouchState==false&&NewTouchState==true){
		LastTouchState=NewTouchState;
		return true;
	}
	else if(LastTouchState==true&&NewTouchState==false){
		LastTouchState=NewTouchState;
	}
	return false;
}
/**************************************************************************/
int main(void) {
 	SystemClock_Config();
	HAL_Init();
	DRV_InitTimer();
	DRV_Display_Init();
	DRV_Display_Clear();
	DRV_Gyro_Init();
	DRV_Gyro_Reset();
	DRV_Gyro_Calibration();
	DRV_TS_Init();
	/*******************************************/
	SnakeInitialization();
	Game=2;
	StartWindow();
	/*******************************************/
	while (1) {
		while (Game == 2) {
			if (TouchSensing()) {
				Game = 1;
			}
		}
		while (Game == 1) {
			SnakeGame();
			while (1) {
				if (TimeTick) {
					if (TouchSensing()) {
						ChangeDir();
					}
					TimeTick = 0;
					break;
				}
			}
		}
		while (Game == 0) { //GameOver
			GameOverWindow();
			while(1){
				if (TouchSensing()) {
					SnakeInitialization();
					Game = 1;
					break;
				}
			}
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	TimerVar++;
	if(TimerVar==2){
		TimeTick=1;
		TimerVar=0;
	}
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void){
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Activate the Over-Drive mode */
  HAL_PWREx_EnableOverDrive();

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	DRV_ErrorLoop();

}
#endif
