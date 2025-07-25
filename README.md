# F15

[![Stars](https://img.shields.io/github/stars/farhaanaliii/f15?style=for-the-badge\&logo=github\&color=FFD700)](https://github.com/farhaanaliii/f15/stargazers)
[![Forks](https://img.shields.io/github/forks/farhaanaliii/f15?style=for-the-badge\&logo=github\&color=FF69B4)](https://github.com/farhaanaliii/f15/network/members)
[![Issues](https://img.shields.io/github/issues/farhaanaliii/f15?style=for-the-badge\&logo=github\&color=00BFFF)](https://github.com/farhaanaliii/f15/issues)
[![Last Commit](https://img.shields.io/github/last-commit/farhaanaliii/f15?style=for-the-badge\&logo=git\&color=32CD32)](https://github.com/farhaanaliii/f15/commits/main)
[![Author](https://img.shields.io/badge/author-Farhan%20Ali-blueviolet?style=for-the-badge\&logo=github)](https://github.com/farhaanaliii)

</div>

F15 is a simple programming language that I built in early 2024. The development of this language started by following a tutorial on creating a basic interpreter. Even though I’m not a C programmer by trade, I learned and built this language from scratch by watching the tutorial. After diving into Python, I got sidetracked with other projects, but as 2024 is coming to an end, I plan to return to this project and continue developing it.

**Tutorial:** [Watch the Tutorial](https://youtu.be/WABO4o_y8qc)  
*The tutorial is in multiple parts; you can find all the parts on the same channel.*

## Features

- **Lexer & Parser**: The language uses a lexer to tokenize the source code, followed by a parser to build an abstract syntax tree (AST).
- **Scope Management**: Supports variable and function definitions scoped locally.
- **Simple Syntax**: The language supports basic syntax for variables, functions, and expressions.

## Language Overview

F15 features basic constructs, including:

- **Variables**: Define variables with the `let` keyword.
- **Functions**: Define functions using the `function` keyword.
- **Statements**: Use semicolons (`;`) to separate statements.
- **Expressions**: Supports simple expressions and function calls.

## Language Syntax

```f15
let x = "Hello, World!";
function greet(name) {
    out("Hello " + name);
}
greet(x);
```

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/farhaanaliii/F15.git
    ```

2. Navigate to the project folder:

    ```bash
    cd F15
    ```

3. Build the project:

    ```bash
    make
    ```

4. Run the interpreter on a sample file (e.g., `hello.f15`):

    ```bash
    ./build/f15 hello.f15
    ```

## File Extension

The file extension for F15 programs is `.f15`. Save your source files with this extension to run them with the interpreter.

## Contributing

I’m currently working on improving this language, but contributions and suggestions are always welcome! Feel free to fork the project and submit pull requests.

## License

This project is open-source and available under the MIT License.
