*This project has been created as part of the 42 curriculum by achigvin, asergina.*

___

## Description

**Minishell** is a simplified reimplementation of a Unix shell,inspired by **bash**.
The goal of this project is to deeply understand how shells work internally, including:

....* process creation and management
....* file descriptors and redirections
....* environment variables
....* signal handling
....* parsing and command execution

This project recreates a minimal interactive shell that can interpret and execute user commands while respecting Unix behavior as closely as possible.



### Core functionality

....* Interactive prompt using `readline`
....* Command history
....* Execution of binaries via:
......* absolute paths (`/bin/ls`)
......* relative paths (`./a.out`)
......* $PATH resolution



#### Pipes

....* Supports chaining commands with `|`

Example:

	ls -l | grep .c | wc -l



#### Redirections

**Operator**			**Description**

`<`						input redirection

`>`						output redirection

`>>`					append output

`<<`					heredoc

Example:

	cat < input.txt > output.txt



#### Environment variables

....* `$VAR` → expansion
....* `$?` → last exit status



#### Quotes
....* `'single quotes'` → no expansion
....* `"double quotes"` → allows `$` expansion



#### Builtins

....* `echo` (with `-n`)
....* `cd`
....* `pwd`
....* `export`
....* `unset`
....* `env`
....* `exit`



#### Signals

**Key**					**Behavior**

`Ctrl+C`				new prompt

`Ctrl+D`				exit shell

`Ctrl+\`				ignored



### Architecture

Minishell is divided into several logical components:

#### 1. Lexer (Tokenizer)

Splits input into tokens:

....* commands
....* arguments
....* operators (`|`, `<`, `>` etc.)
....* quote logic
....* environment variables

#### 2. Parser

Builds a structured representation of commands:

....* command nodes
....* redirections
....* pipelines

#### 3. Executor

Responsible for:

....* `fork()`
....* `execve()`
....* `pipe()`
....* `dup2()`

#### 4. Builtins

Executed without `execve()` when required (e.g. `cd`, `pwd`)

#### 5. Signal handling

....* Uses `sigaction`
....* Only one global variable allowed (stores signal number)



## Instructions

#### Compile

make

#### Run

./minishell



### Project Structure

minishell/
│
├── include/
├── libft/
│
├── src/
│	├── lexer/
│	├── parser/
│	├──  runner/
│	│	└── builtins/
│	├── main.c
│	└── minishell.c
│
├── Makefile
└── README.md



## Resources

