#pragma once

class PWMController {
public:
    virtual ~PWMController() {};

    virtual uint8_t getResolution() = 0;
    virtual void    setPWMValue(uint8_t newValue) = 0;
};
