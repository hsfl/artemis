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
CMAKE_SOURCE_DIR = /home/vagrant/cosmos/source/projects/beaglebone/source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vagrant/artemis/software/BeagleBone/build

# Include any dependencies generated for this target.
include CMakeFiles/CubesatDevices.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CubesatDevices.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CubesatDevices.dir/flags.make

CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o: CMakeFiles/CubesatDevices.dir/flags.make
CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o: /home/vagrant/cosmos/source/projects/beaglebone/source/device/I2CDevice.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o -c /home/vagrant/cosmos/source/projects/beaglebone/source/device/I2CDevice.cpp

CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/projects/beaglebone/source/device/I2CDevice.cpp > CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.i

CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/projects/beaglebone/source/device/I2CDevice.cpp -o CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.s

CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o.requires:

.PHONY : CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o.requires

CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o.provides: CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o.requires
	$(MAKE) -f CMakeFiles/CubesatDevices.dir/build.make CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o.provides.build
.PHONY : CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o.provides

CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o.provides.build: CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o


CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o: CMakeFiles/CubesatDevices.dir/flags.make
CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o: /home/vagrant/cosmos/source/projects/beaglebone/source/device/SPIDevice.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o -c /home/vagrant/cosmos/source/projects/beaglebone/source/device/SPIDevice.cpp

CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/projects/beaglebone/source/device/SPIDevice.cpp > CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.i

CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/projects/beaglebone/source/device/SPIDevice.cpp -o CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.s

CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o.requires:

.PHONY : CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o.requires

CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o.provides: CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o.requires
	$(MAKE) -f CMakeFiles/CubesatDevices.dir/build.make CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o.provides.build
.PHONY : CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o.provides

CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o.provides.build: CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o


CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o: CMakeFiles/CubesatDevices.dir/flags.make
CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o: /home/vagrant/cosmos/source/projects/beaglebone/source/device/UARTDevice.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o -c /home/vagrant/cosmos/source/projects/beaglebone/source/device/UARTDevice.cpp

CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/projects/beaglebone/source/device/UARTDevice.cpp > CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.i

CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/projects/beaglebone/source/device/UARTDevice.cpp -o CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.s

CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o.requires:

.PHONY : CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o.requires

CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o.provides: CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o.requires
	$(MAKE) -f CMakeFiles/CubesatDevices.dir/build.make CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o.provides.build
.PHONY : CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o.provides

CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o.provides.build: CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o


CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o: CMakeFiles/CubesatDevices.dir/flags.make
CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o: /home/vagrant/cosmos/source/projects/beaglebone/source/device/OPT3001.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o -c /home/vagrant/cosmos/source/projects/beaglebone/source/device/OPT3001.cpp

CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/projects/beaglebone/source/device/OPT3001.cpp > CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.i

CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/projects/beaglebone/source/device/OPT3001.cpp -o CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.s

CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o.requires:

.PHONY : CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o.requires

CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o.provides: CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o.requires
	$(MAKE) -f CMakeFiles/CubesatDevices.dir/build.make CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o.provides.build
.PHONY : CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o.provides

CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o.provides.build: CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o


CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o: CMakeFiles/CubesatDevices.dir/flags.make
CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o: /home/vagrant/cosmos/source/projects/beaglebone/source/device/ADT7311.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o -c /home/vagrant/cosmos/source/projects/beaglebone/source/device/ADT7311.cpp

CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/projects/beaglebone/source/device/ADT7311.cpp > CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.i

CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/projects/beaglebone/source/device/ADT7311.cpp -o CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.s

CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o.requires:

.PHONY : CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o.requires

CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o.provides: CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o.requires
	$(MAKE) -f CMakeFiles/CubesatDevices.dir/build.make CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o.provides.build
.PHONY : CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o.provides

CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o.provides.build: CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o


CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o: CMakeFiles/CubesatDevices.dir/flags.make
CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o: /home/vagrant/cosmos/source/projects/beaglebone/source/device/PyCubed.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o -c /home/vagrant/cosmos/source/projects/beaglebone/source/device/PyCubed.cpp

CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/projects/beaglebone/source/device/PyCubed.cpp > CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.i

CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/projects/beaglebone/source/device/PyCubed.cpp -o CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.s

CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o.requires:

.PHONY : CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o.requires

CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o.provides: CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o.requires
	$(MAKE) -f CMakeFiles/CubesatDevices.dir/build.make CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o.provides.build
.PHONY : CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o.provides

CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o.provides.build: CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o


CMakeFiles/CubesatDevices.dir/device/switch.cpp.o: CMakeFiles/CubesatDevices.dir/flags.make
CMakeFiles/CubesatDevices.dir/device/switch.cpp.o: /home/vagrant/cosmos/source/projects/beaglebone/source/device/switch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/CubesatDevices.dir/device/switch.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/device/switch.cpp.o -c /home/vagrant/cosmos/source/projects/beaglebone/source/device/switch.cpp

CMakeFiles/CubesatDevices.dir/device/switch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/device/switch.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/projects/beaglebone/source/device/switch.cpp > CMakeFiles/CubesatDevices.dir/device/switch.cpp.i

CMakeFiles/CubesatDevices.dir/device/switch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/device/switch.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/projects/beaglebone/source/device/switch.cpp -o CMakeFiles/CubesatDevices.dir/device/switch.cpp.s

CMakeFiles/CubesatDevices.dir/device/switch.cpp.o.requires:

.PHONY : CMakeFiles/CubesatDevices.dir/device/switch.cpp.o.requires

CMakeFiles/CubesatDevices.dir/device/switch.cpp.o.provides: CMakeFiles/CubesatDevices.dir/device/switch.cpp.o.requires
	$(MAKE) -f CMakeFiles/CubesatDevices.dir/build.make CMakeFiles/CubesatDevices.dir/device/switch.cpp.o.provides.build
.PHONY : CMakeFiles/CubesatDevices.dir/device/switch.cpp.o.provides

CMakeFiles/CubesatDevices.dir/device/switch.cpp.o.provides.build: CMakeFiles/CubesatDevices.dir/device/switch.cpp.o


CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o: CMakeFiles/CubesatDevices.dir/flags.make
CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o: /home/vagrant/cosmos/source/projects/beaglebone/source/device/GPIO.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o -c /home/vagrant/cosmos/source/projects/beaglebone/source/device/GPIO.cpp

CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/projects/beaglebone/source/device/GPIO.cpp > CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.i

CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/projects/beaglebone/source/device/GPIO.cpp -o CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.s

CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o.requires:

.PHONY : CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o.requires

CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o.provides: CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o.requires
	$(MAKE) -f CMakeFiles/CubesatDevices.dir/build.make CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o.provides.build
.PHONY : CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o.provides

CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o.provides.build: CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o


CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o: CMakeFiles/CubesatDevices.dir/flags.make
CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o: /home/vagrant/cosmos/source/projects/beaglebone/source/utility/SimpleAgent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o -c /home/vagrant/cosmos/source/projects/beaglebone/source/utility/SimpleAgent.cpp

CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/projects/beaglebone/source/utility/SimpleAgent.cpp > CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.i

CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/projects/beaglebone/source/utility/SimpleAgent.cpp -o CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.s

CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o.requires:

.PHONY : CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o.requires

CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o.provides: CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o.requires
	$(MAKE) -f CMakeFiles/CubesatDevices.dir/build.make CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o.provides.build
.PHONY : CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o.provides

CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o.provides.build: CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o


CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o: CMakeFiles/CubesatDevices.dir/flags.make
CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o: /home/vagrant/cosmos/source/projects/beaglebone/source/utility/Device.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o -c /home/vagrant/cosmos/source/projects/beaglebone/source/utility/Device.cpp

CMakeFiles/CubesatDevices.dir/utility/Device.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CubesatDevices.dir/utility/Device.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/projects/beaglebone/source/utility/Device.cpp > CMakeFiles/CubesatDevices.dir/utility/Device.cpp.i

CMakeFiles/CubesatDevices.dir/utility/Device.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CubesatDevices.dir/utility/Device.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/projects/beaglebone/source/utility/Device.cpp -o CMakeFiles/CubesatDevices.dir/utility/Device.cpp.s

CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o.requires:

.PHONY : CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o.requires

CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o.provides: CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o.requires
	$(MAKE) -f CMakeFiles/CubesatDevices.dir/build.make CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o.provides.build
.PHONY : CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o.provides

CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o.provides.build: CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o


# Object files for target CubesatDevices
CubesatDevices_OBJECTS = \
"CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o" \
"CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o" \
"CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o" \
"CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o" \
"CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o" \
"CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o" \
"CMakeFiles/CubesatDevices.dir/device/switch.cpp.o" \
"CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o" \
"CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o" \
"CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o"

# External object files for target CubesatDevices
CubesatDevices_EXTERNAL_OBJECTS =

libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o
libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o
libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o
libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o
libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o
libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o
libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/device/switch.cpp.o
libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o
libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o
libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o
libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/build.make
libCubesatDevices.a: CMakeFiles/CubesatDevices.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX static library libCubesatDevices.a"
	$(CMAKE_COMMAND) -P CMakeFiles/CubesatDevices.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CubesatDevices.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CubesatDevices.dir/build: libCubesatDevices.a

.PHONY : CMakeFiles/CubesatDevices.dir/build

CMakeFiles/CubesatDevices.dir/requires: CMakeFiles/CubesatDevices.dir/device/I2CDevice.cpp.o.requires
CMakeFiles/CubesatDevices.dir/requires: CMakeFiles/CubesatDevices.dir/device/SPIDevice.cpp.o.requires
CMakeFiles/CubesatDevices.dir/requires: CMakeFiles/CubesatDevices.dir/device/UARTDevice.cpp.o.requires
CMakeFiles/CubesatDevices.dir/requires: CMakeFiles/CubesatDevices.dir/device/OPT3001.cpp.o.requires
CMakeFiles/CubesatDevices.dir/requires: CMakeFiles/CubesatDevices.dir/device/ADT7311.cpp.o.requires
CMakeFiles/CubesatDevices.dir/requires: CMakeFiles/CubesatDevices.dir/device/PyCubed.cpp.o.requires
CMakeFiles/CubesatDevices.dir/requires: CMakeFiles/CubesatDevices.dir/device/switch.cpp.o.requires
CMakeFiles/CubesatDevices.dir/requires: CMakeFiles/CubesatDevices.dir/device/GPIO.cpp.o.requires
CMakeFiles/CubesatDevices.dir/requires: CMakeFiles/CubesatDevices.dir/utility/SimpleAgent.cpp.o.requires
CMakeFiles/CubesatDevices.dir/requires: CMakeFiles/CubesatDevices.dir/utility/Device.cpp.o.requires

.PHONY : CMakeFiles/CubesatDevices.dir/requires

CMakeFiles/CubesatDevices.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CubesatDevices.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CubesatDevices.dir/clean

CMakeFiles/CubesatDevices.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/cosmos/source/projects/beaglebone/source /home/vagrant/cosmos/source/projects/beaglebone/source /home/vagrant/artemis/software/BeagleBone/build /home/vagrant/artemis/software/BeagleBone/build /home/vagrant/artemis/software/BeagleBone/build/CMakeFiles/CubesatDevices.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CubesatDevices.dir/depend

