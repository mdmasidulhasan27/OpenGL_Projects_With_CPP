//Includes:
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <iostream>
#include <string>
#include <GL/glut.h>
//Defines:
#define border 20
#define nStar 1000
#define nBullets 4
//Name spaces:
using namespace std;
//Small Functions:
int rd(int minimum, int mximum)
{
    return (rand()%(mximum-minimum))+minimum;
}
//Static variables:
int planeP = 165, planeLeft=0, planeRight=0;
int bulletPosition[] = {0,106};
int gameSpeed=0, play=0, oldGame=0;
int point=0, life=3, earthLevel=100, nAsteroid=2;
int presentTime=0, levelTime=0;
int mainMenuSelection=1, pages=0, backGround = 1, starMove=0;
string backGroundSt[]= {"Off", "On"}, gameLevelSt[]= {"Low","Middle","High"};
//Structures:
struct asteroid
{
    float y, x, sz, speed;
    int active;
    int r,g,b;
} asteroids[6];

struct star
{
    int x;
    int y;
} stars[nStar];

struct blt
{
    float x, y;
    int active;
}blts[2][nBullets];
//Functions:
void bltGenerate()
{
    for(int i=0; i<nBullets; i++){
        for(int j=0; j<2; j++){
            blts[j][i].y=-(680/nBullets)*i;
            blts[j][i].active=1;
        }
    }
}

void starGenerate()
{
    for(int i=0; i<nStar; i++)
    {
        stars[i].x=rd(0,450);
        stars[i].y=rd(0,680);
    }
}

void resetAnAsteroid(int i)
{
    asteroids[i].y=rd(700+i*100,750+i*100);
    asteroids[i].x=rd(border,450-asteroids[i].sz-border);
    asteroids[i].sz=rd(10,40);
    asteroids[i].speed=1+(3-asteroids[i].sz/15.0);
    asteroids[i].r=rd(150,255);
    asteroids[i].g=rd(150,255);
    asteroids[i].b=rd(150,255);
}

void asteroidGenerate()
{
    for(int i=0; i<nAsteroid; i++)
    {
        resetAnAsteroid(i);
    }
}

void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx,cy);

    for(int i=0; i<=100; i++)
    {
        float angle = 2.0f*3.1416*i/100;
        float x = rx*cosf(angle);
        float y = ry*sinf(angle);
        glVertex2f((x+cx),(y+cy));
    }
    glEnd();
}

void planeStand()
{
    glBegin(GL_POLYGON);///1st base
    glColor3ub(50,50,50);
    glVertex2d(50,150);
    glVertex2d(50,130);
    glVertex2d(400,130);
    glVertex2d(400,150);
    glEnd();

    circle(175,20,225,130);

    glColor3ub(0,200,0);//green grass
    circle(175,8,225,150);

    glBegin(GL_POLYGON);///2nd base
    glColor3ub(80,80,80);
    glVertex2d(130,160);
    glVertex2d(130,150);
    glVertex2d(320,150);
    glVertex2d(320,160);
    glEnd();

    circle(95,7,225,150);

    glColor3ub(80,80,80);///uper part big circle
    circle(70,70,225,280);

    glColor3ub(0,0,0);
    circle(55,55,225,280);

    glBegin(GL_POLYGON);
    glColor3ub(160,160,160);
    glVertex2d(180,370);
    glVertex2d(190,340);
    glVertex2d(260,340);
    glVertex2d(270,360);
    glEnd();


    glBegin(GL_POLYGON);///3nd base
    glColor3ub(200,200,200);
    glVertex2d(160,220);
    glVertex2d(160,160);
    glVertex2d(290,160);
    glVertex2d(290,220);
    glEnd();

    circle(65,5,225,160);//down
    circle(65,3,225,220);//up

    glBegin(GL_POLYGON);
    glColor3ub(150,150,150);
    glVertex2d(160,191);
    glVertex2d(160,189);
    glVertex2d(290,189);
    glVertex2d(290,191);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(150,150,150);
    glVertex2d(188.5,220);
    glVertex2d(188.5,160);
    glVertex2d(190.5,160);
    glVertex2d(190.5,220);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(150,150,150);
    glVertex2d(224,220);
    glVertex2d(224,160);
    glVertex2d(226,160);
    glVertex2d(226,220);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(150,150,150);
    glVertex2d(259.5,220);
    glVertex2d(259.5,160);
    glVertex2d(261.5,160);
    glVertex2d(261.5,220);
    glEnd();
    glPushMatrix();
    glRotated(30,0,0,1);
    glTranslated(120,-170,0.0);
    glColor3ub(80,80,80);///uper part mini circle
    circle(30,50,225,280);

    glColor3ub(0,0,0);
    circle(15,35,225,280);
    glPopMatrix();
}

void planeShape()
{
    glColor3ub(203,211,205);
    circle(15,15,130,150);

    glBegin(GL_POLYGON);///cockpit
    glColor3ub(203,211,205);
    glVertex2d(130,165);
    glVertex2d(130,148);
    glVertex2d(200,148);
    glVertex2d(200,165);
    glEnd();

    glBegin(GL_POLYGON);///front red
    glColor3ub(225,0,0);
    glVertex2d(60,150);
    glVertex2d(60,100);
    glVertex2d(100,100);
    glVertex2d(100,150);
    glEnd();

    glBegin(GL_POLYGON);///yellow
    glColor3ub(255,255,0);
    glVertex2d(100,150);
    glVertex2d(100,100);
    glVertex2d(230,102);
    glVertex2d(230,148);
    glEnd();

    glColor3ub(225,0,0);
    //glTranslated(-32,30,0);
    //glRotated(-16,0,0,1);
    circle(15,25,95,125);

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(230,148);
    glVertex2d(230,102);
    glVertex2d(290,107);
    glVertex2d(290,143);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,0,0);
    glVertex2d(290,143);
    glVertex2d(290,107);
    glVertex2d(345,107);
    glVertex2d(340,143);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(210,0,0);
    glVertex2d(305,130);
    glVertex2d(340,130);
    glVertex2d(380,150);
    glVertex2d(360,150);
    glEnd();

    glBegin(GL_POLYGON);///back up
    glColor3ub(210,0,0);
    glVertex2d(310,185);
    glVertex2d(310,143);
    glVertex2d(340,143);
    glVertex2d(335,185);
    glEnd();

    glBegin(GL_POLYGON);///front fin
    glColor3ub(210,0,0);
    glVertex2d(130,120);
    glVertex2d(190,120);
    glVertex2d(260,200);
    glVertex2d(240,210);
    glEnd();

    glBegin(GL_POLYGON);///back fin
    glColor3ub(210,0,0);
    glVertex2d(110,100);
    glVertex2d(95,70);
    glVertex2d(120,60);
    glVertex2d(160,100);
    glEnd();

    glColor3ub(222,220,220);
    circle(10,25,60,125);///front circle
    glColor3ub(50,50,50);
    circle(4,6,53,125);

    glBegin(GL_POLYGON);///fan
    glColor3ub(150,150,150);
    glVertex2d(34,123);
    glVertex2d(34,117);
    glVertex2d(74,126);
    glVertex2d(74,134);
    glEnd();
}

float planeDesignY = 0;

void bgPlaneDesign()
{
    glPushMatrix();
    glTranslated(0,-110+sin(planeDesignY)*20,0);
    glScaled(1.1,1.4,0);
    glPushMatrix();
    glTranslated(0,290,0);
    glRotated(-10,0,0,1);
    planeShape();
    glPopMatrix();
    planeStand();
    glPopMatrix();
    planeDesignY+=.005;
}

void displayStars()
{
    int i;
    glPointSize(1.0);
    glBegin(GL_POINTS);
    glColor3ub(200,200,200);
    for(i=0; i<nStar; i++)
    {
        glVertex2d(stars[i].x,stars[i].y);
        if(starMove)
        {
            if(stars[i].y<0)
                stars[i].y=680;
            else
                stars[i].y--;
        }
    }
    glEnd();
}

void drawLineCircle(float cx, float cy, float r, int num_segments, int red, int green, int blue)
{
    glBegin(GL_LINE_LOOP);
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

void asteroidArt()
{
    int fireRatio, rdFireR, rdFireG, r, cx, cy;
    for(int i=0; i<nAsteroid; i++)
    {
        fireRatio=(asteroids[i].sz)/15;
        rdFireR=rd(128,255);
        rdFireG=rd(17,192);
        r = asteroids[i].sz/2;
        cx = asteroids[i].x+(asteroids[i].sz/2);
        cy = asteroids[i].y-(asteroids[i].sz/2);
        glBegin(GL_TRIANGLES);
        glColor3ub(rdFireR,rdFireG,0);
        glVertex2d(cx-(r+fireRatio),cy+fireRatio);
        glVertex2d(cx,asteroids[i].y+(fireRatio+(gameSpeed+1))*8+rd(0,asteroids[i].sz*2));
        glVertex2d(cx+(r+fireRatio),cy+fireRatio);
        glEnd();
        drawFiledCircle(cx,cy+fireRatio,r+fireRatio,r+fireRatio,rdFireR,rdFireG,0);
        drawFiledCircle(cx,cy,r,r+10,asteroids[i].r,asteroids[i].g,asteroids[i].b);
    }
}

void bulletArt(int x, int y, int f, int active)
{
    if(active==1){
        glBegin(GL_LINE_LOOP);
        glColor3ub(255,255,255);
        glVertex2d(x+0,border+y+35);
        glVertex2d(x+2,border+y+45);
        glVertex2d(x+4,border+y+35);
        glVertex2d(x+2,border+y+40);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glColor3ub(255,255,255);
        glVertex2d(x+12,border+y+35);
        glVertex2d(x+14,border+y+45);
        glVertex2d(x+16,border+y+35);
        glVertex2d(x+14,border+y+40);
        glEnd();
    }
}

void planeBody()
{
    //Front wing:
    glBegin(GL_POLYGON);
    glColor3ub(255-(3-life)*80,0,0);
    glVertex2d(planeP+0,border+20);
    glVertex2d(planeP+55,border+35);
    glVertex2d(planeP+65,border+35);
    glVertex2d(planeP+120,border+20);
    glEnd();
    //Rare wing:
    glBegin(GL_POLYGON);
    glVertex2d(planeP+35,border+5);
    glVertex2d(planeP+55,border+12);
    glVertex2d(planeP+65,border+12);
    glVertex2d(planeP+85,border+5);
    glEnd();
    //Body:
    glBegin(GL_POLYGON);
    glColor3ub(255-(3-life)*80,255-(3-life)*80,0);
    glVertex2d(planeP+58,border);
    glVertex2d(planeP+50,border+40);
    glVertex2d(planeP+70,border+40);
    glVertex2d(planeP+62,border);
    glEnd();
    drawLineCircle(planeP+60,border+40,10,10,255-(3-life)*80,0,0);
    drawFiledCircle(planeP+60,border+38,7,100,230,230,230);
}

void plane()
{
    for(int i=0; i<2; i++){
        for(int j=0; j<nBullets; j++){
            if(blts[i][j].y<=10)
                blts[i][j].x=planeP;
            else
                bulletArt(blts[i][j].x+bulletPosition[i],blts[i][j].y,0,blts[i][j].active);
            if(blts[i][j].y<=680)
                blts[i][j].y+=5;
            else{
                blts[i][j].y=0;
                blts[i][j].active=1;
            }
        }
        //if(blts[0][i].y<160 && blts[0][i].y>25)
        {
            bulletArt(planeP+bulletPosition[0],10,0,1);
            bulletArt(planeP+bulletPosition[1],10,0,1);
        }
    }
    planeBody();
}

int enemyKilled()
{
    for(int i=0; i<nAsteroid; i++)
    {
        for(int j=0; j<nBullets; j++){
            for(int k=0; k<2; k++){
                if(((asteroids[i].x<=(blts[k][j].x+2+bulletPosition[k])) && ((asteroids[i].x+asteroids[i].sz)>=(blts[k][j].x+2+bulletPosition[k])) && blts[k][j].active)
                   ||((asteroids[i].x<=(blts[k][j].x+14+bulletPosition[k])) && ((asteroids[i].x+asteroids[i].sz)>=(blts[k][j].x+14+bulletPosition[k]))))
                    if(asteroids[i].y-asteroids[i].sz<=blts[k][j].y)
                    {
                        blts[k][j].active=0;
                        return i;
                    }
            }
        }
    }
    return -1;
}

int planeDestroy()
{
    for(int i=0; i<nAsteroid; i++)
    {
        if((asteroids[i].x>planeP && asteroids[i] .x<planeP+120)||(asteroids[i].x+asteroids[i].sz>planeP && asteroids[i].x+asteroids[i].sz<planeP+120))

            if(asteroids[i].y<border+40 && life>0)
            {
                resetAnAsteroid(i);
                return 1;
            }
    }
    return 0;
}

void enemiesMovement()
{
    int index;
    if(planeDestroy())
        life--;
    index = enemyKilled();
    if(index>=0)
    {
        point+=asteroids[index].sz/10;
        resetAnAsteroid(index);
    }
    for(int i=0; i<nAsteroid; i++)
    {
        if(!(asteroids[i].y>0))
            resetAnAsteroid(i);
        else
            asteroids[i].y=asteroids[i].y-asteroids[i].speed;
    }
}

void text(int x, int y, int font, string s, float r, float g, float b)
{
    glColor3f( r, g, b );
    glRasterPos2f(x, y);
    int len, i;
    len = s.length();
    for (i = 0; i < len; i++)
    {
        switch(font)
        {
        case 1:
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
            break;
        default:
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
            break;
        }
    }
}

void planePosition()
{
    if(planeLeft)
        if(planeP>border)
            planeP-=ceil(gameSpeed/5.0)+2;
    if(planeRight)
        if(planeP<450-120-border)
            planeP+=ceil(gameSpeed/5.0)+2;
}

void titleBar()
{
    //back ground
    glBegin(GL_QUADS);
    glColor3ub(0,200,200);
    glVertex2d(0,650);
    glVertex2d(0,680);
    glVertex2d(450,680);
    glVertex2d(450,650);
    glEnd();
    //gameLevel
    glBegin(GL_QUADS);
    glColor3ub(0,100,100);
    glVertex2d(5,655);
    glVertex2d(5,675);
    glVertex2d(110,675);
    glVertex2d(110,655);
    glEnd();
    text(10,660,1,"Level: "+to_string(gameSpeed),1.0,1.0,1.0);
    //earthLevel
    glBegin(GL_QUADS);
    glColor3ub(0,100,100);
    glVertex2d(115,655);
    glVertex2d(115,675);
    glVertex2d(220,675);
    glVertex2d(220,655);
    glEnd();
    text(120,660,1,"Earth: "+to_string(earthLevel)+"%",1.0,1.0,1.0);
    //life
    glBegin(GL_QUADS);
    glColor3ub(0,100,100);
    glVertex2d(230,655);
    glVertex2d(230,675);
    glVertex2d(335,675);
    glVertex2d(335,655);
    glEnd();
    text(235,660,1,"Life: "+to_string(life),1.0,1.0,1.0);
    //score
    glBegin(GL_QUADS);
    glColor3ub(0,100,100);
    glVertex2d(340,655);
    glVertex2d(340,675);
    glVertex2d(445,675);
    glVertex2d(445,655);
    glEnd();
    text(345,660,1,"Score: "+to_string(point),1.0,1.0,1.0);
}

void increaseLevel()
{
    if((presentTime-levelTime)>20000 && gameSpeed<10)
    {
        gameSpeed++;
        levelTime=presentTime;
    }
}

void earth()
{
    drawFiledCircle(225,-980,1000,1000,200-earthLevel*2,0,50+earthLevel*2);
    drawFiledCircle(225,-980,995,1000,100-earthLevel*2,100,150+earthLevel*2);
    drawFiledCircle(225,-980,990,1000,200-earthLevel*2,150,50+earthLevel*2);
    drawFiledCircle(225,-980,985,1000,200-earthLevel*2,220,150+earthLevel*2);
    glPointSize(2.0);
    glColor3ub(0,55+earthLevel*2,0);
    for(int i=0; i<nAsteroid; i++)
    {
        if(asteroids[i].y<=10 && earthLevel!=0)
        {
            earthLevel-=asteroids[i].sz/5.0;
            resetAnAsteroid(i);
            if(earthLevel<0)
                earthLevel=0;
        }
    }
}

int gameResult()
{
    if(earthLevel==0 || life==0)
    {
        text(172,400,2,"Game Over",1.0,0.0,0.0);
        text(115,360,2,"Your Total Score: "+to_string(point*earthLevel/100),1.6,0.7,0.7);
        text(120,100,1,"Press 'space' for Main Menu",1.0,1.0,1.0);
        asteroidGenerate();
        return 1;
    }
    else if(point>=1000)
    {
        point=1000;
        text(157,440,2,"Congratulation",0.3,1.0,0.3);
        text(95,400,2,"You Saved The Earth "+to_string(earthLevel)+"%",0.6,1.0,0.6);
        text(115,360,2,"Your Total Score: "+to_string(point*earthLevel/100),0.6,1.0,0.6);
        text(120,100,1,"Press 'space' for Main Menu",1.0,1.0,1.0);
        return 1;
    }
    return 0;
}

static void idle(void)
{
    presentTime=glutGet(GLUT_ELAPSED_TIME);
    enemiesMovement();
    planePosition();
    increaseLevel();
}

void reset()
{
    planeP = 165, planeLeft=0, planeRight=0;
    asteroidGenerate();
    bltGenerate();
    gameSpeed=0;
    point=0, life=3, earthLevel=100;
    presentTime=0, levelTime=0;
    glutIdleFunc(NULL);
}

void mainMenu()
{
    int menuX=200;
    text(90,580,0,"________GAME________",.5,1,.8);
    text(90,550,0,"_PROTECT The EARTH_",.5,1,.8);
    switch(mainMenuSelection)
    {
    case 0:
        if(oldGame)
            text(10,menuX+120,0,"Continue",0,1,1);
        text(10,menuX+90,1,"Play New Game",1,1,1);
        text(10,menuX+60,1,"Select Level: "+gameLevelSt[(nAsteroid/2)-1],1,1,1);
        text(10,menuX+30,1,"Back Ground: "+backGroundSt[backGround],1,1,1);
        text(10,menuX+0,1,"Quit Game",1,1,1);
        break;
    case 1:
        if(oldGame)
            text(10,menuX+120,1,"Continue",1,1,1);
        text(10,menuX+90,0,"Play New Game",0,1,1);
        text(10,menuX+60,1,"Select Level: "+gameLevelSt[(nAsteroid/2)-1],1,1,1);
        text(10,menuX+30,1,"Back Ground: "+backGroundSt[backGround],1,1,1);
        text(10,menuX+0,1,"Quit Game",1,1,1);
        break;
    case 2:
        if(oldGame)
            text(10,menuX+120,1,"Continue",1,1,1);
        text(10,menuX+90,1,"Play New Game",1,1,1);
        text(10,menuX+60,0,"Select Level: "+gameLevelSt[(nAsteroid/2)-1],0,1,1);
        text(10,menuX+30,1,"Back Ground: "+backGroundSt[backGround],1,1,1);
        text(10,menuX+0,1,"Quit Game",1,1,1);
        break;
    case 3:
        if(oldGame)
            text(10,menuX+120,1,"Continue",1,1,1);
        text(10,menuX+90,1,"Play New Game",1,1,1);
        text(10,menuX+60,1,"Select Level: "+gameLevelSt[(nAsteroid/2)-1],1,1,1);
        text(10,menuX+30,0,"Back Ground: "+backGroundSt[backGround],0,1,1);
        text(10,menuX+0,1,"Quit Game",1,1,1);
        break;
    case 4:
        if(oldGame)
            text(10,menuX+120,1,"Continue",1,1,1);
        text(10,menuX+90,1,"Play New Game",1,1,1);
        text(10,menuX+60,1,"Select Level: "+gameLevelSt[(nAsteroid/2)-1],1,1,1);
        text(10,menuX+30,1,"Back Ground: "+backGroundSt[backGround],1,1,1);
        text(10,menuX+0,0,"Quit Game",0,1,1);
        break;
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(backGround)
        displayStars();
    switch(pages)
    {
    case 0://Starting Page
        bgPlaneDesign();
        glPushMatrix();
        glTranslated(0,cos(planeDesignY)*20,0);
        mainMenu();
        glPopMatrix();
        starMove=0;
        glutIdleFunc(NULL);
        break;
    case 1://Game Page
        if(gameResult())
        {
            oldGame=0;
            mainMenuSelection = 1;
            pages = 2;
            glutIdleFunc(NULL);
        }
        else
        {
            glutIdleFunc(idle);
            earth();
            plane();
            asteroidArt();
            gameResult();
        }
        starMove=1;
        titleBar();
        Sleep(11-gameSpeed);
        break;
    case 2://Result Page
        starMove=0;
        titleBar();
        gameResult();
        break;
    }
    glutPostRedisplay();
    glutSwapBuffers();
}

void special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if(mainMenuSelection>1 || (oldGame && mainMenuSelection>0))
            mainMenuSelection--;
        break;
    case GLUT_KEY_LEFT:
        planeLeft=1;
        break;
    case GLUT_KEY_RIGHT:
        planeRight=1;
        break;
    case GLUT_KEY_DOWN:
        if(mainMenuSelection<4)
            mainMenuSelection++;
        break;
    }
}

void specialup(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        break;
    case GLUT_KEY_DOWN:
        break;
    case GLUT_KEY_LEFT:
        planeLeft=0;
        break;
    case GLUT_KEY_RIGHT:
        planeRight=0;
        break;
    }
}

void spaceKey()
{
    switch(pages)
    {
    case 0:
        switch(mainMenuSelection)
        {
        case 0:
            pages=1;
            break;
        case 1:
            pages=1;
            reset();
            play = 1;
            break;
        case 2:
            if(nAsteroid<6)
                nAsteroid+=2;
            else
                nAsteroid=2;
            break;
        case 3:
            if(backGround)
                backGround=0;
            else
                backGround=1;
            break;
        case 4:
            exit(0);
            break;
        }
        break;
    case 1:
        if(play)
        {
            pages=0;
            oldGame=1;
            mainMenuSelection=0;
        }
        else
        {
            play=1;
        }
        break;
    case 2:
        reset();
        pages=0;
    }
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        spaceKey();
        break;
    case 27:
        exit(0);
        break;
    case '=':
        if(gameSpeed<10)
            gameSpeed++;
        break;
    case '-':
        if(gameSpeed>=0)
            gameSpeed--;
        break;
    }
}

void init (void)
{
    HWND consoleWindow = GetConsoleWindow();
    MoveWindow(consoleWindow, 860, 10, 200, 720, TRUE);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(450,680);
    glutInitWindowPosition(400,10);
    glutCreateWindow("Protect Earth");
    glMatrixMode(GL_PROJECTION);
    glutIgnoreKeyRepeat(1);
    glLoadIdentity();
    glOrtho(0, 450, 0, 680, -10.0, 10.0);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialup);
    glutPostRedisplay();
    starGenerate();
    asteroidGenerate();
    bltGenerate();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    init();
    glClearColor(0,0,0,1);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glutMainLoop();
    return EXIT_SUCCESS;
}
