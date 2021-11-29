#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>
#define nHumans 5
#define orthoX 200
#define orthoY 150
int random(int mn, int mx){return ((rand()%(mx-mn+1)) + mn);}

static float movementX[nHumans];
void generateHuman()
{
    for(int i=0; i<nHumans; i++)
        movementX[i]=-random(0,orthoX/3);
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

void backGround()
{
    glBegin(GL_POLYGON);
    glColor3ub(100,200,255);
    glVertex2d(0,20);
    glVertex2d(0,orthoY);
    glVertex2d(orthoX,orthoY);
    glVertex2d(orthoX,20);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(50,200,50);
    glVertex2d(0,0);
    glVertex2d(0,20);
    glVertex2d(orthoX,20);
    glVertex2d(orthoX,0);
    glEnd();
}

humanWalk(float movementX)
{
    glPushMatrix();
    glTranslated(movementX,cos(2*movementX)/3.0+12,0);
    glScaled(.8,.8,0);
    //hand1
    glPushMatrix();
    glTranslated(-1,11.5,0);
    glRotated(-sin(movementX)*10,0,0,1);
    glBegin(GL_POLYGON);
    glColor3ub(70,0,70);
    glVertex3f(0,-12,0);
    glVertex3f(-1,0,0);
    glVertex3f(-.5,1,0);
    glVertex3f(.5,1,0);
    glVertex3f(1,0,0);
    glVertex3f(.5,-12,0);
    glEnd();
    glPopMatrix();
    //leg1
    glPushMatrix();
    glTranslated(0,cos(movementX)+3,0);
    glRotated(sin(movementX)*10,0,0,1);
    glBegin(GL_POLYGON);
    glColor3ub(70,0,70);
    glVertex3f(-1,-14,0);
    glVertex3f(-1,0,0);
    glVertex3f(-.5,0,0);
    glVertex3f(1,-14,0);
    glEnd();
    glPopMatrix();
    //leg2
    glPushMatrix();
    glTranslated(0,-cos(movementX)+3,0);
    glRotated(-sin(movementX)*10,0,0,1);
    glBegin(GL_POLYGON);
    glColor3ub(190,0,190);
    glVertex3f(-1,-14,0);
    glVertex3f(-1,0,0);
    glVertex3f(-.5,0,0);
    glVertex3f(1,-14,0);
    glEnd();
    glPopMatrix();
    //neck
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(200,0,200);
    glVertex3f(-2,13,0);
    glVertex3f(-1.5,13.5,0);
    glVertex3f(0,12,0);
    glVertex3f(1,10,0);
    glEnd();
    glPopMatrix();
    //body
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(110,0,110);
    glVertex3f(-1,2,0);
    glVertex3f(-2,13,0);
    glVertex3f(1,10,0);
    glVertex3f(0,2,0);
    glEnd();
    glPopMatrix();
    //hand2
    glPushMatrix();
    glTranslated(-1,11.5,0);
    glRotated(sin(movementX)*10,0,0,1);
    glBegin(GL_POLYGON);
    glColor3ub(200,0,200);
    glVertex3f(0,-12,0);
    glVertex3f(-1,0,0);
    glVertex3f(-.5,1,0);
    glVertex3f(.5,1,0);
    glVertex3f(1,0,0);
    glVertex3f(.5,-12,0);
    glEnd();
    glPopMatrix();
    //Head
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(255,255,155);
    glVertex3f(-1.5,13,0);
    glVertex3f(-2,16,0);
    glVertex3f(0,16,0);
    glVertex3f(-.3,12,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(200,200,100);
    glVertex3f(-1.5,13,0);
    glColor3ub(100,100,50);
    glVertex3f(-1.5,14,0);
    glVertex3f(-.2,13,0);
    glColor3ub(200,200,100);
    glVertex3f(-.3,12,0);
    glEnd();
    glPopMatrix();
    //hair
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(10,25,15);
    glVertex3f(-1.5,13,0);
    glVertex3f(-2,16,0);
    glVertex3f(-1,16,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(10,25,15);
    glVertex3f(-2.5,16,0);
    glVertex3f(-2,17,0);
    glVertex3f(0,17,0);
    glVertex3f(0,16,0);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    backGround();
    glPushMatrix();
    glScaled(3,3,0);
    for(int i=0; i<30; i++)
        humanWalk(movementX[i]);
    glPopMatrix();

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
    for(int i=0; i<100; i++){
    if(movementX[i]>orthoX/3+10)
        movementX[i]=0;
    movementX[i]+=.01;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize (orthoX*5, orthoY*4);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Sun Flowers");
    generateHuman();
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glOrtho(0, orthoX, 0, orthoY, -10.0, 10.0);
    glutMainLoop();

    return EXIT_SUCCESS;
}
