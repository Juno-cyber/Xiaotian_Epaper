################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/ds1302/ds1302.c 

OBJS += \
./Libraries/ds1302/ds1302.o 

C_DEPS += \
./Libraries/ds1302/ds1302.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/ds1302/%.o Libraries/ds1302/%.su Libraries/ds1302/%.cyclo: ../Libraries/ds1302/%.c Libraries/ds1302/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/Users/Administrator/STM32CubeIDE/workspace_1.16.1/xiaoshiEpaper/Libraries/include" -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-ds1302

clean-Libraries-2f-ds1302:
	-$(RM) ./Libraries/ds1302/ds1302.cyclo ./Libraries/ds1302/ds1302.d ./Libraries/ds1302/ds1302.o ./Libraries/ds1302/ds1302.su

.PHONY: clean-Libraries-2f-ds1302

