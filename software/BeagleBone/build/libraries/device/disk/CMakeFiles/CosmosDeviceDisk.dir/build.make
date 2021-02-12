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
include libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/depend.make

# Include the progress variables for this target.
include libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/progress.make

# Include the compile flags for this target's objects.
include libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/flags.make

libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o: libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/flags.make
libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o: /home/vagrant/cosmos/source/core/libraries/device/disk/devicedisk.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/device/disk && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o -c /home/vagrant/cosmos/source/core/libraries/device/disk/devicedisk.cpp

libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/device/disk && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/device/disk/devicedisk.cpp > CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.i

libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/device/disk && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/device/disk/devicedisk.cpp -o CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.s

libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o.requires:

.PHONY : libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o.requires

libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o.provides: libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o.requires
	$(MAKE) -f libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/build.make libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o.provides.build
.PHONY : libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o.provides

libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o.provides.build: libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o


# Object files for target CosmosDeviceDisk
CosmosDeviceDisk_OBJECTS = \
"CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o"

# External object files for target CosmosDeviceDisk
CosmosDeviceDisk_EXTERNAL_OBJECTS =

libraries/device/disk/libCosmosDeviceDisk.a: libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o
libraries/device/disk/libCosmosDeviceDisk.a: libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/build.make
libraries/device/disk/libCosmosDeviceDisk.a: libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCosmosDeviceDisk.a"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/device/disk && $(CMAKE_COMMAND) -P CMakeFiles/CosmosDeviceDisk.dir/cmake_clean_target.cmake
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/device/disk && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CosmosDeviceDisk.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/build: libraries/device/disk/libCosmosDeviceDisk.a

.PHONY : libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/build

libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/requires: libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/devicedisk.cpp.o.requires

.PHONY : libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/requires

libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/device/disk && $(CMAKE_COMMAND) -P CMakeFiles/CosmosDeviceDisk.dir/cmake_clean.cmake
.PHONY : libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/clean

libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/cosmos/source/projects/beaglebone/source /home/vagrant/cosmos/source/core/libraries/device/disk /home/vagrant/artemis/software/BeagleBone/build /home/vagrant/artemis/software/BeagleBone/build/libraries/device/disk /home/vagrant/artemis/software/BeagleBone/build/libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libraries/device/disk/CMakeFiles/CosmosDeviceDisk.dir/depend

