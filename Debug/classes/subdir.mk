################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../classes/p2pActionInitialization.cpp \
../classes/p2pDetectorConstruction.cpp \
../classes/p2pEventAction.cpp \
../classes/p2pHit.cpp \
../classes/p2pPhysicsList.cpp \
../classes/p2pPrimaryGeneratorAction.cpp \
../classes/p2pRunAction.cpp \
../classes/p2pSensitiveDetector.cpp \
../classes/p2pSteppingAction.cpp 

OBJS += \
./classes/p2pActionInitialization.o \
./classes/p2pDetectorConstruction.o \
./classes/p2pEventAction.o \
./classes/p2pHit.o \
./classes/p2pPhysicsList.o \
./classes/p2pPrimaryGeneratorAction.o \
./classes/p2pRunAction.o \
./classes/p2pSensitiveDetector.o \
./classes/p2pSteppingAction.o 

CPP_DEPS += \
./classes/p2pActionInitialization.d \
./classes/p2pDetectorConstruction.d \
./classes/p2pEventAction.d \
./classes/p2pHit.d \
./classes/p2pPhysicsList.d \
./classes/p2pPrimaryGeneratorAction.d \
./classes/p2pRunAction.d \
./classes/p2pSensitiveDetector.d \
./classes/p2pSteppingAction.d 


# Each subdirectory must supply rules for building sources it contributes
classes/%.o: ../classes/%.cpp classes/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/geant4.10.07.p02/include/Geant4 -I/usr/local/clhep/2.4.4.0/include -I/usr/local/root/6.18.04/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


