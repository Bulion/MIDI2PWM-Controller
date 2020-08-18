#include "SoftPWMController.hpp"
#include "gpio.h"

uint8_t            SoftPWMController::instancesCounter = 0;
uint8_t            SoftPWMController::resolution = MAX_SOFT_PWM_RESOLUTION;
SoftPWMController *SoftPWMController::softPWMInstancesArray[MAX_SOFT_PWM_INSTANCES] = {nullptr};

SoftPWMController::SoftPWMController(GPIO_TypeDef *gpioPort, uint16_t gpioPin) :
      gpioPort(gpioPort)
    , gpioPin(gpioPin)
    , PWMValue(0)
{
    if(instancesCounter < MAX_SOFT_PWM_INSTANCES)
    {
        softPWMInstancesArray[instancesCounter++] = this;
    }
    else
    {
        while(1) {}
    }
}

SoftPWMController::~SoftPWMController() {}

uint8_t SoftPWMController::getResolution()
{
    return resolution;
}

void SoftPWMController::setPWMValue(uint8_t value)
{
    if(value > resolution)
    {
        value = resolution;
    }
    PWMValue = value;
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
