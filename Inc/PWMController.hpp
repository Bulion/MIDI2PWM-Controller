#pragma once

class PWMController {
public:
    virtual ~PWMController();

    virtual void setPWMValue(uint8_t newValue) = 0;
    virtual void setMidpoint(uint8_t midpointValue) = 0;
    virtual void turnOffOutput() = 0;
    virtual void turnOnOutput() = 0;
};
