#pragma once
#include "stm32f7xx.h"
#include "PWMController.hpp"

class SoftPWMController : public PWMController
{
public:
    SoftPWMController(GPIO_TypeDef *gpioPort, uint16_t gpioPin,
                      I2C_HandleTypeDef *i2cHandler, uint32_t i2cAdress, uint8_t i2cIOPairNumber);
    ~SoftPWMController();

    void setPWMValue(uint8_t value) override;
    void setMidpoint(uint8_t value) override;
    void turnOffOutput()            override;
    void turnOnOutput()             override;

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
    uint8_t       midpointValue;

    I2C_HandleTypeDef *i2cHandler;
    uint8_t            i2cAddress;
    uint8_t            i2cIOPairNumber;
};
