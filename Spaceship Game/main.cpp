#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#define M_PI 3.14159265358979323846

void initWindow(void);

float angle = 0.0;
int left, right;
int leftTime, rightTime;
int thrust, thrustTime;
float x = 20, y = 20, xv, yv, v;
int shield = 0, joyShield = 0, cursor = 1;
int lastTime;
int paused = 0;
int resuming = 1;
int originalWindow = 0, currentWindow;

typedef struct
{
    int inuse;

    float x;
    float y;

    float v;
    float xv;
    float yv;

    int expire;
} Bullet;

#define BULLETS 100

Bullet bulletJet1[BULLETS];
Bullet bulletJet2[BULLETS];

int allocBulletJet1(void)
{
    int i;

    for (i=0; i<BULLETS; i++)
    {
        if (!bulletJet1[i].inuse)
        {
            return i;
        }
    }
    return -1;
}

void initBulletJet1(int i, int time)
{
    float c = cos(angle*M_PI/180.0);
    float s = sin(angle*M_PI/180.0);

    bulletJet1[i].inuse = 1;
    bulletJet1[i].x = x + 3.5 * c;
    bulletJet1[i].y = y + 3.5 * s;
    bulletJet1[i].v = 0.025;
    bulletJet1[i].xv = xv + c * bulletJet1[i].v;
    bulletJet1[i].yv = yv + s * bulletJet1[i].v;
    bulletJet1[i].expire = time + 600;
}

void advanceBulletsJet1(int delta, int time)
{
    int i;

    for (i=0; i<BULLETS; i++)
    {
        if (bulletJet1[i].inuse)
        {
            float x, y;

            if (time > bulletJet1[i].expire)
            {
                bulletJet1[i].inuse = 0;
                continue;
            }
            x = bulletJet1[i].x + bulletJet1[i].xv * delta;
            y = bulletJet1[i].y + bulletJet1[i].yv * delta;
            x = x / 40.0;
            bulletJet1[i].x = (x - floor(x))*40.0;
            y = y / 40.0;
            bulletJet1[i].y = (y - floor(y))*40.0;
        }
    }

}

void shotBulletJet1(void)
{
    int entry;

    entry = allocBulletJet1();
    if (entry >= 0)
    {
        initBulletJet1(entry, glutGet(GLUT_ELAPSED_TIME));
    }
}

void drawBulletsJet1(void)
{
    int i;

    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 1.0);
    for (i=0; i<BULLETS; i++)
    {
        if (bulletJet1[i].inuse)
        {
            glVertex2f(bulletJet1[i].x, bulletJet1[i].y);
        }
    }

    glEnd();
}

int allocBulletJet2(void)
{
    int i;

    for (i=0; i<BULLETS; i++)
    {
        if (!bulletJet2[i].inuse)
        {
            return i;
        }
    }
    return -1;
}

void initBulletJet2(int i, int time)
{
    float c = cos(angle*M_PI/180.0);
    float s = sin(angle*M_PI/180.0);

    bulletJet2[i].inuse = 1;
    bulletJet2[i].x = x + 3.5 * c;
    bulletJet2[i].y = y + 3.5 * s;
    bulletJet2[i].v = 0.025;
    bulletJet2[i].xv = xv + c * bulletJet2[i].v;
    bulletJet2[i].yv = yv + s * bulletJet2[i].v;
    bulletJet2[i].expire = time + 600;
}

void advanceBulletsJet2(int delta, int time)
{
    int i;

    for (i=0; i<BULLETS; i++)
    {
        if (bulletJet2[i].inuse)
        {
            float x, y;
            if (time > bulletJet2[i].expire)
            {
                bulletJet2[i].inuse = 0;
                continue;
            }
            x = bulletJet2[i].x + bulletJet2[i].xv * delta;
            y = bulletJet2[i].y + bulletJet2[i].yv * delta;
            x = x / 40.0;
            bulletJet2[i].x = (x - floor(x))*40.0;
            y = y / 40.0;
            bulletJet2[i].y = (y - floor(y))*40.0;
        }
    }
}

void shotBulletJet2(void)
{
    int entry;

    entry = allocBulletJet2();
    if (entry >= 0)
    {
        initBulletJet2(entry, glutGet(GLUT_ELAPSED_TIME));
    }
}

void drawBulletsJet2(void)
{
    int i;
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 1.0);
    for (i=0; i<BULLETS; i++)
    {
        if (bulletJet2[i].inuse)
        {
            glVertex2f(bulletJet2[i].x, bulletJet2[i].y);
        }
    }
    glEnd();
}

void drawshield(void)
{
    float rad;
    glColor3f(0.6, 1.5, 0.6);
    glBegin(GL_LINE_LOOP);
    for (rad=0.0; rad<11.0; rad += 1.0)
    {
        glVertex2f(3.75 * cos(2*rad/M_PI)+0.4, 3.0 * sin(2*rad/M_PI));
    }
    glEnd();
}

void text(int x, int y, float r, float g, float b, int font, char *string)
{
    glColor3f( r, g, b );
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
    }
}

void drawJet(float angle)
{


    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    if (thrust)
    {
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_STRIP);
        glVertex2f(-0.75, -0.5);
        glVertex2f(-1.75, 0);
        glVertex2f(-0.75, 0.5);
        glEnd();
    }
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(3.5,0.0);
    glVertex2f(0.5, -0.25);
    glVertex2f(-1.0, -1.0);
    glVertex2f(-0.5, 0.0);
    glVertex2f(-1.0, 1.0);
    glVertex2f(0.5,0.25);
    glVertex2f(3.5, 0.0);
    glEnd();
    if (shield)
    {
        drawshield();
    }
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawJet(angle);
    drawBulletsJet1();
    glutSwapBuffers();
}

void idle(void)
{
    int time, delta;

    time = glutGet(GLUT_ELAPSED_TIME);
    if (resuming)
    {
        lastTime = time;
        resuming = 0;
    }
    if (left)
    {
        delta = time - leftTime;
        angle = angle + delta * 0.4;
        leftTime = time;
    }
    if (right)
    {
        delta = time - rightTime;
        angle = angle - delta * 0.4;
        rightTime = time;
    }
    if (thrust)
    {
        delta = time - thrustTime;
        v = delta * 0.00004;
        xv = xv + cos(angle*M_PI/180.0) * v;
        yv = yv + sin(angle*M_PI/180.0) * v;
        thrustTime = time;
    }

    delta = time - lastTime;
    x = x + xv * delta;
    y = y + yv * delta;
    x = x / 40.0;
    x = (x - floor(x))*40.0;
    y = y / 40.0;
    y = (y - floor(y))*40.0;
    lastTime = time;
    advanceBulletsJet1(delta, time);
    glutPostWindowRedisplay(currentWindow);
}

void visible(int vis)
{
    if (vis == GLUT_VISIBLE)
    {
        if (!paused)
        {
            glutIdleFunc(idle);
        }
    }
    else
    {
        glutIdleFunc(NULL);
    }
}


void key(unsigned char key, int px, int py)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;

    case 'S':
    case 's':
        shield = 1;
        break;
    case 'C':
    case 'c':
        cursor = !cursor;
        glutSetCursor(
            cursor ? GLUT_CURSOR_INHERIT : GLUT_CURSOR_NONE);
        break;
    case 'z':
    case 'Z':
        x = 20;
        y = 20;
        xv = 0;
        yv = 0;
        break;
    case 'f':
    case 'F':
        glutGameModeString("400x300:16@60");
        glutEnterGameMode();
        initWindow();
        break;

    case 'l':
        if (originalWindow != 0 && currentWindow != originalWindow)
        {
            glutLeaveGameMode();
            currentWindow = originalWindow;
        }
        break;
    case 'P':
    case 'p':
        paused = !paused;
        if (paused)
        {
            glutIdleFunc(NULL);
        }
        else
        {
            glutIdleFunc(idle);
            resuming = 1;
        }
        break;
    case ' ':
        shotBulletJet1();
        break;
    }
}


void keyup(unsigned char key, int x, int y)
{
    switch (key)
    {

    case 'S':
    case 's':
        shield = 0;
        break;
    }
}


void special(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_UP:
        thrust = 1;
        thrustTime = glutGet(GLUT_ELAPSED_TIME);
        break;

    case GLUT_KEY_LEFT:
        left = 1;
        leftTime = glutGet(GLUT_ELAPSED_TIME);
        printf("%d\n",leftTime);
        break;
    case GLUT_KEY_RIGHT:
        right = 1;
        rightTime = glutGet(GLUT_ELAPSED_TIME);
        break;
    }
}


void specialup(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        thrust = 0;
        break;
    case GLUT_KEY_LEFT:
        left = 0;
        break;
    case GLUT_KEY_RIGHT:
        right = 0;
        break;
    }
}


void initWindow(void)
{
    glutIgnoreKeyRepeat(1);

    glutDisplayFunc(display);
    glutVisibilityFunc(visible);
    glutKeyboardFunc(key);
    glutKeyboardUpFunc(keyup);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialup);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 40, 0, 40, 0, 10);
    glMatrixMode(GL_MODELVIEW);
    glPointSize(3.0);

    currentWindow = glutGetWindow();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    if (argc > 1 && !strcmp(argv[1], "-fullscreen"))
    {
        glutGameModeString("640x480:16@60");
        glutEnterGameMode();
    }
    else
    {
        originalWindow = glutCreateWindow("Fighter Jet");
    }

    initWindow();
    glutMainLoop();
    return 0;
}
