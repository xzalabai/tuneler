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
include CMakeFiles/task2_convolution.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/task2_convolution.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task2_convolution.dir/flags.make

CMakeFiles/task2_convolution.dir/src/task2_convolution/task2_convolution.cpp.obj: CMakeFiles/task2_convolution.dir/flags.make
CMakeFiles/task2_convolution.dir/src/task2_convolution/task2_convolution.cpp.obj: CMakeFiles/task2_convolution.dir/includes_CXX.rsp
CMakeFiles/task2_convolution.dir/src/task2_convolution/task2_convolution.cpp.obj: ../src/task2_convolution/task2_convolution.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/task2_convolution.dir/src/task2_convolution/task2_convolution.cpp.obj"
	D:\MinGw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\task2_convolution.dir\src\task2_convolution\task2_convolution.cpp.obj -c "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\src\task2_convolution\task2_convolution.cpp"

CMakeFiles/task2_convolution.dir/src/task2_convolution/task2_convolution.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task2_convolution.dir/src/task2_convolution/task2_convolution.cpp.i"
	D:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\src\task2_convolution\task2_convolution.cpp" > CMakeFiles\task2_convolution.dir\src\task2_convolution\task2_convolution.cpp.i

CMakeFiles/task2_convolution.dir/src/task2_convolution/task2_convolution.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task2_convolution.dir/src/task2_convolution/task2_convolution.cpp.s"
	D:\MinGw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\src\task2_convolution\task2_convolution.cpp" -o CMakeFiles\task2_convolution.dir\src\task2_convolution\task2_convolution.cpp.s

# Object files for target task2_convolution
task2_convolution_OBJECTS = \
"CMakeFiles/task2_convolution.dir/src/task2_convolution/task2_convolution.cpp.obj"

# External object files for target task2_convolution
task2_convolution_EXTERNAL_OBJECTS =

task2_convolution.exe: CMakeFiles/task2_convolution.dir/src/task2_convolution/task2_convolution.cpp.obj
task2_convolution.exe: CMakeFiles/task2_convolution.dir/build.make
task2_convolution.exe: libppgso.a
task2_convolution.exe: ../dependencies/lib/mingw/libglfw3.a
task2_convolution.exe: ../dependencies/lib/mingw/libglew32.a
task2_convolution.exe: CMakeFiles/task2_convolution.dir/linklibs.rsp
task2_convolution.exe: CMakeFiles/task2_convolution.dir/objects1.rsp
task2_convolution.exe: CMakeFiles/task2_convolution.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable task2_convolution.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\task2_convolution.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task2_convolution.dir/build: task2_convolution.exe

.PHONY : CMakeFiles/task2_convolution.dir/build

CMakeFiles/task2_convolution.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\task2_convolution.dir\cmake_clean.cmake
.PHONY : CMakeFiles/task2_convolution.dir/clean

CMakeFiles/task2_convolution.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug" "D:\fiit\5 sem\Grafika\1 cviko hra test\ppgso-public\cmake-build-debug\CMakeFiles\task2_convolution.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/task2_convolution.dir/depend
