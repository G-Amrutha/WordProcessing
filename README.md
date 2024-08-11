## Word Processing Game

This project is a C++ implementation of a word processing game, developed as part of an assignment for COMP 1602. The game involves converting words into numerical representations based on their alphabetical positions and applying certain processing rules.

## Files

- `WordGame.cpp`: The main C++ source file containing the implementation of the word processing logic.

## Requirements

- A C++ compiler such as g++.

## Compilation and Execution

1. **Compile the program** using a C++ compiler:

   ```bash
   g++ -o word_game WordGame.cpp
   ```

2. **Run the executable**:

   ```bash
   ./word_game
   ```

## How It Works

- The program reads input words and converts each character to its corresponding position in the alphabet, adjusted by subtracting 96 (e.g., 'a' becomes 1, 'b' becomes 2, etc.).
- The game maintains an "AlphaKey," which is a conceptual mapping of each letter's position.
- The processing involves updating this key and possibly skipping already processed characters, as illustrated with the word "Galaxy."

## Example

For the word "Galaxy":

- Convert each letter to its position:
  - 'g' → 7
  - 'a' → 1
  - 'l' → 12
  - 'a' (appears again, so no change)
  - 'x' → 24
  - 'y' → 25
