#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>

static int x;
static float y;

void robot()
{
    glPushMatrix();
    glScaled(.5,.5,0);
    glTranslated(x,y+20,0);
    //leg1
    glBegin(GL_POLYGON);
    glColor3ub(50,50,50);
    glVertex2d(0,0);
    glVertex2d(0,30);
    glVertex2d(5,30);
    glVertex2d(5,0);
    glEnd();
    //leg2
    glBegin(GL_POLYGON);
    glColor3ub(50,50,50);
    glVertex2d(20,0);
    glVertex2d(20,30);
    glVertex2d(25,30);
    glVertex2d(25,0);
    glEnd();
    //body
    glBegin(GL_POLYGON);
    glColor3ub(40,40,40);
    glVertex2d(0,30);
    glVertex2d(0,40);
    glVertex2d(25,40);
    glVertex2d(25,30);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(90,90,90);
    glVertex2d(5,40);
    glVertex2d(5,60);
    glVertex2d(20,60);
    glVertex2d(20,40);
    glEnd();
    //solder
    glBegin(GL_POLYGON);
    glColor3ub(40,40,40);
    glVertex2d(0,60);
    glVertex2d(0,70);
    glVertex2d(25,70);
    glVertex2d(25,60);
    glEnd();
    //neck
    glBegin(GL_POLYGON);
    glColor3ub(70,70,70);
    glVertex2d(10,70);
    glVertex2d(10,75);
    glVertex2d(15,75);
    glVertex2d(15,70);
    glEnd();
    //head
    glBegin(GL_POLYGON);
    glColor3ub(100,100,100);
    glVertex2d(5,75);
    glVertex2d(5,90);
    glVertex2d(20,90);
    glVertex2d(20,75);
    glEnd();
    //eye
    glBegin(GL_POLYGON);
    glColor3ub(255,255,255);
    glVertex2d(8,84);
    glVertex2d(8,87);
    glVertex2d(11,87);
    glVertex2d(11,84);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255,255,255);
    glVertex2d(14,84);
    glVertex2d(14,87);
    glVertex2d(17,87);
    glVertex2d(17,84);
    glEnd();
    //mouth
    glBegin(GL_POLYGON);
    glColor3ub(255,255,255);
    glVertex2d(8,78);
    glVertex2d(8,81);
    glVertex2d(17,81);
    glVertex2d(17,78);
    glEnd();
    //LHand
    glPushMatrix();
    glTranslated(-5,0,0);
    glBegin(GL_POLYGON);
    glColor3ub(0,100,10);
    glVertex2d(0,40);
    glVertex2d(0,70);
    glVertex2d(5,70);
    glVertex2d(5,40);
    glEnd();
    glPopMatrix();
    //RHand
    glPushMatrix();
    glTranslated(5,0,0);
    glBegin(GL_POLYGON);
    glColor3ub(0,100,10);
    glVertex2d(20,40);
    glVertex2d(20,70);
    glVertex2d(25,70);
    glVertex2d(25,40);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    x++;
    y=10+sinf(x/10.0)*20;

    if(x>140)
        x=0;

    Sleep(100);
    glBegin(GL_POLYGON);
    glColor3ub(50,200,50);
    glVertex2d(0,0);
    glVertex2d(0,20);
    glVertex2d(800,20);
    glVertex2d(800,0);
    glEnd();
    robot();
    float j;
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<140; i++)
    {
        glColor3ub(255,0,0);
            glVertex2d(i,j+50);

        j=10*sinf(i/20.0)*2;
    }
    glEnd();
    //glutPostRedisplay();
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

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);

    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("CSE-422_G_181-15-10973_Lab Final- Draw a Robot.");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glOrtho(0, 140, 0, 100, 0, 100.0);
    glutMainLoop();

    return EXIT_SUCCESS;
}
