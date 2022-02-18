################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../build2/CMakeFiles/3.18.2/CompilerIdC/CMakeCCompilerId.c 

OBJS += \
./build2/CMakeFiles/3.18.2/CompilerIdC/CMakeCCompilerId.o 

C_DEPS += \
./build2/CMakeFiles/3.18.2/CompilerIdC/CMakeCCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
build2/CMakeFiles/3.18.2/CompilerIdC/%.o: ../build2/CMakeFiles/3.18.2/CompilerIdC/%.c build2/CMakeFiles/3.18.2/CompilerIdC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


