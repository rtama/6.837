# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build"

# Include any dependencies generated for this target.
include CMakeFiles/a2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/a2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a2.dir/flags.make

CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o: ../3rd_party/lodepng/lodepng.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o -c "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/3rd_party/lodepng/lodepng.cpp"

CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/3rd_party/lodepng/lodepng.cpp" > CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.i

CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/3rd_party/lodepng/lodepng.cpp" -o CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.s

CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o.requires:

.PHONY : CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o.requires

CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o.provides: CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o.requires
	$(MAKE) -f CMakeFiles/a2.dir/build.make CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o.provides.build
.PHONY : CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o.provides

CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o.provides.build: CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o


CMakeFiles/a2.dir/src/main.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/a2.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/src/main.cpp.o -c "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/main.cpp"

CMakeFiles/a2.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/main.cpp" > CMakeFiles/a2.dir/src/main.cpp.i

CMakeFiles/a2.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/main.cpp" -o CMakeFiles/a2.dir/src/main.cpp.s

CMakeFiles/a2.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/a2.dir/src/main.cpp.o.requires

CMakeFiles/a2.dir/src/main.cpp.o.provides: CMakeFiles/a2.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/a2.dir/build.make CMakeFiles/a2.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/a2.dir/src/main.cpp.o.provides

CMakeFiles/a2.dir/src/main.cpp.o.provides.build: CMakeFiles/a2.dir/src/main.cpp.o


CMakeFiles/a2.dir/src/starter2_util.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/src/starter2_util.cpp.o: ../src/starter2_util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/a2.dir/src/starter2_util.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/src/starter2_util.cpp.o -c "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/starter2_util.cpp"

CMakeFiles/a2.dir/src/starter2_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/src/starter2_util.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/starter2_util.cpp" > CMakeFiles/a2.dir/src/starter2_util.cpp.i

CMakeFiles/a2.dir/src/starter2_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/src/starter2_util.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/starter2_util.cpp" -o CMakeFiles/a2.dir/src/starter2_util.cpp.s

CMakeFiles/a2.dir/src/starter2_util.cpp.o.requires:

.PHONY : CMakeFiles/a2.dir/src/starter2_util.cpp.o.requires

CMakeFiles/a2.dir/src/starter2_util.cpp.o.provides: CMakeFiles/a2.dir/src/starter2_util.cpp.o.requires
	$(MAKE) -f CMakeFiles/a2.dir/build.make CMakeFiles/a2.dir/src/starter2_util.cpp.o.provides.build
.PHONY : CMakeFiles/a2.dir/src/starter2_util.cpp.o.provides

CMakeFiles/a2.dir/src/starter2_util.cpp.o.provides.build: CMakeFiles/a2.dir/src/starter2_util.cpp.o


CMakeFiles/a2.dir/src/camera.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/src/camera.cpp.o: ../src/camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/a2.dir/src/camera.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/src/camera.cpp.o -c "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/camera.cpp"

CMakeFiles/a2.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/src/camera.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/camera.cpp" > CMakeFiles/a2.dir/src/camera.cpp.i

CMakeFiles/a2.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/src/camera.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/camera.cpp" -o CMakeFiles/a2.dir/src/camera.cpp.s

CMakeFiles/a2.dir/src/camera.cpp.o.requires:

.PHONY : CMakeFiles/a2.dir/src/camera.cpp.o.requires

CMakeFiles/a2.dir/src/camera.cpp.o.provides: CMakeFiles/a2.dir/src/camera.cpp.o.requires
	$(MAKE) -f CMakeFiles/a2.dir/build.make CMakeFiles/a2.dir/src/camera.cpp.o.provides.build
.PHONY : CMakeFiles/a2.dir/src/camera.cpp.o.provides

CMakeFiles/a2.dir/src/camera.cpp.o.provides.build: CMakeFiles/a2.dir/src/camera.cpp.o


CMakeFiles/a2.dir/src/vertexrecorder.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/src/vertexrecorder.cpp.o: ../src/vertexrecorder.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/a2.dir/src/vertexrecorder.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/src/vertexrecorder.cpp.o -c "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/vertexrecorder.cpp"

CMakeFiles/a2.dir/src/vertexrecorder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/src/vertexrecorder.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/vertexrecorder.cpp" > CMakeFiles/a2.dir/src/vertexrecorder.cpp.i

CMakeFiles/a2.dir/src/vertexrecorder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/src/vertexrecorder.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/vertexrecorder.cpp" -o CMakeFiles/a2.dir/src/vertexrecorder.cpp.s

CMakeFiles/a2.dir/src/vertexrecorder.cpp.o.requires:

.PHONY : CMakeFiles/a2.dir/src/vertexrecorder.cpp.o.requires

CMakeFiles/a2.dir/src/vertexrecorder.cpp.o.provides: CMakeFiles/a2.dir/src/vertexrecorder.cpp.o.requires
	$(MAKE) -f CMakeFiles/a2.dir/build.make CMakeFiles/a2.dir/src/vertexrecorder.cpp.o.provides.build
.PHONY : CMakeFiles/a2.dir/src/vertexrecorder.cpp.o.provides

CMakeFiles/a2.dir/src/vertexrecorder.cpp.o.provides.build: CMakeFiles/a2.dir/src/vertexrecorder.cpp.o


CMakeFiles/a2.dir/src/matrixstack.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/src/matrixstack.cpp.o: ../src/matrixstack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/a2.dir/src/matrixstack.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/src/matrixstack.cpp.o -c "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/matrixstack.cpp"

CMakeFiles/a2.dir/src/matrixstack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/src/matrixstack.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/matrixstack.cpp" > CMakeFiles/a2.dir/src/matrixstack.cpp.i

CMakeFiles/a2.dir/src/matrixstack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/src/matrixstack.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/matrixstack.cpp" -o CMakeFiles/a2.dir/src/matrixstack.cpp.s

CMakeFiles/a2.dir/src/matrixstack.cpp.o.requires:

.PHONY : CMakeFiles/a2.dir/src/matrixstack.cpp.o.requires

CMakeFiles/a2.dir/src/matrixstack.cpp.o.provides: CMakeFiles/a2.dir/src/matrixstack.cpp.o.requires
	$(MAKE) -f CMakeFiles/a2.dir/build.make CMakeFiles/a2.dir/src/matrixstack.cpp.o.provides.build
.PHONY : CMakeFiles/a2.dir/src/matrixstack.cpp.o.provides

CMakeFiles/a2.dir/src/matrixstack.cpp.o.provides.build: CMakeFiles/a2.dir/src/matrixstack.cpp.o


CMakeFiles/a2.dir/src/joint.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/src/joint.cpp.o: ../src/joint.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/a2.dir/src/joint.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/src/joint.cpp.o -c "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/joint.cpp"

CMakeFiles/a2.dir/src/joint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/src/joint.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/joint.cpp" > CMakeFiles/a2.dir/src/joint.cpp.i

CMakeFiles/a2.dir/src/joint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/src/joint.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/joint.cpp" -o CMakeFiles/a2.dir/src/joint.cpp.s

CMakeFiles/a2.dir/src/joint.cpp.o.requires:

.PHONY : CMakeFiles/a2.dir/src/joint.cpp.o.requires

CMakeFiles/a2.dir/src/joint.cpp.o.provides: CMakeFiles/a2.dir/src/joint.cpp.o.requires
	$(MAKE) -f CMakeFiles/a2.dir/build.make CMakeFiles/a2.dir/src/joint.cpp.o.provides.build
.PHONY : CMakeFiles/a2.dir/src/joint.cpp.o.provides

CMakeFiles/a2.dir/src/joint.cpp.o.provides.build: CMakeFiles/a2.dir/src/joint.cpp.o


CMakeFiles/a2.dir/src/mesh.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/src/mesh.cpp.o: ../src/mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/a2.dir/src/mesh.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/src/mesh.cpp.o -c "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/mesh.cpp"

CMakeFiles/a2.dir/src/mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/src/mesh.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/mesh.cpp" > CMakeFiles/a2.dir/src/mesh.cpp.i

CMakeFiles/a2.dir/src/mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/src/mesh.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/mesh.cpp" -o CMakeFiles/a2.dir/src/mesh.cpp.s

CMakeFiles/a2.dir/src/mesh.cpp.o.requires:

.PHONY : CMakeFiles/a2.dir/src/mesh.cpp.o.requires

CMakeFiles/a2.dir/src/mesh.cpp.o.provides: CMakeFiles/a2.dir/src/mesh.cpp.o.requires
	$(MAKE) -f CMakeFiles/a2.dir/build.make CMakeFiles/a2.dir/src/mesh.cpp.o.provides.build
.PHONY : CMakeFiles/a2.dir/src/mesh.cpp.o.provides

CMakeFiles/a2.dir/src/mesh.cpp.o.provides.build: CMakeFiles/a2.dir/src/mesh.cpp.o


CMakeFiles/a2.dir/src/skeletalmodel.cpp.o: CMakeFiles/a2.dir/flags.make
CMakeFiles/a2.dir/src/skeletalmodel.cpp.o: ../src/skeletalmodel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/a2.dir/src/skeletalmodel.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a2.dir/src/skeletalmodel.cpp.o -c "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/skeletalmodel.cpp"

CMakeFiles/a2.dir/src/skeletalmodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a2.dir/src/skeletalmodel.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/skeletalmodel.cpp" > CMakeFiles/a2.dir/src/skeletalmodel.cpp.i

CMakeFiles/a2.dir/src/skeletalmodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a2.dir/src/skeletalmodel.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/src/skeletalmodel.cpp" -o CMakeFiles/a2.dir/src/skeletalmodel.cpp.s

CMakeFiles/a2.dir/src/skeletalmodel.cpp.o.requires:

.PHONY : CMakeFiles/a2.dir/src/skeletalmodel.cpp.o.requires

CMakeFiles/a2.dir/src/skeletalmodel.cpp.o.provides: CMakeFiles/a2.dir/src/skeletalmodel.cpp.o.requires
	$(MAKE) -f CMakeFiles/a2.dir/build.make CMakeFiles/a2.dir/src/skeletalmodel.cpp.o.provides.build
.PHONY : CMakeFiles/a2.dir/src/skeletalmodel.cpp.o.provides

CMakeFiles/a2.dir/src/skeletalmodel.cpp.o.provides.build: CMakeFiles/a2.dir/src/skeletalmodel.cpp.o


# Object files for target a2
a2_OBJECTS = \
"CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o" \
"CMakeFiles/a2.dir/src/main.cpp.o" \
"CMakeFiles/a2.dir/src/starter2_util.cpp.o" \
"CMakeFiles/a2.dir/src/camera.cpp.o" \
"CMakeFiles/a2.dir/src/vertexrecorder.cpp.o" \
"CMakeFiles/a2.dir/src/matrixstack.cpp.o" \
"CMakeFiles/a2.dir/src/joint.cpp.o" \
"CMakeFiles/a2.dir/src/mesh.cpp.o" \
"CMakeFiles/a2.dir/src/skeletalmodel.cpp.o"

# External object files for target a2
a2_EXTERNAL_OBJECTS =

a2: CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o
a2: CMakeFiles/a2.dir/src/main.cpp.o
a2: CMakeFiles/a2.dir/src/starter2_util.cpp.o
a2: CMakeFiles/a2.dir/src/camera.cpp.o
a2: CMakeFiles/a2.dir/src/vertexrecorder.cpp.o
a2: CMakeFiles/a2.dir/src/matrixstack.cpp.o
a2: CMakeFiles/a2.dir/src/joint.cpp.o
a2: CMakeFiles/a2.dir/src/mesh.cpp.o
a2: CMakeFiles/a2.dir/src/skeletalmodel.cpp.o
a2: CMakeFiles/a2.dir/build.make
a2: 3rd_party/glfw/src/libglfw3.a
a2: 3rd_party/nanogui/libnanogui.a
a2: vecmath/libvecmath.a
a2: 3rd_party/glfw/src/libglfw3.a
a2: CMakeFiles/a2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable a2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a2.dir/build: a2

.PHONY : CMakeFiles/a2.dir/build

CMakeFiles/a2.dir/requires: CMakeFiles/a2.dir/3rd_party/lodepng/lodepng.cpp.o.requires
CMakeFiles/a2.dir/requires: CMakeFiles/a2.dir/src/main.cpp.o.requires
CMakeFiles/a2.dir/requires: CMakeFiles/a2.dir/src/starter2_util.cpp.o.requires
CMakeFiles/a2.dir/requires: CMakeFiles/a2.dir/src/camera.cpp.o.requires
CMakeFiles/a2.dir/requires: CMakeFiles/a2.dir/src/vertexrecorder.cpp.o.requires
CMakeFiles/a2.dir/requires: CMakeFiles/a2.dir/src/matrixstack.cpp.o.requires
CMakeFiles/a2.dir/requires: CMakeFiles/a2.dir/src/joint.cpp.o.requires
CMakeFiles/a2.dir/requires: CMakeFiles/a2.dir/src/mesh.cpp.o.requires
CMakeFiles/a2.dir/requires: CMakeFiles/a2.dir/src/skeletalmodel.cpp.o.requires

.PHONY : CMakeFiles/a2.dir/requires

CMakeFiles/a2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a2.dir/clean

CMakeFiles/a2.dir/depend:
	cd "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2" "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2" "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build" "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build" "/Users/reecetamashiro/Dropbox (MIT)/Classes/fall 2016/6.837/pset2/starter2/build/CMakeFiles/a2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/a2.dir/depend

