#include "Frontend.hpp"

#include <exception>

int main(int argc, const char *argv[])
{
    --argc;

    if (argc == 0 || argc > 2) {
        printf("usage: backend <program language input file name> <abstract syntax tree dump output file name>\n");
        return EXIT_SUCCESS;
    }

    const char *programLanguageInputFileName = argv[1];
    const char *abstractSyntaxTreeDumpOutputFileName = argv[2];

    Frontend frontend;
    try {
        frontend.translate(programLanguageInputFileName, abstractSyntaxTreeDumpOutputFileName);

        return EXIT_SUCCESS;
    } catch (const std::exception &exception) {
        std::fprintf(stderr, "%s\n", exception.what());

        frontend.FrontendDtor();

        return EXIT_FAILURE;
    } catch (...) {
        std::fprintf(stderr, "Program failure: unhandled exception\n");

        frontend.FrontendDtor();

        return EXIT_FAILURE;
    }
}

