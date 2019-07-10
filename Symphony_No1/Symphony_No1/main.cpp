#include <stdio.h>
#include <curses.h>
#include <iostream>
#include "puzzle.h"
using namespace std;


struct player
{
	int player_number;
	int hitpoint;
	int** puzzle;
	int* x_cursor;
	int* y_cursor;
	char key;
};



int main() {


	player player1 = {};

	//ƒƒ‚ƒŠ[—Ìˆæ‚ÌŠm•Û
	player1.puzzle = (int**)malloc(sizeof(int*) * PUZZLE_HEIGHT);

	for (int i = 0; i < PUZZLE_HEIGHT; i++)
	{
		player1.puzzle[i] = (int*)malloc(sizeof(int) * PUZZLE_WIDTH);
	}
	
	init(player1.puzzle);

	player1.x_cursor = new int;
	player1.y_cursor = new int;

	*(player1.y_cursor) = 0;
	*(player1.x_cursor) = 0;


	for (int y = 0; y < PUZZLE_HEIGHT; y++)
	{
		for (int x = 0; x < PUZZLE_WIDTH; x++)
		{

			fprintf_s(stdout, "%d,",player1.puzzle[y][x]);

		}
		cout << endl;
	}

	fprintf_s(stdout, "%d,", *(player1.y_cursor));


	cout << endl;

	cin >> player1.key;

	cursorMode(player1.x_cursor, player1.y_cursor, player1.key);

	fprintf_s(stdout, "%d,", *(player1.y_cursor));

	cout << endl;

	cin >> player1.key;

	puzzleMode(player1.puzzle, player1.x_cursor, player1.y_cursor, player1.key);

	for (int y = 0; y < PUZZLE_HEIGHT; y++)
	{
		for (int x = 0; x < PUZZLE_WIDTH; x++)
		{

			fprintf_s(stdout, "%d,", player1.puzzle[y][x]);

		}
		cout << endl;
	}






	return 0;
}