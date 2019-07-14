#pragma once

#define PUZZLE_WIDTH 5
#define PUZZLE_HEIGHT 5



//mainで使う関数
void init(int** puzzle);       //パズルの初期化
void getKey(int* key);         //キー入力の取得
void puzzleDrop(int** puzzle);    //消えた分のパズルを上から落とす
bool puzzleDropCombo(int** puzzle);   //落ち込んがあるか判定
void attackPlayer(int combo);         //相手の体力を減らす
void cursorMode(int* x_cursor, int* y_cursor, char key);      //カーソールモード
void puzzleMode(int** puzzle, int* x_cursor, int* y_cursor, char key);   //パズルモード
int  deleteMode(int** puzzle);     //パズルを消す

void puzzleDelete(int** puzzle, int puzzle_type, int x, int y);
int  connectPuzzleCount(int** puzzle, int** checked_puzzle, int puzzle_type, int x, int y, int count);