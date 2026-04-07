# C Conway’s Game of Life

Or… CCGL.

This is the [Conway’s Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), a cellular automaton, coded in C.

This supports Windows and Unix-like (Linux and MacOS[^1]).

[^1]: MacOS not tested, tester needed!

## Compiling

The following compiler command is going to place the executable on [`bin`](bin/) folder.

### Linux

Requirements:

- `libncurses` (Ubuntu/Debian).
- `ncurses-devel` (Fedora/RHEL).
- GCC/Clang.

Ensure the requirements are installed.

```bash
# Ubuntu/Debian
sudo apt install libncurses-dev
```

```bash
# Fedora/RHEL
sudo dnf install ncurses-devel
```

For compiling, you can use GCC or Clang. For GCC:

```bash
gcc main.c includes/*.c -lncurses -o bin/main
```

For Clang:

```bash
clang main.c includes/*.c -lncurses -o bin/main
```

Ensure the executable has permission to run:

```bash
chmod +x bin/main
```

### macOS

Requirements:

- `ncurses`.
- GCC.

Ensure the requirements are installed.

```bash
brew install ncurses
```

To compile, use GCC:

```bash
gcc main.c includes/*.c -I/usr/local/opt/ncurses/include -L/usr/local/opt/ncurses/lib -lncurses -o bin/main
```

### Windows

Requirements:

- GCC (Install using [MinGW](https://www.mingw-w64.org) or [MSYS2](https://www.msys2.org)).

Compiling:

```bash
gcc main.c includes\*.c -o bin\main.exe
```

## Usage

### Linux and macOS

```bash
<bin> <height> <width>
```

Replace `<bin>` with your binary file, the default is `bin/main`.

### Windows

```bash
<bin> <height> <width>
```

Replace `<bin>` with your executable file, the default is `bin\main.exe`.