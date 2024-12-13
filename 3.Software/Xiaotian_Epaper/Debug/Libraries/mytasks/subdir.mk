################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/mytasks/task_init.c \
../Libraries/mytasks/task_read.c \
../Libraries/mytasks/task_run.c \
../Libraries/mytasks/task_show.c 

OBJS += \
./Libraries/mytasks/task_init.o \
./Libraries/mytasks/task_read.o \
./Libraries/mytasks/task_run.o \
./Libraries/mytasks/task_show.o 

C_DEPS += \
./Libraries/mytasks/task_init.d \
./Libraries/mytasks/task_read.d \
./Libraries/mytasks/task_run.d \
./Libraries/mytasks/task_show.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/mytasks/%.o Libraries/mytasks/%.su Libraries/mytasks/%.cyclo: ../Libraries/mytasks/%.c Libraries/mytasks/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I"D:/Users/Administrator/STM32CubeIDE/workspace_1.16.1/xiaoshiEpaper/Libraries/include" -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Libraries-2f-mytasks

clean-Libraries-2f-mytasks:
	-$(RM) ./Libraries/mytasks/task_init.cyclo ./Libraries/mytasks/task_init.d ./Libraries/mytasks/task_init.o ./Libraries/mytasks/task_init.su ./Libraries/mytasks/task_read.cyclo ./Libraries/mytasks/task_read.d ./Libraries/mytasks/task_read.o ./Libraries/mytasks/task_read.su ./Libraries/mytasks/task_run.cyclo ./Libraries/mytasks/task_run.d ./Libraries/mytasks/task_run.o ./Libraries/mytasks/task_run.su ./Libraries/mytasks/task_show.cyclo ./Libraries/mytasks/task_show.d ./Libraries/mytasks/task_show.o ./Libraries/mytasks/task_show.su

.PHONY: clean-Libraries-2f-mytasks

