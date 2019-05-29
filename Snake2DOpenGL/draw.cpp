#include<GL/glut.h>
#include<GL/gl.h>
#include "draw.h"
#include<stdio.h>
#include<time.h>


/*Default movement initially is in the downward direction*/
short int sDirection = NONE;
int posX[MAXLEN]={20},posY[MAXLEN]={20};
int gridX, gridY;
bool food = true;
extern bool GameOver;
extern int score;
/*Declaration for food variables*/
int foodX,foodY;
int csnakel=1;
extern char _score[];

void initGrid(int x, int y)
{
    gridX = x;
    gridY = y;
}

void drawGrid()
{
    for(int x=0;x<gridX;x++)
    {
        for(int y=0;y<gridY;y++)
        {
            if(x == 0 || x == gridX-1 || y == 0 || y == gridY-1)
                continue;
            else
                unitGrid(x,y);
        }
    }

}

void drawBounds()
{
    for(int x=0;x<gridX;x++)
    {
        for(int y=0;y<gridY;y++)
        {
            if(x == 0 || x == gridX-1 || y == 0 || y == gridY-1)
                unitBound(x,y);
            else
                continue;
        }
    }
}

void unitGrid(int x,int y)
{
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINE_LOOP);
            glVertex2d(x,y);
            glVertex2d(x+1,y);
            glVertex2d(x+1,y+1);
            glVertex2d(x,y+1);
        glEnd();

}
void unitBound(int x,int y)
{
     glColor3f(1.0,0.0,0.0);
     glBegin(GL_POLYGON);
            glVertex2d(x,y);
            glVertex2d(x+1,y);
            glVertex2d(x+1,y+1);
            glVertex2d(x,y+1);
     glEnd();
}
void drawSnake()
{
    if(sDirection==NONE)
    {
        return;
    }
    for(int i=csnakel-1;i>0;i--)
    {
        posX[i]=posX[i-1];
        posY[i]=posY[i-1];
    }
    if(sDirection==RIGHT)
        posX[0]++;
    if(sDirection==LEFT)
        posX[0]--;
    if(sDirection==UP)
        posY[0]++;
    if(sDirection==DOWN)
        posY[0]--;
    if(posX[0]==0||posX[0]==gridX-1||posY[0]==0||posY[0]==gridY-1)
        GameOver = true;
    for(int i = 0;i<csnakel;i++)
    {
        if(i==0)
            glColor3f(0.0,0.0,1.0);
        else
            glColor3f(0.0,1.0,0.0);
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);

    }
    for(int j=1;j<csnakel;j++)
    {
        if(posX[0]==posX[j]&&posY[0]==posY[j])
            GameOver=true;
    }
    if(posX[0]==foodX&&posY[0]==foodY)
    {
        if(csnakel<MAXLEN)
            csnakel++;
        food=true;
        score++;
    }

}

void drawFood()
{
     if(sDirection==NONE)
    {
        return;
    }
    glColor3f(1.0,0.0,1.0);
    if(food)
        randompos(foodX,foodY);
    food = false;
    glRectd(foodX,foodY,foodX+1,foodY+1);
}

void randompos(int& x,int& y)
{
    int _min = 1;
    int _maxX = gridX-2, _maxY=gridY-2;
    srand(time(NULL));
    x = _min+rand()%_maxX;
    y = _min+rand()%_maxY;
}

void scoredisp()
{
    glColor3f(1.0,1.0,1.0);
    char scored[]="score: ";
    strcat(scored,_score);
    renderText((COLUMNS-10),(ROWS-1),GLUT_BITMAP_9_BY_15,scored);
}

void renderText(int x, int y, void* font, char* pstring)
{
    char *cptr;
    glRasterPos2i(x,y);
    for(cptr=pstring;*cptr!='\0';cptr++)
    {
        glutBitmapCharacter(font,*cptr);
    }
}
