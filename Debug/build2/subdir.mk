################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../build2/energycomp.cpp \
../build2/exacmass.cpp \
../build2/gapcollection.cpp \
../build2/lengthcollection.cpp \
../build2/missingmass.cpp \
../build2/thicknesscollection.cpp 

OBJS += \
./build2/energycomp.o \
./build2/exacmass.o \
./build2/gapcollection.o \
./build2/lengthcollection.o \
./build2/missingmass.o \
./build2/thicknesscollection.o 

CPP_DEPS += \
./build2/energycomp.d \
./build2/exacmass.d \
./build2/gapcollection.d \
./build2/lengthcollection.d \
./build2/missingmass.d \
./build2/thicknesscollection.d 


# Each subdirectory must supply rules for building sources it contributes
build2/%.o: ../build2/%.cpp build2/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/geant4.10.07.p02/include/Geant4 -I/usr/local/clhep/2.4.4.0/include -I/usr/local/root/6.18.04/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


