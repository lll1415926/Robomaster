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
CMAKE_SOURCE_DIR = /home/lll/CLionProjects/apple

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lll/CLionProjects/apple/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/apple.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/apple.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/apple.dir/flags.make

CMakeFiles/apple.dir/main.cpp.o: CMakeFiles/apple.dir/flags.make
CMakeFiles/apple.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lll/CLionProjects/apple/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/apple.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/apple.dir/main.cpp.o -c /home/lll/CLionProjects/apple/main.cpp

CMakeFiles/apple.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apple.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lll/CLionProjects/apple/main.cpp > CMakeFiles/apple.dir/main.cpp.i

CMakeFiles/apple.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apple.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lll/CLionProjects/apple/main.cpp -o CMakeFiles/apple.dir/main.cpp.s

# Object files for target apple
apple_OBJECTS = \
"CMakeFiles/apple.dir/main.cpp.o"

# External object files for target apple
apple_EXTERNAL_OBJECTS =

apple: CMakeFiles/apple.dir/main.cpp.o
apple: CMakeFiles/apple.dir/build.make
apple: CMakeFiles/apple.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lll/CLionProjects/apple/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable apple"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/apple.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/apple.dir/build: apple

.PHONY : CMakeFiles/apple.dir/build

CMakeFiles/apple.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/apple.dir/cmake_clean.cmake
.PHONY : CMakeFiles/apple.dir/clean

CMakeFiles/apple.dir/depend:
	cd /home/lll/CLionProjects/apple/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lll/CLionProjects/apple /home/lll/CLionProjects/apple /home/lll/CLionProjects/apple/cmake-build-debug /home/lll/CLionProjects/apple/cmake-build-debug /home/lll/CLionProjects/apple/cmake-build-debug/CMakeFiles/apple.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/apple.dir/depend

