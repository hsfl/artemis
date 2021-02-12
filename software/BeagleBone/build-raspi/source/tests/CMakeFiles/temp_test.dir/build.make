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
include source/tests/CMakeFiles/temp_test.dir/depend.make

# Include the progress variables for this target.
include source/tests/CMakeFiles/temp_test.dir/progress.make

# Include the compile flags for this target's objects.
include source/tests/CMakeFiles/temp_test.dir/flags.make

source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o: source/tests/CMakeFiles/temp_test.dir/flags.make
source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/tests/temp_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/source/tests && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/temp_test.dir/temp_test.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/tests/temp_test.cpp

source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/temp_test.dir/temp_test.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/source/tests && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/tests/temp_test.cpp > CMakeFiles/temp_test.dir/temp_test.cpp.i

source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/temp_test.dir/temp_test.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/source/tests && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/tests/temp_test.cpp -o CMakeFiles/temp_test.dir/temp_test.cpp.s

source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o.requires:

.PHONY : source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o.requires

source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o.provides: source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o.requires
	$(MAKE) -f source/tests/CMakeFiles/temp_test.dir/build.make source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o.provides.build
.PHONY : source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o.provides

source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o.provides.build: source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o


# Object files for target temp_test
temp_test_OBJECTS = \
"CMakeFiles/temp_test.dir/temp_test.cpp.o"

# External object files for target temp_test
temp_test_EXTERNAL_OBJECTS =

bin/temp_test: source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o
bin/temp_test: source/tests/CMakeFiles/temp_test.dir/build.make
bin/temp_test: libraries/support/libCosmosSupport.a
bin/temp_test: libraries/agent/libCosmosAgent.a
bin/temp_test: libraries/device/general/libCosmosDeviceGeneral.a
bin/temp_test: libraries/device/i2c/libCosmosDeviceI2C.a
bin/temp_test: libraries/device/serial/libCosmosDeviceSerial.a
bin/temp_test: libraries/device/cpu/libCosmosDeviceCpu.a
bin/temp_test: libraries/device/disk/libCosmosDeviceDisk.a
bin/temp_test: libraries/math/libCosmosMath.a
bin/temp_test: libraries/physics/libCosmosPhysics.a
bin/temp_test: source/device/libCubesatDevices.a
bin/temp_test: libraries/SimpleAgent/libSimpleAgent.a
bin/temp_test: libraries/agent/libCosmosAgent.a
bin/temp_test: libraries/device/i2c/libCosmosDeviceI2C.a
bin/temp_test: libraries/support/libCosmosSupport.a
bin/temp_test: libraries/device/general/libCosmosDeviceGeneral.a
bin/temp_test: libraries/device/serial/libCosmosDeviceSerial.a
bin/temp_test: libraries/device/cpu/libCosmosDeviceCpu.a
bin/temp_test: libraries/device/disk/libCosmosDeviceDisk.a
bin/temp_test: libraries/support/libCosmosSupport.a
bin/temp_test: libraries/device/general/libCosmosDeviceGeneral.a
bin/temp_test: libraries/device/serial/libCosmosDeviceSerial.a
bin/temp_test: libraries/device/cpu/libCosmosDeviceCpu.a
bin/temp_test: libraries/device/disk/libCosmosDeviceDisk.a
bin/temp_test: libraries/zlib/liblocalzlib.a
bin/temp_test: libraries/math/libCosmosMath.a
bin/temp_test: libraries/physics/libCosmosPhysics.a
bin/temp_test: source/tests/CMakeFiles/temp_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/temp_test"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/source/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/temp_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/tests/CMakeFiles/temp_test.dir/build: bin/temp_test

.PHONY : source/tests/CMakeFiles/temp_test.dir/build

source/tests/CMakeFiles/temp_test.dir/requires: source/tests/CMakeFiles/temp_test.dir/temp_test.cpp.o.requires

.PHONY : source/tests/CMakeFiles/temp_test.dir/requires

source/tests/CMakeFiles/temp_test.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/source/tests && $(CMAKE_COMMAND) -P CMakeFiles/temp_test.dir/cmake_clean.cmake
.PHONY : source/tests/CMakeFiles/temp_test.dir/clean

source/tests/CMakeFiles/temp_test.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/artemis/software/BeagleBone/beaglebone/source/tests /home/vagrant/artemis/software/BeagleBone/build-raspi /home/vagrant/artemis/software/BeagleBone/build-raspi/source/tests /home/vagrant/artemis/software/BeagleBone/build-raspi/source/tests/CMakeFiles/temp_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/tests/CMakeFiles/temp_test.dir/depend

