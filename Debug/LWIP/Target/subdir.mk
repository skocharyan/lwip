################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LWIP/Target/ethernetif.c 

OBJS += \
./LWIP/Target/ethernetif.o 

C_DEPS += \
./LWIP/Target/ethernetif.d 


# Each subdirectory must supply rules for building sources it contributes
LWIP/Target/%.o LWIP/Target/%.su LWIP/Target/%.cyclo: ../LWIP/Target/%.c LWIP/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/system -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/BSP/Components/lan8742 -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include/netif/ppp -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/apps/http -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include/lwip -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include/lwip/apps -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include/lwip/priv -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include/lwip/prot -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include/netif -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include/compat/posix -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include/compat/posix/net -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/src/include/compat/stdc -IC:/Users/Admin/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/Third_Party/LwIP/system/arch -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-LWIP-2f-Target

clean-LWIP-2f-Target:
	-$(RM) ./LWIP/Target/ethernetif.cyclo ./LWIP/Target/ethernetif.d ./LWIP/Target/ethernetif.o ./LWIP/Target/ethernetif.su

.PHONY: clean-LWIP-2f-Target

