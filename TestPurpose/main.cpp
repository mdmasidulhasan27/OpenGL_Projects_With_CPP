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
#include "includes/toolFunctions.cpp"
#define M_PI 3.14159265358979323846
#define iniDistance 10
#define windowX 40
#define windowY 42
#define windowZ 40
#define borderMax 39.0
#define borderMin 1.0
#define numberOfStars 100
#define BULLETS 100

struct Jet
{
    float angle;
    int left, leftTime;
    int right, rightTime;
    int thrust, thrustTime;
    int sheild, sheildTime;
    float x, y, xv, yv, v;
    int life;
    float score;
} Jet1,Jet2;

typedef struct
{
    int inuse;
    float x, y;
    float v;
    float xv, yv;
    int expire;
} Bullet;

struct star
{
    float starX;
    float starY;
}stars[numberOfStars];
Bullet bullet[BULLETS];

void initWindow(void);
int gameLevel=5;
//int joyShield = 0, cursor = 1;
int lastTime;
int paused = 0, resuming = 1;
int originalWindow = 0, currentWindow;
int gameMode = 0, mainMenuSelect=0, backGround=1;
string backGroundSt[]={"Off","on"}, gameLevelSt[]={"Low","Medium","High"};

void starGenerate()
{
    for(int i=0; i<numberOfStars; i++){
        stars[i].starX=random(10,389)/10.0;
        stars[i].starY=random(10,389)/10.0;
    }
}

void starsDisplay()
{
    int i;
    glPointSize(.5);
    glBegin(GL_POINTS);
    glColor3ub(200,200,200);
    for(i=0; i<numberOfStars; i++){
        glVertex2f(stars[i].starX,stars[i].starY);
    }
    glEnd();
}

/*int allocBullet(void)
{
    int i;

    for (i=0; i<BULLETS; i++)
    {
        if (!bullet[i].inuse)
        {
            return i;
        }
    }
    return -1;
}

void initBullet(int i, int time)
{
    float c = cos(Jet1.angle*M_PI/180.0);
    float s = sin(Jet1.angle*M_PI/180.0);

    bullet[i].inuse = 1;
    bullet[i].x = x + 3.5 * c;
    bullet[i].y = y + 3.5 * s;
    bullet[i].v = 0.025;
    bullet[i].xv = xv + c * bullet[i].v;
    bullet[i].yv = yv + s * bullet[i].v;
    bullet[i].expire = time + 600;
}

void advanceBullets(int delta, int time)
{
    int i;

    for (i=0; i<BULLETS; i++)
    {
        if (bullet[i].inuse)
        {
            float x, y;

            if (time > bullet[i].expire)
            {
                bullet[i].inuse = 0;
                continue;
            }
            x = bullet[i].x + bullet[i].xv * delta;
            y = bullet[i].y + bullet[i].yv * delta;
            x = x / 40.0;
            bullet[i].x = (x - floor(x))*40.0;
            y = y / 40.0;
            bullet[i].y = (y - floor(y))*40.0;
        }
    }
}

void shotBullet(void)
{
    int entry;

    entry = allocBullet();
    if (entry >= 0)
    {
        initBullet(entry, glutGet(GLUT_ELAPSED_TIME));
    }
}

void drawBullets(void)
{
    int i;

    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 1.0);
    for (i=0; i<BULLETS; i++)
    {
        if (bullet[i].inuse)
        {
            glVertex2f(bullet[i].x, bullet[i].y);
        }
    }

    glEnd();
}*/

void jet1StartingPosition(void)
{
    Jet1.angle = 0.0;
    Jet1.x=windowX/2+5;
    Jet1.y=windowY/2;
    Jet1.xv=0;
    Jet1.yv=0;
}

void jet2StartingPosition(void)
{
    Jet2.angle = 0.0;
    Jet2.x=windowX/2-5;
    Jet2.y=windowY/2;
    Jet2.xv=0;
    Jet2.yv=0;
}

void jetsStartingPosition(int jetN)
{
    switch(jetN)
    {
    case 0:
        jet1StartingPosition();
        jet2StartingPosition();
        break;
    case 1:
        jet1StartingPosition();
        break;
    case 2:
        jet2StartingPosition();
        break;
    default:
        jet1StartingPosition();
        jet2StartingPosition();
        Jet1.life=10;
        Jet1.score=0;
        Jet2.life=10;
        Jet2.score=0;
        break;
    }
}

void drawShield(int r, int g, int b, int distance)
{
    float rad;
    glColor3ub(r,g,b);
    glBegin(GL_LINE_LOOP);
    for (rad=0.0; rad<11.0; rad += 1.0)
    {
        glVertex2f(3.75 * cos(2*rad/M_PI)+distance, 3.75 * sin(2*rad/M_PI));
    }
    glEnd();
}

void drawJet1(float angle)
{
    glPushMatrix();
    glTranslatef(Jet1.x, Jet1.y, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    if (Jet1.thrust)
    {
        glColor3ub(255, 150, 150);
        glBegin(GL_POLYGON);
        glVertex2f(-0.75, -0.5);
        glVertex2f(-1.75-random(0,3), 0.0);
        glVertex2f(-0.75, 0.5);
        glVertex2f(-0.75, 0.5);
        glVertex2f(-0.5, 0.0);
        glEnd();
    }
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(3.5,0.0);
    glVertex2f(0.0, -0.20);
    glVertex2f(-1.0, -1.0);
    glVertex2f(-0.5, 0.0);
    glVertex2f(-1.0, 1.0);
    glVertex2f(0.0,0.20);
    glVertex2f(3.5, 0.0);
    glEnd();
    if (Jet1.sheild)
    {
        drawShield(255,0,0,iniDistance);
    }
    glPopMatrix();
}

void drawJet2(float angle)
{
    glPushMatrix();
    glTranslatef(Jet2.x, Jet2.y, 0.0);
    glRotatef(Jet2.angle, 0.0, 0.0, 1.0);
    if (Jet2.thrust)
    {
        glColor3ub(150, 150, 255);
        glBegin(GL_POLYGON);
        glVertex2f(0.75, -0.5);
        glVertex2f(1.75+random(0,3), 0.0);
        glVertex2f(0.75, 0.5);
        glVertex2f(0.75, 0.5);
        glVertex2f(0.5, 0.0);
        glEnd();
    }
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-3.5,0.0);
    glVertex2f(0.0, -0.20);
    glVertex2f(1.0, -1.0);
    glVertex2f(0.5, 0.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(0.0,0.20);
    glVertex2f(-3.5, 0.0);
    glEnd();
    if (Jet2.sheild)
    {
        drawShield(100,100,255,-iniDistance);
    }
    glPopMatrix();
}

void border(void)
{
    glBegin(GL_LINE_LOOP);
    glColor3ub(255,0,0);
    glVertex2d(1,1);
    glVertex2d(1,39);
    glVertex2d(39,39);
    glVertex2d(39,1);
    glEnd();
}

void titleBar(void)
{
    float dis=0;
    glBegin(GL_QUADS);
    glColor3ub(0,200,200);
    glVertex2f(0.0,windowY-2);
    glVertex2f(0.0,windowY);
    glVertex2f(windowX,windowY);
    glVertex2f(windowX,windowY-2);
    glEnd();
    //Jet 2 score board:
    glBegin(GL_QUADS);
    glColor3ub(0,100,100);
    glVertex2d(.2+dis,40.2);
    glVertex2d(.2+dis,41.8);
    glVertex2d(9+dis,41.8);
    glVertex2d(9+dis,40.2);
    glEnd();
    text(.4, 40.6, "Score: "+to_string(int(Jet2.score)), 5, 1, 0, 1);
    //Jet 2 life board:
    dis=9;
    glBegin(GL_QUADS);
    glColor3ub(0,100,100);
    glVertex2d(.2+dis,40.2);
    glVertex2d(.2+dis,41.8);
    glVertex2d(9+dis,41.8);
    glVertex2d(9+dis,40.2);
    glEnd();
    text(0.4+dis, 40.6, "Life: "+to_string(Jet2.life), 5, 1, 0, 1);
    //Jet 1 life board:
    dis = 21.8;
    glBegin(GL_QUADS);
    glColor3ub(0,100,100);
    glVertex2d(.2+dis,40.2);
    glVertex2d(.2+dis,41.8);
    glVertex2d(9+dis,41.8);
    glVertex2d(9+dis,40.2);
    glEnd();
    text(0.4+dis, 40.6, "Life: "+to_string(Jet1.life), 5, 1, 1, 0);
    //Jet 1 score board:
    dis = 30.8;
    glBegin(GL_QUADS);
    glColor3ub(0,100,100);
    glVertex2d(.2+dis,40.2);
    glVertex2d(.2+dis,41.8);
    glVertex2d(9+dis,41.8);
    glVertex2d(9+dis,40.2);
    glEnd();
    text(.4+dis, 40.6, "Score: "+to_string(int(Jet1.score)), 5, 1, 1, 0);
}

void mainMenu()
{
    switch(mainMenuSelect)
    {
    case 0:
        text(10,22,"Play New Game",5,1,1,1);
        text(10,20,"Select Level",4,0,1,1);
        text(10,18,"Back Ground: "+backGroundSt[backGround],4,0,1,1);
        break;
    case 1:
        text(10,22,"Play New Game",4,0,1,1);
        text(10,20,"Select Level",5,1,1,1);
        text(10,18,"Back Ground: "+backGroundSt[backGround],4,0,1,1);
        break;
    case 2:
        text(10,22,"Play New Game",4,0,1,1);
        text(10,20,"Select Level",4,0,1,1);
        text(10,18,"Back Ground: "+backGroundSt[backGround],5,1,1,1);
        break;
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(backGround)
        starsDisplay();
    if(gameMode){
        drawJet1(Jet1.angle);
        drawJet2(Jet2.angle);
        titleBar();
    }
    else {
        mainMenu();
    }
    border();
    //drawBullets();
    glutSwapBuffers();
}

void controlLogics(void)
{
    int time, delta;
    time = glutGet(GLUT_ELAPSED_TIME);
    delta = time - lastTime;
    if (resuming)
    {
        lastTime = time;
        resuming = 0;
    }
    //JET1:
    if (Jet1.left)
    {
        delta = time - Jet1.leftTime;
        Jet1.angle = Jet1.angle + delta * 0.4;
        Jet1.leftTime = time;
    }
    if (Jet1.right)
    {
        delta = time - Jet1.rightTime;
        Jet1.angle = Jet1.angle - delta * 0.4;
        Jet1.rightTime = time;
    }
    if (Jet1.thrust)
    {
        delta = time - Jet1.thrustTime;
        Jet1.v = delta * 0.00004;
        Jet1.xv = Jet1.xv + cos(Jet1.angle*M_PI/180.0) * Jet1.v;
        Jet1.yv = Jet1.yv + sin(Jet1.angle*M_PI/180.0) * Jet1.v;
        Jet1.thrustTime = time;
    }

    if (Jet2.left)
    {
        delta = time - Jet2.leftTime;
        Jet2.angle = Jet2.angle + delta * 0.4;
        Jet2.leftTime = time;
    }
    if (Jet2.right)
    {
        delta = time - Jet2.rightTime;
        Jet2.angle = Jet2.angle - delta * 0.4;
        Jet2.rightTime = time;
    }
    if (Jet2.thrust)
    {
        delta = time - Jet2.thrustTime;
        Jet2.v = delta * 0.00004;
        Jet2.xv = (Jet2.xv - cos(Jet2.angle*M_PI/180.0) * Jet2.v);
        Jet2.yv = (Jet2.yv - sin(Jet2.angle*M_PI/180.0) * Jet2.v);
        Jet2.thrustTime = time;
    }

    Jet1.x = Jet1.x + Jet1.xv * delta;
    Jet1.x = Jet1.x / 40.0;
    Jet1.x = (Jet1.x - floor(Jet1.x))*40.0;
    Jet1.y = Jet1.y + Jet1.yv * delta;
    Jet1.y = Jet1.y / 40.0;
    Jet1.y = (Jet1.y - floor(Jet1.y))*40.0;

    Jet2.x = Jet2.x + Jet2.xv * delta;
    Jet2.x = Jet2.x / 40.0;
    Jet2.x = (Jet2.x - floor(Jet2.x))*40.0;
    Jet2.y = Jet2.y + Jet2.yv * delta;
    Jet2.y = Jet2.y / 40.0;
    Jet2.y = (Jet2.y - floor(Jet2.y))*40.0;
    lastTime = time;
}

void gameLogic()
{
    if(Jet1.x<borderMin ||Jet1.x>borderMax || Jet1.y<borderMin ||Jet1.y>borderMax)
    {
        if(Jet1.life!=0)
            Jet1.life--;
        jetsStartingPosition(1);
    }
    if(Jet2.x<borderMin ||Jet2.x>borderMax || Jet2.y<borderMin ||Jet2.y>borderMax)
    {
        if(Jet2.life!=0)
            Jet2.life--;
        jetsStartingPosition(2);
    }
    if(Jet1.thrust)
    {
        if(Jet1.score<=1000)
            Jet1.score+=(positive(Jet1.xv)+positive(Jet1.yv));
    }
    if(Jet2.thrust)
    {
        if(Jet2.score<=1000)
            Jet2.score+=(positive(Jet2.xv)+positive(Jet2.yv));
    }
    if(Jet1.life==0 || Jet2.life==0 || Jet1.score>=1000 || Jet2.score>=1000)
    {
        if(Jet1.score>Jet2.score)
        {
            printf("Yollow Winner\n");
        }
        else if(Jet2.score>Jet1.score)
        {
            printf("Pink Winner\n");
        }
        else
        {
            if(Jet1.life>Jet2.life)
            {
                printf("Yollow Winner\n");
            }
            else if(Jet2.life>Jet1.life)
            {
                printf("Pink Winner\n");
            }
            else
            {
                printf("Draw Match\n");
            }
        }
        jetsStartingPosition(3);
        gameMode = 0;
    }

}

void idle(void)
{
    gameLogic();
    controlLogics();
    //advanceBullets(delta, time);
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
    case 'z':
    case 'Z':
        Jet1.x=windowX/2+10;;
        Jet1.y=windowY/2;;
        Jet1.xv = 0;
        Jet1.yv = 0;
        Jet2.x=windowX/2-10;;
        Jet2.y=windowY/2;;
        Jet2.xv = 0;
        Jet2.yv = 0;
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
        //shotBullet();
        break;
    case 'w':
        Jet2.thrust = 1;
        Jet2.thrustTime = glutGet(GLUT_ELAPSED_TIME);
        break;
    case 'a':
        Jet2.left = 1;
        Jet2.leftTime = glutGet(GLUT_ELAPSED_TIME);
        break;
    case 'd':
        Jet2.right = 1;
        Jet2.rightTime = glutGet(GLUT_ELAPSED_TIME);
        break;
    case 'S':
    case 's':
        Jet2.sheild = 1;
        break;
    }
}


void keyup(unsigned char key, int x, int y)
{
    switch (key)
    {

    case 'S':
    case 's':
        Jet2.sheild = 0;
        break;
    case 'w':
        Jet2.thrust = 0;
        break;
    case 'a':
        Jet2.left = 0;
        break;
    case 'd':
        Jet2.right = 0;
        break;

    }
}


void special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if(gameMode){
            Jet1.thrust = 1;
            Jet1.thrustTime = glutGet(GLUT_ELAPSED_TIME);
        }
        else if(!gameMode && mainMenuSelect>0) {
            mainMenuSelect--;
        }
        break;
    case GLUT_KEY_LEFT:
        if(gameMode){
            Jet1.left = 1;
            Jet1.leftTime = glutGet(GLUT_ELAPSED_TIME);
        }
        else {
        }
        break;
    case GLUT_KEY_RIGHT:
        if(gameMode){
            Jet1.right = 1;
            Jet1.rightTime = glutGet(GLUT_ELAPSED_TIME);
        }
        else {
            switch(mainMenuSelect){
                case 0:
                    gameMode=1;
                    break;
                case 1:

                        break;
                case 2:
                    if(backGround)
                        backGround = 0;
                    else
                        backGround = 1;
                        break;
            }

        }
        break;
    case GLUT_KEY_DOWN:
        if(gameMode)
            Jet1.sheild = 1;
        else if(!gameMode && mainMenuSelect<2) {
            mainMenuSelect++;
        }
        break;
    }
}


void specialup(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        Jet1.thrust = 0;
        break;
    case GLUT_KEY_LEFT:
        Jet1.left = 0;
        break;
    case GLUT_KEY_RIGHT:
        Jet1.right = 0;
        break;
    case GLUT_KEY_DOWN:
        Jet1.sheild = 0;
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
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowX, 0, windowY, 0, windowZ);
    //glMatrixMode(GL_MODELVIEW);
    glPointSize(3.0);
    currentWindow = glutGetWindow();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    starGenerate();
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowX*16,windowY*16);
    glutInitWindowPosition(400,10);
    glutCreateWindow("Fighter Jet");
    jetsStartingPosition(3);
    initWindow();
    glutMainLoop();
    return 0;
}