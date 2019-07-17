
#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include "puzzle.h"
using namespace std;

struct player
{
	int playerNumber;
	char* playerName;
	int hitpoint;
	int** puzzle;
	int* x_cursor;
	int* y_cursor;
	char key;
};


char* initName(int number);
int setSquareX(int playerSide, int x);
int setSquareY(int playerSide, int y);
void displayHitpoint(int playerSide, int hitpoint);
void displayDrop(int dropNum, int y, int x);
void displayCursor(int y_cursor, int x_cursor);
void displayAvatar(int playerSide, int hitpoint);
void displayAll(struct player player1, struct player player2);

#define BUFFSIZE 1024

int main()
{
	//������
	int pn = 1;
	int attack = 0;

	player player1 = {};
	player player2 = {};

	//�������[�̈�̊m��
	player1.puzzle = (int**)malloc(sizeof(int*) * PUZZLE_HEIGHT);
	player2.puzzle = (int**)malloc(sizeof(int*) * PUZZLE_HEIGHT);

	for (int i = 0; i < PUZZLE_HEIGHT; i++)
	{
		player1.puzzle[i] = (int*)malloc(sizeof(int) * PUZZLE_WIDTH);
		player2.puzzle[i] = (int*)malloc(sizeof(int) * PUZZLE_WIDTH);
	}

	init(player1.puzzle, 1);

	Sleep(2000);

	init(player2.puzzle, 2);

	player1.x_cursor = new int;
	player1.y_cursor = new int;
	player2.x_cursor = new int;
	player2.y_cursor = new int;
	player1.playerName = new char;
	player2.playerName = new char;

	player1.playerName = initName(1);
	player2.playerName = initName(2);

	fprintf_s(stdout, "%s\n", player1.playerName);
	fprintf_s(stdout, "%s\n", player2.playerName);

	*(player1.y_cursor) = 0;
	*(player1.x_cursor) = 0;
	*(player2.y_cursor) = 0;
	*(player2.x_cursor) = 0;

	player1.hitpoint = 10;
	player2.hitpoint = 50;

	//�\��
	displayAll(player1, player2);

	//�Q�[���X�^�[�g
	while (player1.hitpoint > 0 && player2.hitpoint > 0) {

		pn = 1;

		while (pn == 1)
		{

			cin >> player1.key;

			//x�Ńp�Y�����[�h��
			if (player1.key == 'x')
			{
				break;
			}

			//�J�[�\�����[�h
			cursorMode(player1.x_cursor, player1.y_cursor, player1.key);

			//�\��

			keypad(stdscr, TRUE);
			displayAll(player1, player2);


		}

		while (pn == 1)
		{
			cin >> player1.key;

			//x�Ńp�Y��������������
			if (player1.key == 'x')
			{
				break;
			}

			puzzleMode(player1.puzzle, player1.x_cursor, player1.y_cursor, player1.key);

			//�\��

			displayAll(player1, player2);

		}

		keypad(stdscr, TRUE);

		while (puzzleDropCombo(player1.puzzle))
		{
			attack = 0;
			//�p�Y��������
			attack = deleteMode(player1.puzzle);
			player2.hitpoint -= attack;

			displayAll(player1, player2);

			puzzleDrop(player1.puzzle);

			displayAll(player1, player2);

		}

		if (player2.hitpoint <= 0) break;


		pn = 2;
		while (pn == 2)
		{

			cin >> player2.key;

			//x�Ńp�Y�����[�h��
			if (player2.key == 'x')
			{
				break;
			}

			//�J�[�\�����[�h
			cursorMode(player2.x_cursor, player2.y_cursor, player2.key);

			//�\��
			keypad(stdscr, TRUE);
			displayAll(player1, player2);

		}

		while (pn == 2)
		{
			cin >> player2.key;

			//x�Ńp�Y��������������
			if (player2.key == 'x')
			{
				break;
			}

			puzzleMode(player2.puzzle, player2.x_cursor, player2.y_cursor, player2.key);


			displayAll(player1, player2);

		}


		while (puzzleDropCombo(player2.puzzle))
		{
			attack = 0;
			//�p�Y��������
			attack = deleteMode(player2.puzzle);
			player1.hitpoint -= attack;
			puzzleDrop(player2.puzzle);
			displayAll(player1, player2);
			puzzleDrop(player2.puzzle);
			keypad(stdscr, TRUE);
			displayAll(player1, player2);

		}
	}



	//�t�@�C������
	FILE* fp;
	char s[BUFFSIZE];
	errno_t error;
	error = fopen_s(&fp, "result.txt", "w");
	if (error != 0)
	{
		fprintf_s(stderr, "failed to open");
	}
	else 
	{
		if (pn == 1)
		{
			fprintf(fp, "Winner�@�F�@%s\n", (player1.playerName));
		}
		else if (pn == 2)
		{
			fprintf(fp, "Winner�@�F�@%s\n", (player2.playerName));
		}
		
	}
	return 0;
}

char* initName(int number)
{
	char currentDirectory[BUFFSIZE];
	GetCurrentDirectory(BUFFSIZE, currentDirectory);

	char settingFile[BUFFSIZE];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);

	char section[BUFFSIZE];
	sprintf_s(section, "section");

	char keyWord[BUFFSIZE] = {"a"};
	
	if (number == 1) 
	{
		sprintf_s(keyWord, "player1Name");
	}
	else if (number == 2) 
	{
		sprintf_s(keyWord, "player2Name");
	}
	
	char keyValue[BUFFSIZE];

	GetPrivateProfileString(section, keyWord, "none", keyValue, BUFFSIZE, settingFile);


	fprintf_s(stdout, "%s\n", keyValue);

	return keyValue;
}





//�v���C���[�i���o�[�ƃp�Y���̃}�X���w�肷�邱�ƂŃR�}���h�v�����v�g��̍��W��Ԃ�
int setSquareX(int playerSide, int x) {
	if (playerSide == 0) {
		//Side = 0�Ȃ獶���ɕ\��
		return 15 + x * 6;
	}
	else {
		return 77 + x * 6;
	}
}
int setSquareY(int playerSide, int y) {
	return 14 + y * 3;
}

//HP��\������
void displayHitpoint(int playerSide, int hitpoint) {
	for (int i = 0; i < hitpoint / 2; i++) {
		if (hitpoint > 25) {
			attrset(COLOR_PAIR(4) | A_REVERSE | A_BOLD);
		}
		else {
			attrset(COLOR_PAIR(1) | A_REVERSE | A_BOLD);
		}
		if (playerSide == 0) {
			mvaddstr(11, 4 + i, " ");
		}
		else {
			mvaddstr(11, 115 - i, " ");
		}
	}
	//HP�g
	attrset(COLOR_PAIR(3) | A_BOLD);
	for (int i = 0; i < 52; i++) {
		mvaddstr(10, 3 + i, "=");
		mvaddstr(12, 3 + i, "=");
		mvaddstr(10, 116 - i, "=");
		mvaddstr(12, 116 - i, "=");
	}
	mvaddstr(11, 3, "|");
	mvaddstr(11, 54, "|");
	mvaddstr(11, 116, "|");
	mvaddstr(11, 65, "|");
}

//�h���b�v�̐����������ɁA�w����W�Ƀh���b�v��\������
void displayDrop(int dropNum, int y, int x) {
	const char* drop = "FFFF";

	switch (dropNum) {
	case 1:
		drop = "AAAA";
		attrset(COLOR_PAIR(1) | A_REVERSE | A_BOLD);
		break;
	case 2:
		drop = "BBBB";
		attrset(COLOR_PAIR(2) | A_REVERSE | A_BOLD);
		break;
	case 3:
		drop = "CCCC";
		attrset(COLOR_PAIR(3) | A_REVERSE | A_BOLD);
		break;
	case 4:
		drop = "DDDD";
		attrset(COLOR_PAIR(4) | A_REVERSE | A_BOLD);
		break;
	case 5:
		drop = "EEEE";
		attrset(COLOR_PAIR(5) | A_REVERSE | A_BOLD);
		break;
	default:
		drop = "FFFF";
		attrset(COLOR_PAIR(6) | A_REVERSE | A_BOLD);
		break;
	}
	mvaddstr(y, x, drop);
	mvaddstr(y + 1, x, drop);

}

//�J�[�\���\��
void displayCursor(int y_cursor, int x_cursor)
{
	attrset(COLOR_PAIR(6) | A_REVERSE | A_BOLD);
	mvaddstr(y_cursor - 1, x_cursor - 2, "        ");
	mvaddstr(y_cursor, x_cursor - 2, "  ");
	mvaddstr(y_cursor + 1, x_cursor - 2, "  ");
	mvaddstr(y_cursor, x_cursor + 4, "  ");
	mvaddstr(y_cursor + 1, x_cursor + 4, "  ");
	mvaddstr(y_cursor + 2, x_cursor - 2, "        ");
}

//�L�����\��
void displayAvatar(int playerSide, int hitpoint) {
	attrset(COLOR_PAIR(6) | A_BOLD);
	if (playerSide == 0) {
		if (hitpoint > 25) {
			mvaddstr(4, 20, "�@�@�� �� ��");
			mvaddstr(5, 20, "�@( �L�́M)/");
			mvaddstr(6, 20, " ���@�@  �");
			mvaddstr(7, 20, "�@ (��  �");
			mvaddstr(8, 20, "�@�@ (�m");
		}
		else if (hitpoint > 0) {
			mvaddstr(4, 20, "    �@�@�� �� ��");
			mvaddstr(5, 20, "    �@( �L�́M)/");
			mvaddstr(6, 20, "�@  �Q| ��   �^�R-�A�Q");
			mvaddstr(7, 20, "�@�^�@��----(�Q�Q�Q_�^");
			mvaddstr(8, 20, "�@�P�P�P�P�P�P�P�P�P");
		}
		else if (hitpoint <= 0) {
			mvaddstr(6, 20, "�@�@���܁^�R�Q�Q�Q�Q�Q");
			mvaddstr(7, 20, "�@�^��_/�Q�Q�Q�Q�Q�Q�^");
			mvaddstr(8, 20, "�@�P�P�P�P�P�P�P�P�P");
		}
	}
	else {
		if (hitpoint > 25) {
			mvaddstr(4, 85, ".�@.�_,,_�");
			mvaddstr(5, 85, "�@ (߃�߁@�j");
			mvaddstr(6, 85, "   c/�@  ,��");
			mvaddstr(7, 85, "�@�o ,�A�o");
			mvaddstr(8, 85, " �@ l� �R,)");
		}
		else if (hitpoint > 0) {
			mvaddstr(4, 85, "�@�ȁQ��");
			mvaddstr(5, 85, "�@( ��֥)=�߂�");
			mvaddstr(6, 85, "�@(���@�߂�=��");
			mvaddstr(7, 85, " �@/�@�@)");
			mvaddstr(8, 85, "�@( /�P��");
		}
		else if (hitpoint <= 0) {
			mvaddstr(5, 85, "�V��  �ȁQ��");
			mvaddstr(6, 85, "���܁i �E�ցE�j");
			mvaddstr(7, 85, "�@�M�R_����/�܂�");
			mvaddstr(8, 85, "�@�@ �@ �� ��");
		}
	}
}

//�S�ĕ\��
void displayAll(player player1, player player2) {
	initscr();//�[������J�n
	noecho();
	cbreak();
	curs_set(0);
	start_color();//�J���[�ݒ�

	init_pair(1, COLOR_RED, COLOR_BLACK);	// �F�ԍ��P��ԕ����^���n�Ƃ���
	init_pair(2, COLOR_BLUE, COLOR_BLACK);	// ��
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);	// ��
	init_pair(4, COLOR_GREEN, COLOR_BLACK);	// ��
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);	// ��
	init_pair(6, COLOR_WHITE, COLOR_BLACK);	// ��

	erase();

	//HP�\��
	displayHitpoint(0, player1.hitpoint);
	displayHitpoint(1, player2.hitpoint);

	//�p�Y���\��
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			displayDrop(player1.puzzle[y][x], setSquareY(0, y), setSquareX(0, x));
		}
	}
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			displayDrop(player2.puzzle[y][x], setSquareY(1, y), setSquareX(1, x));
		}
	}

	//�J�[�\���\��
	displayCursor(setSquareY(0, *player1.y_cursor), setSquareX(0, *player1.x_cursor));
	displayCursor(setSquareY(1, *player2.y_cursor), setSquareX(1, *player2.x_cursor));

	//�A�o�^�[�\��
	displayAvatar(0, player1.hitpoint);
	displayAvatar(1, player2.hitpoint);

	//�g���\��
	for (int i = 0; i < 30; i++) {
		attrset(COLOR_PAIR(6) | A_REVERSE | A_BOLD);
		mvaddstr(i, 59, "  ");
	}

	refresh();
}