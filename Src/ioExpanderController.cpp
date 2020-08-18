#include "ioExpanderController.hpp"
#include "i2c.h"

constexpr uint8_t IO_EXPANDER_ADDR_LOW = 0x40;
constexpr uint8_t IO_EXPANDER_ADDR_HIGH = 0x42;

IOExpanderController ioExp1(&hi2c1, IO_EXPANDER_ADDR_LOW);
IOExpanderController ioExp2(&hi2c1, IO_EXPANDER_ADDR_HIGH);
IOExpanderController ioExp3(&hi2c2, IO_EXPANDER_ADDR_LOW);
IOExpanderController ioExp4(&hi2c2, IO_EXPANDER_ADDR_HIGH);
IOExpanderController ioExp5(&hi2c3, IO_EXPANDER_ADDR_LOW);
IOExpanderController ioExp6(&hi2c3, IO_EXPANDER_ADDR_HIGH);
IOExpanderController ioExp7(&hi2c4, IO_EXPANDER_ADDR_LOW);
IOExpanderController ioExp8(&hi2c4, IO_EXPANDER_ADDR_HIGH);

IOExpanderController::IOExpanderController(I2C_HandleTypeDef *i2cHandler, uint32_t i2cAddress) :
      i2cHandler(i2cHandler)
    , i2cAddress(i2cAddress)
{

}

uint16_t IOExpanderController::readOutput()
{
    const uint8_t connectionTimeoutMs = 100;
    uint8_t outputPortRegisterAddr = 0x02;
    uint16_t outputPortValues = 0;
    HAL_I2C_Master_Transmit(i2cHandler, i2cAddress, &outputPortRegisterAddr, sizeof(outputPortRegisterAddr), connectionTimeoutMs);
    HAL_I2C_Master_Receive(i2cHandler, i2cAddress, (uint8_t *)(&outputPortValues), sizeof(outputPortValues), connectionTimeoutMs);
    return outputPortValues;
}

void IOExpanderController::writeOutput(uint16_t ioOutputValues)
{
    constexpr uint8_t txBuffSize = 3;
    const uint8_t connectionTimeoutMs = 100;
    const uint8_t outputPortRegisterAddr = 0x02;
    uint8_t txBuff[txBuffSize] = {outputPortRegisterAddr,
                         (uint8_t)(ioOutputValues >> 8),
                         (uint8_t)(ioOutputValues & 0xFF)};
    HAL_I2C_Master_Transmit(i2cHandler, i2cAddress, txBuff, txBuffSize, connectionTimeoutMs);
}
