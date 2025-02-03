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

ADC_HandleTypeDef adcHandle;

void ConfigureADC()
{
    ADC_ChannelConfTypeDef adcChannel;
 
    adcHandle.Instance = ADC1;
 
    adcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
    adcHandle.Init.Resolution = ADC_RESOLUTION_12B;
    adcHandle.Init.ScanConvMode = DISABLE;
    adcHandle.Init.ContinuousConvMode = ENABLE;
    adcHandle.Init.DiscontinuousConvMode = DISABLE;
    adcHandle.Init.NbrOfDiscConversion = 0;
    adcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    adcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    adcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    adcHandle.Init.NbrOfConversion = 1;
    adcHandle.Init.DMAContinuousRequests = ENABLE;
    adcHandle.Init.EOCSelection = DISABLE;

 
    HAL_ADC_Init(&adcHandle);
     
    adcChannel.Channel = ADC_CHANNEL_10;
    adcChannel.Rank = 1;
    adcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
    adcChannel.Offset = 0;
 
    HAL_ADC_ConfigChannel(&adcHandle, &adcChannel);
}

uint16_t buff;

void DMA2_Stream0_Handler()
{
    printf( "Conversion complete: %d\n", buff );
}

void main()
{
    HAL_Init();

    SystemClock_Config();

    UsartPrint_Init();

    ConfigureADC();


    HAL_ADC_Start_DMA( &adcHandle, (uint32_t*)&buff, sizeof( buff ) );

    while (1)
    {
    }

}

DMA_HandleTypeDef dma_init;

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
    // Enable adc clock __HAL_RCC_ADC_CLK_ENABLE()
    __HAL_RCC_ADC1_CLK_ENABLE();

    // Enable gpio port clocks
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef gpio_init =
    {
        .Pin = GPIO_PIN_0,
        .Mode = GPIO_MODE_ANALOG,
        .Pull = GPIO_NOPULL
    };

    HAL_GPIO_Init(GPIOC, &gpio_init);


    // DMA

    // Enable DMA2 interface clock
    __HAL_RCC_DMA2_CLK_ENABLE();
    
    // Config DMA then call dma init
    dma_init.Instance = DMA2_Stream0;
    dma_init.Init.Channel = DMA_CHANNEL_0;
    dma_init.Init.Direction = DMA_PERIPH_TO_MEMORY;
    dma_init.Init.PeriphInc = DMA_PINC_DISABLE;
    dma_init.Init.MemInc = DMA_MINC_ENABLE;
    dma_init.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    dma_init.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    dma_init.Init.Mode = DMA_CIRCULAR;
    dma_init.Init.Priority = DMA_PRIORITY_HIGH;
    dma_init.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    dma_init.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    dma_init.Init.MemBurst = DMA_MBURST_SINGLE;
    dma_init.Init.PeriphBurst = DMA_PBURST_SINGLE;

    HAL_DMA_Init( &dma_init );

    // Configure priority and enable NVIC for transfer complete interrupt on DMA stream
    HAL_NVIC_SetPriority( DMA2_Stream0_IRQn , 1, 1 );
    HAL_NVIC_EnableIRQ( DMA2_Stream0_IRQn );

    // Sets the adc handles member pointer (DMA_Handle) to a dma handle to the one configured above
    __HAL_LINKDMA( hadc, DMA_Handle, dma_init );
}

void Systick_Handler()
{
    HAL_IncTick();
}
