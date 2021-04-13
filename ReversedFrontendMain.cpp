#include "ReversedFrontend.hpp"

int main(int argc, const char *argv[])
{
    --argc;

    if (argc == 0 || argc > 2) {
        printf("usage: reversed_frontend <abstract syntax tree input file name> <translation output file name>\n");
        return EXIT_SUCCESS;
    }

    const char *abstractSyntaxTreeDumpInputFileName = argv[1];
    const char *translationOutputFileName = argv[2];

    ReversedFrontend reversedFrontend;
    try {
        reversedFrontend.translate(abstractSyntaxTreeDumpInputFileName, translationOutputFileName);

        return EXIT_SUCCESS;
    } catch (const std::exception &exception) {
        std::fprintf(stderr, "%s\n", exception.what());

        reversedFrontend.ReversedFrontendDtor();

        return EXIT_FAILURE;
    } catch (...) {
        std::fprintf(stderr, "Program failure: unhandled exception\n");

        reversedFrontend.ReversedFrontendDtor();

        return EXIT_FAILURE;
    }
}


