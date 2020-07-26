#include "SoftPWMController.hpp"
#include "gpio.h"

#include <cstdio>

uint8_t            SoftPWMController::instancesCounter = 0;
uint8_t            SoftPWMController::resolution = MAX_SOFT_PWM_RESOLUTION;
SoftPWMController *SoftPWMController::softPWMInstancesArray[MAX_SOFT_PWM_INSTANCES] = {nullptr};

uint8_t remapValue(uint8_t value, uint8_t start1, uint8_t stop1, uint8_t start2, uint8_t stop2)
{
    return static_cast<uint8_t>(start2 + static_cast<float>(stop2 - start2) * (static_cast<float>(value - start1) / static_cast<float>(stop1 - start1)));
}

SoftPWMController::SoftPWMController(GPIO_TypeDef *gpioPort, uint16_t gpioPin,
                                     I2C_HandleTypeDef *i2cHandler, uint32_t i2cAddress, uint8_t i2cIOPairNumber) :
      gpioPort(gpioPort)
    , gpioPin(gpioPin)
    , PWMValue(0)
    , midpointValue(0)
    , i2cHandler(i2cHandler)
    , i2cAddress(i2cAddress)
    , i2cIOPairNumber(i2cIOPairNumber)
{
    if(instancesCounter < MAX_SOFT_PWM_INSTANCES)
    {
        softPWMInstancesArray[instancesCounter++] = this;
    }
    else
    {
        std::printf("To many SoftPWMController instances!");
        while(1) {}
    }

}

SoftPWMController::~SoftPWMController() {}

void SoftPWMController::setPWMValue(uint8_t value)
{
    uint8_t remapedValue = 0;
    if(value > MAX_SOFT_PWM_RESOLUTION)
    {
        value = MAX_SOFT_PWM_RESOLUTION;
    }
    if(value != midpointValue)
    {
        if(value == 0 || value == MAX_SOFT_PWM_RESOLUTION)
        {
            remapedValue = resolution + 1;
        }
        else if(value < midpointValue)
        {
            remapedValue = remapValue(value, midpointValue, 0, 0, resolution);
        }
        else
        {
            remapedValue = remapValue(value, midpointValue, MAX_SOFT_PWM_RESOLUTION, 0, resolution);
        }
    }

    PWMValue = remapedValue;
}

void SoftPWMController::setMidpoint(uint8_t value)
{
    midpointValue = value;
    setPWMValue(PWMValue);
}

void SoftPWMController::turnOffOutput()
{

}

void SoftPWMController::turnOnOutput()
{

}

void SoftPWMController::updateOutputs()
{
    static uint8_t pwmCounter = 0;
    for(uint8_t i = 0; i < instancesCounter; ++i)
    {
        if(softPWMInstancesArray[i]->PWMValue > pwmCounter)
        {
            LL_GPIO_SetOutputPin(softPWMInstancesArray[i]->gpioPort, softPWMInstancesArray[i]->gpioPin);
        }
        else
        {
            LL_GPIO_ResetOutputPin(softPWMInstancesArray[i]->gpioPort, softPWMInstancesArray[i]->gpioPin);
        }
    }
    ++pwmCounter;
    if(pwmCounter > resolution) { pwmCounter = 0; }
}

void SoftPWMController::setResolution(uint8_t res)
{
    if (res > MAX_SOFT_PWM_RESOLUTION)
    {
        res = MAX_SOFT_PWM_RESOLUTION;
    }
    resolution = res;
}
