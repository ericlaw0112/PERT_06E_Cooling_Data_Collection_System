#include "Thermistor.h"

static ThermistorConfig thermistorConfigs[THERMISTOR_COUNT];

#define A 0.001450787363
#define B 0.0002347177854
#define C 0.00000007681335396

void Thermistor_Init(ThermistorConfig* configs)
{
    for(int i = 0; i < THERMISTOR_COUNT; i++)
    {
        thermistorConfigs[i] = configs[i];
    }
}

static uint32_t Thermistor_ReadRaw(uint8_t index) {
    ADC_ChannelConfTypeDef sConfig = {0};

    // sConfig.Channel = thermistorConfigs[index].channel;
    // sConfig.Rank = ADC_REGULAR_RANK_1;
    // sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    // HAL_ADC_ConfigChannel(thermistorConfigs[index].hadc, &sConfig);

    HAL_ADC_Start(thermistorConfigs[index].hadc);
    HAL_ADC_PollForConversion(thermistorConfigs[index].hadc, HAL_MAX_DELAY);

    uint32_t rawValue = HAL_ADC_GetValue(thermistorConfigs[index].hadc);
    HAL_ADC_Stop(thermistorConfigs[index].hadc);

    return rawValue;
}

// Function to convert raw ADC value to temperature in Celsius
float Thermistor_GetTemperature(uint8_t index) {
    uint32_t rawValue = Thermistor_ReadRaw(index);
    float resistance = (4095.0f / (float)rawValue) - 1.0f;
    resistance = 10000.0f / resistance;

    float temperature;
    temperature = resistance / 10000.0f;                  // (R/R0)
    temperature = log(temperature);                      // ln(R/R0)
    temperature = 1.0f / (A + (B + (C * temperature * temperature )) * temperature); // Calculate temperature
    temperature = temperature - 273.15f;                 // Convert Kelvin to Celsius

    return temperature;
}