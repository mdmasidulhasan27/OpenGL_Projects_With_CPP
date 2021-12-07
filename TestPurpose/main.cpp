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
//functions
void machinePlay();
void idle();
void controlLogics();
struct Jet
{
    double angle;
    int left, leftTime;
    int right, rightTime;
    int thrust, thrustTime;
    int sheild, sheildTime;
    double x, y, xv, yv, v;
    int life;
    double score;
} Jet1,Jet2;

typedef struct
{
    int inuse;
    double x, y;
    double v;
    double xv, yv;
    int expire;
} Bullet;

struct star
{
    double starX;
    double starY;
} stars[numberOfStars];
Bullet bulletJet1[BULLETS];
Bullet bulletJet2[BULLETS];

void initWindow(void);
int gameLevel=5;
int joyShield = 0, cursor = 1;
int lastTime;
int paused = 0, resuming = 1;
int originalWindow = 0, currentWindow;
int pageNo = 0, mainMenuSelect=1, backGround=1;
int gameMode=0;//0 single Player, 1 Multi Player
int winner = 0;//0 draw, 1 yellow, 2 pink
int playPause = 1; //0 for pause, 1 for play
string backGroundSt[]= {"Off","on"}, gameModeSt[]= {"Single Player","Multi Player"};


///Stars
void starGenerate()
{
    for(int i=0; i<numberOfStars; i++)
    {
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
    for(i=0; i<numberOfStars; i++)
    {
        glVertex2f(stars[i].starX,stars[i].starY);
    }
    glEnd();
}

///Bullets
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
    float c = cos(Jet1.angle*M_PI/180.0);
    float s = sin(Jet1.angle*M_PI/180.0);

    bulletJet1[i].inuse = 1;
    bulletJet1[i].x = Jet1.x + 3.5 * c;
    bulletJet1[i].y = Jet1.y + 3.5 * s;
    bulletJet1[i].v = 0.025;
    bulletJet1[i].xv = Jet1.xv + c * bulletJet1[i].v;
    bulletJet1[i].yv = Jet1.yv + s * bulletJet1[i].v;
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
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3d(255, 150, 150);
    for (i=0; i<BULLETS; i++)
    {
        if (bulletJet1[i].inuse)
        {
            double b1x = bulletJet1[i].x, b1y = bulletJet1[i].y, j2x = Jet2.x, j2y = Jet2.y;
            glVertex2f(b1x, b1y);
            if((j2x<b1x && j2x+1.25>b1x && j2y<b1y && j2y+1.25>b1y) || (j2x>b1x && j2x-1.25<b1x && j2y>b1y && j2y-1.25<b1y))
            {
                //printf("Jet 1 hitted\n");
                bulletJet1[i].inuse=0;
                Jet2.life--;
                Jet2.score /= 1.5;
                Jet1.score *= 1.5;
            }
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
    float c = cos((Jet2.angle+180)*M_PI/180.0);
    float s = sin((Jet2.angle+180)*M_PI/180.0);

    bulletJet2[i].inuse = 1;
    bulletJet2[i].x = Jet2.x + 3.5 * c;
    bulletJet2[i].y = Jet2.y + 3.5 * s;
    bulletJet2[i].v = 0.025;
    bulletJet2[i].xv = Jet2.xv + c * bulletJet2[i].v;
    bulletJet2[i].yv = Jet2.yv + s * bulletJet2[i].v;
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
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3d(150, 150, 255);
    for (i=0; i<BULLETS; i++)
    {
        if (bulletJet2[i].inuse)
        {
            double b2x = bulletJet2[i].x, b2y = bulletJet2[i].y, j1x = Jet1.x, j1y = Jet1.y;
            glVertex2f(b2x, b2y);
            if((j1x<b2x && j1x+1.25>b2x && j1y<b2y && j1y+1.25>b2y) || (j1x>b2x && j1x-1.25<b2x && j1y>b2y && j1y-1.25<b2y))
            {
                bulletJet2[i].inuse=0;
                Jet1.life--;
                Jet2.score *= 1.5;
                Jet1.score /= 1.5;
            }
        }
    }
    glEnd();
}

///Jets
void jet1StartingPosition(void)
{
    Jet1.angle = 0.0;
    Jet1.x=windowX/2+5;
    Jet1.y=windowY/2;
    Jet1.xv=0;
    Jet1.yv=0;
    Jet1.leftTime=0;
    Jet1.rightTime=0;
    Jet1.thrustTime=0;
    Jet1.thrust=0;
    Jet1.left=0;
    Jet1.right=0;
}

void jet2StartingPosition(void)
{
    Jet2.angle = 0.0;
    Jet2.x=windowX/2-5;
    Jet2.y=windowY/2;
    Jet2.xv=0;
    Jet2.yv=0;
    Jet2.leftTime=0;
    Jet2.rightTime=0;
    Jet2.thrustTime=0;
    Jet2.thrust=0;
    Jet2.left=0;
    Jet2.right=0;
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
    glColor3ub(255,255,255);
    glVertex2f(0.0,windowY-2);
    glVertex2f(0.0,windowY);
    glVertex2f(windowX,windowY);
    glVertex2f(windowX,windowY-2);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(255,255,255);
    glVertex2f(0.1,windowY-1.9);
    glVertex2f(0.1,windowY-.1);
    glVertex2f(windowX-.1,windowY-.1);
    glVertex2f(windowX-.1,windowY-1.9);
    glEnd();
    //Jet 2 score board:
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2d(.2+dis,40.2);
    glVertex2d(.2+dis,41.8);
    glVertex2d(9+dis,41.8);
    glVertex2d(9+dis,40.2);
    glEnd();
    text(.4, 40.6, "Score: "+to_string(int(Jet2.score)), 5, 1, 0, 1);
    //Jet 2 life board:
    dis=9;
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2d(.2+dis,40.2);
    glVertex2d(.2+dis,41.8);
    glVertex2d(9+dis,41.8);
    glVertex2d(9+dis,40.2);
    glEnd();
    text(0.4+dis, 40.6, "Life: "+to_string(Jet2.life), 5, 1, 0, 1);
    //Jet 1 life board:
    dis = 21.8;
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2d(.2+dis,40.2);
    glVertex2d(.2+dis,41.8);
    glVertex2d(9+dis,41.8);
    glVertex2d(9+dis,40.2);
    glEnd();
    text(0.4+dis, 40.6, "Life: "+to_string(Jet1.life), 5, 1, 1, 0);
    //Jet 1 score board:
    dis = 30.8;
    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
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
        if(playPause==0)
            text(10,20,"Continue",5,1,1,1);
        text(10,18,"Play New Game",4,0,1,1);
        text(10,16,"Mode: "+gameModeSt[gameMode],4,0,1,1);
        text(10,14,"Back Ground: "+backGroundSt[backGround],4,0,1,1);
        text(10,12,"Quit Game",4,0,1,1);
        break;
    case 1:
        if(playPause==0)
            text(10,20,"Continue",4,0,1,1);
        text(10,18,"Play New Game",5,1,1,1);
        text(10,16,"Mode: "+gameModeSt[gameMode],4,0,1,1);
        text(10,14,"Back Ground: "+backGroundSt[backGround],4,0,1,1);
        text(10,12,"Quit Game",4,0,1,1);
        break;
    case 2:
        if(playPause==0)
            text(10,20,"Continue",4,0,1,1);
        text(10,18,"Play New Game",4,0,1,1);
        text(10,16,"Mode: "+gameModeSt[gameMode],5,1,1,1);
        text(10,14,"Back Ground: "+backGroundSt[backGround],4,0,1,1);
        text(10,12,"Quit Game",4,0,1,1);
        break;
    case 3:
        if(playPause==0)
            text(10,20,"Continue",4,0,1,1);
        text(10,18,"Play New Game",4,0,1,1);
        text(10,16,"Mode: "+gameModeSt[gameMode],4,0,1,1);
        text(10,14,"Back Ground: "+backGroundSt[backGround],5,1,1,1);
        text(10,12,"Quit Game",4,0,1,1);
        break;
    case 4:
        if(playPause==0)
            text(10,20,"Continue",4,0,1,1);
        text(10,18,"Play New Game",4,0,1,1);
        text(10,16,"Mode: "+gameModeSt[gameMode],4,0,1,1);
        text(10,14,"Back Ground: "+backGroundSt[backGround],4,0,1,1);
        text(10,12,"Quit Game",5,1,1,1);
        break;
    }
}

void display(void)
{
    if(gameMode==0)
        machinePlay();
    glClear(GL_COLOR_BUFFER_BIT);
    if(backGround)
        starsDisplay();
    switch(pageNo)
    {
    case 0:
        //menu Page
        mainMenu();
        glutIdleFunc(NULL);
        break;
    case 1:
        //game page
        glutIdleFunc(idle);
        drawBulletsJet1();
        drawBulletsJet2();
        drawJet1(Jet1.angle);
        drawJet2(Jet2.angle);
        titleBar();
        break;
    case 2:
        //game Over Page
        switch(winner)
        {
        case 0:
            text(14,24,"######  Draw Match  ######",5,0,1,0);
            break;
        case 1:
            text(14,24,"###  Yellow is Winner  ###",5,1,1,0);
            text(14,22,"        Point: "+to_string(int(Jet1.score)),5,1,1,0);
            break;
        case 2:
            text(14,24,"###  Pink is Winner  ###",5,1,0,1);
            text(14,22,"        Point: "+to_string(int(Jet2.score)),5,1,0,1);
            break;
        }
        text(14,4,"press 'enter' for main menu",4,1,1,1);
        glutIdleFunc(NULL);
        break;
    }
    border();
    glutPostRedisplay();
    glutSwapBuffers();
}

void controlLogics(int work)
{
    int time, delta;
    time = glutGet(GLUT_ELAPSED_TIME);
    delta = time - lastTime;
    //delta = time - lastTime;
    if (!work)
    {
        lastTime = time;
    }
    ///JET1:
    if (Jet1.left)
    {
        delta = time - Jet1.leftTime;
        Jet1.angle = Jet1.angle + delta * 0.3;
        Jet1.leftTime = time;
    }
    if (Jet1.right)
    {
        delta = time - Jet1.rightTime;
        Jet1.angle = Jet1.angle - delta * 0.3;
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
    ///JET2:
    if (Jet2.left)
    {
        delta = time - Jet2.leftTime;
        Jet2.angle = Jet2.angle + delta * 0.3;
        Jet2.leftTime = time;
    }
    if (Jet2.right)
    {
        delta = time - Jet2.rightTime;
        Jet2.angle = Jet2.angle - delta * 0.3;
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
    advanceBulletsJet1(delta, time);
    advanceBulletsJet2(delta, time);
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
            Jet1.score+=Jet1.thrust/100.0;
    }
    if(Jet2.thrust)
    {
        if(Jet2.score<=1000)
            Jet2.score+=Jet2.thrust/100.0;
    }
    if(Jet1.life==0 || Jet2.life==0 || Jet1.score>=1000 || Jet2.score>=1000)
    {
        if(Jet1.score>Jet2.score)
            winner = 1;
        else if(Jet2.score>Jet1.score)
            winner = 2;
        else
        {
            if(Jet1.life>Jet2.life)
                winner = 1;
            else if(Jet2.life>Jet1.life)
                winner = 2;
            else
                winner = 0;
        }
        pageNo = 2;
    }
}

void idle(void)
{
    if(playPause==1)
    {
        gameLogic();
        controlLogics(1);
    }
    else
    {
        controlLogics(0);
    }
    //glutPostWindowRedisplay(currentWindow);
    //glutPostRedisplay();
    //glutSwapBuffers();
}

void visible(int vis)
{
    if (vis == GLUT_VISIBLE)
    {
        if (playPause)
        {
            glutIdleFunc(idle);
        }
    }
    else
    {
        glutIdleFunc(NULL);
    }
}

void enter()
{
    switch(pageNo)
    {
    case 0:
        switch(mainMenuSelect)
        {
        case 0:
            playPause = 1;
            pageNo = 1;
            break;
        case 1:
            playPause = 1;
            pageNo=1;
            jetsStartingPosition(3);
            break;
        case 2:
            if(gameMode){
                gameMode=0;
                Jet2.thrust=0;
                Jet2.left=0;
                Jet2.right=0;
            }
            else
                gameMode=1;
            break;
        case 3:
            if(backGround)
                backGround = 0;
            else
                backGround = 1;
            break;
        case 4:
            exit(0);
            break;
        }
        break;
    case 1:
        playPause=0;
        pageNo=0;
        mainMenuSelect=0;
        break;
    case 2:
        //game over page
        pageNo=0;
        playPause=1;
        mainMenuSelect=1;
        jetsStartingPosition(3);
        break;
    }
}

double getAngle(double y1, double y2, double x1, double x2)
{
    double angle = (y2-y1)/(x2-x1);
    angle = atan(angle);
    angle = angle *(180/3.14159265359);
    if(angle<0)
        angle *= -1;
    return angle;
}
double pointsDistance()
{
    return sqrt(pow((Jet1.x-Jet2.x),2)+ pow((Jet1.y-Jet2.y),2));
}

void machinePlay()
{
    double angle;
    double distance = pointsDistance();
    if(Jet1.x<Jet2.x && Jet1.y<=Jet2.y)
    {
        //left bottom
        angle = getAngle(Jet1.y, Jet2.y, Jet1.x, Jet2.x);
    }
    else if(Jet1.x>=Jet2.x && Jet1.y<Jet2.y)
    {
        //right bottom
        angle = getAngle(Jet1.x, Jet2.x, Jet1.y, Jet2.y)+90;
    }
    else if(Jet1.x>Jet2.x && Jet1.y>=Jet2.y)
    {
        //right top
        angle = getAngle(Jet1.y, Jet2.y, Jet1.x, Jet2.x)+180;
    }
    else if(Jet1.x<=Jet2.x && Jet1.y>Jet2.y)
    {
        //left top
        angle = getAngle(Jet1.x, Jet2.x, Jet1.y, Jet2.y)+270;
    }

    int jet2Angle = Jet2.angle;
    jet2Angle=abs(jet2Angle);
    jet2Angle %= 360;
    printf("%.1lf\n",distance);
    if(angle==jet2Angle)
    {
        Jet2.left = 0;
        Jet2.right = 0;
    }
    else if(jet2Angle<=(360-angle))
    {
        Jet2.right = 1;
        Jet2.rightTime = glutGet(GLUT_ELAPSED_TIME);
        Jet2.left = 0;
    }
    else if(jet2Angle>=(360-angle))
    {
        Jet2.left = 1;
        Jet2.leftTime = glutGet(GLUT_ELAPSED_TIME);
        Jet2.right = 0;
    }
    if(distance>15.0){
        Jet2.thrust=1;
        Jet2.thrustTime = glutGet(GLUT_ELAPSED_TIME);
    }
    else{
        Jet2.thrust=0;
    }

}

void key(unsigned char key, int px, int py)
{
    switch (key)
    {
    case 27:
        exit(0);
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
        shotBulletJet2();
        //Jet2.sheild = 1;
        break;
    case 13:
        enter();
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
        if(pageNo==0)
        {
            if(playPause==0 && mainMenuSelect>0)
                mainMenuSelect--;
            else if(mainMenuSelect>1)
                mainMenuSelect--;
        }
        else if(pageNo==1)
        {
            Jet1.thrust = 1;
            Jet1.thrustTime = glutGet(GLUT_ELAPSED_TIME);
        }
        break;
    case GLUT_KEY_LEFT:
        if(pageNo==1)
        {
            Jet1.left = 1;
            Jet1.leftTime = glutGet(GLUT_ELAPSED_TIME);
        }
        break;
    case GLUT_KEY_RIGHT:
        if(pageNo==1)
        {
            Jet1.right = 1;
            Jet1.rightTime = glutGet(GLUT_ELAPSED_TIME);
        }
        break;
    case GLUT_KEY_DOWN:
        if(pageNo==0 && mainMenuSelect<4)
        {
            mainMenuSelect++;
        }
        else if(pageNo==1)
        {
            shotBulletJet1();
            //Jet1.sheild = 1;
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
