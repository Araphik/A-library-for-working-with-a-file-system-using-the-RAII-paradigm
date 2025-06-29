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

build/
├── bin/
│ ├── TestProgramStaticLinking
│ └── TestProgramDynamicLinking
└── lib/
├── libFileRAII.a
└── libFileRAII.so (or .dylib)

## Usage (Example)

#include "FileRAII.h"

// Writing
FileRAII writer("log.txt", std::ios::out);
writer.writeLine("Message");

// Reading
FileRAII reader("data.txt", std::ios::in);
