#pragma once

#include "ioExpanderController.hpp"
#include "PWMController.hpp"

class HBridgeController
{
public:
    HBridgeController(IOExpanderController &io, PWMController *pwm);

    void setPWMValue(uint8_t value);
    void setMidpointValue(uint8_t value);
    void turnOutputOff();
    void turnOutputOn();

private:
    enum OutputDir
    {
        POSITIVE,
        NEGATIVE
    };

    void setOutputDir(OutputDir dir);

    static uint8_t       instanceNumber;

    uint8_t              lastPWMInputValue;
    uint8_t              midpointValue;
    OutputDir            lastOutputDir;
    uint8_t              ioPairNum;
    IOExpanderController ioExpCtl;
    PWMController        *pwmCtl;
};
