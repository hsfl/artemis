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
CMAKE_BINARY_DIR = /home/vagrant/artemis/software/BeagleBone/build-raspi

# Include any dependencies generated for this target.
include source/agents/CMakeFiles/agent_switch.dir/depend.make

# Include the progress variables for this target.
include source/agents/CMakeFiles/agent_switch.dir/progress.make

# Include the compile flags for this target's objects.
include source/agents/CMakeFiles/agent_switch.dir/flags.make

source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o: source/agents/CMakeFiles/agent_switch.dir/flags.make
source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_switch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/source/agents && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/agent_switch.dir/agent_switch.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_switch.cpp

source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/agent_switch.dir/agent_switch.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/source/agents && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_switch.cpp > CMakeFiles/agent_switch.dir/agent_switch.cpp.i

source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/agent_switch.dir/agent_switch.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/source/agents && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_switch.cpp -o CMakeFiles/agent_switch.dir/agent_switch.cpp.s

source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o.requires:

.PHONY : source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o.requires

source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o.provides: source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o.requires
	$(MAKE) -f source/agents/CMakeFiles/agent_switch.dir/build.make source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o.provides.build
.PHONY : source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o.provides

source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o.provides.build: source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o


# Object files for target agent_switch
agent_switch_OBJECTS = \
"CMakeFiles/agent_switch.dir/agent_switch.cpp.o"

# External object files for target agent_switch
agent_switch_EXTERNAL_OBJECTS =

bin/agent_switch: source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o
bin/agent_switch: source/agents/CMakeFiles/agent_switch.dir/build.make
bin/agent_switch: libraries/support/libCosmosSupport.a
bin/agent_switch: libraries/agent/libCosmosAgent.a
bin/agent_switch: libraries/device/general/libCosmosDeviceGeneral.a
bin/agent_switch: libraries/device/i2c/libCosmosDeviceI2C.a
bin/agent_switch: libraries/device/serial/libCosmosDeviceSerial.a
bin/agent_switch: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_switch: libraries/device/disk/libCosmosDeviceDisk.a
bin/agent_switch: libraries/math/libCosmosMath.a
bin/agent_switch: libraries/physics/libCosmosPhysics.a
bin/agent_switch: source/device/libCubesatDevices.a
bin/agent_switch: libraries/SimpleAgent/libSimpleAgent.a
bin/agent_switch: libraries/SimpleAgent/libSimpleAgent.a
bin/agent_switch: libraries/agent/libCosmosAgent.a
bin/agent_switch: libraries/device/i2c/libCosmosDeviceI2C.a
bin/agent_switch: libraries/support/libCosmosSupport.a
bin/agent_switch: libraries/device/general/libCosmosDeviceGeneral.a
bin/agent_switch: libraries/device/serial/libCosmosDeviceSerial.a
bin/agent_switch: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_switch: libraries/device/disk/libCosmosDeviceDisk.a
bin/agent_switch: libraries/support/libCosmosSupport.a
bin/agent_switch: libraries/device/general/libCosmosDeviceGeneral.a
bin/agent_switch: libraries/device/serial/libCosmosDeviceSerial.a
bin/agent_switch: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_switch: libraries/device/disk/libCosmosDeviceDisk.a
bin/agent_switch: libraries/zlib/liblocalzlib.a
bin/agent_switch: libraries/math/libCosmosMath.a
bin/agent_switch: libraries/physics/libCosmosPhysics.a
bin/agent_switch: source/agents/CMakeFiles/agent_switch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/agent_switch"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/source/agents && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/agent_switch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/agents/CMakeFiles/agent_switch.dir/build: bin/agent_switch

.PHONY : source/agents/CMakeFiles/agent_switch.dir/build

source/agents/CMakeFiles/agent_switch.dir/requires: source/agents/CMakeFiles/agent_switch.dir/agent_switch.cpp.o.requires

.PHONY : source/agents/CMakeFiles/agent_switch.dir/requires

source/agents/CMakeFiles/agent_switch.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/source/agents && $(CMAKE_COMMAND) -P CMakeFiles/agent_switch.dir/cmake_clean.cmake
.PHONY : source/agents/CMakeFiles/agent_switch.dir/clean

source/agents/CMakeFiles/agent_switch.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents /home/vagrant/artemis/software/BeagleBone/build-raspi /home/vagrant/artemis/software/BeagleBone/build-raspi/source/agents /home/vagrant/artemis/software/BeagleBone/build-raspi/source/agents/CMakeFiles/agent_switch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/agents/CMakeFiles/agent_switch.dir/depend

