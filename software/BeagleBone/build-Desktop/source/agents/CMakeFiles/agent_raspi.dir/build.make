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
CMAKE_BINARY_DIR = /home/vagrant/artemis/software/BeagleBone/build-Desktop

# Include any dependencies generated for this target.
include source/agents/CMakeFiles/agent_raspi.dir/depend.make

# Include the progress variables for this target.
include source/agents/CMakeFiles/agent_raspi.dir/progress.make

# Include the compile flags for this target's objects.
include source/agents/CMakeFiles/agent_raspi.dir/flags.make

source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o: source/agents/CMakeFiles/agent_raspi.dir/flags.make
source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_raspi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_raspi.cpp

source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/agent_raspi.dir/agent_raspi.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_raspi.cpp > CMakeFiles/agent_raspi.dir/agent_raspi.cpp.i

source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/agent_raspi.dir/agent_raspi.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_raspi.cpp -o CMakeFiles/agent_raspi.dir/agent_raspi.cpp.s

source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o.requires:

.PHONY : source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o.requires

source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o.provides: source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o.requires
	$(MAKE) -f source/agents/CMakeFiles/agent_raspi.dir/build.make source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o.provides.build
.PHONY : source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o.provides

source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o.provides.build: source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o


# Object files for target agent_raspi
agent_raspi_OBJECTS = \
"CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o"

# External object files for target agent_raspi
agent_raspi_EXTERNAL_OBJECTS =

bin/agent_raspi: source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o
bin/agent_raspi: source/agents/CMakeFiles/agent_raspi.dir/build.make
bin/agent_raspi: libraries/support/libCosmosSupport.a
bin/agent_raspi: libraries/agent/libCosmosAgent.a
bin/agent_raspi: libraries/device/general/libCosmosDeviceGeneral.a
bin/agent_raspi: libraries/device/i2c/libCosmosDeviceI2C.a
bin/agent_raspi: libraries/device/serial/libCosmosDeviceSerial.a
bin/agent_raspi: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_raspi: libraries/device/disk/libCosmosDeviceDisk.a
bin/agent_raspi: libraries/math/libCosmosMath.a
bin/agent_raspi: libraries/physics/libCosmosPhysics.a
bin/agent_raspi: source/device/libCubesatDevices.a
bin/agent_raspi: libraries/SimpleAgent/libSimpleAgent.a
bin/agent_raspi: libraries/SimpleAgent/libSimpleAgent.a
bin/agent_raspi: libraries/support/libCosmosSupport.a
bin/agent_raspi: libraries/agent/libCosmosAgent.a
bin/agent_raspi: libraries/support/libCosmosError.a
bin/agent_raspi: libraries/support/libCosmosJson.a
bin/agent_raspi: libraries/device/i2c/libCosmosDeviceI2C.a
bin/agent_raspi: libraries/device/disk/libCosmosDeviceDisk.a
bin/agent_raspi: libraries/device/general/libCosmosDeviceGeneral.a
bin/agent_raspi: libraries/device/serial/libCosmosDeviceSerial.a
bin/agent_raspi: libraries/support/libCosmosNetwork.a
bin/agent_raspi: libraries/support/libCosmosSlip.a
bin/agent_raspi: libraries/physics/libCosmosPhysics.a
bin/agent_raspi: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_raspi: libraries/support/libCosmosNamespace.a
bin/agent_raspi: libraries/support/libCosmosTime.a
bin/agent_raspi: libraries/support/libCosmosData.a
bin/agent_raspi: libraries/support/libCosmosConvert.a
bin/agent_raspi: libraries/support/libCosmosCad.a
bin/agent_raspi: libraries/support/libCosmosEphem.a
bin/agent_raspi: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_raspi: libraries/support/libCosmosNamespace.a
bin/agent_raspi: libraries/support/libCosmosTime.a
bin/agent_raspi: libraries/support/libCosmosData.a
bin/agent_raspi: libraries/support/libCosmosConvert.a
bin/agent_raspi: libraries/support/libCosmosCad.a
bin/agent_raspi: libraries/support/libCosmosEphem.a
bin/agent_raspi: libraries/support/libCosmosString.a
bin/agent_raspi: libraries/zlib/liblocalzlib.a
bin/agent_raspi: libraries/math/libCosmosMath.a
bin/agent_raspi: source/agents/CMakeFiles/agent_raspi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/agent_raspi"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/agent_raspi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/agents/CMakeFiles/agent_raspi.dir/build: bin/agent_raspi

.PHONY : source/agents/CMakeFiles/agent_raspi.dir/build

source/agents/CMakeFiles/agent_raspi.dir/requires: source/agents/CMakeFiles/agent_raspi.dir/agent_raspi.cpp.o.requires

.PHONY : source/agents/CMakeFiles/agent_raspi.dir/requires

source/agents/CMakeFiles/agent_raspi.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents && $(CMAKE_COMMAND) -P CMakeFiles/agent_raspi.dir/cmake_clean.cmake
.PHONY : source/agents/CMakeFiles/agent_raspi.dir/clean

source/agents/CMakeFiles/agent_raspi.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents /home/vagrant/artemis/software/BeagleBone/build-Desktop /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents/CMakeFiles/agent_raspi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/agents/CMakeFiles/agent_raspi.dir/depend

