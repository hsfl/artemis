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
include source/agents/CMakeFiles/agent_pycubed.dir/depend.make

# Include the progress variables for this target.
include source/agents/CMakeFiles/agent_pycubed.dir/progress.make

# Include the compile flags for this target's objects.
include source/agents/CMakeFiles/agent_pycubed.dir/flags.make

source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o: source/agents/CMakeFiles/agent_pycubed.dir/flags.make
source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_pycubed.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_pycubed.cpp

source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_pycubed.cpp > CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.i

source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents/agent_pycubed.cpp -o CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.s

source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o.requires:

.PHONY : source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o.requires

source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o.provides: source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o.requires
	$(MAKE) -f source/agents/CMakeFiles/agent_pycubed.dir/build.make source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o.provides.build
.PHONY : source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o.provides

source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o.provides.build: source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o


# Object files for target agent_pycubed
agent_pycubed_OBJECTS = \
"CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o"

# External object files for target agent_pycubed
agent_pycubed_EXTERNAL_OBJECTS =

bin/agent_pycubed: source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o
bin/agent_pycubed: source/agents/CMakeFiles/agent_pycubed.dir/build.make
bin/agent_pycubed: libraries/support/libCosmosSupport.a
bin/agent_pycubed: libraries/agent/libCosmosAgent.a
bin/agent_pycubed: libraries/device/general/libCosmosDeviceGeneral.a
bin/agent_pycubed: libraries/device/i2c/libCosmosDeviceI2C.a
bin/agent_pycubed: libraries/device/serial/libCosmosDeviceSerial.a
bin/agent_pycubed: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_pycubed: libraries/device/disk/libCosmosDeviceDisk.a
bin/agent_pycubed: libraries/math/libCosmosMath.a
bin/agent_pycubed: libraries/physics/libCosmosPhysics.a
bin/agent_pycubed: source/device/libCubesatDevices.a
bin/agent_pycubed: libraries/SimpleAgent/libSimpleAgent.a
bin/agent_pycubed: libraries/SimpleAgent/libSimpleAgent.a
bin/agent_pycubed: libraries/agent/libCosmosAgent.a
bin/agent_pycubed: libraries/device/i2c/libCosmosDeviceI2C.a
bin/agent_pycubed: libraries/support/libCosmosSupport.a
bin/agent_pycubed: libraries/device/general/libCosmosDeviceGeneral.a
bin/agent_pycubed: libraries/device/serial/libCosmosDeviceSerial.a
bin/agent_pycubed: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_pycubed: libraries/device/disk/libCosmosDeviceDisk.a
bin/agent_pycubed: libraries/support/libCosmosSupport.a
bin/agent_pycubed: libraries/device/general/libCosmosDeviceGeneral.a
bin/agent_pycubed: libraries/device/serial/libCosmosDeviceSerial.a
bin/agent_pycubed: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_pycubed: libraries/device/disk/libCosmosDeviceDisk.a
bin/agent_pycubed: libraries/zlib/liblocalzlib.a
bin/agent_pycubed: libraries/math/libCosmosMath.a
bin/agent_pycubed: libraries/physics/libCosmosPhysics.a
bin/agent_pycubed: source/agents/CMakeFiles/agent_pycubed.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/agent_pycubed"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/agent_pycubed.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/agents/CMakeFiles/agent_pycubed.dir/build: bin/agent_pycubed

.PHONY : source/agents/CMakeFiles/agent_pycubed.dir/build

source/agents/CMakeFiles/agent_pycubed.dir/requires: source/agents/CMakeFiles/agent_pycubed.dir/agent_pycubed.cpp.o.requires

.PHONY : source/agents/CMakeFiles/agent_pycubed.dir/requires

source/agents/CMakeFiles/agent_pycubed.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents && $(CMAKE_COMMAND) -P CMakeFiles/agent_pycubed.dir/cmake_clean.cmake
.PHONY : source/agents/CMakeFiles/agent_pycubed.dir/clean

source/agents/CMakeFiles/agent_pycubed.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/artemis/software/BeagleBone/beaglebone/source/agents /home/vagrant/artemis/software/BeagleBone/build-Desktop /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents /home/vagrant/artemis/software/BeagleBone/build-Desktop/source/agents/CMakeFiles/agent_pycubed.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/agents/CMakeFiles/agent_pycubed.dir/depend
