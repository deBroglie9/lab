################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../EtherCAT/src/coeappl.c \
../EtherCAT/src/ecatappl.c \
../EtherCAT/src/ecatcoe.c \
../EtherCAT/src/ecatslv.c \
../EtherCAT/src/mailbox.c \
../EtherCAT/src/objdef.c \
../EtherCAT/src/sdoserv.c 

OBJS += \
./EtherCAT/src/coeappl.o \
./EtherCAT/src/ecatappl.o \
./EtherCAT/src/ecatcoe.o \
./EtherCAT/src/ecatslv.o \
./EtherCAT/src/mailbox.o \
./EtherCAT/src/objdef.o \
./EtherCAT/src/sdoserv.o 

C_DEPS += \
./EtherCAT/src/coeappl.d \
./EtherCAT/src/ecatappl.d \
./EtherCAT/src/ecatcoe.d \
./EtherCAT/src/ecatslv.d \
./EtherCAT/src/mailbox.d \
./EtherCAT/src/objdef.d \
./EtherCAT/src/sdoserv.d 


# Each subdirectory must supply rules for building sources it contributes
EtherCAT/src/%.o EtherCAT/src/%.su EtherCAT/src/%.cyclo: ../EtherCAT/src/%.c EtherCAT/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx -DMETAL_INTERNAL -DMETAL_MAX_DEVICE_REGIONS=2 -DRPMSG_BUFFER_SIZE=512 -DVIRTIO_SLAVE_ONLY -DNO_ATOMIC_64_SUPPORT -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../OPENAMP -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include/metal/compiler/gcc -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/STM32CubeIDE/workspace_1.16.0/SLAVES/CM4/EtherCAT/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-EtherCAT-2f-src

clean-EtherCAT-2f-src:
	-$(RM) ./EtherCAT/src/coeappl.cyclo ./EtherCAT/src/coeappl.d ./EtherCAT/src/coeappl.o ./EtherCAT/src/coeappl.su ./EtherCAT/src/ecatappl.cyclo ./EtherCAT/src/ecatappl.d ./EtherCAT/src/ecatappl.o ./EtherCAT/src/ecatappl.su ./EtherCAT/src/ecatcoe.cyclo ./EtherCAT/src/ecatcoe.d ./EtherCAT/src/ecatcoe.o ./EtherCAT/src/ecatcoe.su ./EtherCAT/src/ecatslv.cyclo ./EtherCAT/src/ecatslv.d ./EtherCAT/src/ecatslv.o ./EtherCAT/src/ecatslv.su ./EtherCAT/src/mailbox.cyclo ./EtherCAT/src/mailbox.d ./EtherCAT/src/mailbox.o ./EtherCAT/src/mailbox.su ./EtherCAT/src/objdef.cyclo ./EtherCAT/src/objdef.d ./EtherCAT/src/objdef.o ./EtherCAT/src/objdef.su ./EtherCAT/src/sdoserv.cyclo ./EtherCAT/src/sdoserv.d ./EtherCAT/src/sdoserv.o ./EtherCAT/src/sdoserv.su

.PHONY: clean-EtherCAT-2f-src

