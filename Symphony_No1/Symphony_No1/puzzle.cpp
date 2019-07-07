#include "puzzle.h"
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>


void hello() {
	fprintf_s(stdout, "hello");
}

//パズルの初期化
void init(char** puzzle) 
{

	//メモリー領域の確保
	puzzle = (char**)malloc(sizeof(char*) * PUZZLE_HEIGHT);

	for (int i = 0; i < PUZZLE_HEIGHT; i++) 
	{
		if (puzzle == NULL)
		{

		}
		else {
			puzzle[i] = (char*)malloc(sizeof(char) * PUZZLE_WIDTH);
		}
	}

	//乱数からパズルを作る
	//randomの値で記号を決める
	//１：a　２：b　３：c　４：d　５：e
	for (int y = 0; y < PUZZLE_HEIGHT; y++) {
		for (int x = 0; x < PUZZLE_WIDTH; x++) {
			
			//乱数生成
			srand((unsigned int)time(NULL));
			int random = rand() % 5 + 1;

			//記号を配列へ代入
			if (puzzle != NULL)
			{
				switch (random) {
				case 1:
					puzzle[y][x] = 'a';
					break;

				case 2:
					puzzle[y][x] = 'b';
					break;

				case 3:
					puzzle[y][x] = 'c';
					break;

				case 4:
					puzzle[y][x] = 'd';
					break;

				case 5:
					puzzle[y][x] = 'e';
					break;
				}
			}
		}
	}
	
}

