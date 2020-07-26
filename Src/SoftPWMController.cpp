#include "SoftPWMController.hpp"
#include "MIDIDecoder.hpp"

uint8_t SoftPWMController::instancesCounter = 0;
uint8_t SoftPWMController::resolution = 127;

uint8_t remapValue(uint8_t value, uint8_t start1, uint8_t stop1, uint8_t start2, uint8_t stop2)
{
    return static_cast<uint8_t>(start2 + static_cast<float>(stop2 - start2) * (static_cast<float>(value - start1) / static_cast<float>(stop1 - start1)));
}

SoftPWMController::SoftPWMController(GPIO_TypeDef *gpioPort, uint16_t gpioPin,
                                     I2C_TypeDef *i2cHandler, uint8_t i2cAddress, uint8_t i2cIOPairNumber) :
      midpointValue(0)
    , i2cHandler(i2cHandler)
    , i2cAddress(i2cAddress)
    , i2cIOPairNumber(i2cIOPairNumber)
{
    if(instancesCounter < MAX_SOFT_PWM_INSTANCES)
    {
        instance = &softPWMInstancesArray[instancesCounter++];
        instance->gpioPort = gpioPort;
        instance->gpioPin = gpioPin;
        instance->PWMValue = 0;
    }
}

SoftPWMController::~SoftPWMController()
{

}

void SoftPWMController::setPWMValue(uint8_t value)
{
    uint8_t remapedValue = 0;

    if(value < midpointValue)
    {
        remapedValue = remapValue(value, midpointValue, 0, 0, resolution);
    }
    else
    {
        remapedValue = remapValue(value, midpointValue, MAX_MIDI_VALUE, 0, resolution);
    }

    instance->PWMValue = remapedValue;
}

void SoftPWMController::setMidpoint(uint8_t value)
{
    midpointValue = value;
    setPWMValue(instance->PWMValue);
}

void SoftPWMController::turnOffOutput()
{

}

void SoftPWMController::turnOnOutput()
{

}

void SoftPWMController::updateOutputs()
{

}

void SoftPWMController::setResolution(uint8_t res)
{
    resolution = res;
}
