# Nano GCC
This is a toy compiler toolchain, consisting of a front-end, back-end, assembler and disassembler.

Under the hood, a C-like language is parsed to a universal AST by the front-end, then translated to my [toy virtual machine](https://github.com/CuriousGeorgiy/nano-cpu) commands by the back-end, and finally translated to my toy virtual machine bytecode by the assembler. The bytecode can be disassembled using the corresponding tool.
