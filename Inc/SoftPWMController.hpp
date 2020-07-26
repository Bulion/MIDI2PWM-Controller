#pragma once
#include "stm32f7xx.h"
#include "PWMController.hpp"

typedef struct {
    GPIO_TypeDef *gpioPort;
    uint16_t      gpioPin;
    uint8_t       PWMValue;
} softPWM_TypeDef;

class SoftPWMController : public PWMController
{
public:
    SoftPWMController(GPIO_TypeDef *gpioPort, uint16_t gpioPin,
                      I2C_TypeDef *i2cHandler, uint8_t i2cAdress, uint8_t i2cIOPairNumber);
    ~SoftPWMController();

    void setPWMValue(uint8_t value) override;
    void setMidpoint(uint8_t value) override;
    void turnOffOutput()            override;
    void turnOnOutput()             override;

    static void updateOutputs();
    static void setResolution(uint8_t resolution);

private:
    static constexpr uint8_t MAX_SOFT_PWM_INSTANCES = 38;
    static uint8_t instancesCounter;
    static uint8_t resolution;
    static softPWM_TypeDef softPWMInstancesArray[MAX_SOFT_PWM_INSTANCES];

    softPWM_TypeDef *instance;
    uint8_t midpointValue;

    I2C_TypeDef *i2cHandler;
    uint8_t      i2cAddress;
    uint8_t      i2cIOPairNumber;
};
