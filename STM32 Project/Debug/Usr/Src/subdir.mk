################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Usr/Src/1016top.c 

OBJS += \
./Usr/Src/1016top.o 

C_DEPS += \
./Usr/Src/1016top.d 


# Each subdirectory must supply rules for building sources it contributes
Usr/Src/%.o Usr/Src/%.su Usr/Src/%.cyclo: ../Usr/Src/%.c Usr/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32C011xx -c -I../Core/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc -I../Drivers/STM32C0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32C0xx/Include -I../Drivers/CMSIS/Include -I"C:/EE/Projects/1016 Breadboard Power Supply/STM32 Project/Usr/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Usr-2f-Src

clean-Usr-2f-Src:
	-$(RM) ./Usr/Src/1016top.cyclo ./Usr/Src/1016top.d ./Usr/Src/1016top.o ./Usr/Src/1016top.su

.PHONY: clean-Usr-2f-Src

