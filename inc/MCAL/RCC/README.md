# RCC Driver

## Implemented functionalities so far

### Clock control

```c
uint8_t rcc_enableClk(uint8_t clock);
uint8_t rcc_disableClk(uint8_t clock);
uint8_t rcc_getClkStatus(uint8_t clock, uint8_t* clockStatus);
```

### System clock control

```c
uint8_t rcc_selectSysClk(uint8_t sysClk);
uint8_t rcc_getSysClk(uint8_t *sysClk);
```

### PLL clock configuration

```c
uint8_t rcc_configPLL(uint8_t PLL_src, uint16_t PLL_N, uint8_t PLL_M, uint8_t PLL_P, uint8_t PLL_Q);
```

### Peripheral busses configuration

```c
uint8_t rcc_configAPB1(uint8_t APB_pre);
uint8_t rcc_configAPB2(uint8_t APB_pre);
uint8_t rcc_configAHB(uint8_t AHB_pre);
```

### Peripheral control

```c
uint8_t rcc_controlAPB1Peripheral(uint32_t APB1_periph, uint8_t periph_state);
uint8_t rcc_controlAPB2Peripheral(uint32_t APB2_periph, uint8_t periph_state);
uint8_t rcc_controlAHB1Peripheral(uint32_t AHB1_periph, uint8_t periph_state);
uint8_t rcc_controlAHB2Peripheral(uint32_t AHB2_periph, uint8_t periph_state);
```

### Microcontroller clock output configuration

```c
uint8_t rcc_configMCO1(uint8_t MCO1_Src, uint8_t MCO_Pre);
uint8_t rcc_configMCO2(uint8_t MCO2_Src, uint8_t MCO_Pre);
```
