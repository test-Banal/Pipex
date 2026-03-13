# Pipex

## Project Overview

Pipex is a project from the 42 School curriculum that reproduces the behavior of Unix pipes (|) in the shell.
The goal is to understand how the shell connects multiple commands together using pipes, redirects input/output files, and executes programs using low-level Unix system calls.
This project helped me explore process creation, inter-process communication, and file descriptor management in C.

 ## Examples
 The program reproduces the behavior of the following shell command:
< infile cmd1 | cmd2 > outfile
Example usage:
./pipex infile "grep hello" "wc -l" outfile
Equivalent shell command:
< infile grep hello | wc -l > outfile

## Technologies & Concepts
Language: C
Unix system calls
Process creation (fork)
Program execution (execve)
Pipes (pipe)
File descriptors
Input/output redirections
Error handling

## Program Workflow
Open the input and output files
Create a pipe for communication between processes
Fork two child processes
Redirect standard input/output using dup2
Execute commands with execve
Wait for processes to finish
This reproduces how Unix shells internally execute piped commands.

## What I Learned
How Unix pipes allow communication between processes
How shells connect commands together
Managing file descriptors safely
Using fork, execve, dup2 and pipe
Understanding low-level process execution
Installation

## Clone the repository:
git clone https://github.com/yourusername/pipex.git
cd pipex
Compile the project:
make
Run the program:
./pipex infile "cmd1" "cmd2" outfile

## About 42
This project is part of the 42 School curriculum, a peer-to-peer programming school focused on low-level programming, algorithms, and system understanding.

## Author
Alban – 42 Paris
