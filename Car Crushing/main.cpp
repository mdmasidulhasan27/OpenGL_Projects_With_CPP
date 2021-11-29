#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#define carNumber 4
#define lanePoints 11
struct car
{
    int opositCarSide;
    float opositCarY;
    int r, g, b;
}opositCars[carNumber];

struct laneDivider
{
    int x;
    float y;
}laneDividers[lanePoints];

int random(int minimum, int mximum){return (rand()%(mximum-minimum))+minimum;}
int carSide=0;
int point=0;
int life = 3;
float speed = .4;
void stringWrite(int x, int y, int font, std::string s, float r, float g, float b)
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

void laneDividerGenerator()
{
    for(int i=0; i<15; i++)
    {
        laneDividers[i].y=70*i;
    }
}

void carGenerate()
{
    for(int i=0; i<carNumber; i++)
    {
        opositCars[i].opositCarSide = random(0,3);
        opositCars[i].opositCarY = 700+i*300;
        opositCars[i].r = random(0,255);
        opositCars[i].g = random(0,255);
        opositCars[i].b = random(0,255);
    }
}

void roadSide()
{
    ///Left Side
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(0,0);
    glVertex2d(20,0);
    glVertex2d(20,10);
    glVertex2d(0,0);
    glEnd();

    glBegin(GL_POLYGON);
    glPopMatrix();
    glColor3ub(255,255,0);
    glVertex2d(0,0);
    glVertex2d(20,10);
    glVertex2d(20,45);
    glVertex2d(0,35);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(0,35);
    glVertex2d(20,45);
    glVertex2d(20,80);
    glVertex2d(0,70);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(0,70);
    glVertex2d(20,80);
    glVertex2d(20,115);
    glVertex2d(0,105);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(0,105);
    glVertex2d(20,115);
    glVertex2d(20,150);
    glVertex2d(0,140);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(0,140);
    glVertex2d(20,150);
    glVertex2d(20,185);
    glVertex2d(0,175);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(0,175);
    glVertex2d(20,185);
    glVertex2d(20,220);
    glVertex2d(0,210);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(0,210);
    glVertex2d(20,220);
    glVertex2d(20,255);
    glVertex2d(0,245);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(0,245);
    glVertex2d(20,255);
    glVertex2d(20,290);
    glVertex2d(0,280);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(0,280);
    glVertex2d(20,290);
    glVertex2d(20,325);
    glVertex2d(0,315);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(0,315);
    glVertex2d(20,325);
    glVertex2d(20,360);
    glVertex2d(0,350);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(0,350);
    glVertex2d(20,360);
    glVertex2d(20,395);
    glVertex2d(0,385);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(0,385);
    glVertex2d(20,395);
    glVertex2d(20,430);
    glVertex2d(0,420);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(0,420);
    glVertex2d(20,430);
    glVertex2d(20,465);
    glVertex2d(0,455);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(0,455);
    glVertex2d(20,465);
    glVertex2d(20,500);
    glVertex2d(0,490);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(0,490);
    glVertex2d(20,500);
    glVertex2d(20,535);
    glVertex2d(0,525);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(0,525);
    glVertex2d(20,535);
    glVertex2d(20,570);
    glVertex2d(0,560);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(0,560);
    glVertex2d(20,570);
    glVertex2d(20,605);
    glVertex2d(0,595);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(0,595);
    glVertex2d(20,605);
    glVertex2d(20,640);
    glVertex2d(0,630);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(0,630);
    glVertex2d(20,640);
    glVertex2d(20,675);
    glVertex2d(0,665);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(0,665);
    glVertex2d(20,675);
    glVertex2d(20,700);
    glVertex2d(0,690);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(0,690);
    glVertex2d(20,700);
    glVertex2d(20,735);
    glVertex2d(0,725);
    glEnd();


    ///Right Side
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(580,0);
    glVertex2d(600,0);
    glVertex2d(600,10);
    glVertex2d(580,0);
    glEnd();

    glBegin(GL_POLYGON);
    glPopMatrix();
    glColor3ub(255,255,0);
    glVertex2d(580,0);
    glVertex2d(600,10);
    glVertex2d(600,45);
    glVertex2d(580,35);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(580,35);
    glVertex2d(600,45);
    glVertex2d(600,80);
    glVertex2d(580,70);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(580,70);
    glVertex2d(600,80);
    glVertex2d(600,115);
    glVertex2d(580,105);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(580,105);
    glVertex2d(600,115);
    glVertex2d(600,150);
    glVertex2d(580,140);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(580,140);
    glVertex2d(600,150);
    glVertex2d(600,185);
    glVertex2d(580,175);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(580,175);
    glVertex2d(600,185);
    glVertex2d(600,220);
    glVertex2d(580,210);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(580,210);
    glVertex2d(600,220);
    glVertex2d(600,255);
    glVertex2d(580,245);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(580,245);
    glVertex2d(600,255);
    glVertex2d(600,290);
    glVertex2d(580,280);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(580,280);
    glVertex2d(600,290);
    glVertex2d(600,325);
    glVertex2d(580,315);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(580,315);
    glVertex2d(600,325);
    glVertex2d(600,360);
    glVertex2d(580,350);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(580,350);
    glVertex2d(600,360);
    glVertex2d(600,395);
    glVertex2d(580,385);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(580,385);
    glVertex2d(600,395);
    glVertex2d(600,430);
    glVertex2d(580,420);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(580,420);
    glVertex2d(600,430);
    glVertex2d(600,465);
    glVertex2d(580,455);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(580,455);
    glVertex2d(600,465);
    glVertex2d(600,500);
    glVertex2d(580,490);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(580,490);
    glVertex2d(600,500);
    glVertex2d(600,535);
    glVertex2d(580,525);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(580,525);
    glVertex2d(600,535);
    glVertex2d(600,570);
    glVertex2d(580,560);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(580,560);
    glVertex2d(600,570);
    glVertex2d(600,605);
    glVertex2d(580,595);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(580,595);
    glVertex2d(600,605);
    glVertex2d(600,640);
    glVertex2d(580,630);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(580,630);
    glVertex2d(600,640);
    glVertex2d(600,675);
    glVertex2d(580,665);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(580,665);
    glVertex2d(600,675);
    glVertex2d(600,700);
    glVertex2d(580,690);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2d(580,690);
    glVertex2d(600,700);
    glVertex2d(600,735);
    glVertex2d(580,725);
    glEnd();
    glPopMatrix();
}

void car()
{
    glPushMatrix();
    glTranslatef(200.0*carSide+100, 70.0, 0.0);
    glRotated(0,0,0,1);
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(-30,-35);
    glVertex2d(-30,-20);
    glVertex2d(30,-20);
    glVertex2d(30,-35);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(-30,10);
    glVertex2d(-30,25);
    glVertex2d(30,25);
    glVertex2d(30,10);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(0,255,0);
    glVertex2d(-25,-40);
    glVertex2d(-25,30);
    glVertex2d(-15,40);
    glVertex2d(15,40);
    glVertex2d(25,30);
    glVertex2d(25,-40);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,0,0);
    glVertex2d(-15,-30);
    glVertex2d(-15,10);
    glVertex2d(15,10);
    glVertex2d(15,-30);
    glEnd();
    //back glass
    glBegin(GL_POLYGON);
    glColor3ub(0,50,0);
    glVertex2d(-23,-38);
    glVertex2d(-23,-7);
    glVertex2d(23,-7);
    glVertex2d(23,-38);
    glEnd();
    //front glass
    glBegin(GL_POLYGON);
    glColor3ub(255,255,255);
    glVertex2d(-15,11);
    glVertex2d(-23,24);
    glVertex2d(23,24);
    glVertex2d(15,11);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2d(-15,11);
    glVertex2d(-23,24);
    glVertex2d(23,24);
    glVertex2d(15,11);
    glEnd();
    //left glass
    glBegin(GL_POLYGON);
    glColor3ub(255,255,255);
    glVertex2d(-22,-5);
    glVertex2d(-22,19);
    glVertex2d(-17,9);
    glVertex2d(-17,-5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2d(-22,-5);
    glVertex2d(-22,19);
    glVertex2d(-17,9);
    glVertex2d(-17,-5);
    glEnd();
    //right glass
    glBegin(GL_POLYGON);
    glColor3ub(255,255,255);
    glVertex2d(18,-5);
    glVertex2d(18,10);
    glVertex2d(23,20);
    glVertex2d(23,-5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2d(18,-5);
    glVertex2d(18,10);
    glVertex2d(23,20);
    glVertex2d(23,-5);
    glEnd();
    glPopMatrix();

}

void opositCar(int i)
{
    glPushMatrix();
    glTranslatef(opositCars[i].opositCarSide*200+100, opositCars[i].opositCarY-=speed*1.5, 0.0);
    glRotated(180,0,0,1);
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(-30,-35);
    glVertex2d(-30,-20);
    glVertex2d(30,-20);
    glVertex2d(30,-35);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0);
    glVertex2d(-30,10);
    glVertex2d(-30,25);
    glVertex2d(30,25);
    glVertex2d(30,10);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3ub(opositCars[i].r,255,opositCars[i].b);
    glVertex2d(-25,-40);
    glVertex2d(-25,30);
    glVertex2d(-15,40);
    glVertex2d(15,40);
    glVertex2d(25,30);
    glVertex2d(25,-40);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255,opositCars[i].g,0);
    glVertex2d(-15,-30);
    glVertex2d(-15,10);
    glVertex2d(15,10);
    glVertex2d(15,-30);
    glEnd();
    //back glass
    glBegin(GL_POLYGON);
    glColor3ub(0,50,0);
    glVertex2d(-23,-38);
    glVertex2d(-23,-7);
    glVertex2d(23,-7);
    glVertex2d(23,-38);
    glEnd();
    //front glass
    glBegin(GL_POLYGON);
    glColor3ub(255,255,255);
    glVertex2d(-15,11);
    glVertex2d(-23,24);
    glVertex2d(23,24);
    glVertex2d(15,11);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2d(-15,11);
    glVertex2d(-23,24);
    glVertex2d(23,24);
    glVertex2d(15,11);
    glEnd();
    //left glass
    glBegin(GL_POLYGON);
    glColor3ub(255,255,255);
    glVertex2d(-22,-5);
    glVertex2d(-22,19);
    glVertex2d(-17,9);
    glVertex2d(-17,-5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2d(-22,-5);
    glVertex2d(-22,19);
    glVertex2d(-17,9);
    glVertex2d(-17,-5);
    glEnd();
    //right glass
    glBegin(GL_POLYGON);
    glColor3ub(255,255,255);
    glVertex2d(18,-5);
    glVertex2d(18,10);
    glVertex2d(23,20);
    glVertex2d(23,-5);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3ub(0,0,0);
    glVertex2d(18,-5);
    glVertex2d(18,10);
    glVertex2d(23,20);
    glVertex2d(23,-5);
    glEnd();
    glPopMatrix();
}

void road()
{
    glBegin(GL_QUADS);
    glColor3ub(100,100,100);
    glVertex2d(20,0);
    glVertex2d(20,700);
    glVertex2d(580,700);
    glVertex2d(580,0);
    glEnd();
}

void laneDevider()
{
    for(int i=0; i<lanePoints; i++){
        glPushMatrix();
        glTranslatef(200,laneDividers[i].y,0);
        glBegin(GL_QUADS);
        glColor3ub(255,255,0);
        glVertex2d(0,0);
        glVertex2d(0,40);
        glVertex2d(10,40);
        glVertex2d(10,0);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(400,laneDividers[i].y,0);
        glBegin(GL_QUADS);
        glColor3ub(255,255,0);
        glVertex2d(0,0);
        glVertex2d(0,40);
        glVertex2d(10,40);
        glVertex2d(10,0);
        glEnd();
        glPopMatrix();
        laneDividers[i].y-=speed;
        if(laneDividers[i].y<-70){
            laneDividers[i].y=700;
            point++;
        }
    }
}

static void idle(void)
{
    for(int i=0; i<carNumber; i++){
        if(opositCars[i].opositCarY<=-200){
            opositCars[i].opositCarSide=random(0,3);
            opositCars[i].opositCarY=800;
        }
        if(opositCars[i].opositCarSide==carSide)
        {
            if(opositCars[i].opositCarY<105 && opositCars[i].opositCarY>=30){
                life--;
                opositCars[i].opositCarY=800+50;
            }
        }
    }
    glutPostRedisplay();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
    roadSide();
    road();
    laneDevider();
    car();
    for(int i=0; i<carNumber; i++){
        opositCar(i);
    }
    stringWrite(440,680,11,"Score: "+std::to_string(point),1,1,1);
    stringWrite(30,680,11,"Life: "+std::to_string(life),1,1,1);
    if(life==0){
        glutIdleFunc(NULL);
        stringWrite(250,330,11,"Game Over",1,0,0);
    }
    glutSwapBuffers();
}

void special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if(carSide>0)
            carSide--;
        break;
    case GLUT_KEY_RIGHT:
        if(carSide<2)
            carSide++;
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    carGenerate();
    laneDividerGenerator();
    glutInitWindowSize(600,700);
    glutInitWindowPosition(400,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Car Crushing Game");
    glutSpecialFunc(special);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    point = 0;
    glClearColor(1,1,1,1);
    glOrtho(0, 600, 0, 700, 0, 600);
    glutMainLoop();
    return EXIT_SUCCESS;
}
