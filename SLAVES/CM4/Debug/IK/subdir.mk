################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../IK/IK_7DOF.c \
../IK/IK_7DOF_data.c \
../IK/IK_7DOF_initialize.c \
../IK/IK_7DOF_rtwutil.c \
../IK/IK_7DOF_terminate.c \
../IK/exp.c \
../IK/log.c \
../IK/norm.c \
../IK/power.c \
../IK/rtGetInf.c \
../IK/rtGetNaN.c \
../IK/rt_nonfinite.c 

OBJS += \
./IK/IK_7DOF.o \
./IK/IK_7DOF_data.o \
./IK/IK_7DOF_initialize.o \
./IK/IK_7DOF_rtwutil.o \
./IK/IK_7DOF_terminate.o \
./IK/exp.o \
./IK/log.o \
./IK/norm.o \
./IK/power.o \
./IK/rtGetInf.o \
./IK/rtGetNaN.o \
./IK/rt_nonfinite.o 

C_DEPS += \
./IK/IK_7DOF.d \
./IK/IK_7DOF_data.d \
./IK/IK_7DOF_initialize.d \
./IK/IK_7DOF_rtwutil.d \
./IK/IK_7DOF_terminate.d \
./IK/exp.d \
./IK/log.d \
./IK/norm.d \
./IK/power.d \
./IK/rtGetInf.d \
./IK/rtGetNaN.d \
./IK/rt_nonfinite.d 


# Each subdirectory must supply rules for building sources it contributes
IK/%.o IK/%.su IK/%.cyclo: ../IK/%.c IK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H755xx -DMETAL_INTERNAL -DMETAL_MAX_DEVICE_REGIONS=2 -DRPMSG_BUFFER_SIZE=512 -DVIRTIO_SLAVE_ONLY -DNO_ATOMIC_64_SUPPORT -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../OPENAMP -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include/metal/compiler/gcc -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/STM32CubeIDE/workspace_1.16.0/SLAVES/CM4/EtherCAT/inc" -I"D:/STM32CubeIDE/workspace_1.16.0/SLAVES/CM4/IK" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-IK

clean-IK:
	-$(RM) ./IK/IK_7DOF.cyclo ./IK/IK_7DOF.d ./IK/IK_7DOF.o ./IK/IK_7DOF.su ./IK/IK_7DOF_data.cyclo ./IK/IK_7DOF_data.d ./IK/IK_7DOF_data.o ./IK/IK_7DOF_data.su ./IK/IK_7DOF_initialize.cyclo ./IK/IK_7DOF_initialize.d ./IK/IK_7DOF_initialize.o ./IK/IK_7DOF_initialize.su ./IK/IK_7DOF_rtwutil.cyclo ./IK/IK_7DOF_rtwutil.d ./IK/IK_7DOF_rtwutil.o ./IK/IK_7DOF_rtwutil.su ./IK/IK_7DOF_terminate.cyclo ./IK/IK_7DOF_terminate.d ./IK/IK_7DOF_terminate.o ./IK/IK_7DOF_terminate.su ./IK/exp.cyclo ./IK/exp.d ./IK/exp.o ./IK/exp.su ./IK/log.cyclo ./IK/log.d ./IK/log.o ./IK/log.su ./IK/norm.cyclo ./IK/norm.d ./IK/norm.o ./IK/norm.su ./IK/power.cyclo ./IK/power.d ./IK/power.o ./IK/power.su ./IK/rtGetInf.cyclo ./IK/rtGetInf.d ./IK/rtGetInf.o ./IK/rtGetInf.su ./IK/rtGetNaN.cyclo ./IK/rtGetNaN.d ./IK/rtGetNaN.o ./IK/rtGetNaN.su ./IK/rt_nonfinite.cyclo ./IK/rt_nonfinite.d ./IK/rt_nonfinite.o ./IK/rt_nonfinite.su

.PHONY: clean-IK

