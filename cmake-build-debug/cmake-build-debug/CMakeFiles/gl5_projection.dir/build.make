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
include CMakeFiles/gl5_projection.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gl5_projection.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gl5_projection.dir/flags.make

CMakeFiles/gl5_projection.dir/src/gl5_projection/gl5_projection.cpp.obj: CMakeFiles/gl5_projection.dir/flags.make
CMakeFiles/gl5_projection.dir/src/gl5_projection/gl5_projection.cpp.obj: CMakeFiles/gl5_projection.dir/includes_CXX.rsp
CMakeFiles/gl5_projection.dir/src/gl5_projection/gl5_projection.cpp.obj: ../src/gl5_projection/gl5_projection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gl5_projection.dir/src/gl5_projection/gl5_projection.cpp.obj"
	D:\MinGw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gl5_projection.dir\src\gl5_projection\gl5_projection.cpp.obj -c "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\src\gl5_projection\gl5_projection.cpp"

CMakeFiles/gl5_projection.dir/src/gl5_projection/gl5_projection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gl5_projection.dir/src/gl5_projection/gl5_projection.cpp.i"
	D:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\src\gl5_projection\gl5_projection.cpp" > CMakeFiles\gl5_projection.dir\src\gl5_projection\gl5_projection.cpp.i

CMakeFiles/gl5_projection.dir/src/gl5_projection/gl5_projection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gl5_projection.dir/src/gl5_projection/gl5_projection.cpp.s"
	D:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\src\gl5_projection\gl5_projection.cpp" -o CMakeFiles\gl5_projection.dir\src\gl5_projection\gl5_projection.cpp.s

# Object files for target gl5_projection
gl5_projection_OBJECTS = \
"CMakeFiles/gl5_projection.dir/src/gl5_projection/gl5_projection.cpp.obj"

# External object files for target gl5_projection
gl5_projection_EXTERNAL_OBJECTS =

gl5_projection.exe: CMakeFiles/gl5_projection.dir/src/gl5_projection/gl5_projection.cpp.obj
gl5_projection.exe: CMakeFiles/gl5_projection.dir/build.make
gl5_projection.exe: libppgso.a
gl5_projection.exe: libshaders.a
gl5_projection.exe: ../dependencies/lib/mingw/libglfw3.a
gl5_projection.exe: ../dependencies/lib/mingw/libglew32.a
gl5_projection.exe: CMakeFiles/gl5_projection.dir/linklibs.rsp
gl5_projection.exe: CMakeFiles/gl5_projection.dir/objects1.rsp
gl5_projection.exe: CMakeFiles/gl5_projection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gl5_projection.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gl5_projection.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gl5_projection.dir/build: gl5_projection.exe

.PHONY : CMakeFiles/gl5_projection.dir/build

CMakeFiles/gl5_projection.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\gl5_projection.dir\cmake_clean.cmake
.PHONY : CMakeFiles/gl5_projection.dir/clean

CMakeFiles/gl5_projection.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug\CMakeFiles\gl5_projection.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/gl5_projection.dir/depend

