# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /mnt/c/Users/Arseny/Documents/Prog/Contest_15

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Arseny/Documents/Prog/Contest_15/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Contest_15.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Contest_15.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Contest_15.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Contest_15.dir/flags.make

CMakeFiles/Contest_15.dir/3.c.o: CMakeFiles/Contest_15.dir/flags.make
CMakeFiles/Contest_15.dir/3.c.o: ../3.c
CMakeFiles/Contest_15.dir/3.c.o: CMakeFiles/Contest_15.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Arseny/Documents/Prog/Contest_15/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Contest_15.dir/3.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Contest_15.dir/3.c.o -MF CMakeFiles/Contest_15.dir/3.c.o.d -o CMakeFiles/Contest_15.dir/3.c.o -c /mnt/c/Users/Arseny/Documents/Prog/Contest_15/3.c

CMakeFiles/Contest_15.dir/3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Contest_15.dir/3.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Arseny/Documents/Prog/Contest_15/3.c > CMakeFiles/Contest_15.dir/3.c.i

CMakeFiles/Contest_15.dir/3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Contest_15.dir/3.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Arseny/Documents/Prog/Contest_15/3.c -o CMakeFiles/Contest_15.dir/3.c.s

# Object files for target Contest_15
Contest_15_OBJECTS = \
"CMakeFiles/Contest_15.dir/3.c.o"

# External object files for target Contest_15
Contest_15_EXTERNAL_OBJECTS =

Contest_15: CMakeFiles/Contest_15.dir/3.c.o
Contest_15: CMakeFiles/Contest_15.dir/build.make
Contest_15: CMakeFiles/Contest_15.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Arseny/Documents/Prog/Contest_15/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Contest_15"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Contest_15.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Contest_15.dir/build: Contest_15
.PHONY : CMakeFiles/Contest_15.dir/build

CMakeFiles/Contest_15.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Contest_15.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Contest_15.dir/clean

CMakeFiles/Contest_15.dir/depend:
	cd /mnt/c/Users/Arseny/Documents/Prog/Contest_15/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Arseny/Documents/Prog/Contest_15 /mnt/c/Users/Arseny/Documents/Prog/Contest_15 /mnt/c/Users/Arseny/Documents/Prog/Contest_15/cmake-build-debug /mnt/c/Users/Arseny/Documents/Prog/Contest_15/cmake-build-debug /mnt/c/Users/Arseny/Documents/Prog/Contest_15/cmake-build-debug/CMakeFiles/Contest_15.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Contest_15.dir/depend

