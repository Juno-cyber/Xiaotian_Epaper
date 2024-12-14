################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/myusart/myusart.c 

OBJS += \
./Libraries/myusart/myusart.o 

C_DEPS += \
./Libraries/myusart/myusart.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/myusart/%.o Libraries/myusart/%.su Libraries/myusart/%.cyclo: ../Libraries/myusart/%.c Libraries/myusart/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/Users/Administrator/Documents/GitHub/Xiaotian_Epaper/3.Software/Xiaotian_Epaper/Libraries/include" -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-myusart

clean-Libraries-2f-myusart:
	-$(RM) ./Libraries/myusart/myusart.cyclo ./Libraries/myusart/myusart.d ./Libraries/myusart/myusart.o ./Libraries/myusart/myusart.su

.PHONY: clean-Libraries-2f-myusart

