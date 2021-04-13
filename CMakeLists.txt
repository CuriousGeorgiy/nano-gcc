cmake_minimum_required(VERSION 3.17)
project(nano-gcc)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
add_compile_options("/std:c++latest")

add_executable(frontend FrontendMain.cpp Frontend.cpp ProgramLanguage.cpp ProgramLanguageAnalyser.cpp AbstractSyntaxTree.cpp
        ProgramLanguageLexer.cpp SyntaxError.cpp File.cpp Canary.cpp)
target_include_directories(frontend PUBLIC "$PROJECT_DIR$")

add_executable(backend BackendMain.cpp Backend.cpp AbstractSyntaxTreeDumpLanguage.cpp AbstractSyntaxTreeDumpLanguageAnalyser.cpp
        AbstractSyntaxTree.cpp AbstractSyntaxTreeDumpLanguageLexer.cpp SyntaxError.cpp File.cpp Canary.cpp)
target_include_directories(backend PUBLIC "$PROJECT_DIR$")

add_executable(reversed_frontend ReversedFrontendMain.cpp ReversedFrontend.cpp AbstractSyntaxTreeDumpLanguage.cpp
        AbstractSyntaxTreeDumpLanguageAnalyser.cpp AbstractSyntaxTree.cpp AbstractSyntaxTreeDumpLanguageLexer.cpp
        SyntaxError.cpp File.cpp Canary.cpp)
target_include_directories(reversed_frontend PUBLIC "$PROJECT_DIR$")

add_executable(middleend MiddleendMain.cpp Middleend.cpp AbstractSyntaxTreeDumpLanguage.cpp
        AbstractSyntaxTreeDumpLanguageAnalyser.cpp AbstractSyntaxTree.cpp AbstractSyntaxTreeDumpLanguageLexer.cpp
        SyntaxError.cpp File.cpp Canary.cpp)
target_include_directories(middleend PUBLIC "$PROJECT_DIR$")
