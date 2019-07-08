#include <stdio.h>
#include <curses.h>
#include <iostream>
#include "puzzle.h"
using namespace std;


struct player
{
	int playerNumber;
	int hitpoint;
	char** puzzle;
};



int main() {


	player player1 = {};

	//ƒƒ‚ƒŠ[—Ìˆæ‚ÌŠm•Û
	player1.puzzle = (char**)malloc(sizeof(char*) * PUZZLE_HEIGHT);

	for (int i = 0; i < PUZZLE_HEIGHT; i++)
	{
		player1.puzzle[i] = (char*)malloc(sizeof(char) * PUZZLE_WIDTH);
	}
	
	init(player1.puzzle);

	for (int y = 0; y < PUZZLE_HEIGHT; y++)
	{
		for (int x = 0; x < PUZZLE_WIDTH; x++)
		{

			fprintf_s(stdout, "%d,",player1.puzzle[y][x]);

		}
		cout << endl;
	}


	return 0;
}