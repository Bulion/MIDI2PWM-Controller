################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f750xx.s 

OBJS += \
./startup/startup_stm32f750xx.o 

S_DEPS += \
./startup/startup_stm32f750xx.d 


# Each subdirectory must supply rules for building sources it contributes
startup/startup_stm32f750xx.o: ../startup/startup_stm32f750xx.s
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -x assembler-with-cpp -MMD -MP -MF"startup/startup_stm32f750xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

