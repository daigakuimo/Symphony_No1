#pragma once

#define PUZZLE_WIDTH 5
#define PUZZLE_HEIGHT 5

//mainÇ≈égÇ§ä÷êî
void init(char** puzzle);
void puzzleMove(char** puzzle);
void puzzleDelete(char** puzzle);
void puzzleDrop(char** puzzle);
bool puzzleDropCombo(char** puzzle);
void attackPlayer(int combo);



void cursorMode(char** puzzle);
void puzzleMode(char** puzzle);