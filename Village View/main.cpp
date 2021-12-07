#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>
#define nFlowers 100
#define numberOfStars 500
#define numberOfClouds 6
#define windowX 140
#define windowY 100
int random(int mn, int mx)
{
    return ((rand()%(mx-mn+1)) + mn);
}
int dayNight = 1; //1 for day and 0 for night
int dayNightColor=255;
float sunX,sunY, boatX;
double speed = 0;

struct star
{
    double starX;
    double starY;
    double sz;
} stars[numberOfStars];

struct flowerPosition
{
    float x;
    float y;
    float sz;
    float speed;
    int r;
    int g;
    int b;
    int color;
} flowers[nFlowers], clouds[numberOfClouds];
//static float flowerX;
static float flowerY=0;

void positionsGenerate()
{
    int i;
    for(i=0; i<100; i++)
    {
        flowers[i].x=i*2.5;
        flowers[i].y=(i%3)*3;
        flowers[i].sz=random(0,10);
    }
    return;
}

void starGenerate()
{
    for(int i=0; i<numberOfStars; i++)
    {
        stars[i].starX=random(0,windowX);
        stars[i].starY=random(0,windowY);
    }
}

void cloudsGenerate()
{
    for(int i=0; i<numberOfClouds; i++)
    {
        clouds[i].x = random(-30,3400)/20;
        clouds[i].y = random(60,100);
        clouds[i].sz = clouds[i].y/100.0;
        clouds[i].color = random(0,100);
        clouds[i].speed = random(5,50)/1000.0;
    }
}

void starsDisplay()
{
    int i;

    for(i=0; i<numberOfStars; i++)
    {
        glPointSize(random(1,5)/10.0);
        glBegin(GL_POINTS);
        glColor3ub(255,255,255);
        glVertex2f(stars[i].starX,stars[i].starY);
        glEnd();
    }
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

void displaySun(float x, float y)
{
    glPushMatrix();
    glTranslated(x,y,0);
    drawFiledCircle(0.0,0.0,10.0,100,255,100+dayNightColor*1.5,0);
    glPopMatrix();
}

void displayMoon(float x, float y)
{
    glPushMatrix();
    glTranslated(x,y,0);
    drawFiledCircle(0.0,0.0,7.0,100,250,250,250);
    glPopMatrix();
}

void cloud(float x, float y, float s, float color)
{
    glPushMatrix();
    glTranslated(x,y,0);
    glScaled(s,s,0);
    drawFiledCircle(-8.0,0.0,6.0,100,color+(dayNightColor/2.0),color+(dayNightColor/2.0),color+(dayNightColor/2.0));
    drawFiledCircle(-0.0,0.0,8.0,100,color+(dayNightColor/2.0),color+(dayNightColor/2.0),color+(dayNightColor/2.0));
    drawFiledCircle(8.0,0.0,5.0,100,color+(dayNightColor/2.0),color+(dayNightColor/2.0),color+(dayNightColor/2.0));
    glPopMatrix();
}

void displayClouds()
{
    for(int i=0; i<numberOfClouds; i++)
    {
        cloud(clouds[i].x, clouds[i].y, clouds[i].sz, clouds[i].color);
        clouds[i].x+=clouds[i].speed;
        if(clouds[i].x>170)
            clouds[i].x = -30;
    }
}

void sunFlower()
{
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
    glBegin(GL_POLYGON);
    glColor3ub(255,149,15);
    glVertex2d(0,0);
    glColor3ub(250,250,15);
    glVertex2d(-5,15);
    glVertex2d(0,20);
    glVertex2d(+5,15);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255,149,15);
    glVertex2d(0,0);
    glColor3ub(250,250,15);
    glVertex2d(-5,-15);
    glVertex2d(0,-20);
    glVertex2d(+5,-15);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255,149,15);
    glVertex2d(0,0);
    glColor3ub(250,250,15);
    glVertex2d(-15,-5);
    glVertex2d(-20,0);
    glVertex2d(-15,5);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255,149,15);
    glVertex2d(0,0);
    glColor3ub(250,250,15);
    glVertex2d(15,-5);
    glVertex2d(20,0);
    glVertex2d(15,5);
    glEnd();

    glPushMatrix();
    glRotated(45,0,0,1);
    glColor3ub(255,150,100);
    glBegin(GL_POLYGON);
    glColor3ub(255,149,15);
    glVertex2d(0,0);
    glColor3ub(250,250,15);
    glVertex2d(-5,15);
    glVertex2d(0,20);
    glVertex2d(+5,15);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255,149,15);
    glVertex2d(0,0);
    glColor3ub(250,250,15);
    glVertex2d(-5,-15);
    glVertex2d(0,-20);
    glVertex2d(+5,-15);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255,149,15);
    glVertex2d(0,0);
    glColor3ub(250,250,15);
    glVertex2d(-15,-5);
    glVertex2d(-20,0);
    glVertex2d(-15,5);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(255,149,15);
    glVertex2d(0,0);
    glColor3ub(250,250,15);
    glVertex2d(15,-5);
    glVertex2d(20,0);
    glVertex2d(15,5);
    glEnd();
    glPopMatrix();
    drawFiledCircle(0,0,4,50,155,55,0);
}

void displayFlowers()
{
    for(int i=0; i<20; i++)
    {
        glPushMatrix();
        glTranslated(flowers[i].x+100,flowers[i].y-2,0);
        glScaled(.12,.12,0);
        sunFlower();
        glPopMatrix();
    }
}

void displayBoat(float x, float y, float sz, int r, int g, int b)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScaled(sz,sz,0);
    glBegin(GL_QUADS);
    glColor3ub(139,69,19);
    glVertex2f(22.0f, -17.5f);
    glVertex2f(21.0f, -16.5f);
    glVertex2f(17.50f, -16.5f);
    glVertex2f(18.0f, -17.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0,0,0);
    glVertex2f(22.0f, -18.0f);
    glVertex2f(22.0f, -17.5f);
    glVertex2f(17.0f, -17.5f);
    glVertex2f(17.0f, -18.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(r,g,b);
    glVertex2f(20.5f, -16.5f);
    glVertex2f(21.0f, -14.5f);
    glVertex2f(18.5f, -14.5f);
    glVertex2f(18.0f, -16.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(139,69,19);
    glVertex2f(19.8f, -14.5f);
    glVertex2f(19.8f, -14.0f);
    glVertex2f(19.7f, -14.0f);
    glVertex2f(19.7f, -14.5f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0,0,0);
    glVertex2f(17.0f, -18.0f);
    glVertex2f(17.0f, -17.5f);
    glVertex2f(15.5f, -17.2f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0,0,0);
    glVertex2f(22.0f, -17.5f);
    glVertex2f(22.0f, -18.0f);
    glVertex2f(23.5f, -17.2f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0,0,0);
    glVertex2f(17.0f, -17.5f);
    glVertex2f(18.0f, -17.5f);
    glVertex2f(17.5f, -16.5f);
    glEnd();

    glPopMatrix();
}

void displayTree(float x, float y, float sz)
{
    //left upper side
    glPushMatrix();
    glTranslated(x,y,0);
    glScaled(sz,sz,0);

    glPushMatrix();
    glColor3ub(50,205,50);
    glTranslatef(-10.5, 2.5, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50,205,50);
    glTranslatef(-7.5, 2.5, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50,205,50);
    glTranslatef(-8.5, 3.5, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(50,205,50);
    glTranslatef(-10.0, 4.0, 0);
    glutSolidSphere(1.0, 150, 150);
    glPopMatrix();

// left side tree
    glBegin(GL_POLYGON);
    glColor3ub(139,69,19);
    glVertex2f(-9.5,1);
    glVertex2f(-9,1.5);
    glVertex2f(-9.5,2.5);
    glVertex2f(-10,2);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(139,69,19);
    glVertex2f(-9,1.5);
    glVertex2f(-8.5,1);
    glVertex2f(-8,2);
    glVertex2f(-8,2.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(139,69,19);
    glVertex2f(-9.5,1);
    glVertex2f(-9.5,-3.5);
    glVertex2f(-9,-4);
    glVertex2f(-8.5,-3.5);
    glVertex2f(-8.5,1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(139,69,19);
    glVertex2f(-9.5,1);
    glVertex2f(-9,1.5);
    glVertex2f(-8.5,1);
    glEnd();

    glPopMatrix();
}

void displayHouse(float x, float y, float sz)
{
    ///displayHouse on right side
    glPushMatrix();
    glScaled(sz,sz,0);
    glTranslated(x,y,0);

    //top
    glBegin(GL_POLYGON);
    glColor3ub(37,50+dayNightColor/1.3,59);
    glVertex2f(25.3,1.2);
    glVertex2f(21.3,1.2);
    glColor3ub(37,150,49);
    glVertex2f(23,-1);
    glVertex2f(27,-1);
    glEnd();

    //top down
    glBegin(GL_POLYGON);
    glColor3ub(47,79,79);
    glVertex2f(21.5,1);
    glVertex2f(21.3,1.2);
    glVertex2f(19.5,-1);
    glVertex2f(20,-1);
    glEnd();

    //left middle
    glBegin(GL_POLYGON);
    glColor3ub(144,90,7);
    glVertex2f(21.5,1);
    glColor3ub(184,134,11);
    glVertex2f(20,-1);
    glVertex2f(20,-2.5);
    glVertex2f(23,-3);
    glVertex2f(23,-1);
    glEnd();

    ///window
    glBegin(GL_POLYGON);
    glColor3ub(255-dayNightColor,255-dayNightColor,0);
    glVertex2f(22,-2.2);
    glVertex2f(22,-1.1);
    glVertex2f(21,-1);
    glVertex2f(21,-2);
    glEnd();
    //lower part
    glBegin(GL_POLYGON);
    glColor3ub(47,79,79);
    glVertex2f(23,-3);
    glVertex2f(20,-2.5);
    glVertex2f(19.7,-2.9);
    glVertex2f(23,-3.5);
    glEnd();
    ///middle part
    glBegin(GL_POLYGON);
    glColor3ub(205,133,63);
    glVertex2f(26.5,-3);
    glColor3ub(135,93,33);
    glVertex2f(26.5,-1);
    glVertex2f(23,-1);
    glColor3ub(205,133,63);
    glVertex2f(23,-3);
    glEnd();
    ///lower part
    glBegin(GL_POLYGON);
    glColor3ub(47,79,79);
    glVertex2f(23,-3);
    glVertex2f(23,-3.5);
    glVertex2f(27,-3.5);
    glVertex2f(26.5,-3);
    glEnd();

    ///door right
    //polygon a//
    glBegin(GL_POLYGON);
    glColor3ub(255-dayNightColor,255-dayNightColor,0);
    glVertex2f(25.5,-3);
    glVertex2f(25.5,-1.2);
    glVertex2f(24,-1.2);
    glVertex2f(24,-3);
    glEnd();

    //right part
    glBegin(GL_POLYGON);
    glColor3ub(140,62,25);
    glVertex2f(24.7,-3);
    glVertex2f(24.7, -1.2);
    glVertex2f(24,-1.2);
    glVertex2f(24,-3);
    glEnd();

// 2nd part
    glBegin(GL_POLYGON);
    glColor3ub(140,62,25);
    glVertex2f(25.5,-3);
    glVertex2f(25.5,-1.2);
    glVertex2f(24.8,-1.4);
    glVertex2f(24.8,-3);
    glEnd();
    glPopMatrix();
}

void backGround()
{
    //sky
    glBegin(GL_POLYGON);
    glColor3ub(dayNightColor/3,dayNightColor-55,dayNightColor);
    glVertex2d(0,20);
    glVertex2d(0,windowY);
    glVertex2d(windowX,100);
    glVertex2d(windowX,20);
    glEnd();

    if(sunY<50)
        starsDisplay();
    displaySun(sunX,sunY);
    displayMoon(sunX,-(sunY*4));
    displayClouds();

    //river
    glBegin(GL_POLYGON);
    glColor3ub(dayNightColor/4.0, dayNightColor/4.0, 100+dayNightColor/2.0);
    glVertex2d(0,0);
    glVertex2d(0,20);
    glColor3ub(dayNightColor/4.0,dayNightColor/4.0,dayNightColor);
    glVertex2d(windowX,20);
    glVertex2d(windowX,0);
    glEnd();

    //ground
    glBegin(GL_POLYGON);
    glColor3ub(dayNightColor/4.0,100+dayNightColor/2.0,dayNightColor/4.0);
    glVertex2d(75,17);
    glColor3ub(dayNightColor/4.0,dayNightColor,dayNightColor/4.0);
    glVertex2d(windowX,17);
    glVertex2d(windowX,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(10,40,10);
    glVertex2d(75,17);
    glVertex2d(73,15);
    glVertex2d(windowX-2,0);
    glVertex2d(windowX,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(dayNightColor/4.0,100+dayNightColor/2.0,dayNightColor/4.0);
    glVertex2d(60,0);
    glColor3ub(dayNightColor/4.0,dayNightColor,dayNightColor/4.0);
    glVertex2d(windowX,17);
    glVertex2d(windowX,0);
    glEnd();

    displayBoat(clouds[5].x,33,.75,150,159,255);
    displayBoat(clouds[6].x,33,.75,250,159,255);
    displayBoat(clouds[4].x,33,.8,255,120,61);
    displayBoat(clouds[3].x,36,1,250,59,21);
    if(speed-30)
        displayBoat(boatX,50+cos(boatX)/2,2,255,99,71);
    if(boatX<30.0 && dayNight)
        boatX+=0.02;
    else
        boatX-=0.02;
    displayHouse(8,8,3);
    displayTree(10,50.2,2);
    displayHouse(.5,5.2,5);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    backGround();
    displayFlowers();
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
    if(flowerY>windowY)
        flowerY=0;
    flowerY+=.005;
    speed+=.01;
    float theta = 2.0f * 3.1415926f * float(speed) / float(80);
    sunX = (windowX/2) * cosf(theta)+(windowX/2);
    sunY = (windowY/2) * sinf(theta)+(windowY/2);
    dayNightColor=sunY*2+55;
    sunY-=20;
    if(sunY>0)
        dayNight=1;
    else dayNight=0;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    positionsGenerate();
    starGenerate();
    cloudsGenerate();
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
