#include "HBridgeController.hpp"

inline uint8_t remapValue(uint8_t value, uint8_t start1, uint8_t stop1, uint8_t start2, uint8_t stop2)
{
    return static_cast<uint8_t>(start2 + static_cast<float>(stop2 - start2) * (static_cast<float>(value - start1) / static_cast<float>(stop1 - start1)));
}

uint8_t HBridgeController::instanceNumber = 0;

HBridgeController::HBridgeController(IOExpanderController &io, PWMController *pwm) :
      lastPWMInputValue(0)
    , midpointValue(0)
    , lastOutputDir(POSITIVE)
    , ioPairNum(instanceNumber++ % 8)
    , ioExpCtl(io)
    , pwmCtl(pwm)
{

}

void HBridgeController::setPWMValue(uint8_t value)
{
    const uint8_t maxInputValue = 127;
    uint8_t remapedValue = 0;
    const uint8_t resolution = pwmCtl->getResolution();

    if(value > maxInputValue)
    {
        value = maxInputValue;
    }

    lastPWMInputValue = value;

    if(value != midpointValue)
    {
        if(value == 0 || value == maxInputValue)
        {
            turnOutputOff();
            remapedValue = resolution + 1;
        }
        else if(value < midpointValue)
        {
            setOutputDir(OutputDir::POSITIVE);
            remapedValue = remapValue(value, midpointValue, 0, 0, resolution);
        }
        else
        {
            setOutputDir(OutputDir::NEGATIVE);
            remapedValue = remapValue(value, midpointValue, maxInputValue, 0, resolution);
        }
    }

    pwmCtl->setPWMValue(remapedValue);
}

void HBridgeController::setMidpointValue(uint8_t value)
{
    midpointValue = value;
    setPWMValue(lastPWMInputValue);
}

void HBridgeController::setOutputDir(OutputDir dir)
{
    lastOutputDir = dir;
    const uint16_t currentIOStatus = ioExpCtl.readOutput();
    const uint16_t clearedIOStatus = (currentIOStatus & ~((uint16_t)(3 << (2 * ioPairNum))));
    const uint16_t dirIOVal = (dir == OutputDir::POSITIVE) ? (1 << (2 * ioPairNum)) : (2 << (2 * ioPairNum));
    ioExpCtl.writeOutput(clearedIOStatus | dirIOVal);
}

void HBridgeController::turnOutputOff()
{
    const uint16_t currentIOStatus = ioExpCtl.readOutput();
    const uint16_t clearedIOStatus = (currentIOStatus & ~((uint16_t)(3 << (2 * ioPairNum))));
    ioExpCtl.writeOutput(clearedIOStatus);
}

void HBridgeController::turnOutputOn()
{
    setOutputDir(lastOutputDir);
}
