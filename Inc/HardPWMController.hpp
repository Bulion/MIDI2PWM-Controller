#pragma once

#include "stm32f7xx_hal.h"
#include "PWMController.hpp"

class HardPWMController : public PWMController
{
public:
    HardPWMController(TIM_HandleTypeDef *htim, uint32_t tim_channel);
    ~HardPWMController();

    uint8_t getResolution()            override;
    void    setPWMValue(uint8_t value) override;

private:
    TIM_HandleTypeDef *htim;
    uint32_t           tim_channel;
};
