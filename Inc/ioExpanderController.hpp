#pragma once

#include <cstdint>
#include "stm32f7xx_hal.h"

class IOExpanderController;

extern IOExpanderController ioExp1;
extern IOExpanderController ioExp2;
extern IOExpanderController ioExp3;
extern IOExpanderController ioExp4;
extern IOExpanderController ioExp5;
extern IOExpanderController ioExp6;
extern IOExpanderController ioExp7;
extern IOExpanderController ioExp8;

class IOExpanderController
{
public:
    IOExpanderController(I2C_HandleTypeDef *i2cHandler, uint32_t i2cAddress);

    uint16_t readOutput();
    void writeOutput(uint16_t ioOutputValues);

private:
    I2C_HandleTypeDef *i2cHandler;
    uint8_t            i2cAddress;
};
