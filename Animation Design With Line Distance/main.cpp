#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define nNode 300
#define windowX 800
#define windowY 500
#define windowZ 500

int speed = 100;
int random(int mn, int mx){return (rand()%(mx+1-mn))+mn;}
int negPosRandom()
{
    if(random(1,2)==1)
        return -1;
    else
        return 1;
}
struct node
{
    float x;
    float y;
    float r,g,b;
    float xv, yv;
}nodes[nNode];

void generateNode()
{
    for(int i=0; i<nNode; i++)
    {
        nodes[i].x=random(0,windowX);
        nodes[i].y=random(0,windowY);
        nodes[i].xv=(random(0,speed)/300.0)*negPosRandom();
        nodes[i].yv=(random(0,speed)/300.0)*negPosRandom();
        nodes[i].r=rand()%255;
        nodes[i].g=rand()%255;
        nodes[i].b=rand()%255;
    }
}

void nodesMove()
{
    for(int i=0; i<nNode; i++)
    {
        nodes[i].x+=nodes[i].xv;
        nodes[i].y+=nodes[i].yv;
    }
}

void nodesMoveChange()
{
    for(int i=0; i<nNode; i++)
    {
        if(nodes[i].x>=windowX)
            nodes[i].xv*=-1;
        if(nodes[i].y>=windowY)
            nodes[i].yv*=-1;
        if(nodes[i].x<=0)
            nodes[i].xv*=-1;
        if(nodes[i].y<=0)
            nodes[i].yv*=-1;
    }
}

int getDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}

void nodesShow()
{

    for(int i=0; i<nNode; i++)
    {
        for(int j=0; j<nNode; j++){
            int distance = getDistance(nodes[i].x,nodes[i].y,nodes[j].x,nodes[j].y);
            if(distance<64){
                //glColor3ub(256-(distance*4),256-(distance*4),256-(distance*4));
                glBegin(GL_LINES);
                glColor3ub(nodes[j].r,nodes[j].g,nodes[j].b);
                glVertex2d(nodes[i].x, nodes[i].y);
                glVertex2d(nodes[j].x, nodes[j].y);
                glEnd();
            }
        }
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    nodesShow();
    glutPostRedisplay();
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':

            break;

        case '+':

            break;

        case '-':

            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    nodesMove();
    nodesMoveChange();
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(windowX,windowY);
    glutInitWindowPosition(100,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Line Design");
    generateNode();
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0,0,0,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glOrtho(0, windowX, 0, windowY, 0, windowZ);
    glutMainLoop();

    return EXIT_SUCCESS;
}
