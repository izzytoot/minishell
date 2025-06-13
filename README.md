# 🐚 MINISHELL 

## 1. About the project
This project was done in partnership with [**Daniela Padilha**](https://github.com/Daniela-Padilha).

A polished, mini‑version of a Unix shell written in pure C. This isn’t just an exercise - it’s about building a real, working Command-Line Interface interpreter that plays nicely with pipes, redirections, heredocs, expansions, signals, and error handling.

## 2. What It Does
1. Reads user input (with readline support for line editing and history);
2. Validates syntax (no unclosed quotes, misplaced operators, etc.);
3. Tokenizes the input and attributed different categories: pipes, redirections, commands (builtins or environment), arguments;
4. Builds an AST (Binary Tree) reflecting pipes, redirections, and commands;
5. Executes it, handling builtins, environment lookup, subprocesses;

The program manages heredocs, multi‑stage redirections, pipes, signals, and exit statuses.

⚠ We take each piece step by step - a code that works and handles everything gracefully.

