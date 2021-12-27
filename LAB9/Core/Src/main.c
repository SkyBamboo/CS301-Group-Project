/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t myMessage[25];
uint8_t mateMessage[25];
int x = 20;
int y = 20;
int* x_base = &x;
int* y_base = &y;
int IsSetUp = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void connectionCheck(){
	LCD_ShowString(10, 0, 90, 19, 12, (uint8_t*)"192.168.0.123");
    LCD_ShowString(145, 5, 90, 10, 12, (uint8_t*)"CS301 Project");
    POINT_COLOR = BLACK;
    LCD_DrawLine(0,20,239,20);
    LCD_DrawLine(20,20,20,319);
    LCD_DrawLine(221,20,221,319);
	BACK_COLOR = WHITE;
    if (IsSetUp) {
		POINT_COLOR = RED;
		LCD_Draw_Circle(120, 10, 6);
		LCD_Draw_Circle(120, 10, 5);
		LCD_Draw_Circle(120, 10, 4);
		LCD_Draw_Circle(120, 10, 3);
		LCD_Draw_Circle(120, 10, 2);
		LCD_Draw_Circle(120, 10, 1);
		//DrawCircle(120, 10, 5);
    }else{
		POINT_COLOR = GREEN;
		LCD_Draw_Circle(120, 10, 6);
		POINT_COLOR = WHITE;
		LCD_Draw_Circle(120, 10, 5);
		LCD_Draw_Circle(120, 10, 4);
		LCD_Draw_Circle(120, 10, 3);
		LCD_Draw_Circle(120, 10, 2);
		LCD_Draw_Circle(120, 10, 1);
		//DrawCircle(120, 10, 6);
    }
}
void calculateDisplayBase(uint8_t *string, int *x_base, int *y_base, int mode) {
    int x = *x_base;
    int y = *y_base;
    int length = strlen(string);
    int row = 0;
    if (length % 25 != 0) {
        row = length / 25 + 1;
    } else {
        row = length / 25;
    }
    if (row * 15 + 10 + y >= 320) {
        //TODO: clean the screen.
        *x_base = 20;
        *y_base = 20;
        x = 20;
        y = 20;
        LCD_Clear(WHITE);
        connectionCheck();
    }
    if (mode == 1) {
        x = 20;
        LCD_Fill(1,y,19,y+15,BLUE);
        POINT_COLOR = BLUE;
    } else if (mode == 0) {
        LCD_Fill(221,y,239,y+15,BLACK);
        POINT_COLOR = BLACK;
        if (row > 1) {
            x = 20;
        } else {
            x = 200 - 8 * length;
        }

    }
    LCD_ShowString(x, y, 200 - x, row * 15, 16, string);
    y += row * 15 + 10;
    *x_base = x;
    *y_base = y;

}

void showString(uint8_t *string, int mode){
	calculateDisplayBase(string, x_base, y_base, mode);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  LCD_Init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  //HAL_UART_Receive_IT(&huart1,(uint8_t*)aRxBuffer,11);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  connectionCheck();
  while (1)
  {
	  calculateDisplayBase((uint8_t*)"Is earth flat? wawaksdjadanak", x_base, y_base, 1);
	  calculateDisplayBase((uint8_t*)"FALSE", x_base, y_base, 0);
	  HAL_Delay(5000);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */




/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
