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
CMAKE_COMMAND = /usr/local/Cellar/cmake/2.8.12.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/2.8.12.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/Cellar/cmake/2.8.12.2/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out

# Include any dependencies generated for this target.
include CMakeFiles/OpenGLFramework.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGLFramework.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGLFramework.dir/flags.make

CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o: CMakeFiles/OpenGLFramework.dir/flags.make
CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o: ../application/solar_system.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o -c /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/application/solar_system.cpp

CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/application/solar_system.cpp > CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.i

CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/application/solar_system.cpp -o CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.s

CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o.requires:
.PHONY : CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o.requires

CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o.provides: CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenGLFramework.dir/build.make CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o.provides.build
.PHONY : CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o.provides

CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o.provides.build: CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o

CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o: CMakeFiles/OpenGLFramework.dir/flags.make
CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o: ../framework/source/model.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o -c /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/model.cpp

CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/model.cpp > CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.i

CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/model.cpp -o CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.s

CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o.requires:
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o.requires

CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o.provides: CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenGLFramework.dir/build.make CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o.provides.build
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o.provides

CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o.provides.build: CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o

CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o: CMakeFiles/OpenGLFramework.dir/flags.make
CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o: ../framework/source/model_loader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o -c /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/model_loader.cpp

CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/model_loader.cpp > CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.i

CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/model_loader.cpp -o CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.s

CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o.requires:
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o.requires

CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o.provides: CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenGLFramework.dir/build.make CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o.provides.build
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o.provides

CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o.provides.build: CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o

CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o: CMakeFiles/OpenGLFramework.dir/flags.make
CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o: ../framework/source/orb.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o -c /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/orb.cpp

CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/orb.cpp > CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.i

CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/orb.cpp -o CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.s

CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o.requires:
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o.requires

CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o.provides: CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenGLFramework.dir/build.make CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o.provides.build
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o.provides

CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o.provides.build: CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o

CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o: CMakeFiles/OpenGLFramework.dir/flags.make
CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o: ../framework/source/planet.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o -c /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/planet.cpp

CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/planet.cpp > CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.i

CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/planet.cpp -o CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.s

CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o.requires:
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o.requires

CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o.provides: CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenGLFramework.dir/build.make CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o.provides.build
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o.provides

CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o.provides.build: CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o

CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o: CMakeFiles/OpenGLFramework.dir/flags.make
CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o: ../framework/source/shader_loader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o -c /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/shader_loader.cpp

CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/shader_loader.cpp > CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.i

CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/shader_loader.cpp -o CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.s

CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o.requires:
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o.requires

CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o.provides: CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenGLFramework.dir/build.make CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o.provides.build
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o.provides

CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o.provides.build: CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o

CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o: CMakeFiles/OpenGLFramework.dir/flags.make
CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o: ../framework/source/sun.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o -c /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/sun.cpp

CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/sun.cpp > CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.i

CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/sun.cpp -o CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.s

CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o.requires:
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o.requires

CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o.provides: CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenGLFramework.dir/build.make CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o.provides.build
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o.provides

CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o.provides.build: CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o

CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o: CMakeFiles/OpenGLFramework.dir/flags.make
CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o: ../framework/source/texture_loader.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o -c /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/texture_loader.cpp

CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/texture_loader.cpp > CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.i

CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/texture_loader.cpp -o CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.s

CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o.requires:
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o.requires

CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o.provides: CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenGLFramework.dir/build.make CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o.provides.build
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o.provides

CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o.provides.build: CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o

CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o: CMakeFiles/OpenGLFramework.dir/flags.make
CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o: ../framework/source/utils.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o -c /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/utils.cpp

CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/utils.cpp > CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.i

CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/framework/source/utils.cpp -o CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.s

CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o.requires:
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o.requires

CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o.provides: CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenGLFramework.dir/build.make CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o.provides.build
.PHONY : CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o.provides

CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o.provides.build: CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o

CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o: CMakeFiles/OpenGLFramework.dir/flags.make
CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o: ../external/tinyobjloader-aa07206/tiny_obj_loader.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o -c /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/tinyobjloader-aa07206/tiny_obj_loader.cc

CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/tinyobjloader-aa07206/tiny_obj_loader.cc > CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.i

CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/external/tinyobjloader-aa07206/tiny_obj_loader.cc -o CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.s

CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o.requires:
.PHONY : CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o.requires

CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o.provides: CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o.requires
	$(MAKE) -f CMakeFiles/OpenGLFramework.dir/build.make CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o.provides.build
.PHONY : CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o.provides

CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o.provides.build: CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o

# Object files for target OpenGLFramework
OpenGLFramework_OBJECTS = \
"CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o" \
"CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o" \
"CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o" \
"CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o" \
"CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o" \
"CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o" \
"CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o" \
"CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o" \
"CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o" \
"CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o"

# External object files for target OpenGLFramework
OpenGLFramework_EXTERNAL_OBJECTS =

Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o
Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o
Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o
Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o
Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o
Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o
Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o
Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o
Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o
Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o
Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/build.make
Debug/OpenGLFramework: Debug/libglfw.3.1.dylib
Debug/OpenGLFramework: libglbindingd.dylib
Debug/OpenGLFramework: CMakeFiles/OpenGLFramework.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Debug/OpenGLFramework"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenGLFramework.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGLFramework.dir/build: Debug/OpenGLFramework
.PHONY : CMakeFiles/OpenGLFramework.dir/build

CMakeFiles/OpenGLFramework.dir/requires: CMakeFiles/OpenGLFramework.dir/application/solar_system.cpp.o.requires
CMakeFiles/OpenGLFramework.dir/requires: CMakeFiles/OpenGLFramework.dir/framework/source/model.cpp.o.requires
CMakeFiles/OpenGLFramework.dir/requires: CMakeFiles/OpenGLFramework.dir/framework/source/model_loader.cpp.o.requires
CMakeFiles/OpenGLFramework.dir/requires: CMakeFiles/OpenGLFramework.dir/framework/source/orb.cpp.o.requires
CMakeFiles/OpenGLFramework.dir/requires: CMakeFiles/OpenGLFramework.dir/framework/source/planet.cpp.o.requires
CMakeFiles/OpenGLFramework.dir/requires: CMakeFiles/OpenGLFramework.dir/framework/source/shader_loader.cpp.o.requires
CMakeFiles/OpenGLFramework.dir/requires: CMakeFiles/OpenGLFramework.dir/framework/source/sun.cpp.o.requires
CMakeFiles/OpenGLFramework.dir/requires: CMakeFiles/OpenGLFramework.dir/framework/source/texture_loader.cpp.o.requires
CMakeFiles/OpenGLFramework.dir/requires: CMakeFiles/OpenGLFramework.dir/framework/source/utils.cpp.o.requires
CMakeFiles/OpenGLFramework.dir/requires: CMakeFiles/OpenGLFramework.dir/external/tinyobjloader-aa07206/tiny_obj_loader.cc.o.requires
.PHONY : CMakeFiles/OpenGLFramework.dir/requires

CMakeFiles/OpenGLFramework.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenGLFramework.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenGLFramework.dir/clean

CMakeFiles/OpenGLFramework.dir/depend:
	cd /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out /Users/jonas/Documents/code/uni/computer_graphics/OpenGLFramework/cmake_out/CMakeFiles/OpenGLFramework.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenGLFramework.dir/depend

