#pragma once

#define PUZZLE_WIDTH 5
#define PUZZLE_HEIGHT 5




//mainÇ≈égÇ§ä÷êî
void init(int** puzzle);
void getKey(int* key);
void puzzleDrop(int** puzzle);
bool puzzleDropCombo(int** puzzle);
void attackPlayer(int combo);
void cursorMode(int* x_cursor, int* y_cursor, char key);
void puzzleMode(int** puzzle, int* x_cursor, int* y_cursor, char key);
int  deleteMode(int** puzzle);

void puzzleDelete(int** puzzle, int puzzle_type, int x, int y);
int  connectPuzzleCount(int** puzzle, int** checked_puzzle, int puzzle_type, int x, int y, int count);