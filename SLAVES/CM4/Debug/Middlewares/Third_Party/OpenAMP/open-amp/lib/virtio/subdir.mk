################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32CubeIDE/workspace_1.16.0/SLAVES/Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtio.c \
D:/STM32CubeIDE/workspace_1.16.0/SLAVES/Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtqueue.c 

OBJS += \
./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtio.o \
./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtqueue.o 

C_DEPS += \
./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtio.d \
./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtqueue.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtio.o: D:/STM32CubeIDE/workspace_1.16.0/SLAVES/Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtio.c Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx -DMETAL_INTERNAL -DMETAL_MAX_DEVICE_REGIONS=2 -DRPMSG_BUFFER_SIZE=512 -DVIRTIO_SLAVE_ONLY -DNO_ATOMIC_64_SUPPORT -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../OPENAMP -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include/metal/compiler/gcc -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/STM32CubeIDE/workspace_1.16.0/SLAVES/CM4/EtherCAT/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtqueue.o: D:/STM32CubeIDE/workspace_1.16.0/SLAVES/Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtqueue.c Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx -DMETAL_INTERNAL -DMETAL_MAX_DEVICE_REGIONS=2 -DRPMSG_BUFFER_SIZE=512 -DVIRTIO_SLAVE_ONLY -DNO_ATOMIC_64_SUPPORT -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../OPENAMP -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include/metal/compiler/gcc -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/STM32CubeIDE/workspace_1.16.0/SLAVES/CM4/EtherCAT/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-OpenAMP-2f-open-2d-amp-2f-lib-2f-virtio

clean-Middlewares-2f-Third_Party-2f-OpenAMP-2f-open-2d-amp-2f-lib-2f-virtio:
	-$(RM) ./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtio.cyclo ./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtio.d ./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtio.o ./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtio.su ./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtqueue.cyclo ./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtqueue.d ./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtqueue.o ./Middlewares/Third_Party/OpenAMP/open-amp/lib/virtio/virtqueue.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-OpenAMP-2f-open-2d-amp-2f-lib-2f-virtio

