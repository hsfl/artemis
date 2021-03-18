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
include libraries/support/CMakeFiles/CosmosTime.dir/depend.make

# Include the progress variables for this target.
include libraries/support/CMakeFiles/CosmosTime.dir/progress.make

# Include the compile flags for this target's objects.
include libraries/support/CMakeFiles/CosmosTime.dir/flags.make

libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o: libraries/support/CMakeFiles/CosmosTime.dir/flags.make
libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o: /home/vagrant/cosmos/source/core/libraries/support/timelib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosTime.dir/timelib.cpp.o -c /home/vagrant/cosmos/source/core/libraries/support/timelib.cpp

libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosTime.dir/timelib.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/support/timelib.cpp > CMakeFiles/CosmosTime.dir/timelib.cpp.i

libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosTime.dir/timelib.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/support/timelib.cpp -o CMakeFiles/CosmosTime.dir/timelib.cpp.s

libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o.requires:

.PHONY : libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o.requires

libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o.provides: libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o.requires
	$(MAKE) -f libraries/support/CMakeFiles/CosmosTime.dir/build.make libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o.provides.build
.PHONY : libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o.provides

libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o.provides.build: libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o


libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o: libraries/support/CMakeFiles/CosmosTime.dir/flags.make
libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o: /home/vagrant/cosmos/source/core/libraries/support/timeutils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosTime.dir/timeutils.cpp.o -c /home/vagrant/cosmos/source/core/libraries/support/timeutils.cpp

libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosTime.dir/timeutils.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/support/timeutils.cpp > CMakeFiles/CosmosTime.dir/timeutils.cpp.i

libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosTime.dir/timeutils.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/support/timeutils.cpp -o CMakeFiles/CosmosTime.dir/timeutils.cpp.s

libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o.requires:

.PHONY : libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o.requires

libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o.provides: libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o.requires
	$(MAKE) -f libraries/support/CMakeFiles/CosmosTime.dir/build.make libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o.provides.build
.PHONY : libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o.provides

libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o.provides.build: libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o


libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o: libraries/support/CMakeFiles/CosmosTime.dir/flags.make
libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o: /home/vagrant/cosmos/source/core/libraries/support/elapsedtime.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o -c /home/vagrant/cosmos/source/core/libraries/support/elapsedtime.cpp

libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosTime.dir/elapsedtime.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/support/elapsedtime.cpp > CMakeFiles/CosmosTime.dir/elapsedtime.cpp.i

libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosTime.dir/elapsedtime.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/support/elapsedtime.cpp -o CMakeFiles/CosmosTime.dir/elapsedtime.cpp.s

libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o.requires:

.PHONY : libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o.requires

libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o.provides: libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o.requires
	$(MAKE) -f libraries/support/CMakeFiles/CosmosTime.dir/build.make libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o.provides.build
.PHONY : libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o.provides

libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o.provides.build: libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o


# Object files for target CosmosTime
CosmosTime_OBJECTS = \
"CMakeFiles/CosmosTime.dir/timelib.cpp.o" \
"CMakeFiles/CosmosTime.dir/timeutils.cpp.o" \
"CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o"

# External object files for target CosmosTime
CosmosTime_EXTERNAL_OBJECTS =

libraries/support/libCosmosTime.a: libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o
libraries/support/libCosmosTime.a: libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o
libraries/support/libCosmosTime.a: libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o
libraries/support/libCosmosTime.a: libraries/support/CMakeFiles/CosmosTime.dir/build.make
libraries/support/libCosmosTime.a: libraries/support/CMakeFiles/CosmosTime.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libCosmosTime.a"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && $(CMAKE_COMMAND) -P CMakeFiles/CosmosTime.dir/cmake_clean_target.cmake
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CosmosTime.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libraries/support/CMakeFiles/CosmosTime.dir/build: libraries/support/libCosmosTime.a

.PHONY : libraries/support/CMakeFiles/CosmosTime.dir/build

libraries/support/CMakeFiles/CosmosTime.dir/requires: libraries/support/CMakeFiles/CosmosTime.dir/timelib.cpp.o.requires
libraries/support/CMakeFiles/CosmosTime.dir/requires: libraries/support/CMakeFiles/CosmosTime.dir/timeutils.cpp.o.requires
libraries/support/CMakeFiles/CosmosTime.dir/requires: libraries/support/CMakeFiles/CosmosTime.dir/elapsedtime.cpp.o.requires

.PHONY : libraries/support/CMakeFiles/CosmosTime.dir/requires

libraries/support/CMakeFiles/CosmosTime.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && $(CMAKE_COMMAND) -P CMakeFiles/CosmosTime.dir/cmake_clean.cmake
.PHONY : libraries/support/CMakeFiles/CosmosTime.dir/clean

libraries/support/CMakeFiles/CosmosTime.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/cosmos/source/core/libraries/support /home/vagrant/artemis/software/BeagleBone/build-Desktop /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support/CMakeFiles/CosmosTime.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libraries/support/CMakeFiles/CosmosTime.dir/depend

