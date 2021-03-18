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
include libraries/support/CMakeFiles/CosmosSupport.dir/depend.make

# Include the progress variables for this target.
include libraries/support/CMakeFiles/CosmosSupport.dir/progress.make

# Include the compile flags for this target's objects.
include libraries/support/CMakeFiles/CosmosSupport.dir/flags.make

libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o: libraries/support/CMakeFiles/CosmosSupport.dir/flags.make
libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o: /home/vagrant/cosmos/source/core/libraries/support/estimation_lib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-arm32/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support && /usr/bin/arm-linux-gnueabihf-g++-4.9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o -c /home/vagrant/cosmos/source/core/libraries/support/estimation_lib.cpp

libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/support/estimation_lib.cpp > CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.i

libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support && /usr/bin/arm-linux-gnueabihf-g++-4.9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/support/estimation_lib.cpp -o CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.s

libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o.requires:

.PHONY : libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o.requires

libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o.provides: libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o.requires
	$(MAKE) -f libraries/support/CMakeFiles/CosmosSupport.dir/build.make libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o.provides.build
.PHONY : libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o.provides

libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o.provides.build: libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o


# Object files for target CosmosSupport
CosmosSupport_OBJECTS = \
"CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o"

# External object files for target CosmosSupport
CosmosSupport_EXTERNAL_OBJECTS =

libraries/support/libCosmosSupport.a: libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o
libraries/support/libCosmosSupport.a: libraries/support/CMakeFiles/CosmosSupport.dir/build.make
libraries/support/libCosmosSupport.a: libraries/support/CMakeFiles/CosmosSupport.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-arm32/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCosmosSupport.a"
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support && $(CMAKE_COMMAND) -P CMakeFiles/CosmosSupport.dir/cmake_clean_target.cmake
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CosmosSupport.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libraries/support/CMakeFiles/CosmosSupport.dir/build: libraries/support/libCosmosSupport.a

.PHONY : libraries/support/CMakeFiles/CosmosSupport.dir/build

libraries/support/CMakeFiles/CosmosSupport.dir/requires: libraries/support/CMakeFiles/CosmosSupport.dir/estimation_lib.cpp.o.requires

.PHONY : libraries/support/CMakeFiles/CosmosSupport.dir/requires

libraries/support/CMakeFiles/CosmosSupport.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support && $(CMAKE_COMMAND) -P CMakeFiles/CosmosSupport.dir/cmake_clean.cmake
.PHONY : libraries/support/CMakeFiles/CosmosSupport.dir/clean

libraries/support/CMakeFiles/CosmosSupport.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-arm32 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/cosmos/source/core/libraries/support /home/vagrant/artemis/software/BeagleBone/build-arm32 /home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support /home/vagrant/artemis/software/BeagleBone/build-arm32/libraries/support/CMakeFiles/CosmosSupport.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libraries/support/CMakeFiles/CosmosSupport.dir/depend

