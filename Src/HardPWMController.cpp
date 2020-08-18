#include "HardPWMController.hpp"

HardPWMController::HardPWMController(TIM_HandleTypeDef *htim, uint32_t tim_channel) :
      htim(htim)
    , tim_channel(tim_channel)
{
    HAL_TIM_PWM_Start(htim, tim_channel);
}

HardPWMController::~HardPWMController() {}

uint8_t HardPWMController::getResolution()
{
    return __HAL_TIM_GET_AUTORELOAD(htim);
}

void HardPWMController::setPWMValue(uint8_t value)
{
    const uint8_t resolution __HAL_TIM_GET_AUTORELOAD(htim);
    if(value > resolution)
    {
        value = resolution;
    }
    __HAL_TIM_SET_COMPARE(htim, tim_channel, value);
}
