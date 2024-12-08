################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ISRs.c" \
"../Sources/main.c" \
"../Sources/mcu_conf.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/ISRs.c \
../Sources/main.c \
../Sources/mcu_conf.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/ISRs.o \
./Sources/main.o \
./Sources/mcu_conf.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/ISRs.d \
./Sources/main.d \
./Sources/mcu_conf.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/ISRs.o" \
"./Sources/main.o" \
"./Sources/mcu_conf.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/ISRs.d" \
"./Sources/main.d" \
"./Sources/mcu_conf.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/ISRs.o \
./Sources/main.o \
./Sources/mcu_conf.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/ISRs.o: ../Sources/ISRs.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ISRs.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ISRs.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcu_conf.o: ../Sources/mcu_conf.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcu_conf.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcu_conf.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


