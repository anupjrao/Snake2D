#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/gl.h>
#include "draw.h"
#include<conio.h>
#include<stdio.h>
#include<ctime>


#define FPS 10

long int score = 0;
bool GameOver = false;
bool inputReady = true;
char text[] = "Game over, score is: ";
char _score[10];
char pname[] = "Snake2D ";
char pcred[] = "Project by: Anup J Rao(1GA16CS025)";
char pstart[] = "Press a D-pad key to start";


extern int sDirection;
/*Callback timer function */

void timercb(int);

/*Callback for window "Test Game" */

void display_cbtg();

/*Callback for window "Test Game" */

void reshape_cbtg(int,int);

/*Callback to keyboard event handling */

void keyboard_ev_cb(int,int,int);

/*Initialization function*/
void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    initGrid(COLUMNS,ROWS);
}
/*Main function*/

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500,500);
    glutCreateWindow("Snake 2D");
    glutInitDisplayMode(GL_RGB | GLUT_DOUBLE);
    glutDisplayFunc(display_cbtg);
    glutReshapeFunc(reshape_cbtg);
    glutTimerFunc(0,timercb,0);
    glutSpecialFunc(keyboard_ev_cb);
    init();
    glutMainLoop();
    return 0;
}

void display_cbtg()
{
    glClear(GL_COLOR_BUFFER_BIT);
    /*Note to self:Only enable during development, grids for reference*/
    //drawGrid();
    drawBounds();
    if(sDirection==NONE)
    {
        glColor3f(1.0,1.0,1.0);
        renderText(15,30,GLUT_BITMAP_9_BY_15,pname);
        renderText(7,20,GLUT_BITMAP_9_BY_15,pcred);
        renderText(10,15,GLUT_BITMAP_8_BY_13,pstart);
    }
    //Going to call a function to render the snake and food from draw
    drawSnake();
    drawFood();
    scoredisp();
    int ctime1 = time(NULL);
    if(time(NULL)>=ctime1+0) // Added small delay to user input to prevent the simultaneous input bug.
    {
        inputReady=true;
    }
    glutSwapBuffers();
    itoa(score,_score,10);
    if(GameOver)
    {
        strcat(text,_score);
        MessageBox(NULL,text,"Game Over",0);
        exit(0);
    }
}

void reshape_cbtg(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,COLUMNS,0,ROWS,-1,1);
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_MODELVIEW);
}

void timercb(int x)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timercb,0);
}

void keyboard_ev_cb(int key, int,int)
{
    if(inputReady==true)
    switch(key)
        {
            case GLUT_KEY_UP:
                            if(sDirection!=DOWN) sDirection = UP;
                            inputReady=false;
                            break;
            case GLUT_KEY_DOWN:
                            if(sDirection!=UP) sDirection = DOWN;
                            inputReady=false;
                            break;
            case GLUT_KEY_RIGHT:
                            if(sDirection!=LEFT) sDirection = RIGHT;
                            inputReady=false;
                            break;
            case GLUT_KEY_LEFT:
                            if(sDirection!=RIGHT) sDirection = LEFT;
                            inputReady=false;
                            break;
        }
}
