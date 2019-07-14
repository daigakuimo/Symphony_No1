#include "puzzle.h"
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;


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
	int* checked_puzzle[PUZZLE_WIDTH];

	*checked_puzzle = (int*)malloc(sizeof(int) * PUZZLE_HEIGHT);


	int clearCount = 0;

	for (int y = 0; y < PUZZLE_HEIGHT; y++) {
		for (int x = 0; x < PUZZLE_WIDTH; x++) {
			int count = connectPuzzleCount(puzzle, checked_puzzle, puzzle[y][x], x, y, 0);
			fprintf_s(stdout, "%d\n", count);
			if (count >= 3) {
				puzzleDelete(puzzle, puzzle[y][x], x, y);
				clearCount = clearCount + count;
			}
		}
	}

	return clearCount;
}

int connectPuzzleCount(int** puzzle, int** checked_puzzle,int puzzle_type, int x, int y, int count)
{
	if (y < 0 || x < 0 || y > 4 || x > 4)
	{
		return count;
	}

	if (puzzle[y][x] != puzzle_type || puzzle[y][x] == 0 || checked_puzzle[y][x] == 1)
	{
		return count;
	}

	count++;
	checked_puzzle[y][x] = 1;

	connectPuzzleCount(puzzle, checked_puzzle, puzzle_type, x, y - 1, count);
	connectPuzzleCount(puzzle, checked_puzzle, puzzle_type, x - 1, y, count);
	connectPuzzleCount(puzzle, checked_puzzle, puzzle_type, x, y + 1, count);
	connectPuzzleCount(puzzle, checked_puzzle, puzzle_type, x + 1, y, count);

}

//パズルを消す
void puzzleDelete(int** puzzle,int puzzle_type,int x,int y) 
{

	if (y < 0 || x < 0 || y > 4 || x > 4) {
		return;
	}

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
void puzzleDrop(int** puzzle)
{
	//
	for (int x = 0; x < PUZZLE_WIDTH; x++) 
	{
		for (int k = 4; k >= 1; k--)
		{
			int temp = k;
			if (puzzle[k][x] != 0)
			{
				continue;
			}

			for (int y = k - 1; y >= 0; y--)
			{

				if (puzzle[y][x] == 0)
				{
					continue;
				}

				puzzle[temp][x] = puzzle[y][x];
				puzzle[y][x] = 0;
				temp = y;

			}

		}
	}

	//
	int seed = (unsigned)time(NULL);
	for (int y = 0; y < PUZZLE_HEIGHT; y++)
	{
		for (int x = 0; x < PUZZLE_WIDTH; x++)
		{

			if (puzzle[y][x] == 0)
			{
				//乱数生成
				srand(seed++);
				int random = rand() % 5 + 1;

				puzzle[y][x] = random;
			}

		}
	}

	fprintf_s(stdout, "finish\n");
}

//落ち込んがあるか判定
bool puzzleDropCombo(int** puzzle) 
{

	int *checked_puzzle[PUZZLE_WIDTH];
	*checked_puzzle = (int*)malloc(sizeof(int) * PUZZLE_HEIGHT);


	for (int y = 0; y < PUZZLE_HEIGHT; y++) 
	{
		for (int x = 0; x < PUZZLE_WIDTH; x++) 
		{
			int count = connectPuzzleCount(puzzle, checked_puzzle, puzzle[y][x], x, y, 0);
			if (count >= 3)
			{
				return true;
			}
		}
	}

	return false;
}

void attackPlayer(int combo)
{

}
