# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = "D:\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2018.2.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/raw2_raycast.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/raw2_raycast.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/raw2_raycast.dir/flags.make

CMakeFiles/raw2_raycast.dir/src/raw2_raycast/raw2_raycast.cpp.obj: CMakeFiles/raw2_raycast.dir/flags.make
CMakeFiles/raw2_raycast.dir/src/raw2_raycast/raw2_raycast.cpp.obj: CMakeFiles/raw2_raycast.dir/includes_CXX.rsp
CMakeFiles/raw2_raycast.dir/src/raw2_raycast/raw2_raycast.cpp.obj: ../src/raw2_raycast/raw2_raycast.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/raw2_raycast.dir/src/raw2_raycast/raw2_raycast.cpp.obj"
	D:\MinGw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\raw2_raycast.dir\src\raw2_raycast\raw2_raycast.cpp.obj -c "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\src\raw2_raycast\raw2_raycast.cpp"

CMakeFiles/raw2_raycast.dir/src/raw2_raycast/raw2_raycast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raw2_raycast.dir/src/raw2_raycast/raw2_raycast.cpp.i"
	D:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\src\raw2_raycast\raw2_raycast.cpp" > CMakeFiles\raw2_raycast.dir\src\raw2_raycast\raw2_raycast.cpp.i

CMakeFiles/raw2_raycast.dir/src/raw2_raycast/raw2_raycast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raw2_raycast.dir/src/raw2_raycast/raw2_raycast.cpp.s"
	D:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\src\raw2_raycast\raw2_raycast.cpp" -o CMakeFiles\raw2_raycast.dir\src\raw2_raycast\raw2_raycast.cpp.s

# Object files for target raw2_raycast
raw2_raycast_OBJECTS = \
"CMakeFiles/raw2_raycast.dir/src/raw2_raycast/raw2_raycast.cpp.obj"

# External object files for target raw2_raycast
raw2_raycast_EXTERNAL_OBJECTS =

raw2_raycast.exe: CMakeFiles/raw2_raycast.dir/src/raw2_raycast/raw2_raycast.cpp.obj
raw2_raycast.exe: CMakeFiles/raw2_raycast.dir/build.make
raw2_raycast.exe: libppgso.a
raw2_raycast.exe: ../dependencies/lib/mingw/libglfw3.a
raw2_raycast.exe: ../dependencies/lib/mingw/libglew32.a
raw2_raycast.exe: CMakeFiles/raw2_raycast.dir/linklibs.rsp
raw2_raycast.exe: CMakeFiles/raw2_raycast.dir/objects1.rsp
raw2_raycast.exe: CMakeFiles/raw2_raycast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable raw2_raycast.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\raw2_raycast.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/raw2_raycast.dir/build: raw2_raycast.exe

.PHONY : CMakeFiles/raw2_raycast.dir/build

CMakeFiles/raw2_raycast.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\raw2_raycast.dir\cmake_clean.cmake
.PHONY : CMakeFiles/raw2_raycast.dir/clean

CMakeFiles/raw2_raycast.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug\CMakeFiles\raw2_raycast.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/raw2_raycast.dir/depend

