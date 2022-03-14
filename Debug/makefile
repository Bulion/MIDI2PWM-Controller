################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include Src/subdir.mk
-include Middlewares/WELES/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/WELES/STM32_USB_Device_Library/Class/MIDI/Src/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MIDI-to-PWM-Controller.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
MIDI-to-PWM-Controller.list \

OBJCOPY_HEX += \
MIDI-to-PWM-Controller.hex \


# All Target
all: MIDI-to-PWM-Controller.elf secondary-outputs

# Tool invocations
MIDI-to-PWM-Controller.elf: $(OBJS) $(USER_OBJS) ../STM32F750V8Tx_FLASH.ld
	arm-none-eabi-gcc -o "MIDI-to-PWM-Controller.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"../STM32F750V8Tx_FLASH.ld" --specs=nosys.specs -Wl,-Map="MIDI-to-PWM-Controller.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

MIDI-to-PWM-Controller.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "MIDI-to-PWM-Controller.list"
	@echo 'Finished building: $@'
	@echo ' '

MIDI-to-PWM-Controller.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "MIDI-to-PWM-Controller.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
