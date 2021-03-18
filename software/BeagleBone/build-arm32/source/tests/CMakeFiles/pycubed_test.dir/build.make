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
CMAKE_BINARY_DIR = /home/vagrant/artemis/software/BeagleBone/build-arm32

# Include any dependencies generated for this target.
include source/tests/CMakeFiles/pycubed_test.dir/depend.make

# Include the progress variables for this target.
include source/tests/CMakeFiles/pycubed_test.dir/progress.make

# Include the compile flags for this target's objects.
include source/tests/CMakeFiles/pycubed_test.dir/flags.make

source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o: source/tests/CMakeFiles/pycubed_test.dir/flags.make
source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o: /home/vagrant/artemis/software/BeagleBone/beaglebone/source/tests/pycubed_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-arm32/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32/source/tests && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o -c /home/vagrant/artemis/software/BeagleBone/beaglebone/source/tests/pycubed_test.cpp

source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pycubed_test.dir/pycubed_test.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32/source/tests && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/artemis/software/BeagleBone/beaglebone/source/tests/pycubed_test.cpp > CMakeFiles/pycubed_test.dir/pycubed_test.cpp.i

source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pycubed_test.dir/pycubed_test.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32/source/tests && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/artemis/software/BeagleBone/beaglebone/source/tests/pycubed_test.cpp -o CMakeFiles/pycubed_test.dir/pycubed_test.cpp.s

source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o.requires:

.PHONY : source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o.requires

source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o.provides: source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o.requires
	$(MAKE) -f source/tests/CMakeFiles/pycubed_test.dir/build.make source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o.provides.build
.PHONY : source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o.provides

source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o.provides.build: source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o


# Object files for target pycubed_test
pycubed_test_OBJECTS = \
"CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o"

# External object files for target pycubed_test
pycubed_test_EXTERNAL_OBJECTS =

bin/pycubed_test: source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o
bin/pycubed_test: source/tests/CMakeFiles/pycubed_test.dir/build.make
bin/pycubed_test: libraries/support/libCosmosSupport.a
bin/pycubed_test: libraries/agent/libCosmosAgent.a
bin/pycubed_test: libraries/device/general/libCosmosDeviceGeneral.a
bin/pycubed_test: libraries/device/i2c/libCosmosDeviceI2C.a
bin/pycubed_test: libraries/device/serial/libCosmosDeviceSerial.a
bin/pycubed_test: libraries/device/cpu/libCosmosDeviceCpu.a
bin/pycubed_test: libraries/device/disk/libCosmosDeviceDisk.a
bin/pycubed_test: libraries/math/libCosmosMath.a
bin/pycubed_test: libraries/physics/libCosmosPhysics.a
bin/pycubed_test: source/device/libCubesatDevices.a
bin/pycubed_test: libraries/SimpleAgent/libSimpleAgent.a
bin/pycubed_test: libraries/support/libCosmosSupport.a
bin/pycubed_test: libraries/agent/libCosmosAgent.a
bin/pycubed_test: libraries/support/libCosmosError.a
bin/pycubed_test: libraries/support/libCosmosJson.a
bin/pycubed_test: libraries/device/i2c/libCosmosDeviceI2C.a
bin/pycubed_test: libraries/device/disk/libCosmosDeviceDisk.a
bin/pycubed_test: libraries/device/general/libCosmosDeviceGeneral.a
bin/pycubed_test: libraries/device/serial/libCosmosDeviceSerial.a
bin/pycubed_test: libraries/support/libCosmosNetwork.a
bin/pycubed_test: libraries/support/libCosmosSlip.a
bin/pycubed_test: libraries/physics/libCosmosPhysics.a
bin/pycubed_test: libraries/device/cpu/libCosmosDeviceCpu.a
bin/pycubed_test: libraries/support/libCosmosNamespace.a
bin/pycubed_test: libraries/support/libCosmosTime.a
bin/pycubed_test: libraries/support/libCosmosData.a
bin/pycubed_test: libraries/support/libCosmosConvert.a
bin/pycubed_test: libraries/support/libCosmosCad.a
bin/pycubed_test: libraries/support/libCosmosEphem.a
bin/pycubed_test: libraries/device/cpu/libCosmosDeviceCpu.a
bin/pycubed_test: libraries/support/libCosmosNamespace.a
bin/pycubed_test: libraries/support/libCosmosTime.a
bin/pycubed_test: libraries/support/libCosmosData.a
bin/pycubed_test: libraries/support/libCosmosConvert.a
bin/pycubed_test: libraries/support/libCosmosCad.a
bin/pycubed_test: libraries/support/libCosmosEphem.a
bin/pycubed_test: libraries/support/libCosmosString.a
bin/pycubed_test: libraries/zlib/liblocalzlib.a
bin/pycubed_test: libraries/math/libCosmosMath.a
bin/pycubed_test: source/tests/CMakeFiles/pycubed_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-arm32/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/pycubed_test"
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32/source/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pycubed_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/tests/CMakeFiles/pycubed_test.dir/build: bin/pycubed_test

.PHONY : source/tests/CMakeFiles/pycubed_test.dir/build

source/tests/CMakeFiles/pycubed_test.dir/requires: source/tests/CMakeFiles/pycubed_test.dir/pycubed_test.cpp.o.requires

.PHONY : source/tests/CMakeFiles/pycubed_test.dir/requires

source/tests/CMakeFiles/pycubed_test.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32/source/tests && $(CMAKE_COMMAND) -P CMakeFiles/pycubed_test.dir/cmake_clean.cmake
.PHONY : source/tests/CMakeFiles/pycubed_test.dir/clean

source/tests/CMakeFiles/pycubed_test.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/artemis/software/BeagleBone/beaglebone/source/tests /home/vagrant/artemis/software/BeagleBone/build-arm32 /home/vagrant/artemis/software/BeagleBone/build-arm32/source/tests /home/vagrant/artemis/software/BeagleBone/build-arm32/source/tests/CMakeFiles/pycubed_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/tests/CMakeFiles/pycubed_test.dir/depend

