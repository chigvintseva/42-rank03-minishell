*This project has been created as part of the 42 curriculum by achigvin, asergina.*


## Description

**Minishell** is a simplified reimplementation of a Unix shell,inspired by **bash**.
The goal of this project is to deeply understand how shells work internally, including:

- process creation and management
- file descriptors and redirections
- environment variables
- signal handling
- parsing and command execution

This project recreates a minimal interactive shell that can interpret and execute user commands while respecting Unix behavior as closely as possible.

---

### Core functionality

- Interactive prompt using `readline`
- Command history
- Execution of binaries via:
  - absolute paths (`/bin/ls`)
  - relative paths (`./a.out`)
  - $PATH resolution

---

#### Pipes

- Supports chaining commands with `|`

Example:

	ls -l | grep .c | wc -l

---

#### Redirections

| **Operator** | **Description**    |
|--------------|--------------------|
| `<`          | `stdin` redirect   |
| `>`          | `stdout` overwrite |
| `>>`         | `stdout` append    |
| `<<`         | heredoc            |

Example:

	cat < input.txt > output.txt

---

#### Environment variables

- `$VAR` → expansion
- `$?` → last exit status

---

#### Quotes
- `'single quotes'` → no expansion
- `"double quotes"` → allows `$` expansion

---

#### Builtins

- `echo` (with `-n`)
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

---

#### Signals

| **Key**    | **Behavior**    |
|------------|-----------------|
| `Ctrl+C`   | new prompt      |
| `Ctrl+D`   | exit shell      |
| `Ctrl+\`   | ignored         |

---

### Architecture

Minishell is divided into several logical components:

#### 1. Lexer (Tokenizer)

Splits input into tokens:

- commands
- arguments
- operators (`|`, `<`, `>` etc.)
- quote logic
- environment variables

#### 2. Parser

Builds a structured representation of commands:

- command nodes
- redirections
- pipelines

#### 3. Executor

Responsible for:

- `fork()`
- `execve()`
- `pipe()`
- `dup2()`

#### 4. Builtins

Executed without `execve()` when required (e.g. `cd`, `pwd`)

#### 5. Signal handling

- Uses `sigaction`
- Only one global variable allowed (stores signal number)


## Instructions

#### Compile

make

#### Run

./minishell

---

### Project Structure

```text
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
```

## Resources

### External Materials

#### 1. Guides we consulted to understad the flow and solution approaches of the project:
- https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/

- https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions

- https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

- https://harm-smits.github.io/42docs/projects/minishell 

#### 2. Theoretical materials we went through to acquire the knowledge of the topics required within the project's development

- https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/

- https://github.com/adam-p/markdown-here/wiki/markdown-cheatsheet

- https://www.gnu.org/software/bash/manual/bash.html

- https://learngitbranching.js.org/

- https://docs.github.com/en/get-started/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax

### AI Usage Cases

#### 1. Beginning of the project: 
After gathering the knowledge from the existing guides and theoretical materials on Bash performance, we used AI chat bots to **summarize the knowledge and get the general summarization of the flow of the developemnt of the minishell and identify what we still lack**. It allowed us not to follow someone's guide exactly but to go from the particular to general which later resulted in our own implementation architecture.

#### 2. Development stage:
While writing the code, AI was mainly used for **quality assurance** of the written code parts in order to avoid multiple repetitive and tedious tasks, **identify and avoid common risks and biases** such as going too much into details and loosing the crucial logic parts due to some human-prone biases.

