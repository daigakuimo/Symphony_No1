#include "puzzle.h"
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>



//パズルの初期化
void init(char** puzzle) 
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


//キー入力によるパズルの移動
void puzzleMove(char** puzzle)
{

	

}


void cursorMode(char** puzzle) 
{

	

}

void puzzleMode(char** puzzle) 
{

}

void puzzleDelete(char** puzzle) 
{

}


void puzzleDrop(char** puzzle)
{

}

bool puzzleDropCombo(char** puzzle) 
{
	return true;
}

void attackPlayer(int combo)
{

}
