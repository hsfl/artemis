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
CMAKE_BINARY_DIR = /home/vagrant/artemis/software/BeagleBone/build-debug-raspi

# Utility rule file for config.

# Include the progress variables for this target.
include CMakeFiles/config.dir/progress.make

CMakeFiles/config:
	/usr/bin/cmake -E copy_directory /home/vagrant/artemis/software/BeagleBone/beaglebone/config /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/bin/config

config: CMakeFiles/config
config: CMakeFiles/config.dir/build.make

.PHONY : config

# Rule to build all files generated by this target.
CMakeFiles/config.dir/build: config

.PHONY : CMakeFiles/config.dir/build

CMakeFiles/config.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/config.dir/cmake_clean.cmake
.PHONY : CMakeFiles/config.dir/clean

CMakeFiles/config.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build-debug-raspi && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/artemis/software/BeagleBone/beaglebone /home/vagrant/artemis/software/BeagleBone/build-debug-raspi /home/vagrant/artemis/software/BeagleBone/build-debug-raspi /home/vagrant/artemis/software/BeagleBone/build-debug-raspi/CMakeFiles/config.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/config.dir/depend

