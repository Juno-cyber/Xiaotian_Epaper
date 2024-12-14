################################################################################
# 自动生成的文件。不要编辑！
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Libraries/myusart/subdir.mk
-include Libraries/mytasks/subdir.mk
-include Libraries/ds1302/subdir.mk
-include Libraries/EPD_W21/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Xiaotian_Epaper
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Xiaotian_Epaper.elf \

MAP_FILES += \
Xiaotian_Epaper.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Xiaotian_Epaper.list \

OBJCOPY_HEX += \
Xiaotian_Epaper.hex \

OBJCOPY_BIN += \
Xiaotian_Epaper.bin \


# 所有目标
all: main-build

# 主构建目标
main-build: Xiaotian_Epaper.elf secondary-outputs

# 工具调用
Xiaotian_Epaper.elf Xiaotian_Epaper.map: $(OBJS) $(USER_OBJS) D:\Users\Administrator\Documents\GitHub\Xiaotian_Epaper\3.Software\Xiaotian_Epaper\STM32F103CBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Xiaotian_Epaper.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Users\Administrator\Documents\GitHub\Xiaotian_Epaper\3.Software\Xiaotian_Epaper\STM32F103CBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Xiaotian_Epaper.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo '已结束构建目标： $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo '已结束构建： $@'
	@echo ' '

Xiaotian_Epaper.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Xiaotian_Epaper.list"
	@echo '已结束构建： $@'
	@echo ' '

Xiaotian_Epaper.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Xiaotian_Epaper.hex"
	@echo '已结束构建： $@'
	@echo ' '

Xiaotian_Epaper.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Xiaotian_Epaper.bin"
	@echo '已结束构建： $@'
	@echo ' '

# 其他目标
clean:
	-$(RM) Xiaotian_Epaper.bin Xiaotian_Epaper.elf Xiaotian_Epaper.hex Xiaotian_Epaper.list Xiaotian_Epaper.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
