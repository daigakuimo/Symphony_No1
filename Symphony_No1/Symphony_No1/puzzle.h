#pragma once

#define PUZZLE_WIDTH 5
#define PUZZLE_HEIGHT 5



//main�Ŏg���֐�
void init(int** puzzle);       //�p�Y���̏�����
void getKey(int* key);         //�L�[���͂̎擾
void puzzleDrop(int** puzzle);    //���������̃p�Y�����ォ�痎�Ƃ�
bool puzzleDropCombo(int** puzzle);   //�������񂪂��邩����
void attackPlayer(int combo);         //����̗̑͂����炷
void cursorMode(int* x_cursor, int* y_cursor, char key);      //�J�[�\�[�����[�h
void puzzleMode(int** puzzle, int* x_cursor, int* y_cursor, char key);   //�p�Y�����[�h
int  deleteMode(int** puzzle);     //�p�Y��������

void puzzleDelete(int** puzzle, int puzzle_type, int x, int y);
int  connectPuzzleCount(int** puzzle, int** checked_puzzle, int puzzle_type, int x, int y, int count);