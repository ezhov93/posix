# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = C:\Qt\Tools\CMake_64\bin\cmake.exe

# The command to remove a file.
RM = C:\Qt\Tools\CMake_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build

# Include any dependencies generated for this target.
include src/CMakeFiles/Posix.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/Posix.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Posix.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Posix.dir/flags.make

src/CMakeFiles/Posix.dir/utils.c.obj: src/CMakeFiles/Posix.dir/flags.make
src/CMakeFiles/Posix.dir/utils.c.obj: src/CMakeFiles/Posix.dir/includes_C.rsp
src/CMakeFiles/Posix.dir/utils.c.obj: ../src/utils.c
src/CMakeFiles/Posix.dir/utils.c.obj: src/CMakeFiles/Posix.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/Posix.dir/utils.c.obj"
	cd /d D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build\src && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/CMakeFiles/Posix.dir/utils.c.obj -MF CMakeFiles\Posix.dir\utils.c.obj.d -o CMakeFiles\Posix.dir\utils.c.obj -c D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\src\utils.c

src/CMakeFiles/Posix.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Posix.dir/utils.c.i"
	cd /d D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build\src && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\src\utils.c > CMakeFiles\Posix.dir\utils.c.i

src/CMakeFiles/Posix.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Posix.dir/utils.c.s"
	cd /d D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build\src && C:\Qt\Tools\mingw1120_64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\src\utils.c -o CMakeFiles\Posix.dir\utils.c.s

# Object files for target Posix
Posix_OBJECTS = \
"CMakeFiles/Posix.dir/utils.c.obj"

# External object files for target Posix
Posix_EXTERNAL_OBJECTS =

src/libPosix.a: src/CMakeFiles/Posix.dir/utils.c.obj
src/libPosix.a: src/CMakeFiles/Posix.dir/build.make
src/libPosix.a: src/CMakeFiles/Posix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libPosix.a"
	cd /d D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build\src && $(CMAKE_COMMAND) -P CMakeFiles\Posix.dir\cmake_clean_target.cmake
	cd /d D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Posix.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Posix.dir/build: src/libPosix.a
.PHONY : src/CMakeFiles/Posix.dir/build

src/CMakeFiles/Posix.dir/clean:
	cd /d D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build\src && $(CMAKE_COMMAND) -P CMakeFiles\Posix.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/Posix.dir/clean

src/CMakeFiles/Posix.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\src D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build\src D:\Submicron\asnpu\firmware\correlator\bootloader111\lib\posix\build\src\CMakeFiles\Posix.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/Posix.dir/depend
