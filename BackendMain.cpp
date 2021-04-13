#include "Backend.hpp"

int main(int argc, const char *argv[])
{
    --argc;

    if (argc == 0 || argc > 2) {
        printf("usage: backend <abstract syntax tree input file name> <translation output file name>\n");
        return EXIT_SUCCESS;
    }

    const char *abstractSyntaxTreeDumpInputFileName = argv[1];
    const char *translationOutputFileName = argv[2];

    Backend backend;
    try {
        backend.translate(abstractSyntaxTreeDumpInputFileName, translationOutputFileName);

        return EXIT_SUCCESS;
    } catch (const std::exception &exception) {
        std::fprintf(stderr, "%s\n", exception.what());

        backend.BackendDtor();

        return EXIT_FAILURE;
    } catch (...) {
        std::fprintf(stderr, "Program failure: unhandled exception\n");

        backend.BackendDtor();

        return EXIT_FAILURE;
    }
}
