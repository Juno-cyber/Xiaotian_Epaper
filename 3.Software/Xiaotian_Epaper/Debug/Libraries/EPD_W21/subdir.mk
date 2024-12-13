################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/EPD_W21/EPAPER.c 

OBJS += \
./Libraries/EPD_W21/EPAPER.o 

C_DEPS += \
./Libraries/EPD_W21/EPAPER.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/EPD_W21/%.o Libraries/EPD_W21/%.su Libraries/EPD_W21/%.cyclo: ../Libraries/EPD_W21/%.c Libraries/EPD_W21/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/Users/Administrator/STM32CubeIDE/workspace_1.16.1/xiaoshiEpaper/Libraries/include" -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-EPD_W21

clean-Libraries-2f-EPD_W21:
	-$(RM) ./Libraries/EPD_W21/EPAPER.cyclo ./Libraries/EPD_W21/EPAPER.d ./Libraries/EPD_W21/EPAPER.o ./Libraries/EPD_W21/EPAPER.su

.PHONY: clean-Libraries-2f-EPD_W21

