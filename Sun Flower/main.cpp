#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>
#define nFlowers 100;
int random(int mn, int mx){return ((rand()%(mx-mn+1)) + mn);}

struct flowerPosition
{
    int x;
    int y;
    int sz;
    int r;
    int g;
    int b;
}flowers[100];
//static float flowerX;
static float flowerY=0;

void positionsGenerate()
{
    int i;
    for(i=0; i<100; i++)
    {
        flowers[i].x=i*10;
        flowers[i].y=(i%2)*10;
        flowers[i].sz=random(0,10);
    }
    return;
}

void drawFiledCircle(float cx, float cy, float r, int num_segments, int red, int green, int blue)
{
    glBegin(GL_POLYGON);
    glColor3ub(red,green,blue);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void sunFlower()
{
    glPushMatrix();
    glTranslated(100,100,0);
    glRotated(10,0,0,1);
    glRotated(sinf(flowerY)*10.0,0,0,1);
    glBegin(GL_POLYGON);
    glColor3ub(0,140,0);
    glVertex2d(-1,0);
    glVertex2d(-1,40);
    glVertex2d(1,40);
    glVertex2d(1,0);
    glEnd();
    glTranslated(0,50,0);
    glColor3ub(250,250,0);
    glBegin(GL_POLYGON);
    glVertex2d(0,0);
    glVertex2d(-5,15);
    glVertex2d(0,20);
    glVertex2d(+5,15);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(0,0);
    glVertex2d(-5,-15);
    glVertex2d(0,-20);
    glVertex2d(+5,-15);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(0,0);
    glVertex2d(-15,-5);
    glVertex2d(-20,0);
    glVertex2d(-15,5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(0,0);
    glVertex2d(15,-5);
    glVertex2d(20,0);
    glVertex2d(15,5);
    glEnd();

    glPushMatrix();
    glRotated(45,0,0,1);
    glColor3ub(255,150,100);
    glBegin(GL_POLYGON);
    glVertex2d(0,0);
    glVertex2d(-5,15);
    glVertex2d(0,20);
    glVertex2d(+5,15);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(0,0);
    glVertex2d(-5,-15);
    glVertex2d(0,-20);
    glVertex2d(+5,-15);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(0,0);
    glVertex2d(-15,-5);
    glVertex2d(-20,0);
    glVertex2d(-15,5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2d(0,0);
    glVertex2d(15,-5);
    glVertex2d(20,0);
    glVertex2d(15,5);
    glEnd();
    glPopMatrix();
    drawFiledCircle(0,0,4,50,255,255,255);
    glPopMatrix();
}

void backGround()
{
    glBegin(GL_POLYGON);
    glColor3ub(100,200,255);
    glVertex2d(0,20);
    glVertex2d(0,100);
    glVertex2d(800,100);
    glVertex2d(800,20);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(50,200,50);
    glVertex2d(0,0);
    glVertex2d(0,20);
    glVertex2d(800,20);
    glVertex2d(800,0);
    glEnd();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    backGround();
    for(int i=0; i<20; i++){
        glPushMatrix();
        glTranslated(flowers[i].x,flowers[i].y,0);
        glScaled(.5,.5,0);
        sunFlower();
        glPopMatrix();
    }
    glutPostRedisplay();
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 1:
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    if(flowerY>100)
        flowerY=0;
    flowerY+=.001;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    positionsGenerate();
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Sun Flowers");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glOrtho(0, 140, 0, 100, 0, 100.0);
    glutMainLoop();

    return EXIT_SUCCESS;
}
