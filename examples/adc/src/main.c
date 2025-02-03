#include <stdint.h>
#include <stdio.h>

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_rcc_ex.h"

#include "stm32f4xx_hal_flash_ex.h"

#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_gpio_ex.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_cortex.h"


#include "usart_print.h"

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

ADC_HandleTypeDef adc1Handle;
ADC_HandleTypeDef adc2Handle;
ADC_HandleTypeDef adc3Handle;

void ConfigureADC()
{
    ADC_ChannelConfTypeDef adc1Channel;
 
    adc1Handle.Instance = ADC1;
 
    adc1Handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
    adc1Handle.Init.Resolution = ADC_RESOLUTION_12B;
    adc1Handle.Init.ScanConvMode = DISABLE;
    adc1Handle.Init.ContinuousConvMode = ENABLE;
    adc1Handle.Init.DiscontinuousConvMode = DISABLE;
    adc1Handle.Init.NbrOfDiscConversion = 0;
    adc1Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    adc1Handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    adc1Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    adc1Handle.Init.NbrOfConversion = 1;
    adc1Handle.Init.DMAContinuousRequests = ENABLE;
    adc1Handle.Init.EOCSelection = DISABLE;

 
    HAL_ADC_Init(&adc1Handle);
     
    adc1Channel.Channel = ADC_CHANNEL_10;
    adc1Channel.Rank = 1;
    adc1Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    adc1Channel.Offset = 0;
 
    HAL_ADC_ConfigChannel(&adc1Handle, &adc1Channel);


    ADC_ChannelConfTypeDef adc2Channel;
 
    adc2Handle.Instance = ADC2;
 
    adc2Handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
    adc2Handle.Init.Resolution = ADC_RESOLUTION_12B;
    adc2Handle.Init.ScanConvMode = DISABLE;
    adc2Handle.Init.ContinuousConvMode = ENABLE;
    adc2Handle.Init.DiscontinuousConvMode = DISABLE;
    adc2Handle.Init.NbrOfDiscConversion = 0;
    adc2Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    adc2Handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    adc2Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    adc2Handle.Init.NbrOfConversion = 1;
    adc2Handle.Init.DMAContinuousRequests = ENABLE;
    adc2Handle.Init.EOCSelection = DISABLE;

 
    HAL_ADC_Init(&adc2Handle);
     
    adc2Channel.Channel = ADC_CHANNEL_11;
    adc2Channel.Rank = 1;
    adc2Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    adc2Channel.Offset = 0;
 
    HAL_ADC_ConfigChannel(&adc2Handle, &adc2Channel);


    ADC_ChannelConfTypeDef adc3Channel;
 
    adc3Handle.Instance = ADC3;
 
    adc3Handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
    adc3Handle.Init.Resolution = ADC_RESOLUTION_12B;
    adc3Handle.Init.ScanConvMode = DISABLE;
    adc3Handle.Init.ContinuousConvMode = ENABLE;
    adc3Handle.Init.DiscontinuousConvMode = DISABLE;
    adc3Handle.Init.NbrOfDiscConversion = 0;
    adc3Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    adc3Handle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    adc3Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    adc3Handle.Init.NbrOfConversion = 1;
    adc3Handle.Init.DMAContinuousRequests = ENABLE;
    adc3Handle.Init.EOCSelection = DISABLE;

 
    HAL_ADC_Init(&adc3Handle);
     
    adc3Channel.Channel = ADC_CHANNEL_12;
    adc3Channel.Rank = 1;
    adc3Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    adc3Channel.Offset = 0;
 
    HAL_ADC_ConfigChannel(&adc3Handle, &adc3Channel);

}

void main()
{
    HAL_Init();

    SystemClock_Config();

    UsartPrint_Init();

    ConfigureADC();

    HAL_ADC_Start( &adc1Handle );
    HAL_ADC_Start( &adc2Handle );
    HAL_ADC_Start( &adc3Handle );

    while (1)
    {
        HAL_ADC_PollForConversion( &adc1Handle, 1000 );
        printf("ADC1: %d\n", HAL_ADC_GetValue( &adc1Handle ) );
        
        HAL_ADC_PollForConversion( &adc2Handle, 1000 );
        printf("ADC2: %d\n", HAL_ADC_GetValue( &adc2Handle ) );

        HAL_ADC_PollForConversion( &adc3Handle, 1000 );
        printf("ADC3: %d\n", HAL_ADC_GetValue( &adc3Handle ) );

        printf("\n");
        HAL_Delay(100);

    }

}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
    // Enable adc clock __HAL_RCC_ADC_CLK_ENABLE()
    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_ADC2_CLK_ENABLE();
    __HAL_RCC_ADC3_CLK_ENABLE();

    // Enable gpio port clocks
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef gpio_init =
    {
        .Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2,
        .Mode = GPIO_MODE_ANALOG,
        .Pull = GPIO_NOPULL
    };

    HAL_GPIO_Init(GPIOC, &gpio_init);
}

void Systick_Handler()
{
    HAL_IncTick();
}
