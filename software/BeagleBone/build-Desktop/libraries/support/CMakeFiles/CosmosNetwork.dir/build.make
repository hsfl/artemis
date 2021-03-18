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
include libraries/support/CMakeFiles/CosmosNetwork.dir/depend.make

# Include the progress variables for this target.
include libraries/support/CMakeFiles/CosmosNetwork.dir/progress.make

# Include the compile flags for this target's objects.
include libraries/support/CMakeFiles/CosmosNetwork.dir/flags.make

libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o: libraries/support/CMakeFiles/CosmosNetwork.dir/flags.make
libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o: /home/vagrant/cosmos/source/core/libraries/support/socketlib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o -c /home/vagrant/cosmos/source/core/libraries/support/socketlib.cpp

libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosNetwork.dir/socketlib.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/support/socketlib.cpp > CMakeFiles/CosmosNetwork.dir/socketlib.cpp.i

libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosNetwork.dir/socketlib.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/support/socketlib.cpp -o CMakeFiles/CosmosNetwork.dir/socketlib.cpp.s

libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o.requires:

.PHONY : libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o.requires

libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o.provides: libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o.requires
	$(MAKE) -f libraries/support/CMakeFiles/CosmosNetwork.dir/build.make libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o.provides.build
.PHONY : libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o.provides

libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o.provides.build: libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o


# Object files for target CosmosNetwork
CosmosNetwork_OBJECTS = \
"CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o"

# External object files for target CosmosNetwork
CosmosNetwork_EXTERNAL_OBJECTS =

libraries/support/libCosmosNetwork.a: libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o
libraries/support/libCosmosNetwork.a: libraries/support/CMakeFiles/CosmosNetwork.dir/build.make
libraries/support/libCosmosNetwork.a: libraries/support/CMakeFiles/CosmosNetwork.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCosmosNetwork.a"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && $(CMAKE_COMMAND) -P CMakeFiles/CosmosNetwork.dir/cmake_clean_target.cmake
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CosmosNetwork.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libraries/support/CMakeFiles/CosmosNetwork.dir/build: libraries/support/libCosmosNetwork.a

.PHONY : libraries/support/CMakeFiles/CosmosNetwork.dir/build

libraries/support/CMakeFiles/CosmosNetwork.dir/requires: libraries/support/CMakeFiles/CosmosNetwork.dir/socketlib.cpp.o.requires

.PHONY : libraries/support/CMakeFiles/CosmosNetwork.dir/requires

libraries/support/CMakeFiles/CosmosNetwork.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && $(CMAKE_COMMAND) -P CMakeFiles/CosmosNetwork.dir/cmake_clean.cmake
.PHONY : libraries/support/CMakeFiles/CosmosNetwork.dir/clean

libraries/support/CMakeFiles/CosmosNetwork.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/cosmos/source/core/libraries/support /home/vagrant/artemis/software/BeagleBone/build-Desktop /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support/CMakeFiles/CosmosNetwork.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libraries/support/CMakeFiles/CosmosNetwork.dir/depend

