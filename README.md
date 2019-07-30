tabstospaces
============

Basic Tab to Space converter.

## Usage
Takes any number of file names, and an option `-t n`, where `n` is an integer specifying spaces per tab.
Replaces tabs in those files with `n` times as many spaces

## Dependencies
  - C compiler.
  - CMake

## Build

    cd tabstospaces
    mkdir build && cd $_
    cmake ..
    make
    ./tabstospaces
