#ifndef RCC_H_
#define RCC_H_

/*****************************************************************************/
/*                              Includes                                     */
/*****************************************************************************/
#include <stdint.h>
#include "LIB/bitMasks.h"
#include "rcc_prescalers.h"

/*****************************************************************************/
/*                              Defines                                      */
/*****************************************************************************/
#define RETURN_OK               0
#define RETURN_NOT_OK           1

#define CLK_READY               1
#define CLK_NOT_READY           0

/*  clock enable/disable/getStatus  */
#define CLOCK_HSI                BIT0_MASK
#define CLOCK_HSE                BIT16_MASK
#define CLOCK_PLL                BIT24_MASK
#define CLOCK_PLLI2S             BIT26_MASK

#define MCO_PRE_1                0x0
#define MCO_PRE_2                0x4
#define MCO_PRE_3                0x5
#define MCO_PRE_4                0x6
#define MCO_PRE_5                0x7

#define MCO1_SRC_HSI             0x0
#define MCO1_SRC_LSE             0x200000
#define MCO1_SRC_HSE             0x400000
#define MCO1_SRC_PLL             0x600000

#define MCO2_SRC_SYSCLK          0x0
#define MCO2_SRC_PLLI2S          0x40000000
#define MCO2_SRC_HSE             0x80000000
#define MCO2_SRC_PLL             0xC0000000

#define SYSCLK_HSI              0x00
#define SYSCLK_HSE              0x01
#define SYSCLK_PLL              0x02

#define PLL_SRC_HSI             0x0
#define PLL_SRC_HSE             BIT22_MASK

#define PERIPH_STATE_ENABLED    0
#define PERIPH_STATE_DISABLED   1

#define APB1_PERIPH_TIM2        BIT0_MASK            
#define APB1_PERIPH_TIM3        BIT1_MASK   
#define APB1_PERIPH_TIM4        BIT2_MASK   
#define APB1_PERIPH_TIM5        BIT3_MASK   
#define APB1_PERIPH_WWDG        BIT11_MASK            
#define APB1_PERIPH_SPI2        BIT14_MASK            
#define APB1_PERIPH_SPI3        BIT15_MASK 
#define APB1_PERIPH_USART2      BIT17_MASK      
#define APB1_PERIPH_I2C1        BIT21_MASK    
#define APB1_PERIPH_I2C2        BIT22_MASK    
#define APB1_PERIPH_I2C3        BIT23_MASK    
#define APB1_PERIPH_PWR         BIT28_MASK 

#define APB2_PERIPH_TIM1        BIT0_MASK            
#define APB2_PERIPH_USART1      BIT4_MASK      
#define APB2_PERIPH_USART6      BIT5_MASK      
#define APB2_PERIPH_ADC1        BIT8_MASK    
#define APB2_PERIPH_SDIO        BIT11_MASK    
#define APB2_PERIPH_SPI1        BIT12_MASK    
#define APB2_PERIPH_SPI4        BIT13_MASK    
#define APB2_PERIPH_SYSCFG      BIT14_MASK      
#define APB2_PERIPH_TIM9        BIT16_MASK    
#define APB2_PERIPH_TIM10       BIT17_MASK     
#define APB2_PERIPH_TIM11       BIT18_MASK

#define AHB1_PERIPH_GPIOA       BIT0_MASK            
#define AHB1_PERIPH_GPIOB       BIT1_MASK     
#define AHB1_PERIPH_GPIOC       BIT2_MASK     
#define AHB1_PERIPH_GPIOD       BIT3_MASK     
#define AHB1_PERIPH_GPIOE       BIT4_MASK     
#define AHB1_PERIPH_GPIOH       BIT7_MASK     
#define AHB1_PERIPH_CRC         BIT12_MASK   
#define AHB1_PERIPH_DMA1        BIT21_MASK    
#define AHB1_PERIPH_DMA2        BIT22_MASK    

#define AHB2_PERIPH_OTGFS       BIT7_MASK     

/*****************************************************************************/
/*                              Types                                        */
/*****************************************************************************/


/*****************************************************************************/
/*                          Function Prototypes                              */
/*****************************************************************************/
uint8_t rcc_selectSysClk(uint8_t sysClk);
uint8_t rcc_getSysClk(uint8_t *sysClk);

uint8_t rcc_getClkStatus(uint8_t clock, uint8_t* clockStatus);

uint8_t rcc_enableClk(uint8_t clock);
uint8_t rcc_disableClk(uint8_t clock);
/**
 * Clock source selection may generate glitches on MCO1. It is
 * highly recommended to configure these bits only after reset before enabling the external
 * oscillators and PLL
 * max = gpio max = 100 MHz
*/
uint8_t rcc_configMCO1(uint8_t MCO1_Src, uint8_t MCO_Pre);
uint8_t rcc_configMCO2(uint8_t MCO2_Src, uint8_t MCO_Pre);

/**
 * PLL_source :
 * PLL_N : 192 ~ 432
 * PLL_clk = src * N / (M * P)
 * PLL_48CK = src * N / (M * Q)
*/
uint8_t rcc_configPLL(uint8_t PLL_src, uint16_t PLL_N, uint8_t PLL_M, uint8_t PLL_P, uint8_t PLL_Q);

/**
 * max 42 MHz
*/
uint8_t rcc_configAPB1(uint8_t APB_pre);
/**
 * max 84 MHz
*/
uint8_t rcc_configAPB2(uint8_t APB_pre);
uint8_t rcc_configAHB(uint8_t AHB_pre);

uint8_t rcc_controlAPB1Peripheral(uint32_t APB1_periph, uint8_t periph_state);
uint8_t rcc_controlAPB2Peripheral(uint32_t APB2_periph, uint8_t periph_state);
uint8_t rcc_controlAHB1Peripheral(uint32_t AHB1_periph, uint8_t periph_state);
uint8_t rcc_controlAHB2Peripheral(uint32_t AHB2_periph, uint8_t periph_state);


/**
 * PLLI2S_N : 192 ~ 432
 * PLLI2S_clk = src * PLLI2S_N / (M * PLLI2S_R)
*/
//uint8_t rcc_configPLLI2S(uint16_t PLLI2S_N, uint8_t PLLI2S_R);
//uint8_t rcc_enableClk_HSE_BYP();


#endif /* RCC_H_ */