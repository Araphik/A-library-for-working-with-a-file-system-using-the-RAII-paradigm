# FileRAII - RAII File Handling Wrapper

## Description
A C++ library implementing RAII pattern for safe file operations with automatic resource management.

## Features
- Automatic file opening/closing
- Exception-safe operations
- Support for read/write/append modes
- Cross-platform (Linux/macOS)

## Requirements
- CMake 3.10+
- C++20 compiler (g++/clang++)

## Build Instructions

### Configure
mkdir build && cd build
cmake ..

### Build
cmake --build .

### Run tests
./bin/TestProgramDynamicLinking

## Project Structure

```plaintext
build/
├── bin/
│   ├── TestProgramStaticLinking
│   └── TestProgramDynamicLinking
└── lib/
  ├── libFileRAII.a
  └── libFileRAII.so (or .dylib)
```

## Usage (Example)

```plaintext
#include "FileRAII.h"

// Open a file for reading
FileRAII reader("file.txt", std::ios::in);

// Open a file for writing (overwriting)
FileRAII writer("file.txt", std::ios::out);

// Open a file for appending
FileRAII appender("file.txt", std::ios::app);

// Open a file for reading and writing
FileRAII rwFile("file.txt", std::ios::in | std::ios::out);

// Write a line to a file
file.writeLine("Hello, World!");

// Read a line from a file
std::string line = file.readLine();

// Check if the file is open
if (file.isOpen()) { /* ... */ }

// Close the file (called automatically when the object is destroyed)
file.close();
```
