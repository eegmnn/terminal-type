# Terminal-Typer


## Overview

**Terminal-Typer** is a terminal-based typing test that challenges your speed and accuracy in typing. This application was developed as a **day-long project** for the sheer fun of coding, therefore the program has a lot of missing components and features. If you're looking for a simple but fun typing exercise that runs in your terminal, terminal-typer still may not be the best choice :)).

This app is a lightweight and minimalist typing test that can be run on **Linux**, **macOS**, and even **Windows** (using WSL or a compatible terminal but no isntructions provided for them).


## Screenshots

![terminal-typer Running](https://github.com/eegmnn/terminal-typer/blob/67a6ead7412418244db7d0471cd7be162715de5b/assets/screenshot-terminal-typer.png)

## Getting Started

### Prerequisites

- **g++ compiler** (for compiling the C++ code)
- **ncurses library** (for terminal UI)

Make sure you have `g++` and `ncurses` installed on your machine. You can use the package manager of your OS to install them.

### Installation

Below, you'll find installation instructions for **Linux**, **macOS**, and **Windows** (via WSL).

#### Linux Installation

1. **Clone the Repository**:

   ```sh
   git clone https://github.com/eegmnn/terminal-typer.git
   cd terminal-typer

2. **Install Dependencies** (if not already installed):

   ```sh
   sudo apt-get update
   sudo apt-get install g++ libncurses5-dev

3. **Compile the Code**:

   ```sh
   g++ terminal-typer.cpp -o terminal-typer -lncurses

3. **Run the Application**:

   ```sh
   ./terminal-typer


#### macOS Installation

1. **Clone the Repository**:

   ```sh
   git clone https://github.com/eegmnn/terminal-typer.git
   cd terminal-typer

2. **Install Dependencies using Homebrew** (if not already installed):

   ```sh
   brew install gcc ncurses

3. **Compile the Code**:

   ```sh
   g++ terminal-typer.cpp -o terminal-typer -lncurses

3. **Run the Application**:

   ```sh
   ./terminal-typer

  
