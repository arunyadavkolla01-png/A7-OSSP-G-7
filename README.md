# ShellForge — Multi-User Linux Shell

## 1. Project Overview

ShellForge is a custom Linux command-line shell developed using the C programming language. It demonstrates fundamental operating system concepts such as user authentication, command parsing, process creation, process management, built-in commands, signal handling, and inter-process communication using pipes.

The shell provides an interactive command-line interface where users can enter commands, execute supported built-in operations, and run external Linux programs.

## 2. Objectives

* Develop a basic interactive Linux shell using C.
* Implement user authentication and session management.
* Read and parse user commands.
* Execute external programs using process creation and execution system calls.
* Manage child processes and process termination.
* Implement built-in shell commands.
* Handle signals such as `SIGINT` and `SIGCHLD`.
* Support command pipelines using the Linux `pipe()` system call.
* Demonstrate core operating system concepts through practical implementation.

## 3. Features

### Week 1–2: Authentication and Input Handling

* User authentication using a configured user list.
* Session initialization and termination.
* Interactive command prompt.
* Dynamic command-line input handling using memory allocation.

### Week 3: Command Parsing

* Split command input into individual tokens.
* Identify the command and its arguments.
* Prepare parsed commands for execution.

### Week 4: Process Management

* Create child processes using `fork()`.
* Execute external programs using `execvp()`.
* Wait for child processes using `waitpid()`.

### Week 5: Built-in Commands

* Implement selected shell commands internally.
* Handle built-in operations without launching separate external programs.
* Support shell exit functionality.

### Week 6: Signal Handling

* Handle keyboard interrupts using `SIGINT`.
* Configure child-process signal handling using `SIGCHLD`.
* Improve shell behavior when commands are interrupted or completed.

### Week 7: Pipe Support

* Create a pipe using `pipe()`.
* Redirect standard output and standard input using `dup2()`.
* Connect the output of one command to the input of another.
* Execute two commands connected by a single pipe.

Example:

```bash
ls | wc
```

**Current limitation:** The Week 7 implementation supports one pipe connecting two commands. Multiple consecutive pipes and advanced shell features require additional implementation.

## 4. Technologies Used

* **Programming Language:** C
* **Operating System:** Linux / Ubuntu
* **Compiler:** GCC
* **Build Tool:** GNU Make
* **Version Control:** Git
* **System Calls and APIs:** `fork()`, `execvp()`, `waitpid()`, `pipe()`, `dup2()`, `signal()`
* **Inter-Process Communication:** Pipes

## 5. Project Structure

```text
MultiUserShell/
├── Makefile
├── README.md
├── users/
│   └── users.txt
├── include/
│   ├── auth.h
│   ├── input.h
│   ├── shell.h
│   ├── parser.h
│   ├── process.h
│   ├── builtin.h
│   ├── signals.h
│   └── pipes.h
├── src/
│   ├── main.c
│   ├── auth.c
│   ├── input.c
│   ├── parser.c
│   ├── process.c
│   ├── builtin.c
│   ├── signals.c
│   └── pipes.c
├── bin/
├── docs/
├── tests/
└── screenshots/
```

*Note: This structure represents the intended organization. Update it to match the files actually present in your repository.*

## 6. Prerequisites

Ensure the following tools are installed:

* Linux or Ubuntu environment
* GCC compiler
* GNU Make
* Git

Install the compiler and build tools on Ubuntu using:

```bash
sudo apt update
sudo apt install build-essential git
```

## 7. Installation and Execution

### Step 1: Clone the Repository

```bash
git clone https://github.com/arunyadavkolla01-png/A7-OSSP-G-7.git
cd A7-OSSP-G-7
```

### Step 2: Compile the Project

```bash
make
```

The executable is expected to be generated at:

```text
bin/shellforge
```

### Step 3: Run the Shell

```bash
./bin/shellforge
```

Alternatively, if the Makefile includes a `run` target:

```bash
make run
```

### Step 4: Clean Build Files

```bash
make clean
```

## 8. Supported Commands and Examples

The exact commands available depend on the built-ins implemented in the source code and the external programs installed on the system.

| Example               | Purpose                                       |
| --------------------- | --------------------------------------------- |
| `ls`                  | List directory contents                       |
| `pwd`                 | Display the current working directory         |
| `whoami`              | Display the current operating-system username |
| `date`                | Display the current date and time             |
| `ls \| wc`            | Pass the output of `ls` to `wc`               |
| `ps -ef \| grep bash` | Filter process information                    |
| `exit`                | Exit the shell, if implemented as a built-in  |

External commands work only if the shell correctly executes them and the relevant programs are available in the system's command search path.

## 9. Operating System Concepts Demonstrated

| Concept                     | Purpose                                                       |
| --------------------------- | ------------------------------------------------------------- |
| Process creation            | `fork()` creates child processes                              |
| Program execution           | `execvp()` replaces a process image with a new program        |
| Process synchronization     | `waitpid()` waits for child-process state changes             |
| File descriptors            | Standard input and output are represented by file descriptors |
| I/O redirection             | `dup2()` redirects input or output                            |
| Inter-process communication | Pipes transfer data between processes                         |
| Signal handling             | Signals allow the shell to respond to events                  |
| Dynamic memory              | Input and parsing operations may allocate memory dynamically  |

## 10. Testing

The following tests can be used to verify the shell:

1. Start the shell and verify that the prompt appears.
2. Test valid and invalid authentication, if authentication is required at startup.
3. Execute a valid external command such as `ls`.
4. Execute commands with arguments, such as `ls -l`.
5. Test implemented built-in commands.
6. Test keyboard interrupt handling.
7. Test a valid pipeline, such as `ls | wc`.
8. Test invalid pipeline inputs, such as `| wc` and `ls |`.
9. Verify that child processes terminate and the shell continues operating.
10. Rebuild the project and check for compiler warnings or errors.

Record the actual test results in the project's `tests/` directory.

## 11. Limitations

* Pipeline support is limited to two commands connected by one pipe in the current implementation.
* Advanced shell features such as command history, tab completion, background execution, and job control may not be supported.
* Input redirection and output redirection are not included unless implemented separately.
* Authentication security depends on how user credentials are stored and verified.
* Command behavior depends on the underlying Linux environment and installed programs.

## 12. Future Enhancements

* Support multiple commands in a pipeline.
* Implement input and output redirection.
* Add command history and tab completion.
* Introduce background process execution.
* Improve job control and signal management.
* Add automated test cases.
* Improve authentication and credential storage.
* Expand error handling and documentation.

## 13. Team and Contributors

Add the verified names of all project members, their registration details if required by your institution, and the faculty guide.

* **Project Title:** Multi-User Linux Shell — ShellForge
* **Subject:** Operating Systems and System Programming
* **Institution:** Add your institution's official name.
* **Team Members:** Add the verified team member names.
* **Faculty Guide:** Add the verified faculty guide name.

## 14. Conclusion

ShellForge demonstrates the implementation of a basic Linux shell in C by combining command input, parsing, process creation, built-in operations, signal handling, and pipe-based inter-process communication. The project provides practical experience with Linux system calls and foundational operating system concepts.

## 15. License

Add the license selected for this project, if applicable. If no license has been selected, do not claim that the project is released under a particular open-source license.


## PROJECT FLOW

             ShellForge
                 │
                 ▼
       ┌───────────────────┐
       │ User Authentication│
       └─────────┬─────────┘
                 │
        ┌────────┴────────┐
        │                 │
     Failed            Successful
        │                 │
        ▼                 ▼
 Access Denied      User Shell Session
                          │
                          ▼
                    Read Command
                          │
                 ┌────────┴────────┐
                 │                 │
              Normal             Pipe
                 │                 │
                 ▼                 ▼
             Parse Line       Execute Pipe
                 │
          ┌──────┴──────┐
          │             │
       Built-in      External
          │             │
          ▼             ▼
      Execute       fork()
                     execvp()
                     waitpid()




## Week 8 Features

- Memory leak detection using Valgrind
- Debugging using GDB
- AddressSanitizer support
- Defensive programming practices
- Improved error handling
