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

# Utility rule file for doc_doxygen.

# Include any custom commands dependencies for this target.
include docs/CMakeFiles/doc_doxygen.dir/compiler_depend.make

# Include the progress variables for this target.
include docs/CMakeFiles/doc_doxygen.dir/progress.make

docs/CMakeFiles/doc_doxygen:
	cd /home/local1/Documents/g4sipm/docs && doxygen g4sipm.doxyfile

doc_doxygen: docs/CMakeFiles/doc_doxygen
doc_doxygen: docs/CMakeFiles/doc_doxygen.dir/build.make
.PHONY : doc_doxygen

# Rule to build all files generated by this target.
docs/CMakeFiles/doc_doxygen.dir/build: doc_doxygen
.PHONY : docs/CMakeFiles/doc_doxygen.dir/build

docs/CMakeFiles/doc_doxygen.dir/clean:
	cd /home/local1/Documents/g4sipm/build/docs && $(CMAKE_COMMAND) -P CMakeFiles/doc_doxygen.dir/cmake_clean.cmake
.PHONY : docs/CMakeFiles/doc_doxygen.dir/clean

docs/CMakeFiles/doc_doxygen.dir/depend:
	cd /home/local1/Documents/g4sipm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/local1/Documents/g4sipm /home/local1/Documents/g4sipm/docs /home/local1/Documents/g4sipm/build /home/local1/Documents/g4sipm/build/docs /home/local1/Documents/g4sipm/build/docs/CMakeFiles/doc_doxygen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : docs/CMakeFiles/doc_doxygen.dir/depend

