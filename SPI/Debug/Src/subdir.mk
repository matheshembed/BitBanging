################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/bmp280.c \
../Src/delay.c \
../Src/main.c \
../Src/spi_bitbang.c \
../Src/spi_protocol.c \
../Src/stm32f446xx_gpio_driver.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/bmp280.o \
./Src/delay.o \
./Src/main.o \
./Src/spi_bitbang.o \
./Src/spi_protocol.o \
./Src/stm32f446xx_gpio_driver.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/bmp280.d \
./Src/delay.d \
./Src/main.d \
./Src/spi_bitbang.d \
./Src/spi_protocol.d \
./Src/stm32f446xx_gpio_driver.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g1 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"D:/Softwares/Stm32/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"D:/Softwares/Stm32/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers/STM32F4xx_HAL_Driver" -I"D:/Softwares/Stm32/en.stm32cubef4-v1-28-0/STM32Cube_FW_F4_V1.28.0/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/bmp280.cyclo ./Src/bmp280.d ./Src/bmp280.o ./Src/bmp280.su ./Src/delay.cyclo ./Src/delay.d ./Src/delay.o ./Src/delay.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/spi_bitbang.cyclo ./Src/spi_bitbang.d ./Src/spi_bitbang.o ./Src/spi_bitbang.su ./Src/spi_protocol.cyclo ./Src/spi_protocol.d ./Src/spi_protocol.o ./Src/spi_protocol.su ./Src/stm32f446xx_gpio_driver.cyclo ./Src/stm32f446xx_gpio_driver.d ./Src/stm32f446xx_gpio_driver.o ./Src/stm32f446xx_gpio_driver.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

