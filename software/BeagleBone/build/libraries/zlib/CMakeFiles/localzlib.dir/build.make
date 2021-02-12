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
include libraries/zlib/CMakeFiles/localzlib.dir/depend.make

# Include the progress variables for this target.
include libraries/zlib/CMakeFiles/localzlib.dir/progress.make

# Include the compile flags for this target's objects.
include libraries/zlib/CMakeFiles/localzlib.dir/flags.make

libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/adler32.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/adler32.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/adler32.c

libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/adler32.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/adler32.c > CMakeFiles/localzlib.dir/adler32.c.i

libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/adler32.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/adler32.c -o CMakeFiles/localzlib.dir/adler32.c.s

libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o


libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/compress.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/compress.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/compress.c

libraries/zlib/CMakeFiles/localzlib.dir/compress.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/compress.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/compress.c > CMakeFiles/localzlib.dir/compress.c.i

libraries/zlib/CMakeFiles/localzlib.dir/compress.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/compress.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/compress.c -o CMakeFiles/localzlib.dir/compress.c.s

libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o


libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/crc32.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/crc32.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/crc32.c

libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/crc32.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/crc32.c > CMakeFiles/localzlib.dir/crc32.c.i

libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/crc32.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/crc32.c -o CMakeFiles/localzlib.dir/crc32.c.s

libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o


libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/deflate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/deflate.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/deflate.c

libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/deflate.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/deflate.c > CMakeFiles/localzlib.dir/deflate.c.i

libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/deflate.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/deflate.c -o CMakeFiles/localzlib.dir/deflate.c.s

libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o


libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzclose.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/gzclose.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzclose.c

libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/gzclose.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzclose.c > CMakeFiles/localzlib.dir/gzclose.c.i

libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/gzclose.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzclose.c -o CMakeFiles/localzlib.dir/gzclose.c.s

libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o


libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzlib.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/gzlib.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzlib.c

libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/gzlib.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzlib.c > CMakeFiles/localzlib.dir/gzlib.c.i

libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/gzlib.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzlib.c -o CMakeFiles/localzlib.dir/gzlib.c.s

libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o


libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/gzread.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzread.c

libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/gzread.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzread.c > CMakeFiles/localzlib.dir/gzread.c.i

libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/gzread.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzread.c -o CMakeFiles/localzlib.dir/gzread.c.s

libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o


libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzwrite.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/gzwrite.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzwrite.c

libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/gzwrite.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzwrite.c > CMakeFiles/localzlib.dir/gzwrite.c.i

libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/gzwrite.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/gzwrite.c -o CMakeFiles/localzlib.dir/gzwrite.c.s

libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o


libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/infback.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/infback.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/infback.c

libraries/zlib/CMakeFiles/localzlib.dir/infback.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/infback.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/infback.c > CMakeFiles/localzlib.dir/infback.c.i

libraries/zlib/CMakeFiles/localzlib.dir/infback.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/infback.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/infback.c -o CMakeFiles/localzlib.dir/infback.c.s

libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o


libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inffast.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/inffast.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inffast.c

libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/inffast.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inffast.c > CMakeFiles/localzlib.dir/inffast.c.i

libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/inffast.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inffast.c -o CMakeFiles/localzlib.dir/inffast.c.s

libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o


libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inflate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/inflate.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inflate.c

libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/inflate.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inflate.c > CMakeFiles/localzlib.dir/inflate.c.i

libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/inflate.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inflate.c -o CMakeFiles/localzlib.dir/inflate.c.s

libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o


libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inftrees.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/inftrees.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inftrees.c

libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/inftrees.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inftrees.c > CMakeFiles/localzlib.dir/inftrees.c.i

libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/inftrees.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/inftrees.c -o CMakeFiles/localzlib.dir/inftrees.c.s

libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o


libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/trees.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/trees.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/trees.c

libraries/zlib/CMakeFiles/localzlib.dir/trees.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/trees.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/trees.c > CMakeFiles/localzlib.dir/trees.c.i

libraries/zlib/CMakeFiles/localzlib.dir/trees.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/trees.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/trees.c -o CMakeFiles/localzlib.dir/trees.c.s

libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o


libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/uncompr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/uncompr.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/uncompr.c

libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/uncompr.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/uncompr.c > CMakeFiles/localzlib.dir/uncompr.c.i

libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/uncompr.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/uncompr.c -o CMakeFiles/localzlib.dir/uncompr.c.s

libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o


libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o: libraries/zlib/CMakeFiles/localzlib.dir/flags.make
libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o: /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/zutil.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/localzlib.dir/zutil.c.o   -c /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/zutil.c

libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/localzlib.dir/zutil.c.i"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/zutil.c > CMakeFiles/localzlib.dir/zutil.c.i

libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/localzlib.dir/zutil.c.s"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && /usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib/zutil.c -o CMakeFiles/localzlib.dir/zutil.c.s

libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o.requires:

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o.requires

libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o.provides: libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o.requires
	$(MAKE) -f libraries/zlib/CMakeFiles/localzlib.dir/build.make libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o.provides.build
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o.provides

libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o.provides.build: libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o


# Object files for target localzlib
localzlib_OBJECTS = \
"CMakeFiles/localzlib.dir/adler32.c.o" \
"CMakeFiles/localzlib.dir/compress.c.o" \
"CMakeFiles/localzlib.dir/crc32.c.o" \
"CMakeFiles/localzlib.dir/deflate.c.o" \
"CMakeFiles/localzlib.dir/gzclose.c.o" \
"CMakeFiles/localzlib.dir/gzlib.c.o" \
"CMakeFiles/localzlib.dir/gzread.c.o" \
"CMakeFiles/localzlib.dir/gzwrite.c.o" \
"CMakeFiles/localzlib.dir/infback.c.o" \
"CMakeFiles/localzlib.dir/inffast.c.o" \
"CMakeFiles/localzlib.dir/inflate.c.o" \
"CMakeFiles/localzlib.dir/inftrees.c.o" \
"CMakeFiles/localzlib.dir/trees.c.o" \
"CMakeFiles/localzlib.dir/uncompr.c.o" \
"CMakeFiles/localzlib.dir/zutil.c.o"

# External object files for target localzlib
localzlib_EXTERNAL_OBJECTS =

libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/build.make
libraries/zlib/liblocalzlib.a: libraries/zlib/CMakeFiles/localzlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/artemis/software/BeagleBone/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking C static library liblocalzlib.a"
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && $(CMAKE_COMMAND) -P CMakeFiles/localzlib.dir/cmake_clean_target.cmake
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/localzlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libraries/zlib/CMakeFiles/localzlib.dir/build: libraries/zlib/liblocalzlib.a

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/build

libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/adler32.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/compress.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/crc32.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/deflate.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/gzclose.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/gzlib.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/gzread.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/gzwrite.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/infback.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/inffast.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/inflate.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/inftrees.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/trees.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/uncompr.c.o.requires
libraries/zlib/CMakeFiles/localzlib.dir/requires: libraries/zlib/CMakeFiles/localzlib.dir/zutil.c.o.requires

.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/requires

libraries/zlib/CMakeFiles/localzlib.dir/clean:
	cd /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib && $(CMAKE_COMMAND) -P CMakeFiles/localzlib.dir/cmake_clean.cmake
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/clean

libraries/zlib/CMakeFiles/localzlib.dir/depend:
	cd /home/vagrant/artemis/software/BeagleBone/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/cosmos/source/projects/beaglebone/source /home/vagrant/cosmos/source/core/libraries/thirdparty/zlib /home/vagrant/artemis/software/BeagleBone/build /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib /home/vagrant/artemis/software/BeagleBone/build/libraries/zlib/CMakeFiles/localzlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libraries/zlib/CMakeFiles/localzlib.dir/depend

