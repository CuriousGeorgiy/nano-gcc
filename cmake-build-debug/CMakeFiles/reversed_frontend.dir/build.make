# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\79017\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\203.7148.70\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\79017\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\203.7148.70\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\reversed_frontend.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\reversed_frontend.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\reversed_frontend.dir\flags.make

CMakeFiles\reversed_frontend.dir\ReversedFrontendMain.cpp.obj: CMakeFiles\reversed_frontend.dir\flags.make
CMakeFiles\reversed_frontend.dir\ReversedFrontendMain.cpp.obj: ..\ReversedFrontendMain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/reversed_frontend.dir/ReversedFrontendMain.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\reversed_frontend.dir\ReversedFrontendMain.cpp.obj /FdCMakeFiles\reversed_frontend.dir\ /FS -c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\ReversedFrontendMain.cpp"
<<

CMakeFiles\reversed_frontend.dir\ReversedFrontendMain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reversed_frontend.dir/ReversedFrontendMain.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe > CMakeFiles\reversed_frontend.dir\ReversedFrontendMain.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\ReversedFrontendMain.cpp"
<<

CMakeFiles\reversed_frontend.dir\ReversedFrontendMain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reversed_frontend.dir/ReversedFrontendMain.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\reversed_frontend.dir\ReversedFrontendMain.cpp.s /c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\ReversedFrontendMain.cpp"
<<

CMakeFiles\reversed_frontend.dir\ReversedFrontend.cpp.obj: CMakeFiles\reversed_frontend.dir\flags.make
CMakeFiles\reversed_frontend.dir\ReversedFrontend.cpp.obj: ..\ReversedFrontend.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/reversed_frontend.dir/ReversedFrontend.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\reversed_frontend.dir\ReversedFrontend.cpp.obj /FdCMakeFiles\reversed_frontend.dir\ /FS -c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\ReversedFrontend.cpp"
<<

CMakeFiles\reversed_frontend.dir\ReversedFrontend.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reversed_frontend.dir/ReversedFrontend.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe > CMakeFiles\reversed_frontend.dir\ReversedFrontend.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\ReversedFrontend.cpp"
<<

CMakeFiles\reversed_frontend.dir\ReversedFrontend.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reversed_frontend.dir/ReversedFrontend.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\reversed_frontend.dir\ReversedFrontend.cpp.s /c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\ReversedFrontend.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguage.cpp.obj: CMakeFiles\reversed_frontend.dir\flags.make
CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguage.cpp.obj: ..\AbstractSyntaxTreeDumpLanguage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/reversed_frontend.dir/AbstractSyntaxTreeDumpLanguage.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguage.cpp.obj /FdCMakeFiles\reversed_frontend.dir\ /FS -c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTreeDumpLanguage.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reversed_frontend.dir/AbstractSyntaxTreeDumpLanguage.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe > CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguage.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTreeDumpLanguage.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reversed_frontend.dir/AbstractSyntaxTreeDumpLanguage.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguage.cpp.s /c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTreeDumpLanguage.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageAnalyser.cpp.obj: CMakeFiles\reversed_frontend.dir\flags.make
CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageAnalyser.cpp.obj: ..\AbstractSyntaxTreeDumpLanguageAnalyser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/reversed_frontend.dir/AbstractSyntaxTreeDumpLanguageAnalyser.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageAnalyser.cpp.obj /FdCMakeFiles\reversed_frontend.dir\ /FS -c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTreeDumpLanguageAnalyser.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageAnalyser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reversed_frontend.dir/AbstractSyntaxTreeDumpLanguageAnalyser.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe > CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageAnalyser.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTreeDumpLanguageAnalyser.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageAnalyser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reversed_frontend.dir/AbstractSyntaxTreeDumpLanguageAnalyser.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageAnalyser.cpp.s /c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTreeDumpLanguageAnalyser.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTree.cpp.obj: CMakeFiles\reversed_frontend.dir\flags.make
CMakeFiles\reversed_frontend.dir\AbstractSyntaxTree.cpp.obj: ..\AbstractSyntaxTree.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/reversed_frontend.dir/AbstractSyntaxTree.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\reversed_frontend.dir\AbstractSyntaxTree.cpp.obj /FdCMakeFiles\reversed_frontend.dir\ /FS -c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTree.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTree.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reversed_frontend.dir/AbstractSyntaxTree.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe > CMakeFiles\reversed_frontend.dir\AbstractSyntaxTree.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTree.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTree.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reversed_frontend.dir/AbstractSyntaxTree.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\reversed_frontend.dir\AbstractSyntaxTree.cpp.s /c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTree.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageLexer.cpp.obj: CMakeFiles\reversed_frontend.dir\flags.make
CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageLexer.cpp.obj: ..\AbstractSyntaxTreeDumpLanguageLexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/reversed_frontend.dir/AbstractSyntaxTreeDumpLanguageLexer.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageLexer.cpp.obj /FdCMakeFiles\reversed_frontend.dir\ /FS -c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTreeDumpLanguageLexer.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageLexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reversed_frontend.dir/AbstractSyntaxTreeDumpLanguageLexer.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe > CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageLexer.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTreeDumpLanguageLexer.cpp"
<<

CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageLexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reversed_frontend.dir/AbstractSyntaxTreeDumpLanguageLexer.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageLexer.cpp.s /c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\AbstractSyntaxTreeDumpLanguageLexer.cpp"
<<

CMakeFiles\reversed_frontend.dir\SyntaxError.cpp.obj: CMakeFiles\reversed_frontend.dir\flags.make
CMakeFiles\reversed_frontend.dir\SyntaxError.cpp.obj: ..\SyntaxError.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/reversed_frontend.dir/SyntaxError.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\reversed_frontend.dir\SyntaxError.cpp.obj /FdCMakeFiles\reversed_frontend.dir\ /FS -c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\SyntaxError.cpp"
<<

CMakeFiles\reversed_frontend.dir\SyntaxError.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reversed_frontend.dir/SyntaxError.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe > CMakeFiles\reversed_frontend.dir\SyntaxError.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\SyntaxError.cpp"
<<

CMakeFiles\reversed_frontend.dir\SyntaxError.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reversed_frontend.dir/SyntaxError.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\reversed_frontend.dir\SyntaxError.cpp.s /c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\SyntaxError.cpp"
<<

CMakeFiles\reversed_frontend.dir\File.cpp.obj: CMakeFiles\reversed_frontend.dir\flags.make
CMakeFiles\reversed_frontend.dir\File.cpp.obj: ..\File.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/reversed_frontend.dir/File.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\reversed_frontend.dir\File.cpp.obj /FdCMakeFiles\reversed_frontend.dir\ /FS -c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\File.cpp"
<<

CMakeFiles\reversed_frontend.dir\File.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reversed_frontend.dir/File.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe > CMakeFiles\reversed_frontend.dir\File.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\File.cpp"
<<

CMakeFiles\reversed_frontend.dir\File.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reversed_frontend.dir/File.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\reversed_frontend.dir\File.cpp.s /c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\File.cpp"
<<

CMakeFiles\reversed_frontend.dir\Canary.cpp.obj: CMakeFiles\reversed_frontend.dir\flags.make
CMakeFiles\reversed_frontend.dir\Canary.cpp.obj: ..\Canary.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/reversed_frontend.dir/Canary.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\reversed_frontend.dir\Canary.cpp.obj /FdCMakeFiles\reversed_frontend.dir\ /FS -c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\Canary.cpp"
<<

CMakeFiles\reversed_frontend.dir\Canary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reversed_frontend.dir/Canary.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe > CMakeFiles\reversed_frontend.dir\Canary.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\Canary.cpp"
<<

CMakeFiles\reversed_frontend.dir\Canary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reversed_frontend.dir/Canary.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\reversed_frontend.dir\Canary.cpp.s /c "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\Canary.cpp"
<<

# Object files for target reversed_frontend
reversed_frontend_OBJECTS = \
"CMakeFiles\reversed_frontend.dir\ReversedFrontendMain.cpp.obj" \
"CMakeFiles\reversed_frontend.dir\ReversedFrontend.cpp.obj" \
"CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguage.cpp.obj" \
"CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageAnalyser.cpp.obj" \
"CMakeFiles\reversed_frontend.dir\AbstractSyntaxTree.cpp.obj" \
"CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageLexer.cpp.obj" \
"CMakeFiles\reversed_frontend.dir\SyntaxError.cpp.obj" \
"CMakeFiles\reversed_frontend.dir\File.cpp.obj" \
"CMakeFiles\reversed_frontend.dir\Canary.cpp.obj"

# External object files for target reversed_frontend
reversed_frontend_EXTERNAL_OBJECTS =

reversed_frontend.exe: CMakeFiles\reversed_frontend.dir\ReversedFrontendMain.cpp.obj
reversed_frontend.exe: CMakeFiles\reversed_frontend.dir\ReversedFrontend.cpp.obj
reversed_frontend.exe: CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguage.cpp.obj
reversed_frontend.exe: CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageAnalyser.cpp.obj
reversed_frontend.exe: CMakeFiles\reversed_frontend.dir\AbstractSyntaxTree.cpp.obj
reversed_frontend.exe: CMakeFiles\reversed_frontend.dir\AbstractSyntaxTreeDumpLanguageLexer.cpp.obj
reversed_frontend.exe: CMakeFiles\reversed_frontend.dir\SyntaxError.cpp.obj
reversed_frontend.exe: CMakeFiles\reversed_frontend.dir\File.cpp.obj
reversed_frontend.exe: CMakeFiles\reversed_frontend.dir\Canary.cpp.obj
reversed_frontend.exe: CMakeFiles\reversed_frontend.dir\build.make
reversed_frontend.exe: CMakeFiles\reversed_frontend.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable reversed_frontend.exe"
	C:\Users\79017\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\203.7148.70\bin\cmake\win\bin\cmake.exe -E vs_link_exe --intdir=CMakeFiles\reversed_frontend.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1428~1.293\bin\Hostx64\x64\link.exe /nologo @CMakeFiles\reversed_frontend.dir\objects1.rsp @<<
 /out:reversed_frontend.exe /implib:reversed_frontend.lib /pdb:"C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\reversed_frontend.pdb" /version:0.0  /machine:x64 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\reversed_frontend.dir\build: reversed_frontend.exe

.PHONY : CMakeFiles\reversed_frontend.dir\build

CMakeFiles\reversed_frontend.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\reversed_frontend.dir\cmake_clean.cmake
.PHONY : CMakeFiles\reversed_frontend.dir\clean

CMakeFiles\reversed_frontend.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc" "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc" "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug" "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug" "C:\Users\79017\Documents\Work\MIPT\1 semester\Programming\nano-gcc\cmake-build-debug\CMakeFiles\reversed_frontend.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\reversed_frontend.dir\depend
