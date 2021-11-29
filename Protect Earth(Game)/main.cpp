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
#define numberOfStars 1000
        //Name spaces:
using namespace std;
        //Small Functions:
int random(int minimum, int mximum){return (rand()%(mximum-minimum))+minimum;}
        //Static variables:
static int planeX = 165, planeLeft=0, planeRight=0;
static int bulletsX = planeX,bulletsY = 0;
static int asteroidY=700, asteroidSize=random(5,70), asteroidX=random(border,450-asteroidSize-border);
static int gameSpeed=0, play=0;
static int score=0, life=3, earthLevel=100;
static int presentTime=0, levelTime=0;
        //Structures:
struct star
{
    int starX;
    int starY;
}stars[numberOfStars];
struct asteroid
{
    int asteroidX;
    int asteroidY;
    int asteroidSize;
    int asteroidSpeed;
};
        //Functions:

void starGenerate()
{
    for(int i=0; i<numberOfStars; i++){
        stars[i].starX=random(0,450);
        stars[i].starY=random(0,650);
    }
}

void displayStars()
{
    int i;
    glPointSize(1.0);
    glBegin(GL_POINTS);
    glColor3ub(200,200,200);
    for(i=0; i<numberOfStars; i++){
        glVertex2d(stars[i].starX,stars[i].starY);
        if(stars[i].starY<0)
            stars[i].starY=650;
        else
            stars[i].starY--;
    }
    glEnd();
}

void drawFiledCircle(float cx, float cy, float r, int num_segments, int red, int green, int blue)
{
    glBegin(GL_POLYGON);
    glColor3ub(red,green,blue);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}

void asteroidArt()
{
    int fireRatio=(asteroidSize*10)/100;
    int randomFireR=random(128,255);
    int randomFireG=random(17,192);
    int r = asteroidSize/2;
    int cx = asteroidX+(asteroidSize/2);
    int cy = asteroidY-(asteroidSize/2);
    glBegin(GL_TRIANGLES);
    glColor3ub(randomFireR,randomFireG,0);
    glVertex2d(cx-(r+fireRatio),cy+fireRatio);
    glVertex2d(cx,asteroidY+(fireRatio+(gameSpeed+1))*8+random(0,50));
    glVertex2d(cx+(r+fireRatio),cy+fireRatio);
    glEnd();
    drawFiledCircle(cx,cy+fireRatio,r+fireRatio,r+fireRatio,randomFireR,randomFireG,0);
    drawFiledCircle(cx,cy,r,r+10,200,200,200);
}

void bulletsDynamic()
{
    glBegin(GL_TRIANGLES);
    glColor3ub(255,255,255);
    glVertex2d(planeX+0,border+35);
    glVertex2d(planeX+5,border+45);
    glVertex2d(planeX+10,border+35);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(255,255,255);
    glVertex2d(planeX+15,border+35);
    glVertex2d(planeX+20,border+45);
    glVertex2d(planeX+25,border+35);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(255,255,255);
    glVertex2d(planeX+95,border+35);
    glVertex2d(planeX+100,border+45);
    glVertex2d(planeX+105,border+35);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(255,255,255);
    glVertex2d(planeX+110,border+35);
    glVertex2d(planeX+115,border+45);
    glVertex2d(planeX+120,border+35);
    glEnd();
}

void bulletsStatic()
{
    glBegin(GL_TRIANGLES);
    glColor3ub(255,255,255);
    glVertex2d(bulletsX+0,bulletsY+border+35);
    glVertex2d(bulletsX+5,bulletsY+border+45);
    glVertex2d(bulletsX+10,bulletsY+border+35);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(255,255,255);
    glVertex2d(bulletsX+15,bulletsY+border+35);
    glVertex2d(bulletsX+20,bulletsY+border+45);
    glVertex2d(bulletsX+25,bulletsY+border+35);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(255,255,255);
    glVertex2d(bulletsX+95,bulletsY+border+35);
    glVertex2d(bulletsX+100,bulletsY+border+45);
    glVertex2d(bulletsX+105,bulletsY+border+35);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3ub(255,255,255);
    glVertex2d(bulletsX+110,bulletsY+border+35);
    glVertex2d(bulletsX+115,bulletsY+border+45);
    glVertex2d(bulletsX+120,bulletsY+border+35);
    glEnd();
}

void planeBody()
{
    //Front wing:
    glBegin(GL_QUADS);
    glColor3ub(255-life*70,220,255);
    glVertex2d(planeX+0,border+20);
    glVertex2d(planeX+55,border+35);
    glVertex2d(planeX+65,border+35);
    glVertex2d(planeX+120,border+20);
    glEnd();
    //Rare wing:
    glBegin(GL_QUADS);
    glColor3ub(40,170,240);
    glVertex2d(planeX+35,border+5);
    glVertex2d(planeX+55,border+12);
    glVertex2d(planeX+65,border+12);
    glVertex2d(planeX+85,border+5);
    glEnd();
    //Body:
    drawFiledCircle(planeX+60,border+40,10,10,255-life*80,life*40,100+life*30);
    drawFiledCircle(planeX+60,border+38,7,100,230,230,230);
    glBegin(GL_POLYGON);
    glColor3ub(255-life*80,life*50,100+life*35);
    glVertex2d(planeX+58,border);
    glVertex2d(planeX+50,border+40);
    glVertex2d(planeX+70,border+40);
    glVertex2d(planeX+62,border);
    glEnd();
}

void plane()
{
    bulletsStatic();
    if(bulletsY>200)
    {
        bulletsDynamic();
    }
    planeBody();
}

void bullets()
{
    if(bulletsY<600)
    {
        bulletsY+=15;
    }
    else
    {
        bulletsY=0;
        bulletsX=planeX;
    }
}

int enemyKilled()
{
    if(((asteroidX<=bulletsX && asteroidX+asteroidSize>=bulletsX)||(asteroidX<=bulletsX+10 && asteroidX+asteroidSize>=bulletsX+10))
            || ((asteroidX<=bulletsX+15 && asteroidX+asteroidSize>=bulletsX+15)||(asteroidX<=bulletsX+25 && asteroidX+asteroidSize>=bulletsX+25))
            || ((asteroidX<=bulletsX+95 && asteroidX+asteroidSize>=bulletsX+95)||(asteroidX<=bulletsX+105 && asteroidX+asteroidSize>=bulletsX+105))
            || ((asteroidX<=bulletsX+110 && asteroidX+asteroidSize>=bulletsX+110)||(asteroidX<=bulletsX+120 && asteroidX+asteroidSize>=bulletsX+120)))
        if(asteroidY<=bulletsY)
        {
            score+=(asteroidSize/10);
            return 1;
        }
    return 0;
}

int planeDestroy()
{
    if((asteroidX>planeX && asteroidX<planeX+120)||(asteroidX+asteroidSize>planeX && asteroidX+asteroidSize<planeX+120))
        if(asteroidY<border+40 && life>0){
            life--;
            return 1;
        }
    return 0;
}

void enemiesMovement()
{
    if(!(asteroidY>0) || enemyKilled() || planeDestroy())
    {
        asteroidY=700;
        asteroidSize=random(10,70);
        asteroidX=random(border,450-border-asteroidSize);
    }
    else
    {
        asteroidY-=2;
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
        switch(font){
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
    {
        if(planeX>border)
            planeX-=ceil(gameSpeed/5.0)+2;
    }
    if(planeRight)
    {
        if(planeX<450-120-border)
            planeX+=ceil(gameSpeed/5.0)+2;
    }
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
    text(345,660,1,"Score: "+to_string(score),1.0,1.0,1.0);
}

void playIcon()
{
    if(!play){
        glBegin(GL_LINE_LOOP);
        glColor3ub(200,200,200);
        glVertex2d(200,300);
        glVertex2d(200,350);
        glVertex2d(250,325);
        glEnd();
    }
}

void increaseLevel()
{
    if((presentTime-levelTime)>20000 && gameSpeed<10){
        gameSpeed++;
        levelTime=presentTime;
    }
}

void earth()
{
    int i;
    drawFiledCircle(225,-980,1000,1000,200-earthLevel*2,0,50+earthLevel*2);
    glPointSize(2.0);
    glColor3ub(0,55+earthLevel*2,0);
    glBegin(GL_POINTS);
    for(i=0; i<100; i++)
    {
        glVertex2d(random(170,280),random(0,20));
    }
    for(i=0; i<100; i++)
    {
        glVertex2d(random(100,350),random(0,15));
    }
    for(i=0; i<100; i++)
    {
        glVertex2d(random(50,400),random(0,8));
    }
    glEnd();
    if(asteroidY-10==0 && earthLevel!=0){
        earthLevel-=asteroidSize/3;
        if(earthLevel<0)
            earthLevel=0;
    }
}

int gameResult()
{
    if(earthLevel==0 || life==0){
        text(172,400,2,"Game Over",1.0,0.0,0.0);
        text(120,100,1,"Press 'p' to play again",1.0,1.0,1.0);
        return 1;
    }
    else if(score>=1000){
        score=1000;
        text(157,440,2,"Congratulation",0.3,1.0,0.3);
        text(95,400,2,"You Saved The Earth "+to_string(earthLevel)+"%",0.6,1.0,0.6);
        text(115,360,2,"Your Total Score: "+to_string(score*earthLevel/100),0.6,1.0,0.6);
        text(120,100,1,"Press 'p' to play again",1.0,1.0,1.0);
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
    glutPostRedisplay();
}

void reset()
{
    planeX = 165, planeLeft=0, planeRight=0;
    bulletsX = planeX,bulletsY = 0;
    asteroidY=700, asteroidSize=random(5,70), asteroidX=random(border,450-asteroidSize-border);
    gameSpeed=0, play=0;
    score=0, life=3, earthLevel=100;
    presentTime=0, levelTime=0;
    glutIdleFunc(NULL);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    displayStars();
    if(gameResult())
    {
        glutIdleFunc(NULL);
    }
    else
    {
        earth();
        plane();
        asteroidArt();
        playIcon();
        gameResult();
        bullets();
    }
    titleBar();
    Sleep(11-gameSpeed);
    glutSwapBuffers();
}

void special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        break;
    case GLUT_KEY_LEFT:
        planeLeft=1;
        break;
    case GLUT_KEY_RIGHT:
        planeRight=1;
        break;
    }
}

void specialup(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:

        break;
    case GLUT_KEY_LEFT:
        planeLeft=0;
        break;
    case GLUT_KEY_RIGHT:
        planeRight=0;
        break;
    }
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
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
    case ' ':
        if(play){
            play=0;
            glutIdleFunc(NULL);
        }
        else{
            play=1;
            glutIdleFunc(idle);
        }
        break;
    case 'p':
        reset();
        break;
    }
    glutPostRedisplay();
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
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    init();
    glClearColor(0,0,0,1);
    glutMainLoop();
    return EXIT_SUCCESS;
}
