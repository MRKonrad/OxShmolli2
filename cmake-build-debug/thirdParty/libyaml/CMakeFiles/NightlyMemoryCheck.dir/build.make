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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kwerys/Code/OxShmolli2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kwerys/Code/OxShmolli2/cmake-build-debug

# Utility rule file for NightlyMemoryCheck.

# Include the progress variables for this target.
include thirdParty/libyaml/CMakeFiles/NightlyMemoryCheck.dir/progress.make

thirdParty/libyaml/CMakeFiles/NightlyMemoryCheck:
	cd /Users/kwerys/Code/OxShmolli2/cmake-build-debug/thirdParty/libyaml && /Applications/CLion.app/Contents/bin/cmake/bin/ctest -D NightlyMemoryCheck

NightlyMemoryCheck: thirdParty/libyaml/CMakeFiles/NightlyMemoryCheck
NightlyMemoryCheck: thirdParty/libyaml/CMakeFiles/NightlyMemoryCheck.dir/build.make

.PHONY : NightlyMemoryCheck

# Rule to build all files generated by this target.
thirdParty/libyaml/CMakeFiles/NightlyMemoryCheck.dir/build: NightlyMemoryCheck

.PHONY : thirdParty/libyaml/CMakeFiles/NightlyMemoryCheck.dir/build

thirdParty/libyaml/CMakeFiles/NightlyMemoryCheck.dir/clean:
	cd /Users/kwerys/Code/OxShmolli2/cmake-build-debug/thirdParty/libyaml && $(CMAKE_COMMAND) -P CMakeFiles/NightlyMemoryCheck.dir/cmake_clean.cmake
.PHONY : thirdParty/libyaml/CMakeFiles/NightlyMemoryCheck.dir/clean

thirdParty/libyaml/CMakeFiles/NightlyMemoryCheck.dir/depend:
	cd /Users/kwerys/Code/OxShmolli2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kwerys/Code/OxShmolli2 /Users/kwerys/Code/OxShmolli2/thirdParty/libyaml /Users/kwerys/Code/OxShmolli2/cmake-build-debug /Users/kwerys/Code/OxShmolli2/cmake-build-debug/thirdParty/libyaml /Users/kwerys/Code/OxShmolli2/cmake-build-debug/thirdParty/libyaml/CMakeFiles/NightlyMemoryCheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdParty/libyaml/CMakeFiles/NightlyMemoryCheck.dir/depend

