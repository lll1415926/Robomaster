# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/lll/CLionProjects/plate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lll/CLionProjects/plate/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/plate.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/plate.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/plate.dir/flags.make

CMakeFiles/plate.dir/main.cpp.o: CMakeFiles/plate.dir/flags.make
CMakeFiles/plate.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lll/CLionProjects/plate/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/plate.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/plate.dir/main.cpp.o -c /home/lll/CLionProjects/plate/main.cpp

CMakeFiles/plate.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plate.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lll/CLionProjects/plate/main.cpp > CMakeFiles/plate.dir/main.cpp.i

CMakeFiles/plate.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plate.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lll/CLionProjects/plate/main.cpp -o CMakeFiles/plate.dir/main.cpp.s

# Object files for target plate
plate_OBJECTS = \
"CMakeFiles/plate.dir/main.cpp.o"

# External object files for target plate
plate_EXTERNAL_OBJECTS =

plate: CMakeFiles/plate.dir/main.cpp.o
plate: CMakeFiles/plate.dir/build.make
plate: CMakeFiles/plate.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lll/CLionProjects/plate/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable plate"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/plate.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/plate.dir/build: plate

.PHONY : CMakeFiles/plate.dir/build

CMakeFiles/plate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/plate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/plate.dir/clean

CMakeFiles/plate.dir/depend:
	cd /home/lll/CLionProjects/plate/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lll/CLionProjects/plate /home/lll/CLionProjects/plate /home/lll/CLionProjects/plate/cmake-build-debug /home/lll/CLionProjects/plate/cmake-build-debug /home/lll/CLionProjects/plate/cmake-build-debug/CMakeFiles/plate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/plate.dir/depend

