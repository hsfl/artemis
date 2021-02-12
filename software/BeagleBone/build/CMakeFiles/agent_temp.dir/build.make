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
include CMakeFiles/agent_temp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/agent_temp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/agent_temp.dir/flags.make

CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o: CMakeFiles/agent_temp.dir/flags.make
CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o: /home/vagrant/cosmos/source/projects/beaglebone/source/agents/agent_temp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o -c /home/vagrant/cosmos/source/projects/beaglebone/source/agents/agent_temp.cpp

CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/projects/beaglebone/source/agents/agent_temp.cpp > CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.i

CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/projects/beaglebone/source/agents/agent_temp.cpp -o CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.s

CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o.requires:

.PHONY : CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o.requires

CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o.provides: CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o.requires
	$(MAKE) -f CMakeFiles/agent_temp.dir/build.make CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o.provides.build
.PHONY : CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o.provides

CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o.provides.build: CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o


# Object files for target agent_temp
agent_temp_OBJECTS = \
"CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o"

# External object files for target agent_temp
agent_temp_EXTERNAL_OBJECTS =

bin/agent_temp: CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o
bin/agent_temp: CMakeFiles/agent_temp.dir/build.make
bin/agent_temp: libraries/support/libCosmosSupport.a
bin/agent_temp: libraries/agent/libCosmosAgent.a
bin/agent_temp: libraries/device/general/libCosmosDeviceGeneral.a
bin/agent_temp: libraries/device/i2c/libCosmosDeviceI2C.a
bin/agent_temp: libraries/device/serial/libCosmosDeviceSerial.a
bin/agent_temp: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_temp: libraries/device/disk/libCosmosDeviceDisk.a
bin/agent_temp: libraries/math/libCosmosMath.a
bin/agent_temp: libCubesatDevices.a
bin/agent_temp: libraries/agent/libCosmosAgent.a
bin/agent_temp: libraries/device/i2c/libCosmosDeviceI2C.a
bin/agent_temp: libraries/support/libCosmosSupport.a
bin/agent_temp: libraries/device/general/libCosmosDeviceGeneral.a
bin/agent_temp: libraries/device/serial/libCosmosDeviceSerial.a
bin/agent_temp: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_temp: libraries/device/disk/libCosmosDeviceDisk.a
bin/agent_temp: libraries/support/libCosmosSupport.a
bin/agent_temp: libraries/device/general/libCosmosDeviceGeneral.a
bin/agent_temp: libraries/device/serial/libCosmosDeviceSerial.a
bin/agent_temp: libraries/device/cpu/libCosmosDeviceCpu.a
bin/agent_temp: libraries/device/disk/libCosmosDeviceDisk.a
bin/agent_temp: libraries/zlib/liblocalzlib.a
bin/agent_temp: libraries/math/libCosmosMath.a
bin/agent_temp: CMakeFiles/agent_temp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/agent_temp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/agent_temp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/agent_temp.dir/build: bin/agent_temp

.PHONY : CMakeFiles/agent_temp.dir/build

CMakeFiles/agent_temp.dir/requires: CMakeFiles/agent_temp.dir/agents/agent_temp.cpp.o.requires

.PHONY : CMakeFiles/agent_temp.dir/requires

CMakeFiles/agent_temp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/agent_temp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/agent_temp.dir/clean

CMakeFiles/agent_temp.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/cosmos/source/projects/beaglebone/source /home/vagrant/cosmos/source/projects/beaglebone/source /home/vagrant/artemis/software/BeagleBone/build /home/vagrant/artemis/software/BeagleBone/build /home/vagrant/artemis/software/BeagleBone/build/CMakeFiles/agent_temp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/agent_temp.dir/depend

