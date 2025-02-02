

# Pipex

Pipex is a project that recreates the behavior of shell pipelines. It simulates how the UNIX `|` operator works by using low-level system calls like `pipe()`, `fork()`, `dup2()`, and `execve()`.

This project is part of the 42 curriculum and focuses on process management, inter-process communication, and file descriptor manipulation.

---

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [Notes](#notes)
---

## Description

Pipex reads from an input file, executes a sequence of commands where the output of one command is used as input for the next (simulating a pipeline), and writes the final output to an output file.

This project helps in understanding:
- **Process creation** using `fork()`
- **Inter-process communication** using `pipe()`
- **File redirection** using `dup2()`
- **Executing commands** using `execve()`
- **Handling errors** properly in system calls

---

## Features

### ✅ **Mandatory**
- Simulates `cmd1 | cmd2` behavior.
- Reads from an **input file** and writes the result to an **output file**.
- Uses **only** system calls: `pipe()`, `fork()`, `dup2()`, `execve()`, `waitpid()`, etc.
- **Handles errors** properly (invalid files, missing commands, etc.).

### ⭐ **Bonus**
- **Supports multiple commands** (like `cmd1 | cmd2 | cmd3 | ... | cmdN`).
- **Heredoc (`<<`)** implementation for interactive input instead of reading from a file.
- **Error messages printed to `stderr`** for better debugging.
- **Handles edge cases** (permissions, invalid commands, empty files).

---

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/pipex.git
   cd pipex
   ```
### Compile the project:

#### Mandatory version:

```
make
```
#### Bonus version:
```
make bonus
```
#### Clean compiled files:

    make clean    # Removes object files
    make fclean   # Removes object files and binary


## Features

### ✅ **Mandatory**
- Simulates `cmd1 | cmd2` behavior.
- Reads from an **input file** and writes the result to an **output file**.
- Uses **only** system calls: `pipe()`, `fork()`, `dup2()`, `execve()`, `waitpid()`, etc.
- **Handles errors** properly (invalid files, missing commands, etc.).

### ⭐ **Bonus**
- **Supports multiple commands** (like `cmd1 | cmd2 | cmd3 | ... | cmdN`).
- **Heredoc (`<<`)** implementation for interactive input instead of reading from a file.
- **Error messages printed to `stderr`** for better debugging.
- **Handles edge cases** (permissions, invalid commands, empty files).

---

## Examples
### Basic Example (Mandatory)
```
./pipex input.txt "grep error" "wc -l" output.txt
```
- **Reads from input.txt**
- **Filters lines containing "error" using grep**
- **Counts the lines using wc -l**
- **Writes output to output.txt**

### Multiple Commands (Bonus)
```
./pipex input.txt "cat" "grep error" "sort" "uniq" "wc -l" output.txt
```
   Reads input file, filters lines, sorts, removes duplicates, and counts lines.

### Heredoc (Bonus)
```
./pipex here_doc END "cat" "grep error" "wc -l" output.txt
```
   Waits for user input until END is typed.

## Project Structure
```
pipex/
├── src/
│   ├── pipex.c        # Main logic for mandatory part
│   ├── utils.c        # Utility functions (string manipulation, error handling)
│   ├── execute.c      # Executes commands using execve()
│   ├── pipe_management.c  # Handles pipes and processes
│   ├── here_doc.c     # (Bonus) Implements heredoc functionality
│   ├── multiple_pipes.c  # (Bonus) Handles multiple commands
├── includes/
│   └── pipex.h        # Header file with function prototypes and macros
├── Makefile           # Compilation rules
└── README.md
```

### How It Works

1.  The program reads input from `infile`.
2.  It creates a pipe and forks a child process.
3.  The child executes `command1`, writing its output to the pipe.
4.  The parent reads from the pipe and executes `command2`, writing the result to `outfile`.

## Notes

-   **Error Handling:** Always check return values of system calls (`fork()`, `pipe()`, `dup2()`, `execve()`, etc.).
-   **Memory Management:** Free dynamically allocated memory and close file descriptors when done.
-   **Testing:** Test thoroughly with different input scenarios.
-   **Coding Standards:** Follow 42 school coding norms (if applicable).

