# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\User\Desktop\Netrom Code Golf\FruitNinja"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\User\Desktop\Netrom Code Golf\FruitNinja\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/FruitNinja.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FruitNinja.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FruitNinja.dir/flags.make

CMakeFiles/FruitNinja.dir/CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.obj: CMakeFiles/FruitNinja.dir/flags.make
CMakeFiles/FruitNinja.dir/CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.obj: ../CodeGolf\ 2021\ -\ Fruit\ Ninja\ -\ Sursa\ Cadru.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\User\Desktop\Netrom Code Golf\FruitNinja\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FruitNinja.dir/CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FruitNinja.dir\CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.obj -c "C:\Users\User\Desktop\Netrom Code Golf\FruitNinja\CodeGolf 2021 - Fruit Ninja - Sursa Cadru.cpp"

CMakeFiles/FruitNinja.dir/CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FruitNinja.dir/CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\User\Desktop\Netrom Code Golf\FruitNinja\CodeGolf 2021 - Fruit Ninja - Sursa Cadru.cpp" > CMakeFiles\FruitNinja.dir\CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.i

CMakeFiles/FruitNinja.dir/CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FruitNinja.dir/CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\User\Desktop\Netrom Code Golf\FruitNinja\CodeGolf 2021 - Fruit Ninja - Sursa Cadru.cpp" -o CMakeFiles\FruitNinja.dir\CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.s

# Object files for target FruitNinja
FruitNinja_OBJECTS = \
"CMakeFiles/FruitNinja.dir/CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.obj"

# External object files for target FruitNinja
FruitNinja_EXTERNAL_OBJECTS =

FruitNinja.exe: CMakeFiles/FruitNinja.dir/CodeGolf_2021_-_Fruit_Ninja_-_Sursa_Cadru.cpp.obj
FruitNinja.exe: CMakeFiles/FruitNinja.dir/build.make
FruitNinja.exe: CMakeFiles/FruitNinja.dir/linklibs.rsp
FruitNinja.exe: CMakeFiles/FruitNinja.dir/objects1.rsp
FruitNinja.exe: CMakeFiles/FruitNinja.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\User\Desktop\Netrom Code Golf\FruitNinja\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable FruitNinja.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\FruitNinja.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FruitNinja.dir/build: FruitNinja.exe

.PHONY : CMakeFiles/FruitNinja.dir/build

CMakeFiles/FruitNinja.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\FruitNinja.dir\cmake_clean.cmake
.PHONY : CMakeFiles/FruitNinja.dir/clean

CMakeFiles/FruitNinja.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\User\Desktop\Netrom Code Golf\FruitNinja" "C:\Users\User\Desktop\Netrom Code Golf\FruitNinja" "C:\Users\User\Desktop\Netrom Code Golf\FruitNinja\cmake-build-debug" "C:\Users\User\Desktop\Netrom Code Golf\FruitNinja\cmake-build-debug" "C:\Users\User\Desktop\Netrom Code Golf\FruitNinja\cmake-build-debug\CMakeFiles\FruitNinja.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/FruitNinja.dir/depend

