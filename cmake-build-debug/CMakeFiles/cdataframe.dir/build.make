# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.3.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.3.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cdataframe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cdataframe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cdataframe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cdataframe.dir/flags.make

CMakeFiles/cdataframe.dir/main.c.obj: CMakeFiles/cdataframe.dir/flags.make
CMakeFiles/cdataframe.dir/main.c.obj: C:/Users/gabri/OneDrive/Documents/GitHub/cdataframe/main.c
CMakeFiles/cdataframe.dir/main.c.obj: CMakeFiles/cdataframe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cdataframe.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cdataframe.dir/main.c.obj -MF CMakeFiles\cdataframe.dir\main.c.obj.d -o CMakeFiles\cdataframe.dir\main.c.obj -c C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\main.c

CMakeFiles/cdataframe.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/cdataframe.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\main.c > CMakeFiles\cdataframe.dir\main.c.i

CMakeFiles/cdataframe.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/cdataframe.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\main.c -o CMakeFiles\cdataframe.dir\main.c.s

CMakeFiles/cdataframe.dir/column.c.obj: CMakeFiles/cdataframe.dir/flags.make
CMakeFiles/cdataframe.dir/column.c.obj: C:/Users/gabri/OneDrive/Documents/GitHub/cdataframe/column.c
CMakeFiles/cdataframe.dir/column.c.obj: CMakeFiles/cdataframe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/cdataframe.dir/column.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cdataframe.dir/column.c.obj -MF CMakeFiles\cdataframe.dir\column.c.obj.d -o CMakeFiles\cdataframe.dir\column.c.obj -c C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\column.c

CMakeFiles/cdataframe.dir/column.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/cdataframe.dir/column.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\column.c > CMakeFiles\cdataframe.dir\column.c.i

CMakeFiles/cdataframe.dir/column.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/cdataframe.dir/column.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\column.c -o CMakeFiles\cdataframe.dir\column.c.s

CMakeFiles/cdataframe.dir/cdataframe.c.obj: CMakeFiles/cdataframe.dir/flags.make
CMakeFiles/cdataframe.dir/cdataframe.c.obj: C:/Users/gabri/OneDrive/Documents/GitHub/cdataframe/cdataframe.c
CMakeFiles/cdataframe.dir/cdataframe.c.obj: CMakeFiles/cdataframe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/cdataframe.dir/cdataframe.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cdataframe.dir/cdataframe.c.obj -MF CMakeFiles\cdataframe.dir\cdataframe.c.obj.d -o CMakeFiles\cdataframe.dir\cdataframe.c.obj -c C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\cdataframe.c

CMakeFiles/cdataframe.dir/cdataframe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/cdataframe.dir/cdataframe.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\cdataframe.c > CMakeFiles\cdataframe.dir\cdataframe.c.i

CMakeFiles/cdataframe.dir/cdataframe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/cdataframe.dir/cdataframe.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\cdataframe.c -o CMakeFiles\cdataframe.dir\cdataframe.c.s

# Object files for target cdataframe
cdataframe_OBJECTS = \
"CMakeFiles/cdataframe.dir/main.c.obj" \
"CMakeFiles/cdataframe.dir/column.c.obj" \
"CMakeFiles/cdataframe.dir/cdataframe.c.obj"

# External object files for target cdataframe
cdataframe_EXTERNAL_OBJECTS =

cdataframe.exe: CMakeFiles/cdataframe.dir/main.c.obj
cdataframe.exe: CMakeFiles/cdataframe.dir/column.c.obj
cdataframe.exe: CMakeFiles/cdataframe.dir/cdataframe.c.obj
cdataframe.exe: CMakeFiles/cdataframe.dir/build.make
cdataframe.exe: CMakeFiles/cdataframe.dir/linkLibs.rsp
cdataframe.exe: CMakeFiles/cdataframe.dir/objects1.rsp
cdataframe.exe: CMakeFiles/cdataframe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable cdataframe.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cdataframe.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cdataframe.dir/build: cdataframe.exe
.PHONY : CMakeFiles/cdataframe.dir/build

CMakeFiles/cdataframe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cdataframe.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cdataframe.dir/clean

CMakeFiles/cdataframe.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\cmake-build-debug C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\cmake-build-debug C:\Users\gabri\OneDrive\Documents\GitHub\cdataframe\cmake-build-debug\CMakeFiles\cdataframe.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cdataframe.dir/depend

