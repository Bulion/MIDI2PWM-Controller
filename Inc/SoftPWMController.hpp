#pragma once
#include "stm32f7xx.h"
#include "PWMController.hpp"

class SoftPWMController : public PWMController
{
public:
    SoftPWMController(GPIO_TypeDef *gpioPort, uint16_t gpioPin);
    ~SoftPWMController();

    uint8_t getResolution()            override;
    void    setPWMValue(uint8_t value) override;

    static void updateOutputs();
    static void setResolution(uint8_t resolution);

private:
    static constexpr uint8_t MAX_SOFT_PWM_INSTANCES = 38;
    static constexpr uint8_t MAX_SOFT_PWM_RESOLUTION = 127;

    static uint8_t instancesCounter;
    static uint8_t resolution;
    static SoftPWMController *softPWMInstancesArray[MAX_SOFT_PWM_INSTANCES];

    GPIO_TypeDef *gpioPort;
    uint16_t      gpioPin;
    uint8_t       PWMValue;
};
