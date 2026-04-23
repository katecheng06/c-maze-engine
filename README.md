# C-Maze Engine: Logic, Matrices, and File I/O

## 📌 Project Overview
A robust terminal-based maze game developed in C. This project demonstrates low-level memory management, 2D array manipulation, and coordinate geometry. The engine supports dynamic level loading from external files and complex spatial transformations like mirroring and 90-degree clockwise rotation.

## 🛠️ Technical Implementation
- **Dynamic Level Loading:** Utilizes `stdio.h` file streams (`fopen`, `fgets`, `fscanf`) to initialize game states from external `.txt` files.
- **Matrix Transformations:** - **Horizontal Mirroring:** Swaps elements across the central axis of the 2D array.
    - **90° Rotation:** Implements a matrix transpose and row-reversal algorithm to rotate the game world while maintaining player coordinate parity.
- **Sliding Movement Logic:** A custom "multi-step" algorithm that simulates momentum, stopping the player only when specific environmental conditions (wall proximity or item collision) are met.
- **Buffer Management:** Safe handling of char arrays and input buffers to prevent overflow during file reading.

## 🎮 Mechanics
- **Movement:** `8` (Up), `2` (Down), `4` (Left), `6` (Right).
- **Interactive Elements:**
    - `EX`: Exit point (Win condition).
    - `mr`: Mirror item (Flips the maze horizontally).
    - `rc`: Rotation item (Rotates the maze 90° clockwise).

## 🚀 Compilation & Execution
1. Ensure you have a `gameboard.txt` file in the directory.
2. Compile using GCC:
   ```bash
   gcc maze_engine.c -o maze_engine