# minishell

A small interactive Unix shell written in C as part of the 42 curriculum. The
project recreates the core behavior of a shell by implementing command parsing,
expansion, redirections, pipelines, built-in commands, process execution, and
signal handling without relying on an external shell parser.

## Features

- Interactive prompt powered by GNU Readline.
- Command execution through `PATH` lookup and absolute paths.
- Pipelines with `|`.
- Input and output redirections:
  - `<` standard input
  - `>` truncate and write output
  - `>>` append output
  - `<<` here-document input
- Single and double quote handling.
- Environment-variable expansion with `$VARIABLE`.
- Expansion of the last exit status through `$?`.
- Command history through Readline.
- Signal handling for interactive mode and here-documents.
- Environment management with a linked-list representation.
- Centralized allocation tracking through a custom garbage collector.

## Built-in Commands

The implementation includes the following built-ins:

| Command | Purpose |
| --- | --- |
| `echo` | Print arguments, including support for `-n` options |
| `cd` | Change the current working directory |
| `pwd` | Print the current working directory |
| `export` | Create or update environment variables |
| `unset` | Remove environment variables |
| `env` | Display the environment |
| `exit` | Exit the shell with an optional status |

Built-ins are executed inside the shell process when required so that changes
to the working directory and environment persist between commands.

## Requirements

- A C compiler such as GCC or Clang
- GNU Make
- GNU Readline development files
- A Unix-like operating system

On Debian or Ubuntu, install the Readline development package with:

```bash
sudo apt-get install build-essential libreadline-dev
```

The Makefile currently expects Readline under:

```text
$HOME/.local/include
$HOME/.local/lib
```

If Readline is installed in a different location, update `CFLAGS` and `LDFLAGS`
in the Makefile before building.

## Build

From the repository root:

```bash
make
```

This creates the `minishell` executable. The project is compiled with:

```text
cc -Wall -Wextra -Werror -g
```

Available Make targets:

```bash
make          # Build minishell and remove intermediate object files
make clean    # Remove object files
make fclean   # Remove object files and the executable
make re       # Clean and rebuild
```

## Run

Start the shell with:

```bash
./minishell
```

Example session:

```text
$ ./minishell
~/minishell$ echo "hello world"
hello world
~/minishell$ export NAME=minishell
~/minishell$ echo "$NAME"
minishell
~/minishell$ printf "one\ntwo\n" | grep two > result.txt
~/minishell$ cat < result.txt
 two
~/minishell$ exit
```

Use `Ctrl-D` to leave the shell on an empty prompt. Use `Ctrl-C` to interrupt
an interactive command or here-document input.

## Shell Syntax

The parser recognizes the main syntax elements expected from a basic shell:

```text
command argument                 # command and arguments
command | other_command          # pipeline
command < input.txt              # input redirection
command > output.txt             # truncate output
command >> output.txt            # append output
command << DELIMITER             # here-document
"quoted text" and 'literal text' # quote handling
$HOME and $?                     # variable and exit-status expansion
```

## Architecture

The command flow is organized into several stages:

1. Read a line with Readline and add it to history.
2. Tokenize words, quotes, pipes, and redirections.
3. Validate shell syntax.
4. Build command and redirection structures.
5. Expand environment variables and here-document content.
6. Open files and prepare pipe file descriptors.
7. Execute built-ins or external commands.
8. Wait for child processes and update the exit status.
9. Release tracked allocations and restore standard input state.

## Project Structure

```text
.
├── execution/
│   ├── built_in/          # Built-in command implementations
│   ├── exec_cmd/          # External command execution and PATH handling
│   ├── redir/             # Redirections and here-documents
│   ├── signal_handler/    # Interactive signal handling
│   └── utils/             # Execution helpers
├── garbage/               # Allocation tracking and cleanup
├── inc/
│   └── minishell.h        # Shared types and function declarations
├── src/
│   ├── cmd_builder/       # Command and redirection structures
│   ├── expansion/         # Environment and quote expansion
│   ├── parser/            # Syntax validation
│   ├── tokenizer/         # Input tokenization
│   └── utils/              # Environment, string, and file helpers
├── Makefile
├── README.md
├── TODO
└── todo.md
```

## Memory and Error Handling

The project uses a custom allocation registry to keep track of allocated
addresses and release them during shell cleanup. File descriptors, child
processes, redirections, and here-document resources are handled by dedicated
execution helpers.

For development, the Makefile also defines an AddressSanitizer configuration
variable that can be enabled when investigating memory errors:

```bash
make clean
make CFLAGS="-fsanitize=address -g3 -I$HOME/.local/include"
```

## Current Status

This repository is an active educational implementation. The `TODO` and
`todo.md` files contain edge cases and follow-up work discovered during manual
and sanitizer testing. Behavior may therefore differ from Bash in uncommon
cases, especially around malformed redirections, here-documents, environment
edge cases, and memory cleanup.

The implementation is intended for learning and experimentation, not as a
replacement for a production shell.
