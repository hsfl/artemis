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
include libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/depend.make

# Include the progress variables for this target.
include libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/progress.make

# Include the compile flags for this target's objects.
include libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/flags.make

libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o: libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/flags.make
libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o: /home/vagrant/cosmos/source/core/libraries/device/ccsds/spp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/device/ccsds && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o -c /home/vagrant/cosmos/source/core/libraries/device/ccsds/spp.cpp

libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/device/ccsds && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/device/ccsds/spp.cpp > CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.i

libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/device/ccsds && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/device/ccsds/spp.cpp -o CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.s

libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o.requires:

.PHONY : libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o.requires

libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o.provides: libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o.requires
	$(MAKE) -f libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/build.make libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o.provides.build
.PHONY : libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o.provides

libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o.provides.build: libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o


# Object files for target CosmosDeviceCcsds
CosmosDeviceCcsds_OBJECTS = \
"CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o"

# External object files for target CosmosDeviceCcsds
CosmosDeviceCcsds_EXTERNAL_OBJECTS =

libraries/device/ccsds/libCosmosDeviceCcsds.a: libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o
libraries/device/ccsds/libCosmosDeviceCcsds.a: libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/build.make
libraries/device/ccsds/libCosmosDeviceCcsds.a: libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCosmosDeviceCcsds.a"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/device/ccsds && $(CMAKE_COMMAND) -P CMakeFiles/CosmosDeviceCcsds.dir/cmake_clean_target.cmake
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/device/ccsds && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CosmosDeviceCcsds.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/build: libraries/device/ccsds/libCosmosDeviceCcsds.a

.PHONY : libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/build

libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/requires: libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/spp.cpp.o.requires

.PHONY : libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/requires

libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/device/ccsds && $(CMAKE_COMMAND) -P CMakeFiles/CosmosDeviceCcsds.dir/cmake_clean.cmake
.PHONY : libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/clean

libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/cosmos/source/core/libraries/device/ccsds /home/vagrant/artemis/software/BeagleBone/build-Desktop /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/device/ccsds /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libraries/device/ccsds/CMakeFiles/CosmosDeviceCcsds.dir/depend
