# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = /home/group36/Project/UnitTest/UnitTest/Airpump

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/group36/Project/UnitTest/UnitTest/Airpump/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/Test_airpump.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/Test_airpump.cpp.o: ../Test_airpump.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/group36/Project/UnitTest/UnitTest/Airpump/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/Test_airpump.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/Test_airpump.cpp.o -c /home/group36/Project/UnitTest/UnitTest/Airpump/Test_airpump.cpp

CMakeFiles/main.dir/Test_airpump.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/Test_airpump.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/group36/Project/UnitTest/UnitTest/Airpump/Test_airpump.cpp > CMakeFiles/main.dir/Test_airpump.cpp.i

CMakeFiles/main.dir/Test_airpump.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/Test_airpump.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/group36/Project/UnitTest/UnitTest/Airpump/Test_airpump.cpp -o CMakeFiles/main.dir/Test_airpump.cpp.s

CMakeFiles/main.dir/pwmctrl.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/pwmctrl.cpp.o: ../pwmctrl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/group36/Project/UnitTest/UnitTest/Airpump/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/pwmctrl.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/pwmctrl.cpp.o -c /home/group36/Project/UnitTest/UnitTest/Airpump/pwmctrl.cpp

CMakeFiles/main.dir/pwmctrl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/pwmctrl.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/group36/Project/UnitTest/UnitTest/Airpump/pwmctrl.cpp > CMakeFiles/main.dir/pwmctrl.cpp.i

CMakeFiles/main.dir/pwmctrl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/pwmctrl.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/group36/Project/UnitTest/UnitTest/Airpump/pwmctrl.cpp -o CMakeFiles/main.dir/pwmctrl.cpp.s

CMakeFiles/main.dir/airpump.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/airpump.cpp.o: ../airpump.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/group36/Project/UnitTest/UnitTest/Airpump/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/airpump.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/airpump.cpp.o -c /home/group36/Project/UnitTest/UnitTest/Airpump/airpump.cpp

CMakeFiles/main.dir/airpump.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/airpump.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/group36/Project/UnitTest/UnitTest/Airpump/airpump.cpp > CMakeFiles/main.dir/airpump.cpp.i

CMakeFiles/main.dir/airpump.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/airpump.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/group36/Project/UnitTest/UnitTest/Airpump/airpump.cpp -o CMakeFiles/main.dir/airpump.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/Test_airpump.cpp.o" \
"CMakeFiles/main.dir/pwmctrl.cpp.o" \
"CMakeFiles/main.dir/airpump.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/Test_airpump.cpp.o
main: CMakeFiles/main.dir/pwmctrl.cpp.o
main: CMakeFiles/main.dir/airpump.cpp.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/group36/Project/UnitTest/UnitTest/Airpump/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/group36/Project/UnitTest/UnitTest/Airpump/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/group36/Project/UnitTest/UnitTest/Airpump /home/group36/Project/UnitTest/UnitTest/Airpump /home/group36/Project/UnitTest/UnitTest/Airpump/build /home/group36/Project/UnitTest/UnitTest/Airpump/build /home/group36/Project/UnitTest/UnitTest/Airpump/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

