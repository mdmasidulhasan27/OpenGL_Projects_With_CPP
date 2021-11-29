#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#define nNode 50
#define windowX 800
#define windowY 500
#define windowZ 500

int speed = 4;
int random(int mn, int mx){return (rand()%(mx+1-mn))+mn;}
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
        nodes[i].xv=random(0,speed)/30.0;
        nodes[i].yv=random(0,speed)/30.0;
        nodes[i].r=random(0,255);
        nodes[i].g=random(0,255);
        nodes[i].b=random(0,255);
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

void nodesShow()
{
    glBegin(GL_POLYGON);
    for(int i=0; i<nNode; i++)
    {
        glColor3ub(nodes[i].r,nodes[i].g,nodes[i].b);
        glVertex2d(nodes[i].x, nodes[i].y);
    }
    glEnd();
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
