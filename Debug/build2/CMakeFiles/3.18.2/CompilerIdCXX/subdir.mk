################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../build2/CMakeFiles/3.18.2/CompilerIdCXX/CMakeCXXCompilerId.cpp 

OBJS += \
./build2/CMakeFiles/3.18.2/CompilerIdCXX/CMakeCXXCompilerId.o 

CPP_DEPS += \
./build2/CMakeFiles/3.18.2/CompilerIdCXX/CMakeCXXCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
build2/CMakeFiles/3.18.2/CompilerIdCXX/%.o: ../build2/CMakeFiles/3.18.2/CompilerIdCXX/%.cpp build2/CMakeFiles/3.18.2/CompilerIdCXX/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/geant4.10.07.p02/include/Geant4 -I/usr/local/clhep/2.4.4.0/include -I/usr/local/root/6.18.04/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


