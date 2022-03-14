################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/WELES/STM32_USB_Device_Library/Class/MIDI/Src/usbd_midi.c 

OBJS += \
./Middlewares/WELES/STM32_USB_Device_Library/Class/MIDI/Src/usbd_midi.o 

C_DEPS += \
./Middlewares/WELES/STM32_USB_Device_Library/Class/MIDI/Src/usbd_midi.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/WELES/STM32_USB_Device_Library/Class/MIDI/Src/usbd_midi.o: ../Middlewares/WELES/STM32_USB_Device_Library/Class/MIDI/Src/usbd_midi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F750xx -c -I../Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/WELES/STM32_USB_Device_Library/Core/Inc -I../Middlewares/WELES/STM32_USB_Device_Library/Class/MIDI/Inc -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O2 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/WELES/STM32_USB_Device_Library/Class/MIDI/Src/usbd_midi.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

