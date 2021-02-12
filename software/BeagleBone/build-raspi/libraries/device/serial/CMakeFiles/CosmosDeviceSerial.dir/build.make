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
include libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/depend.make

# Include the progress variables for this target.
include libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/progress.make

# Include the compile flags for this target's objects.
include libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/flags.make

libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o: libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/flags.make
libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o: /home/vagrant/cosmos/source/core/libraries/device/serial/serialclass.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/libraries/device/serial && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o -c /home/vagrant/cosmos/source/core/libraries/device/serial/serialclass.cpp

libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/libraries/device/serial && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/device/serial/serialclass.cpp > CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.i

libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/libraries/device/serial && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/device/serial/serialclass.cpp -o CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.s

libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o.requires:

.PHONY : libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o.requires

libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o.provides: libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o.requires
	$(MAKE) -f libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/build.make libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o.provides.build
.PHONY : libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o.provides

libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o.provides.build: libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o


# Object files for target CosmosDeviceSerial
CosmosDeviceSerial_OBJECTS = \
"CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o"

# External object files for target CosmosDeviceSerial
CosmosDeviceSerial_EXTERNAL_OBJECTS =

libraries/device/serial/libCosmosDeviceSerial.a: libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o
libraries/device/serial/libCosmosDeviceSerial.a: libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/build.make
libraries/device/serial/libCosmosDeviceSerial.a: libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-raspi/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCosmosDeviceSerial.a"
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/libraries/device/serial && $(CMAKE_COMMAND) -P CMakeFiles/CosmosDeviceSerial.dir/cmake_clean_target.cmake
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/libraries/device/serial && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CosmosDeviceSerial.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/build: libraries/device/serial/libCosmosDeviceSerial.a

.PHONY : libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/build

libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/requires: libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/serialclass.cpp.o.requires

.PHONY : libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/requires

libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi/libraries/device/serial && $(CMAKE_COMMAND) -P CMakeFiles/CosmosDeviceSerial.dir/cmake_clean.cmake
.PHONY : libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/clean

libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-raspi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/cosmos/source/core/libraries/device/serial /home/vagrant/artemis/software/BeagleBone/build-raspi /home/vagrant/artemis/software/BeagleBone/build-raspi/libraries/device/serial /home/vagrant/artemis/software/BeagleBone/build-raspi/libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libraries/device/serial/CMakeFiles/CosmosDeviceSerial.dir/depend

