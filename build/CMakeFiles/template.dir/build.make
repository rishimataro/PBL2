# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = C:\cmake-3.31.0-rc3-windows-x86_64\bin\cmake.exe

# The command to remove a file.
RM = C:\cmake-3.31.0-rc3-windows-x86_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\03_PBL2\PBL2\PBL2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\03_PBL2\PBL2\PBL2\build

# Include any dependencies generated for this target.
include CMakeFiles/template.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/template.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/template.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/template.dir/flags.make

CMakeFiles/template.dir/codegen:
.PHONY : CMakeFiles/template.dir/codegen

CMakeFiles/template.dir/src/Template/LinkedList.cpp.obj: CMakeFiles/template.dir/flags.make
CMakeFiles/template.dir/src/Template/LinkedList.cpp.obj: CMakeFiles/template.dir/includes_CXX.rsp
CMakeFiles/template.dir/src/Template/LinkedList.cpp.obj: F:/03_PBL2/PBL2/PBL2/src/Template/LinkedList.cpp
CMakeFiles/template.dir/src/Template/LinkedList.cpp.obj: CMakeFiles/template.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\03_PBL2\PBL2\PBL2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/template.dir/src/Template/LinkedList.cpp.obj"
	C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/template.dir/src/Template/LinkedList.cpp.obj -MF CMakeFiles\template.dir\src\Template\LinkedList.cpp.obj.d -o CMakeFiles\template.dir\src\Template\LinkedList.cpp.obj -c F:\03_PBL2\PBL2\PBL2\src\Template\LinkedList.cpp

CMakeFiles/template.dir/src/Template/LinkedList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/template.dir/src/Template/LinkedList.cpp.i"
	C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\03_PBL2\PBL2\PBL2\src\Template\LinkedList.cpp > CMakeFiles\template.dir\src\Template\LinkedList.cpp.i

CMakeFiles/template.dir/src/Template/LinkedList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/template.dir/src/Template/LinkedList.cpp.s"
	C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\03_PBL2\PBL2\PBL2\src\Template\LinkedList.cpp -o CMakeFiles\template.dir\src\Template\LinkedList.cpp.s

# Object files for target template
template_OBJECTS = \
"CMakeFiles/template.dir/src/Template/LinkedList.cpp.obj"

# External object files for target template
template_EXTERNAL_OBJECTS =

libtemplate.a: CMakeFiles/template.dir/src/Template/LinkedList.cpp.obj
libtemplate.a: CMakeFiles/template.dir/build.make
libtemplate.a: CMakeFiles/template.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=F:\03_PBL2\PBL2\PBL2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtemplate.a"
	$(CMAKE_COMMAND) -P CMakeFiles\template.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\template.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/template.dir/build: libtemplate.a
.PHONY : CMakeFiles/template.dir/build

CMakeFiles/template.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\template.dir\cmake_clean.cmake
.PHONY : CMakeFiles/template.dir/clean

CMakeFiles/template.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\03_PBL2\PBL2\PBL2 F:\03_PBL2\PBL2\PBL2 F:\03_PBL2\PBL2\PBL2\build F:\03_PBL2\PBL2\PBL2\build F:\03_PBL2\PBL2\PBL2\build\CMakeFiles\template.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/template.dir/depend

