# Operating Systems Assignment 1 - Spring Semester 2025

## 📋 Authors
- **Student Name**: Ido Cohen  
- **Student Name**: Eitan Halimi

---

This project is a collection of exercises from the "Operating Systems" course, covering basic and advanced topics in Unix/Linux environment work. The purpose of the exercises is to provide mastery of tools, system programming, and understanding of fundamental concepts such as processes, inter-process communication, memory management, and performance analysis.

## 📁 Project Structure

The project is divided into 7 stages, with each stage located in a separate directory (`q1` to `q7`). Each stage focuses on a different topic and demonstrates a specific skill.

---

## 💻 Stage 1: Compilation and Debugging in Linux (`q1`)

### 🎯 Objective

This stage demonstrates the creation and analysis of common software crashes. The goal is to familiarize with the basic debugging process in Linux, including the use of core dumps and textual and graphical debugging tools.

### 📖 File Description

The directory contains three simple C programs, each designed to fail in a predictable manner:

- **`stack_overflow.c`**: Causes program crash due to stack overflow through infinite recursive calls.
- **`divide_by_zero.c`**: Causes crash due to division by zero, which is an illegal arithmetic operation.
- **`invalid_memory.c`**: Causes crash (Segmentation Fault) by attempting to write to an illegal and undefined memory address (`0xdeadbeef`).

### 🛠️ Compilation and Execution

To compile the programs, use `gcc`. It's recommended to compile once with the debug flag `-g` and once without it, to demonstrate the difference in `core dump` analysis.

```bash
# Compilation with debug information
gcc -g stack_overflow.c -o stack_overflow_debug

# Compilation without debug information
gcc stack_overflow.c -o stack_overflow

# (Repeat the process for other files)
```

After execution, the program will crash and generate a core file (if the system is configured for it). This file can be analyzed using gdb:

```bash
# Run the program to create core dump
./stack_overflow_debug

# Open the core dump with gdb
gdb ./stack_overflow_debug core

# Inside gdb, you can use 'where' or 'bt' commands to see the call stack
(gdb) where
```

This stage also demonstrated the use of a graphical debugger like `ddd` for visual crash analysis.

## 🔢 Stage 2: Using Existing Libraries (`q2`)

### 🎯 Objective

This exercise demonstrates the use of C++ standard library (`<complex>`) to solve a mathematical problem, as well as reading command line arguments and basic user input handling.

### 📖 Code Description

The file `mandelbrot.cpp` is a program that checks whether a given complex number belongs to the Mandelbrot set.

- **The `checkIfMandelbrot` function**: Takes a complex number `c` and number of iterations `N`, and calculates the sequence `z_{n+1} = z_n^2 + c`. If the absolute value of `z` grows above 2, the function returns `false` (the number doesn't belong to the set). Otherwise, it returns `true`.

- **The `main` function**: Analyzes the arguments passed from the terminal (`argv`). It expects 2 or 3 arguments: the real part, the imaginary part, and an optional number of iterations (default is 1000). If the number of arguments is invalid, the program prints a usage message to `stderr` and exits.

### 🛠️ Compilation and Execution

```bash
# Compilation
g++ mandelbrot.cpp -o mandelbrot

# Execution examples
# Number that belongs to the set
./mandelbrot -0.5 0.5
# Output: -0.5 + 0.5i : is in the Mandelbrot set.

# Number that doesn't belong to the set
./mandelbrot 1 1
# Output: 1 + 1i : is not in the Mandelbrot set.

# Execution with invalid number of arguments
./mandelbrot 1
# Output (to stderr): Usage: ./mandelbrot <real part> <imaginary part> [<iterations>]
```

## 📦 Stage 3: Building Dynamic Library (`q3`)

### 🎯 Objective

This stage is an extension of stage 2. The goal is to convert the Mandelbrot set checking logic into a separate dynamic library (`.so` - Shared Object), and write a main program that uses this library.

### 📖 File Description

- **`mandelbrot.hpp`:** Header file that declares the `is_in_mandelbrot` function.
- **`mandelbrot.cpp`:** Implementation of the `is_in_mandelbrot` function, intended to be part of the dynamic library.
- **`main.cpp`:** Main program that uses the library. It reads pairs of numbers from standard input (`stdin`) using `scanf` in a loop. For each pair, it creates a complex number, calls the `is_in_mandelbrot` function from the library, and prints the result. The loop stops when the user enters `0 0`.

### 🛠️ Compilation and Execution

The compilation process is performed in several steps, and it's recommended to manage it using a Makefile:

1. **Create object file from library implementation:**

```bash
g++ -fPIC -c mandelbrot.cpp -o mandelbrot.o
```

2. **Create dynamic library (`.so`) from object file:**

```bash
g++ -shared -o libmandelbrot.so mandelbrot.o
```

3. **Compile main program and link it to the dynamic library:**

```bash
# -L.  - tells the linker to search for libraries in the current directory
# -lmandelbrot - tells the linker to link the libmandelbrot.so library
g++ main.cpp -o use_mandelbrot -L. -lmandelbrot
```

4. **Run the program:**

For the system to find the library at runtime, update the `LD_LIBRARY_PATH` variable:

```bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./use_mandelbrot
```

### 📜 Execution Example

```bash
$ ./use_mandelbrot
Enter values for <real> <image>:
0.1 0.1
0.1 + 0.1i : is in the Mandelbrot set.

Enter another complex number (re im), or 0 0 to quit:
1 1
1 + 1i : is not in the Mandelbrot set.

Enter another complex number (re im), or 0 0 to quit:
0 0
program finish
```

## 📊 Stage 4: Code Coverage Testing (`q4`)

### 🎯 Objective

This exercise demonstrates how to check code coverage using the `gcov` tool. The goal is to ensure that the prepared test suite runs all code lines and logical branches in the program, including error handling.

### 📖 Code Description

The file `myDijkstra.cpp` implements Dijkstra's algorithm for finding the shortest paths in a weighted graph.

- **Input**: The program reads from `stdin` the number of vertices (`V`), number of edges (`E`), and source vertex (`src`). Then it reads the `E` edges, where each edge is defined by `u`, `v`, `w` (source vertex, destination, and weight).

- **Validity checks**: The code includes important input validations:
  - Ensures that the number of vertices, edges, and source are valid.
  - Ensures that edge vertices are within the legal range.
  - Ensures that edge weights are not negative (necessary condition for Dijkstra).

- **Output**: The program prints the shortest distances from the source vertex to all other vertices.

### 🛠️ Coverage Testing Process

1. **Compilation with coverage flags:**

```bash
g++ --coverage myDijkstra.cpp -o myDijkstra
```

The `--coverage` flag (or `-fprofile-arcs -ftest-coverage`) adds instrumentation code to track line execution.

2. **Running the program with test inputs:**

The program should be run multiple times with different inputs to cover all cases:
- Valid input.
- Input with invalid data (e.g., negative V).
- Input with invalid edge (e.g., vertex out of range).
- Input with negative weight.

After each run, `.gcda` files are created containing the execution information.

3. **Creating coverage report with gcov:**

```bash
gcov myDijkstra.cpp
```

The command creates a `myDijkstra.cpp.gcov` file that shows for each code line how many times it was executed. Lines that were not executed are marked with `#####`. The goal is to reach a state where there are no lines marked this way, indicating 100% coverage.

## ⏱️ Stage 5: Performance Analysis (`q5`)

### 🎯 Objective

This stage demonstrates how to analyze program performance (Profiling) using the `gprof` tool. The goal is to find bottlenecks in the code and understand the differences in execution times of algorithms with different complexities.

### 📖 File Description

The directory contains three implementations for the "maximum contiguous subarray sum" problem:

- **`maxSubArray1.cpp`:** Linear implementation (Kadane's algorithm), O(n) complexity.
- **`maxSubArray2.cpp`:** Quadratic implementation, O(n²) complexity.
- **`maxSubArray3.cpp`:** Naive implementation (Brute-force), O(n³) complexity.

Each program receives two arguments: `seed` for initializing the random number generator and `N` for the array size. The programs generate a random array of integers (including negatives) and run the appropriate algorithm on it.

### 🛠️ Performance Analysis Process

1. **Compilation with profiling flag:**

```bash
# Repeat the operation for each of the three files
g++ -pg maxSubArray1.cpp -o maxSubArray1
g++ -pg maxSubArray2.cpp -o maxSubArray2
g++ -pg maxSubArray3.cpp -o maxSubArray3
```

The `-pg` flag adds instructions to the code for collecting information about function execution times.

2. **Running the programs with large input:**

The programs should be run with different N values (e.g., 100, 1000, 10000) so that performance differences are significant. After each run, a `gmon.out` file is created.

```bash
./maxSubArray1 123 10000
./maxSubArray2 123 1000
./maxSubArray3 123 100
```

3. **Creating report with gprof:**

```bash
gprof ./maxSubArray1 gmon.out > profile1.txt
gprof ./maxSubArray2 gmon.out > profile2.txt
gprof ./maxSubArray3 gmon.out > profile3.txt
```

The generated reports (`profileX.txt`) will clearly show the differences in execution time. For high complexity (O(n³)), the `maxSubarraySum` function will take a significant percentage of the total execution time, while the `generateInput` function will be negligible. For the efficient algorithm (O(n)), the difference will be much smaller.

## 📡 Stage 6: Communication Using Signals (`q6`)

### 🎯 Objective

This exercise demonstrates inter-process communication (IPC) using signals only. The goal is to implement a simple protocol for transferring an 8-bit number from one process (sender) to another (receiver).

### 📖 File Description

- **`signal_sender.cpp` (sender)**:
  - Asks the user for the PID of the receiving process and a number (0-255) to send.
  - Validates the input (that the PID exists and the number is in range).
  - Iterates over the 8 bits of the number (from most significant to least).
  - For each bit, sends the appropriate signal using the `kill()` system call:
    - `SIGUSR1` for bit 0.
    - `SIGUSR2` for bit 1.
  - Between each signal transmission, the program performs `usleep(100000)` (100 milliseconds delay) to prevent signal loss on the receiver side.

- **`signal_receiver.cpp` (receiver)**:
  - Prints its own PID so the user can pass it to the sender.
  - Sets up a single signal handler, `handle_sigusr`, for both `SIGUSR1` and `SIGUSR2` using `sigaction`.
  - Inside the handler: performs bit shifting (`<<= 1`) on a global variable `result`, and if `SIGUSR2` was received, adds 1. Counts the number of bits received.
  - Signal blocking: when setting up `sigaction`, the `sa_mask` is configured to block `SIGUSR1` and `SIGUSR2` while the handler is running. This prevents interruption of the handler by another signal of the same type.
  - After receiving 8 bits, the program prints the assembled number and exits.
  - The main loop uses `pause()` to passively wait for signal reception.

### 🛠️ Execution

1. **In one terminal, run the receiver:**

```bash
g++ signal_receiver.cpp -o receiver
./receiver
# Output: My PID is 12345
```

2. **In a second terminal, run the sender and input the received PID and the number to send:**

```bash
g++ signal_sender.cpp -o sender
./sender
# User input:
Enter receiver PID: 12345
Enter message: 42
```

3. **In the first terminal (receiver) the output will appear:**

```bash
Received 42
```

## 🔗 Stage 7: Using Pipes and Process Creation (`q7`)

### 🎯 Objective

This exercise is a comprehensive exercise demonstrating the construction of a command pipeline similar to shell, using system calls for process creation (`fork`), inter-process communication (`pipe`), and program replacement (`execlp`).

### 📖 File Description

**`PB2add.cpp`:** A simple utility tool for adding a record to the `phonebook.txt` file. The program receives a name and phone number as arguments and adds them as a new line to the file. It uses low-level system calls (`open`, `write`, `close`) for file operations.

**`findPhone.cpp`:** The core of the exercise. This program implements the pipeline:
```bash
grep <name> phonebook.txt | sed 's/ /#/g' | sed 's/,/ /' | awk '{print $2}'
```

The process is carried out as follows:

1. The main program creates 3 pipes that will be used to connect the 4 processes.

2. **Process 1 (grep):** The program creates a child process (`fork`). The child duplicates (`dup2`) the write end of the first pipe to `STDOUT`, so all output from `grep` is streamed to the pipe. Then, it runs `execlp` to replace itself with the `grep` command.

3. **Process 2 (sed 1):** A second child is created. It duplicates the read end of the first pipe to `STDIN` and the write end of the second pipe to `STDOUT`, then runs `sed 's/ /#/g'`.

4. **Process 3 (sed 2):** A third child is created. It connects between the second and third pipes and runs `sed 's/,/ /'`.

5. **Process 4 (awk):** A fourth child is created. It duplicates the read end of the third pipe to `STDIN` (its output will go to the standard terminal `STDOUT`) and runs `awk '{print $2}'`.

6. **The parent process:** After creating all children, the parent closes all pipe ends in its possession (a critical step to prevent deadlocks), and waits for all four children to finish using `waitpid`.

### 🛠️ Compilation and Execution

```bash
# Compilation
g++ PB2add.cpp -o add2PB
g++ findPhone.cpp -o findPhone

# 1. Create phonebook
./add2PB "ido co" 054-5531555
./add2PB "Micky Mouse" 123-4567890

# 2. Search for phone number
./findPhone Micky
# Output:
# Notice:the program use the first name only (argv[1])
# The phone number/s:
# 123-4567890
# The program has finished
```

---

## 📜 Summary and Skills Acquired

This project provided comprehensive practical experience with a wide range of tools and fundamental concepts in operating systems in a Linux environment. The different stages led to gradual development of skills:

### 🔧 Fundamentals
Compilation, linking, and basic use of debugger (`gdb`) for crash analysis (Q1).

### 📚 Using and Creating Libraries
Familiarity with standard libraries, and understanding the process of creating and linking dynamic libraries (`.so`), enabling modular and reusable code writing (Q2, Q3).

### 🔍 Code Analysis and Testing
Using advanced tools for software behavior analysis:
- **`gcov`**: To ensure code quality through complete coverage testing (Q4).
- **`gprof`**: To identify performance bottlenecks and understand the practical significance of algorithmic complexity (Q5).

### ⚙️ System Programming and Processes
Mastery of central system calls for process management and inter-process communication:
- **Signals**: Implementation of basic communication protocol using `kill` and `sigaction` (Q6).
- **Pipes and Processes**: Building complex data processing chains by combining `fork`, `exec`, `pipe`, and `dup2`, which forms the basis for shell operation in Unix (Q7).

Overall, the project built a solid foundation in C/C++ programming in a Linux environment, emphasizing proper practices of development, testing, and performance analysis.
