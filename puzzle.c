#include "gba1.h"
#include "8x8ascii.h"

#define FIELD_WIDTH  6
#define FIELD_HEIGHT  6

void locate(hword, hword);
void print_ascii(hword);
void prints(unsigned char *);
void draw_point(hword, hword, hword);
hword devision(hword,hword);
void cursor(hword);
void initialScreen();
void cursorMode();
void puzzleMode();
int connectPuzzleCount(hword,hword,hword,int);
void clearPuzzle(hword,hword,hword);
void fallPuzzle(hword);
void draw_kaonashi(hword, hword);
void displayHp();

hword lx = 0,ly = 0;
hword cx = 0,cy = 0;
hword cursor_x = 12, cursor_y = 10;
hword mode = 0;
hword purple = BGR(0x0C, 0x00, 0x0C);
hword white = BGR(0x1F, 0x1F, 0x1F);
hword black = BGR(0x00, 0x00, 0x00);
hword skyblue=0x7FE0;
int clearCount = 0;

hword cells[FIELD_HEIGHT][FIELD_WIDTH];
int check[FIELD_HEIGHT][FIELD_WIDTH];

int main(){
  hword *ptr, *ptr2;
  ptr = 0x04000000;
  *ptr = 0x0F03;

  *((unsigned short *)0x04000100) = 0x0000;
	*((unsigned short *)0x04000102) = 0x0080;

  initialScreen();

  while(1){
    ptr2 = 0x04000130;
    hword key = (~(*ptr2))&0x0001;

    if(key == KEY_A){
      break;
    }
  }
  hword x=0,y=0;
  for(y = 0; y < 160; y++){
    for(x = 0; x < 240; x++){
      draw_point(x,y,0x001F);
    }
  }

  hword kx = 120;
  hword ky = 20;
  draw_kaonashi(kx,ky);
  displayHp();

  for(y = 0; y < FIELD_HEIGHT; y++){
    for(x = 0; x < FIELD_WIDTH; x++){

      if(*((unsigned short *)0x04000100) >= 0xFFFF){
        *((unsigned short *)0x04000100) = 0x0000;
      }

      hword rand = *((unsigned short *)0x04000100);
      int i;
      for(i = 0; i < 101; i++){}
      switch(devision(rand,5)){
        case 0:
         cells[y][x] = 3;
         break;

        case 1:
          cells[y][x] = 4;
          break;

        case 2:
          cells[y][x] = 10;
          break;

        case 3:
          cells[y][x] = 5;
          break;

        case 4:
          cells[y][x] = 9;
          break;
      }

      lx = 12 + x;
      ly = 10 + y;
      locate(lx, ly);
      print_ascii(cells[y][x]);
    }
  }

	*((unsigned short *)0x04000102) = 0x0000;

  while(1){
    ptr2 = 0x04000130;
    hword key = (~(*ptr2))&0x00FF;
    switch(key){
      case KEY_A:
        mode = 1;
        break;

      case KEY_B:
        mode = 2;
        break;

      default:
        mode = 0;
        break;
    }

    switch(mode){
      case 1:
        puzzleMode();
        break;

      case 2:
        cursorMode();
        break;
    }

    if(clearCount >= 100){
      break;
    }
  }

  for(y = 0; y < 160; y++){
    for(x = 0; x < 240; x++){
      draw_point(x,y,black);
    }
  }
  lx = 12;
  ly = 10;
  locate(lx,ly);
  prints("finish");


  return 0;
}

void draw_point(hword x,hword y,hword color){
  hword *ptr;
	ptr = 0x06000000;
  ptr=ptr+240*y+x;
  *ptr=color;
}

void locate(hword x, hword y){
  cx = x*8;
  cy = y*8;
}

void print_ascii(hword ascii_num){
  int i,j;
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      hword bit = 1<<(7-j);
      if((char8x8[ascii_num][i]&bit)==bit){
        draw_point(cx, cy, white);
      }else{
        draw_point(cx,cy,black);
      }
      cx++;
    }
      cy++;
      cx = cx - 8;
  }
}

void prints(unsigned char *str){


  while(*str != 0){
    print_ascii(*str);
	  str++;
	  lx++;
	  locate(lx,ly);
	}
}

hword devision(hword n,hword m){
  while(n >= m){
    n = n-m;
  }
  return n;
}

void cursor(hword color){
  locate(cursor_x, cursor_y);
  cy = cy + 7;
  int i;
  for(i = 0; i<8; i++){
    draw_point(cx,cy,color);
    cx++;
  }
}

void initialScreen(){
  lx = 0;
  ly = 0;
  locate(lx,ly);
  prints("This is the Puzzle game");

  lx = 0;
  ly = 2;
  locate(lx,ly);
  prints("1. Push B, CURSOR mode and");

  lx = 0;
  ly = 3;
  locate(lx,ly);
  prints("push ARROW KEYs, cursor move");

  lx = 0;
  ly = 5;
  locate(lx,ly);
  prints("2. Puzh A, PUZZLE mode and");

  lx = 0;
  ly = 6;
  locate(lx,ly);
  prints("push ARROE KEYs, puzzle move");
  lx = 0;
  ly = 7;
  locate(lx,ly);
  prints("PUZZLE mode is few seconds");

  lx = 0;
  ly = 9;
  locate(lx,ly);
  prints("3. back 1");

  lx = 5;
  ly = 11;
  locate(lx,ly);
  prints("Please beat KAONASHI");

  hword kx=120;
  hword ky=104;
  draw_kaonashi(kx,ky);

  lx = 5;
  ly = 16;
  locate(lx,ly);
  prints("Let`s start! Push A!");
}

void cursorMode(){
  hword *ptr;
  hword dx = 0, dy = 0;
  hword k_pre = 0;
  hword cursor_px = 0, cursor_py = 0;
  cursor(purple);

  while(mode == 2){
		ptr = 0x04000130;
		hword k = (~(*ptr))&0x00FF;

    if(k_pre == 0x0000 && k != 0x0000){
        hword cursor_px = cursor_x, cursor_py = cursor_y;
        switch(k){
          case KEY_UP:
            if(cursor_y >10){
              cursor_y--;
            }
            break;

          case  KEY_LEFT:
            if(cursor_x > 12){
              cursor_x--;
            }
            break;

          case KEY_RIGHT:
            if(cursor_x < 17){
              cursor_x++;
            }
            break;

          case  KEY_DOWN:
            if(cursor_y < 15){
              cursor_y++;
            }
            break;

          case KEY_A:
            mode = 1;
            break;
        }

        locate(cursor_px, cursor_py);
        print_ascii(cells[cursor_py-10][cursor_px-12]);
        cursor(purple);
        cursor_px = cursor_x, cursor_py = cursor_y;
      }

      k_pre = k;
  }
}

void draw_kaonashi(hword kx,hword ky){
  int x;
  int y=ky;
  int i;
  hword m=0x7C1F;

  for(x=kx-2;x<=kx+2;x=x+1){
    draw_point(x,y-1,black);
  }

  for(i=1;i<=4;i=i+1){
    for(x=kx-i-2;x<=kx+i+2;x=x+1){
      if(x<=kx-i-1||x>=kx+i+1){
        draw_point(x,y,black);
      }else{
        draw_point(x,y,white);
      }
    }
    y=y+1;
  }

  for(i=0;i<7;i=i+1){
    for(x=kx-7;x<=kx+7;x=x+1){
      if(i==0&&(x==kx-3||x==kx+3)){
        draw_point(x,y,m);
      }else if((i==2||i==3)&&((x>=kx-4&&x<=kx-2)||(x>=kx+2&&x<=kx+4))){
        draw_point(x,y,black);
      }else if((i==5||i==6)&&(x==kx-3||x==kx+3)){
        draw_point(x,y,m);
      }else if(x<=kx-6||x>=kx+6){
        draw_point(x,y,black);
      }else{
        draw_point(x,y,white);
      }
    }
    y=y+1;
  }

  for(i=0;i<2;i=i+1){
    for(x=kx-7;x<=kx+7;x=x+1){
      if(i==1&&(x>=kx-2&&x<=kx+2)){
        draw_point(x,y,black);
      }else if(x<=kx-5||x>=kx+5){
        draw_point(x,y,black);
      }else{
        draw_point(x,y,white);
      }
    }
    y=y+1;
  }

  for(i=3;i>=1;i=i-1){
    for(x=kx-7;x<=kx+7;x=x+1){
      if(i==3&&(x>=kx-2&&x<=kx+2)){
        draw_point(x,y,black);
      }else if(x<=kx-i-1||x>=kx+i+1){
        draw_point(x,y,black);
      }else{
        draw_point(x,y,white);
      }
    }
    y=y+1;
  }

  for(i=0;i<19;i=i+1){
    for(x=kx-7;x<=kx+7;x=x+1){
      draw_point(x,y,black);
    }
    y=y+1;
  }
}

void displayHp(){
  hword hp = (100 - (hword)clearCount)/2;
  if(hp < 0 || hp > 100){
    hp = 0;
  }
  hword x,y;
  for(y = 64; y <= 68; y++){
    for(x = 94; x <= 146; x++){
      if(((y != 64) && (y!= 68) && (x != 94) && (x != 146) && (95+hp < x)) ){
        draw_point(x,y,black);
      }else{
        draw_point(x,y, white);
      }
    }
  }
}
