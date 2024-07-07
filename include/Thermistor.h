#ifndef __THERMISTOR_H__
#define __THERMISTOR_H__

// #include "Arduino.h"
#include "stm32f1xx_hal.h"

#define THERMISTOR_COUNT 5

typedef struct 
{
    ADC_HandleTypeDef* hadc;
    uint32_t channel;

} ThermistorConfig;

void Thermistor_Init(ThermistorConfig* configs);
float Thermistor_GetTemperature(uint8_t index);

#endif /* __THERMISTOR_H__ */

