#pragma once

struct player
{
	int playerNumber;
	int hitpoint;
	int** puzzle;
	int* x_cursor;
	int* y_cursor;
	char key;
};

int setSquareX(int playerSide, int x);
int setSquareY(int playerSide, int y);
void displayHitpoint(int playerSide, int hitpoint);
void displayDrop(int dropNum, int y, int x);
void displayCursor(int y_cursor, int x_cursor);
void displayAvatar(int playerSide, int hitpoint);
void displayAll(player player1, player player2);