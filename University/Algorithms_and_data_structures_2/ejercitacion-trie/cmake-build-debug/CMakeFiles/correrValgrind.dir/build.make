# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "F:\Mariano\UBA\algo 2\ejercitacion-trie"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "F:\Mariano\UBA\algo 2\ejercitacion-trie\cmake-build-debug"

# Utility rule file for correrValgrind.

# Include the progress variables for this target.
include CMakeFiles/correrValgrind.dir/progress.make

CMakeFiles/correrValgrind: correrTests.exe
	valgrind --leak-check=full -v ./correrTests 2>&1

correrValgrind: CMakeFiles/correrValgrind
correrValgrind: CMakeFiles/correrValgrind.dir/build.make

.PHONY : correrValgrind

# Rule to build all files generated by this target.
CMakeFiles/correrValgrind.dir/build: correrValgrind

.PHONY : CMakeFiles/correrValgrind.dir/build

CMakeFiles/correrValgrind.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\correrValgrind.dir\cmake_clean.cmake
.PHONY : CMakeFiles/correrValgrind.dir/clean

CMakeFiles/correrValgrind.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "F:\Mariano\UBA\algo 2\ejercitacion-trie" "F:\Mariano\UBA\algo 2\ejercitacion-trie" "F:\Mariano\UBA\algo 2\ejercitacion-trie\cmake-build-debug" "F:\Mariano\UBA\algo 2\ejercitacion-trie\cmake-build-debug" "F:\Mariano\UBA\algo 2\ejercitacion-trie\cmake-build-debug\CMakeFiles\correrValgrind.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/correrValgrind.dir/depend

