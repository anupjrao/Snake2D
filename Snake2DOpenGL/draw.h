#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

/*Macro subs to set directions*/
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define NONE 0
#define COLUMNS 40
#define ROWS 40

/*Maximum length*/
#define MAXLEN 1521

void initGrid(int, int);
void drawGrid();
void unitGrid(int,int);
void drawSnake();
void drawBounds();
void unitBound(int,int);
void drawFood();
void randompos(int&,int&);
void scoredisp();
void renderText(int x, int y,void* font, char* string);

#endif // DRAW_H_INCLUDED
