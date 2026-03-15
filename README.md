# 🐚 Minishell

> A minimal UNIX shell written in C — a 42 School project.

Minishell reproduces the core behaviour of **bash**, including command parsing, pipes, redirections, heredocs, variable expansion, signal handling, and a full set of built-in commands.

---

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Building](#building)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Supported Syntax](#supported-syntax)
- [Project Structure](#project-structure)

---

## Features

| Feature | Description |
|---|---|
| **Prompt** | Interactive prompt with command history (↑ / ↓) |
| **Command execution** | Runs external binaries found via `$PATH` |
| **Pipes** | `cmd1 \| cmd2 \| cmd3` — unlimited pipe chains |
| **Redirections** | `<`, `>`, `>>` input/output redirection |
| **Heredoc** | `<< DELIMITER` — reads until delimiter, expands variables |
| **Variable expansion** | `$VAR`, `$?` (last exit status) |
| **Quote handling** | Single quotes `'…'` (no expansion) and double quotes `"…"` (expansion) |
| **Signal handling** | `Ctrl-C` (new prompt), `Ctrl-D` (exit), `Ctrl-\` (ignored) |
| **Environment** | Full environment inherited and managed at runtime |
| **Garbage collector** | Custom memory manager to prevent leaks |

---

## Requirements

- **C compiler** — `cc` (clang or gcc)
- **GNU Readline** library

### Installing readline

**Linux (apt)**
```bash
sudo apt-get install libreadline-dev
```

**macOS (Homebrew)**
```bash
brew install readline
```

> The `Makefile` expects readline headers/libs under `$HOME/.local`. Adjust `CFLAGS` / `LDFLAGS` in the `Makefile` if your installation is elsewhere.

---

## Building

```bash
# Clone the repository
git clone https://github.com/ALIELYOUSS/minishell.git
cd minishell

# Build the binary
make
```

This produces the `minishell` executable in the project root.

| Target | Description |
|---|---|
| `make` / `make all` | Build the binary (compiles & cleans object files) |
| `make clean` | Remove object files |
| `make fclean` | Remove object files **and** the binary |
| `make re` | Full rebuild (`fclean` + `all`) |

---

## Usage

```bash
./minishell
```

You will be greeted with the interactive prompt:

```
~/minishell$ ✗🤯✗
```

Type any command just as you would in bash:

```bash
~/minishell$ ✗🤯✗ echo "Hello, World!"
Hello, World!

~/minishell$ ✗🤯✗ ls -la | grep .c | wc -l

~/minishell$ ✗🤯✗ cat << EOF
> line one
> line two
> EOF

~/minishell$ ✗🤯✗ export MY_VAR=42 && echo $MY_VAR
42
```

---

## Built-in Commands

These commands are implemented directly inside minishell (no child process spawned):

| Command | Description |
|---|---|
| `echo [-n] [args…]` | Print arguments to stdout; `-n` suppresses the trailing newline |
| `cd [path]` | Change the current working directory (`~` goes home, `-` goes to previous) |
| `pwd` | Print the current working directory |
| `export [key[=value]…]` | Set or display exported environment variables |
| `unset [key…]` | Remove environment variables |
| `env` | Print all environment variables |
| `exit [n]` | Exit the shell with optional exit code `n` |

---

## Supported Syntax

```bash
# Simple command
ls -la

# Pipe chain
ps aux | grep bash | awk '{print $1}'

# Input / output redirection
cat < input.txt > output.txt

# Append redirection
echo "more data" >> log.txt

# Heredoc
cat << STOP
some text here
STOP

# Variable expansion
echo $HOME
echo "Exit status: $?"

# Single quotes — no expansion
echo '$HOME'           # prints: $HOME

# Double quotes — expansion enabled
echo "$HOME"           # prints: /home/user

# Chained commands with semicolons are not supported — use pipes or sub-shells
```

---

## Project Structure

```
minishell/
├── inc/
│   └── minishell.h          # Global header — all structs, enums & prototypes
├── src/
│   ├── main.c               # Entry point, readline loop
│   ├── tokenizer/           # Lexer: breaks input into tokens
│   ├── parser/              # Syntax validation
│   ├── cmd_builder/         # Builds the command list from tokens
│   ├── expansion/           # Variable ($VAR, $?) and quote expansion
│   └── utils/               # String helpers, env utilities, libft wrappers
├── execution/
│   ├── exec_cmd/            # Command dispatcher & PATH resolution
│   ├── built_in/            # Built-in command implementations
│   ├── redir/               # Redirection & heredoc handling
│   ├── signal_handler/      # SIGINT / SIGQUIT handlers
│   └── utils/               # Execution-layer utilities
├── garbage/
│   └── garbage.c            # Custom garbage collector
└── Makefile
```

---

## Authors

- **Ali El Youssi** — [alel-you@student.42.fr](mailto:alel-you@student.42.fr)

---

*Built as part of the 42 curriculum.*
