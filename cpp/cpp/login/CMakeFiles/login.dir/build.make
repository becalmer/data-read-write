# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /data/home/liujinqiao/server/data_struct

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /data/home/liujinqiao/server/data_struct/cpp

# Include any dependencies generated for this target.
include cpp/login/CMakeFiles/login.dir/depend.make

# Include the progress variables for this target.
include cpp/login/CMakeFiles/login.dir/progress.make

# Include the compile flags for this target's objects.
include cpp/login/CMakeFiles/login.dir/flags.make

cpp/login/CMakeFiles/login.dir/login.cpp.o: cpp/login/CMakeFiles/login.dir/flags.make
cpp/login/CMakeFiles/login.dir/login.cpp.o: login/login.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /data/home/liujinqiao/server/data_struct/cpp/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object cpp/login/CMakeFiles/login.dir/login.cpp.o"
	cd /data/home/liujinqiao/server/data_struct/cpp/cpp/login && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/login.dir/login.cpp.o -c /data/home/liujinqiao/server/data_struct/cpp/login/login.cpp

cpp/login/CMakeFiles/login.dir/login.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/login.dir/login.cpp.i"
	cd /data/home/liujinqiao/server/data_struct/cpp/cpp/login && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /data/home/liujinqiao/server/data_struct/cpp/login/login.cpp > CMakeFiles/login.dir/login.cpp.i

cpp/login/CMakeFiles/login.dir/login.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/login.dir/login.cpp.s"
	cd /data/home/liujinqiao/server/data_struct/cpp/cpp/login && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /data/home/liujinqiao/server/data_struct/cpp/login/login.cpp -o CMakeFiles/login.dir/login.cpp.s

cpp/login/CMakeFiles/login.dir/login.cpp.o.requires:
.PHONY : cpp/login/CMakeFiles/login.dir/login.cpp.o.requires

cpp/login/CMakeFiles/login.dir/login.cpp.o.provides: cpp/login/CMakeFiles/login.dir/login.cpp.o.requires
	$(MAKE) -f cpp/login/CMakeFiles/login.dir/build.make cpp/login/CMakeFiles/login.dir/login.cpp.o.provides.build
.PHONY : cpp/login/CMakeFiles/login.dir/login.cpp.o.provides

cpp/login/CMakeFiles/login.dir/login.cpp.o.provides.build: cpp/login/CMakeFiles/login.dir/login.cpp.o

# Object files for target login
login_OBJECTS = \
"CMakeFiles/login.dir/login.cpp.o"

# External object files for target login
login_EXTERNAL_OBJECTS =

cpp/login/liblogin.a: cpp/login/CMakeFiles/login.dir/login.cpp.o
cpp/login/liblogin.a: cpp/login/CMakeFiles/login.dir/build.make
cpp/login/liblogin.a: cpp/login/CMakeFiles/login.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library liblogin.a"
	cd /data/home/liujinqiao/server/data_struct/cpp/cpp/login && $(CMAKE_COMMAND) -P CMakeFiles/login.dir/cmake_clean_target.cmake
	cd /data/home/liujinqiao/server/data_struct/cpp/cpp/login && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/login.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cpp/login/CMakeFiles/login.dir/build: cpp/login/liblogin.a
.PHONY : cpp/login/CMakeFiles/login.dir/build

cpp/login/CMakeFiles/login.dir/requires: cpp/login/CMakeFiles/login.dir/login.cpp.o.requires
.PHONY : cpp/login/CMakeFiles/login.dir/requires

cpp/login/CMakeFiles/login.dir/clean:
	cd /data/home/liujinqiao/server/data_struct/cpp/cpp/login && $(CMAKE_COMMAND) -P CMakeFiles/login.dir/cmake_clean.cmake
.PHONY : cpp/login/CMakeFiles/login.dir/clean

cpp/login/CMakeFiles/login.dir/depend:
	cd /data/home/liujinqiao/server/data_struct/cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /data/home/liujinqiao/server/data_struct /data/home/liujinqiao/server/data_struct/cpp/login /data/home/liujinqiao/server/data_struct/cpp /data/home/liujinqiao/server/data_struct/cpp/cpp/login /data/home/liujinqiao/server/data_struct/cpp/cpp/login/CMakeFiles/login.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cpp/login/CMakeFiles/login.dir/depend
