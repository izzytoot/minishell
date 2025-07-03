# 🐚 MINISHELL 

## ℹ️ About the project
This project was done in partnership with [**Daniela Padilha**](https://github.com/Daniela-Padilha).

It's a polished, mini‑version of a Unix shell written in pure C. This isn’t just an exercise - it’s about building a real, working Command-Line Interface interpreter that plays nicely with pipes, redirections, heredocs, expansions, signals, and error handling.

## 💪 What It Does
1. Reads user input (with readline support for line editing and history);
2. Validates syntax (no unclosed quotes, misplaced operators, etc.);
3. Tokenizes the input and attributed different categories: pipes, redirections, commands (builtins or environment), arguments;
4. Builds an AST (Binary Tree) reflecting pipes, redirections, and commands;
5. Executes it, handling builtins, environment lookup, subprocesses;

The program manages heredocs, multi‑stage redirections, pipes, signals, and exit statuses.

⚠️ We took each piece step by step, ending with a code that works and handles everything gracefully.

## 🧠 Implementation Phases
Here's how it all comes together:

#### <ins>a. Syntax Check</ins>
- It scans the raw input for basic syntax sanity;
- It detects unclosed quotes, misplaced pipes/redirections, usage of unsuppported operators (&& and ||);
- It refuses to parse broken commands early, printing errors like bash would;

#### <ins>b. Tokenization & Sub‑tokenization</ins>
- It keeps track of quoting modes to prevent unintended word-splitting;
- It splits input into tokens: words, pipes, redirections;
- It further splits word tokens into filenames, type of command (builtin or environment) or arguments;
- It checks for repeated command words and empty quote situations;

#### <ins>c. Binary Tree (AST) Building</ins>
- It parses the token stream into a binary tree:
- Pipes (|) create left and right branches;
- Redirections link to command nodes and filename nodes;
- Command nodes will be the last node of the tree.
- This structure reflects evaluation order and establishes an execution flow.

🌳 **BINARY TREE EXAMPLE** 

<ins>Input line:</ins> cat file.txt | grep hello > out.txt

              PIPE
              "|"
             /    \
         CMD       REDIR_OUT
        "cat"         ">"
         ARG         /   \
       file.txt    CMD   FILENAME
                 "grep"  "out.txt"
                  ARG
                "hello"

Executes left branch first (cat file.txt) and writes into pipe, and right branch after (grep hello > out.txt), reading from pipe.

#### <ins>d. Tree Execution</ins>
Traverses and executes the AST:

##### d.1 Expansions

- It handles "$VAR", "$?", "$0" and "$EMPTY" expansions;
- It performs word-splitting or joining after expansions unless inside single quotes;
- It replaces the node-argument array;

##### d.2 Heredoc Execution

- It detects how many heredocs are there in the input line;
- It performs the existant heredocs by:
  - detecting the EOF,
  - creating a temporary file,
  - opening a heredoc buffer in a child process,
  - expanding variables inside heredoc if EOF not quoted.

##### d.3 Pipe Execution

- It chains tree nodes through pipes;
- It uses fork(), pipe(), and dup2() to connect child processes;

##### d.4 Redirections Execution

- It applies <, >, and >> to redirect stdin/stdout;
- It opens files with correct flags and uses dup2() to hook them;
- It handles FD opening, duplicating and closing;
- It performs the command linked to the redirect token te correct stdin/stdout;

##### d.5 Command Execution

-  Builtin Commands
  - cd, echo, pwd, export, unset, env, exit;
  - Executed in parent process;
  - It outputs errors and updates exit status without forking.

- Environment Commands
  - Launch external executables using execve()
  - Executed in child process, it searches PATH, handles ENOENT and prints meaningful error messages like bash.

#### <ins>e. Transversal Mechanics</ins>
These mechanics touch every part of the shell:

<ins>Signal Handling</ins>

- SIGINT (Ctrl+C): interrupts input or current command, then resets prompt;
- SIGQUIT (Ctrl+\): ignored, same behavior as bash;
- Interactive handling during heredoc, builtins, execution phases.

<ins>Exit Code Handling</ins>

- Every command sets the correct exit code;
- Exit codes can be checked by expanding $?;
- Child processes inherit parent’s signal-derived or exec-derived exit status;

## 🔥 Build, run and test

```
git clone <https://github.com/izzytoot/minishell.git>
cd minishell
make
./minishell
```

Feel free to test our Minishell. Here is our own list of tests which we compiled troughout this loooooong journey. Have fun!

## 😱 **[OUR LIST OF 282 TESTS](https://www.notion.so/meeru/1d02544e44e2807d9013fd3eefbfebf4?v=1d02544e44e28087a970000c7fb78979)** 😱
