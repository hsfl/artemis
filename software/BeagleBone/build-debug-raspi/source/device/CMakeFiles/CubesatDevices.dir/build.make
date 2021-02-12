# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vagrant/artemis/software/BeagleBone/beaglebone

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vagrant/artemis/software/BeagleBone/build-debug-raspi

# Include any dependencies generated for this target.
include source/device/CMakeFiles/CubesatDevices.dir/depend.make

# Include the progress variables for this target.
include source/device/CMakeFiles/CubesatDevices.dir/progress.make

# Include the compile flags for this target's objects.
include source/device/CMakeFiles/CubesatDevices.dir/flags.make

source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o: source/device/CMakeFiles/CubesatDevices.dir/flags.make
source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/I2CDevice.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/I2CDevice.cpp

source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/I2CDevice.cpp > CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.i

source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/I2CDevice.cpp -o CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.s

source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o.requires:

.PHONY : source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o.requires

source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o.provides: source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o.requires
	$(MAKE) -f source/device/CMakeFiles/CubesatDevices.dir/build.make source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o.provides.build
.PHONY : source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o.provides

source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o.provides.build: source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o


source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o: source/device/CMakeFiles/CubesatDevices.dir/flags.make
source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/SPIDevice.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/SPIDevice.cpp

source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/SPIDevice.cpp > CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.i

source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/SPIDevice.cpp -o CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.s

source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o.requires:

.PHONY : source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o.requires

source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o.provides: source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o.requires
	$(MAKE) -f source/device/CMakeFiles/CubesatDevices.dir/build.make source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o.provides.build
.PHONY : source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o.provides

source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o.provides.build: source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o


source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o: source/device/CMakeFiles/CubesatDevices.dir/flags.make
source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/UARTDevice.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/UARTDevice.cpp

source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/UARTDevice.cpp > CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.i

source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/UARTDevice.cpp -o CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.s

source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o.requires:

.PHONY : source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o.requires

source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o.provides: source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o.requires
	$(MAKE) -f source/device/CMakeFiles/CubesatDevices.dir/build.make source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o.provides.build
.PHONY : source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o.provides

source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o.provides.build: source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o


source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o: source/device/CMakeFiles/CubesatDevices.dir/flags.make
source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/OPT3001.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/OPT3001.cpp

source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/OPT3001.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/OPT3001.cpp > CMakeFiles/CubesatDevices.dir/OPT3001.cpp.i

source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/OPT3001.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/OPT3001.cpp -o CMakeFiles/CubesatDevices.dir/OPT3001.cpp.s

source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o.requires:

.PHONY : source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o.requires

source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o.provides: source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o.requires
	$(MAKE) -f source/device/CMakeFiles/CubesatDevices.dir/build.make source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o.provides.build
.PHONY : source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o.provides

source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o.provides.build: source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o


source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o: source/device/CMakeFiles/CubesatDevices.dir/flags.make
source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/ADT7311.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/ADT7311.cpp

source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/ADT7311.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/ADT7311.cpp > CMakeFiles/CubesatDevices.dir/ADT7311.cpp.i

source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/ADT7311.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/ADT7311.cpp -o CMakeFiles/CubesatDevices.dir/ADT7311.cpp.s

source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o.requires:

.PHONY : source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o.requires

source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o.provides: source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o.requires
	$(MAKE) -f source/device/CMakeFiles/CubesatDevices.dir/build.make source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o.provides.build
.PHONY : source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o.provides

source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o.provides.build: source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o


source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o: source/device/CMakeFiles/CubesatDevices.dir/flags.make
source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/PyCubed.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/PyCubed.cpp

source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/PyCubed.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/PyCubed.cpp > CMakeFiles/CubesatDevices.dir/PyCubed.cpp.i

source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/PyCubed.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/PyCubed.cpp -o CMakeFiles/CubesatDevices.dir/PyCubed.cpp.s

source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o.requires:

.PHONY : source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o.requires

source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o.provides: source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o.requires
	$(MAKE) -f source/device/CMakeFiles/CubesatDevices.dir/build.make source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o.provides.build
.PHONY : source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o.provides

source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o.provides.build: source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o


source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o: source/device/CMakeFiles/CubesatDevices.dir/flags.make
source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/GPIO.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/GPIO.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/GPIO.cpp

source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/GPIO.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/GPIO.cpp > CMakeFiles/CubesatDevices.dir/GPIO.cpp.i

source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/GPIO.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device/GPIO.cpp -o CMakeFiles/CubesatDevices.dir/GPIO.cpp.s

source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o.requires:

.PHONY : source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o.requires

source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o.provides: source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o.requires
	$(MAKE) -f source/device/CMakeFiles/CubesatDevices.dir/build.make source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o.provides.build
.PHONY : source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o.provides

source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o.provides.build: source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o


# Object files for target CubesatDevices
CubesatDevices_OBJECTS = \
"CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o" \
"CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o" \
"CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o" \
"CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o" \
"CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o" \
"CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o" \
"CMakeFiles/CubesatDevices.dir/GPIO.cpp.o"

# External object files for target CubesatDevices
CubesatDevices_EXTERNAL_OBJECTS =

source/device/libCubesatDevices.a: source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o
source/device/libCubesatDevices.a: source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o
source/device/libCubesatDevices.a: source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o
source/device/libCubesatDevices.a: source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o
source/device/libCubesatDevices.a: source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o
source/device/libCubesatDevices.a: source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o
source/device/libCubesatDevices.a: source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o
source/device/libCubesatDevices.a: source/device/CMakeFiles/CubesatDevices.dir/build.make
source/device/libCubesatDevices.a: source/device/CMakeFiles/CubesatDevices.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-debug-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libCubesatDevices.a"
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && $(CMAKE_COMMAND) -P CMakeFiles/CubesatDevices.dir/cmake_clean_target.cmake
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CubesatDevices.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/device/CMakeFiles/CubesatDevices.dir/build: source/device/libCubesatDevices.a

.PHONY : source/device/CMakeFiles/CubesatDevices.dir/build

source/device/CMakeFiles/CubesatDevices.dir/requires: source/device/CMakeFiles/CubesatDevices.dir/I2CDevice.cpp.o.requires
source/device/CMakeFiles/CubesatDevices.dir/requires: source/device/CMakeFiles/CubesatDevices.dir/SPIDevice.cpp.o.requires
source/device/CMakeFiles/CubesatDevices.dir/requires: source/device/CMakeFiles/CubesatDevices.dir/UARTDevice.cpp.o.requires
source/device/CMakeFiles/CubesatDevices.dir/requires: source/device/CMakeFiles/CubesatDevices.dir/OPT3001.cpp.o.requires
source/device/CMakeFiles/CubesatDevices.dir/requires: source/device/CMakeFiles/CubesatDevices.dir/ADT7311.cpp.o.requires
source/device/CMakeFiles/CubesatDevices.dir/requires: source/device/CMakeFiles/CubesatDevices.dir/PyCubed.cpp.o.requires
source/device/CMakeFiles/CubesatDevices.dir/requires: source/device/CMakeFiles/CubesatDevices.dir/GPIO.cpp.o.requires

.PHONY : source/device/CMakeFiles/CubesatDevices.dir/requires

source/device/CMakeFiles/CubesatDevices.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device && $(CMAKE_COMMAND) -P CMakeFiles/CubesatDevices.dir/cmake_clean.cmake
.PHONY : source/device/CMakeFiles/CubesatDevices.dir/clean

source/device/CMakeFiles/CubesatDevices.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/artemis/software/BeagleBone/beaglebone/source/device /home/vagrant/artemis/software/BeagleBone/build-debug-raspi /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/source/device/CMakeFiles/CubesatDevices.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/device/CMakeFiles/CubesatDevices.dir/depend

