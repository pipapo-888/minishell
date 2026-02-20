_This project has been created as part of the 42 curriculum by knomura, habe._

## Description

This project is about remaking a simplified version of a Unix shell similar to Bash.
The goal is to understand how a Unix shell works by implementing core features such as
command parsing, process creation, pipes, redirections, and environment variable handling.

By recreating a shell from scratch, this project provides hands-on experience with
system calls, process management, and memory handling in C.

## Instructions

### Compilation

To compile and run this project, you need:

- A Unix-based operating system (Linux or macOS)
- GCC or Clang compiler
- GNU Make
- GNU Readline library

Compile the project using:

- make

### Execution

./minishell

## Resources

### References

- bash manual: ex. `man bash`
  // HABE へここに参考にしたウェブサイトとか notion に上げてるやつでもいいから適当に２ −3 個追加しておいて

### AI Usage

AI tools (ChatGPT, Gemini, Claude Code) were used to:

- clarify Bash behavior and edge cases
- understand Unix system calls such as `fork`, `execve`, `pipe`, `dup2` and related functions.
- review logic and suggest improvements in parsing strategies

All final implementation choices and code were written and validated by the authors.
