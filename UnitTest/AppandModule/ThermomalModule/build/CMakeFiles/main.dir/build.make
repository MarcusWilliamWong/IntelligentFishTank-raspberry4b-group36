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
CMAKE_SOURCE_DIR = /home/group36/Project/UnitTest/UnitTest/ThermomalModule

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/group36/Project/UnitTest/UnitTest/ThermomalModule/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/app.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/app.cpp.o: ../app.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/group36/Project/UnitTest/UnitTest/ThermomalModule/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/app.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/app.cpp.o -c /home/group36/Project/UnitTest/UnitTest/ThermomalModule/app.cpp

CMakeFiles/main.dir/app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/app.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/group36/Project/UnitTest/UnitTest/ThermomalModule/app.cpp > CMakeFiles/main.dir/app.cpp.i

CMakeFiles/main.dir/app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/app.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/group36/Project/UnitTest/UnitTest/ThermomalModule/app.cpp -o CMakeFiles/main.dir/app.cpp.s

CMakeFiles/main.dir/threadPool.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/threadPool.cpp.o: ../threadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/group36/Project/UnitTest/UnitTest/ThermomalModule/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/threadPool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/threadPool.cpp.o -c /home/group36/Project/UnitTest/UnitTest/ThermomalModule/threadPool.cpp

CMakeFiles/main.dir/threadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/threadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/group36/Project/UnitTest/UnitTest/ThermomalModule/threadPool.cpp > CMakeFiles/main.dir/threadPool.cpp.i

CMakeFiles/main.dir/threadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/threadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/group36/Project/UnitTest/UnitTest/ThermomalModule/threadPool.cpp -o CMakeFiles/main.dir/threadPool.cpp.s

CMakeFiles/main.dir/pwmctrl.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/pwmctrl.cpp.o: ../pwmctrl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/group36/Project/UnitTest/UnitTest/ThermomalModule/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/pwmctrl.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/pwmctrl.cpp.o -c /home/group36/Project/UnitTest/UnitTest/ThermomalModule/pwmctrl.cpp

CMakeFiles/main.dir/pwmctrl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/pwmctrl.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/group36/Project/UnitTest/UnitTest/ThermomalModule/pwmctrl.cpp > CMakeFiles/main.dir/pwmctrl.cpp.i

CMakeFiles/main.dir/pwmctrl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/pwmctrl.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/group36/Project/UnitTest/UnitTest/ThermomalModule/pwmctrl.cpp -o CMakeFiles/main.dir/pwmctrl.cpp.s

CMakeFiles/main.dir/heater.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/heater.cpp.o: ../heater.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/group36/Project/UnitTest/UnitTest/ThermomalModule/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/heater.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/heater.cpp.o -c /home/group36/Project/UnitTest/UnitTest/ThermomalModule/heater.cpp

CMakeFiles/main.dir/heater.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/heater.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/group36/Project/UnitTest/UnitTest/ThermomalModule/heater.cpp > CMakeFiles/main.dir/heater.cpp.i

CMakeFiles/main.dir/heater.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/heater.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/group36/Project/UnitTest/UnitTest/ThermomalModule/heater.cpp -o CMakeFiles/main.dir/heater.cpp.s

CMakeFiles/main.dir/myds18b20.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/myds18b20.cpp.o: ../myds18b20.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/group36/Project/UnitTest/UnitTest/ThermomalModule/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/myds18b20.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/myds18b20.cpp.o -c /home/group36/Project/UnitTest/UnitTest/ThermomalModule/myds18b20.cpp

CMakeFiles/main.dir/myds18b20.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/myds18b20.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/group36/Project/UnitTest/UnitTest/ThermomalModule/myds18b20.cpp > CMakeFiles/main.dir/myds18b20.cpp.i

CMakeFiles/main.dir/myds18b20.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/myds18b20.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/group36/Project/UnitTest/UnitTest/ThermomalModule/myds18b20.cpp -o CMakeFiles/main.dir/myds18b20.cpp.s

CMakeFiles/main.dir/thermalModule.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/thermalModule.cpp.o: ../thermalModule.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/group36/Project/UnitTest/UnitTest/ThermomalModule/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/thermalModule.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/thermalModule.cpp.o -c /home/group36/Project/UnitTest/UnitTest/ThermomalModule/thermalModule.cpp

CMakeFiles/main.dir/thermalModule.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/thermalModule.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/group36/Project/UnitTest/UnitTest/ThermomalModule/thermalModule.cpp > CMakeFiles/main.dir/thermalModule.cpp.i

CMakeFiles/main.dir/thermalModule.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/thermalModule.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/group36/Project/UnitTest/UnitTest/ThermomalModule/thermalModule.cpp -o CMakeFiles/main.dir/thermalModule.cpp.s

CMakeFiles/main.dir/Test_thermalModule.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/Test_thermalModule.cpp.o: ../Test_thermalModule.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/group36/Project/UnitTest/UnitTest/ThermomalModule/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/main.dir/Test_thermalModule.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/main.dir/Test_thermalModule.cpp.o -c /home/group36/Project/UnitTest/UnitTest/ThermomalModule/Test_thermalModule.cpp

CMakeFiles/main.dir/Test_thermalModule.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/Test_thermalModule.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/group36/Project/UnitTest/UnitTest/ThermomalModule/Test_thermalModule.cpp > CMakeFiles/main.dir/Test_thermalModule.cpp.i

CMakeFiles/main.dir/Test_thermalModule.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/Test_thermalModule.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/group36/Project/UnitTest/UnitTest/ThermomalModule/Test_thermalModule.cpp -o CMakeFiles/main.dir/Test_thermalModule.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/app.cpp.o" \
"CMakeFiles/main.dir/threadPool.cpp.o" \
"CMakeFiles/main.dir/pwmctrl.cpp.o" \
"CMakeFiles/main.dir/heater.cpp.o" \
"CMakeFiles/main.dir/myds18b20.cpp.o" \
"CMakeFiles/main.dir/thermalModule.cpp.o" \
"CMakeFiles/main.dir/Test_thermalModule.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/app.cpp.o
main: CMakeFiles/main.dir/threadPool.cpp.o
main: CMakeFiles/main.dir/pwmctrl.cpp.o
main: CMakeFiles/main.dir/heater.cpp.o
main: CMakeFiles/main.dir/myds18b20.cpp.o
main: CMakeFiles/main.dir/thermalModule.cpp.o
main: CMakeFiles/main.dir/Test_thermalModule.cpp.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/group36/Project/UnitTest/UnitTest/ThermomalModule/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/group36/Project/UnitTest/UnitTest/ThermomalModule/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/group36/Project/UnitTest/UnitTest/ThermomalModule /home/group36/Project/UnitTest/UnitTest/ThermomalModule /home/group36/Project/UnitTest/UnitTest/ThermomalModule/build /home/group36/Project/UnitTest/UnitTest/ThermomalModule/build /home/group36/Project/UnitTest/UnitTest/ThermomalModule/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

