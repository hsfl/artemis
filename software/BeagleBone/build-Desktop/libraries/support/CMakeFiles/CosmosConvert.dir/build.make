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
include libraries/support/CMakeFiles/CosmosConvert.dir/depend.make

# Include the progress variables for this target.
include libraries/support/CMakeFiles/CosmosConvert.dir/progress.make

# Include the compile flags for this target's objects.
include libraries/support/CMakeFiles/CosmosConvert.dir/flags.make

libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o: libraries/support/CMakeFiles/CosmosConvert.dir/flags.make
libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o: /home/vagrant/cosmos/source/core/libraries/support/convertlib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosConvert.dir/convertlib.cpp.o -c /home/vagrant/cosmos/source/core/libraries/support/convertlib.cpp

libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosConvert.dir/convertlib.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/support/convertlib.cpp > CMakeFiles/CosmosConvert.dir/convertlib.cpp.i

libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosConvert.dir/convertlib.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/support/convertlib.cpp -o CMakeFiles/CosmosConvert.dir/convertlib.cpp.s

libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o.requires:

.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o.requires

libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o.provides: libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o.requires
	$(MAKE) -f libraries/support/CMakeFiles/CosmosConvert.dir/build.make libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o.provides.build
.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o.provides

libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o.provides.build: libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o


libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o: libraries/support/CMakeFiles/CosmosConvert.dir/flags.make
libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o: /home/vagrant/cosmos/source/core/libraries/support/demlib.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosConvert.dir/demlib.cpp.o -c /home/vagrant/cosmos/source/core/libraries/support/demlib.cpp

libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosConvert.dir/demlib.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/support/demlib.cpp > CMakeFiles/CosmosConvert.dir/demlib.cpp.i

libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosConvert.dir/demlib.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/support/demlib.cpp -o CMakeFiles/CosmosConvert.dir/demlib.cpp.s

libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o.requires:

.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o.requires

libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o.provides: libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o.requires
	$(MAKE) -f libraries/support/CMakeFiles/CosmosConvert.dir/build.make libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o.provides.build
.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o.provides

libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o.provides.build: libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o


libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o: libraries/support/CMakeFiles/CosmosConvert.dir/flags.make
libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o: /home/vagrant/cosmos/source/core/libraries/support/jpleph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosConvert.dir/jpleph.cpp.o -c /home/vagrant/cosmos/source/core/libraries/support/jpleph.cpp

libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosConvert.dir/jpleph.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/support/jpleph.cpp > CMakeFiles/CosmosConvert.dir/jpleph.cpp.i

libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosConvert.dir/jpleph.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/support/jpleph.cpp -o CMakeFiles/CosmosConvert.dir/jpleph.cpp.s

libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o.requires:

.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o.requires

libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o.provides: libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o.requires
	$(MAKE) -f libraries/support/CMakeFiles/CosmosConvert.dir/build.make libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o.provides.build
.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o.provides

libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o.provides.build: libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o


libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o: libraries/support/CMakeFiles/CosmosConvert.dir/flags.make
libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o: /home/vagrant/cosmos/source/core/libraries/support/geomag.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CosmosConvert.dir/geomag.cpp.o -c /home/vagrant/cosmos/source/core/libraries/support/geomag.cpp

libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CosmosConvert.dir/geomag.cpp.i"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/support/geomag.cpp > CMakeFiles/CosmosConvert.dir/geomag.cpp.i

libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CosmosConvert.dir/geomag.cpp.s"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/support/geomag.cpp -o CMakeFiles/CosmosConvert.dir/geomag.cpp.s

libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o.requires:

.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o.requires

libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o.provides: libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o.requires
	$(MAKE) -f libraries/support/CMakeFiles/CosmosConvert.dir/build.make libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o.provides.build
.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o.provides

libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o.provides.build: libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o


# Object files for target CosmosConvert
CosmosConvert_OBJECTS = \
"CMakeFiles/CosmosConvert.dir/convertlib.cpp.o" \
"CMakeFiles/CosmosConvert.dir/demlib.cpp.o" \
"CMakeFiles/CosmosConvert.dir/jpleph.cpp.o" \
"CMakeFiles/CosmosConvert.dir/geomag.cpp.o"

# External object files for target CosmosConvert
CosmosConvert_EXTERNAL_OBJECTS =

libraries/support/libCosmosConvert.a: libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o
libraries/support/libCosmosConvert.a: libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o
libraries/support/libCosmosConvert.a: libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o
libraries/support/libCosmosConvert.a: libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o
libraries/support/libCosmosConvert.a: libraries/support/CMakeFiles/CosmosConvert.dir/build.make
libraries/support/libCosmosConvert.a: libraries/support/CMakeFiles/CosmosConvert.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build-Desktop/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libCosmosConvert.a"
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && $(CMAKE_COMMAND) -P CMakeFiles/CosmosConvert.dir/cmake_clean_target.cmake
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CosmosConvert.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libraries/support/CMakeFiles/CosmosConvert.dir/build: libraries/support/libCosmosConvert.a

.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/build

libraries/support/CMakeFiles/CosmosConvert.dir/requires: libraries/support/CMakeFiles/CosmosConvert.dir/convertlib.cpp.o.requires
libraries/support/CMakeFiles/CosmosConvert.dir/requires: libraries/support/CMakeFiles/CosmosConvert.dir/demlib.cpp.o.requires
libraries/support/CMakeFiles/CosmosConvert.dir/requires: libraries/support/CMakeFiles/CosmosConvert.dir/jpleph.cpp.o.requires
libraries/support/CMakeFiles/CosmosConvert.dir/requires: libraries/support/CMakeFiles/CosmosConvert.dir/geomag.cpp.o.requires

.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/requires

libraries/support/CMakeFiles/CosmosConvert.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support && $(CMAKE_COMMAND) -P CMakeFiles/CosmosConvert.dir/cmake_clean.cmake
.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/clean

libraries/support/CMakeFiles/CosmosConvert.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-Desktop && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/cosmos/source/core/libraries/support /home/vagrant/artemis/software/BeagleBone/build-Desktop /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support /home/vagrant/artemis/software/BeagleBone/build-Desktop/libraries/support/CMakeFiles/CosmosConvert.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libraries/support/CMakeFiles/CosmosConvert.dir/depend

