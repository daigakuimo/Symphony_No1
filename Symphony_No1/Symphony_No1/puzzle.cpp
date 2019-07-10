#include "puzzle.h"
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>



//パズルの初期化
void init(int** puzzle) 
{
	//乱数からパズルを作る
	//randomの値で記号を決める
	//１：a　２：b　３：c　４：d　５：e
	int seed = (unsigned)time(NULL);
	for (int y = 0; y < PUZZLE_HEIGHT; y++) 
	{
		for (int x = 0; x < PUZZLE_WIDTH; x++) 
		{
	
			//乱数生成
			srand(seed++);
			int random = rand() % 5 + 1;

			puzzle[y][x] = random;

		}
	}
	
}

void getKey(int* key) {
	timeout(-1);
	*key = getch();
}



//動かすパズルを決める関数
void cursorMode(int* x_cursor, int* y_cursor, char key) 
{

	switch (key) 
	{

		case 'w':
			if (*y_cursor > 0) {
				(*y_cursor)--;
			}
			break;
		case 'z':
			if (*y_cursor < 4) {
				(*y_cursor)++;
			}
			break;
		case 'a':
			if (*x_cursor > 0) {
				(*x_cursor)--;
			}
			break;
		case 's':
			if (*x_cursor < 4) {
				(*x_cursor)++;
			}
			break;

	}

}

//パズルを動かす
void puzzleMode(int** puzzle, int* x_cursor, int* y_cursor, char key)
{
	//入れ替え用の仮の変数
	int temp_puzzle = puzzle[*y_cursor][*x_cursor];
	int temp_x = *x_cursor;
	int temp_y = *y_cursor;

	switch (key)
	{

		case 'w':
			if (*y_cursor > 0) {
				(*y_cursor)--;		
			}
			break;
		case 'z':
			if (*y_cursor < 4) {
				(*y_cursor)++;
			}
			break;
		case 'a':
			if (*x_cursor > 0) {
				(*x_cursor)--;
			}
			break;
		case 's':
			if (*x_cursor < 4) {
				(*x_cursor)++;
			}
			break;

	}

	puzzle[temp_y][temp_x] = puzzle[*y_cursor][*x_cursor];
	puzzle[*y_cursor][*x_cursor] = temp_puzzle;

}

int deleteMode(int** puzzle)
{
	int** checked_puzzle;
	

	int clearCount = 0;

	for (int y = 0; y < PUZZLE_HEIGHT; y++) {
		for (int x = 0; x < PUZZLE_WIDTH; x++) {
			int count = connectPuzzleCount(puzzle, checked_puzzle, puzzle[y][x], x, y, 0);
			if (count >= 3) {
				puzzleDelete(puzzle, puzzle[y][x], x, y);
				clearCount = clearCount + count;
			}
		}
	}
}

int connectPuzzleCount(int** puzzle, int** checked_puzzle,int puzzle_type, int x, int y, int count)
{
	if (puzzle[y][x] != puzzle_type || puzzle[y][x] == 0 || checked_puzzle[y][x] == 1)
	{
		return count;
	}

	count++;
	checked_puzzle[y][x] = 0;

	connectPuzzleCount(puzzle, checked_puzzle, puzzle_type, x, y - 1, count);
	connectPuzzleCount(puzzle, checked_puzzle, puzzle_type, x - 1, y, count);
	connectPuzzleCount(puzzle, checked_puzzle, puzzle_type, x, y + 1, count);
	connectPuzzleCount(puzzle, checked_puzzle, puzzle_type, x + 1, y, count);

}

//パズルを消す
void puzzleDelete(int** puzzle,int puzzle_type,int x,int y) 
{

	if (puzzle[y][x] != puzzle_type || puzzle[y][x] == 0)
	{
		return;
	}

	puzzle[y][x] = 0;

	puzzleDelete(puzzle, puzzle_type, x, y - 1);
	puzzleDelete(puzzle, puzzle_type, x - 1, y);
	puzzleDelete(puzzle, puzzle_type, x, y + 1);
	puzzleDelete(puzzle, puzzle_type, x + 1, y);

}

//消えたパズルの分だけパズルを落とす
void puzzleDrop(char** puzzle)
{

}

//落ち込んがあるか判定
bool puzzleDropCombo(char** puzzle) 
{
	return true;
}

void attackPlayer(int combo)
{

}
