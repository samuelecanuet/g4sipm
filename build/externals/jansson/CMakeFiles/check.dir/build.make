# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/local1/Documents/g4sipm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/local1/Documents/g4sipm/build

# Utility rule file for check.

# Include any custom commands dependencies for this target.
include externals/jansson/CMakeFiles/check.dir/compiler_depend.make

# Include the progress variables for this target.
include externals/jansson/CMakeFiles/check.dir/progress.make

externals/jansson/CMakeFiles/check: externals/jansson/bin/json_process
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_array
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_copy
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_dump
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_dump_callback
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_equal
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_load
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_loadb
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_number
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_object
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_pack
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_simple
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_unpack
externals/jansson/CMakeFiles/check: externals/jansson/bin/test_memory_funcs
	cd /home/local1/Documents/g4sipm/build/externals/jansson && /usr/bin/ctest

check: externals/jansson/CMakeFiles/check
check: externals/jansson/CMakeFiles/check.dir/build.make
.PHONY : check

# Rule to build all files generated by this target.
externals/jansson/CMakeFiles/check.dir/build: check
.PHONY : externals/jansson/CMakeFiles/check.dir/build

externals/jansson/CMakeFiles/check.dir/clean:
	cd /home/local1/Documents/g4sipm/build/externals/jansson && $(CMAKE_COMMAND) -P CMakeFiles/check.dir/cmake_clean.cmake
.PHONY : externals/jansson/CMakeFiles/check.dir/clean

externals/jansson/CMakeFiles/check.dir/depend:
	cd /home/local1/Documents/g4sipm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/local1/Documents/g4sipm /home/local1/Documents/g4sipm/externals/jansson /home/local1/Documents/g4sipm/build /home/local1/Documents/g4sipm/build/externals/jansson /home/local1/Documents/g4sipm/build/externals/jansson/CMakeFiles/check.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : externals/jansson/CMakeFiles/check.dir/depend

