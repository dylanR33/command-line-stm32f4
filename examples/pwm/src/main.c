#include <stdint.h>

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_flash_ex.h"

#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_gpio_ex.h"

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  //__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSI Oscillator and activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON; RCC_OscInitStruct.HSICalibrationValue = 0x10;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3);
  
}

void main()
{
    HAL_Init();

    SystemClock_Config();

    TIM_HandleTypeDef tim =
    {
        .Instance = TIM3,

        .Init = 
        {
            .Prescaler = 0x0000, // Between 0x0000 - 0xFFFF
            .CounterMode = TIM_COUNTERMODE_UP, // a value of TIM_Counter_Mode
            .Period = 0x00FF,        // 0x0000 - 0xFFFF
            .ClockDivision = TIM_CLOCKDIVISION_DIV1, // a value of TIM_ClockDivision
        }
    };

    TIM_OC_InitTypeDef tim_init =
    {
        .OCMode = TIM_OCMODE_PWM1,
        .Pulse =  0x00AF,
        .OCPolarity = TIM_OCPOLARITY_HIGH,
        .OCFastMode = TIM_OCFAST_DISABLE
    };

    HAL_TIM_PWM_Init(&tim);

    HAL_TIM_PWM_ConfigChannel(&tim, &tim_init, TIM_CHANNEL_3);

    HAL_TIM_PWM_Start(&tim, TIM_CHANNEL_3);

    while (1);

}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{

    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef gpio_init =
    {
        .Pin = GPIO_PIN_0,
        .Mode = GPIO_MODE_AF_PP,
        .Speed = GPIO_SPEED_LOW,
        .Alternate = GPIO_AF2_TIM3
    };

    HAL_GPIO_Init(GPIOB, &gpio_init);
}

void Systick_Handler()
{
    HAL_IncTick();
}
