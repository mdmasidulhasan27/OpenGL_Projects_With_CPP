#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#endif
#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>

void rock();
void display1();
void display2();
void display3();
void ship();
void water();
void water2();
void water3();
void sun();
void moon();
void sky();
void shipCrackLeft();
void shipCrackRight();
void shipCrack();
void shipChimneyLeft();
void shipChimneyRight();
void night();
void cloud1();
void cloud2();
void cloud3();
void boat();
void humanBoat();
void onlyBoat();
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy);

float a=0,b=0,c=0,x=0,i=0,w=0,boaty=0;
float diff=0;
void update(int value)
{
//    a+=1.0;
//    glutPostRedisplay();
//    glutTimerFunc(10,update,0);

    a+=3.0;
    w-=2.0;
    if(w<=-100)
    {
        w=0;
    }
    glutPostRedisplay();

    glutTimerFunc(10,update,0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    display1();
    if(a>1200)
    {
        b+=1.0;
        display2();
    }
    if(b>400)
    {
        c+=0.1;
        display3();
    }
    if(c>1550)
    {
        a=0,b=0,c=0,x=0,i=0,w=0;
    }
    glFlush();
    glutSwapBuffers();
}


void display1()
{
    glClear(GL_COLOR_BUFFER_BIT);
    sky();
    sun();
    glPushMatrix();
    glTranslated(-a,-5,-0.0);
    cloud1();
    cloud2();
    cloud3();
    glPopMatrix();
    water2();
    glPushMatrix();
    glTranslated(a,75,0.0);
    ship();
    glPopMatrix();
    water();
    water3();
}

void display2()
{

    glClear(GL_COLOR_BUFFER_BIT);
    night();
    moon();
    glPushMatrix();
    glTranslated(-b,-5,-0.0);
    cloud1();
    cloud2();
    cloud3();
    glPopMatrix();
    water2();
    rock();
    glPushMatrix();
    glTranslated(b,75,0.0);
    ship();
    glPopMatrix();
    water();
    water3();

}

void display3()
{
    glClear(GL_COLOR_BUFFER_BIT);
    x-=0.1;
    night();
    moon();
    glPushMatrix();
    glTranslated(-b,-5,0.0);
    cloud1();
    cloud2();
    cloud3();
    glPopMatrix();
    water2();
    rock();


    glPushMatrix();
    glTranslated(c+400,85+x,0.0);
    glRotated(-7,0,0,1);
    //ship();
    shipCrack();
    glPopMatrix();
    glPushMatrix();
    glTranslated(c-400,85+x,0.0);
    glRotated(-16,2,0,1);
    shipChimneyRight();
    glPopMatrix();
    water();
    water3();
    if(b>500 && b<1000){
    for(int i=0; i<6; i++){
        glPushMatrix();
        glScaled(3,3,0);
        glTranslated(150+(i*30),30+(sinf(boaty)*(-1*((i%2)+1))),0);
        onlyBoat();
        glPopMatrix();
    }
    }
    if(b>=1000){
    for(int i=0; i<6; i++){
        glPushMatrix();
        glScaled(3+diff/40.0,3+diff/40.0,0);
        glTranslated(150+(i*30)+(diff*i/6.0),30+(sinf(boaty)*(-1*((i%2)+1)))-diff/2.0,0);
        humanBoat();
        glPopMatrix();
        diff+=.01;
    }
    }
    boaty+=.05;
}

void onlyBoat()
{
    //glScaled(1,1,0);

    glColor3ub(255,140,0); //base
    glBegin(GL_POLYGON);
    glVertex2f(0.5,5.0);
    glVertex2f(3,1);
    glVertex2f(22,1);
    glVertex2f(24.0,5.0);
    glEnd();

    glColor3ub(0,0,0); //ring
    glBegin(GL_POLYGON);
    glVertex2f(1.35,3.5);
    glVertex2f(1.6,3.2);
    glVertex2f(23.2,3.2);
    glVertex2f(23.35,3.5);
    glEnd();

    glColor3ub(255,140,0); //base
    glBegin(GL_POLYGON);
    glVertex2f(21.0,5.0);
    glVertex2f(21.9,6.0);
    glVertex2f(24.5,6.0);
    glVertex2f(24.0,5.0);
    glEnd();

}


void humanBoat()
{
    ///Human Boat
    //glScaled(1,1,0);

    glColor3ub(253,228,200);//human
    circle(1.0,0.5,19.8,5.45);
    circle(1.0,0.5,18.0,5.45);
    circle(1.0,0.5,15.2,5.45);
    circle(1.0,0.5,12.5,5.45);
    circle(1.0,0.5,9.8,5.45);
    circle(1.0,0.5,8.0,5.45);
    circle(1.0,0.5,5.4,5.45);
    circle(1.0,0.5,3.0,5.45);

    glColor3ub(240,102,0); //base
    glBegin(GL_POLYGON);
    glVertex2f(0.5,5.0);
    glVertex2f(3,1);
    glVertex2f(22,1);
    glVertex2f(24.0,5.0);
    glEnd();

    glColor3ub(0,0,0); //ring
    glBegin(GL_POLYGON);
    glVertex2f(1.35,3.5);
    glVertex2f(1.6,3.2);
    glVertex2f(23.2,3.2);
    glVertex2f(23.35,3.5);
    glEnd();

    glColor3ub(240,102,0); //base
    glBegin(GL_POLYGON);
    glVertex2f(21.0,5.0);
    glVertex2f(21.9,6.0);
    glVertex2f(24.5,6.0);
    glVertex2f(24.0,5.0);
    glEnd();

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

void sun()
{
    glColor3ub(252, 212, 64);

    circle(40,45,1300,950);
}

void moon()
{
    glColor3ub(255,255,255);
    circle(40,45,1300,950);

    glColor3ub(12, 20, 69);
    circle(35,40,1320,960);
}

void cloud1()
{
    glColor3ub(50,52,86);

    circle(40,40,305,900);
    circle(40,40,320,900);
    circle(40,40,335,900);
    circle(40,40,350,900); //down
    circle(40,40,365,900);
    circle(40,40,380,900);
    circle(40,40,395,900);

    circle(40,50,325,920); //up
    circle(40,70,370,930);
}

void cloud2()
{
    glColor3ub(50,52,86);

    circle(30,30,670,700);
    circle(30,30,685,700);
    circle(30,30,700,700); //down
    circle(30,30,715,700);
    circle(30,30,730,700);

    circle(30,40,680,730); //up
    circle(30,30,710,720);
}

void cloud3()
{
    glColor3ub(50,52,86);

    circle(35,35,1005,800);
    circle(35,35,1020,800);
    circle(35,35,1035,800);
    circle(35,35,1050,800); //down
    circle(35,35,1065,800);
    circle(35,35,1080,800);
    circle(35,35,1095,800);

    circle(35,40,1025,830); //up
    circle(35,35,1070,820);
}

void water3()
{
    glColor3ub(28,163,236);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(1400,0);
    glVertex2f(1400,90);
    glVertex2f(0,90);
    glEnd();
}

void boat()
{

}

void water()
{
    glPushMatrix();
    //glPushMatrix();
    glTranslated(w,0,0.0);
    glColor3ub(28,163,236);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(0,100);
    glVertex2f(10,106);
    glVertex2f(25,108);
    glVertex2f(39,104);
    glVertex2f(50,102);
    glVertex2f(70,108);
    glVertex2f(85,105);
    glVertex2f(95,106);
    glVertex2f(110,109);
    glVertex2f(128,107);
    glVertex2f(139,105);
    glVertex2f(145,107);
    glVertex2f(155,109);
    glVertex2f(172,105);
    glVertex2f(195,106);
    glVertex2f(212,105);
    glVertex2f(254,102);
    glVertex2f(284,106);
    glVertex2f(344,108);
    glVertex2f(360,103);
    glVertex2f(390,104);
    glVertex2f(410,109);
    glVertex2f(450,104);
    glVertex2f(485,100);
    glVertex2f(502,102);
    glVertex2f(552,102);
    glVertex2f(592,106);
    glVertex2f(630,110);
    glVertex2f(680,103);
    glVertex2f(720,107);
    glVertex2f(750,103);
    glVertex2f(800,105);
    glVertex2f(850,107);
    glVertex2f(880,110);
    glVertex2f(900,106);
    glVertex2f(920,103);
    glVertex2f(950,109);
    glVertex2f(980,102);
    glVertex2f(1000,109);
    glVertex2f(1030,102);
    glVertex2f(1050,107);
    glVertex2f(1080,109);
    glVertex2f(1110,105);
    glVertex2f(1140,108);
    glVertex2f(1170,106);
    glVertex2f(1190,107);
    glVertex2f(1220,105);
    glVertex2f(1240,102);
    glVertex2f(1260,109);
    glVertex2f(1280,105);
    glVertex2f(1300,108);
    glVertex2f(1310,106);
    glVertex2f(1330,103);
    glVertex2f(1350,108);
    glVertex2f(1370,102);
    glVertex2f(1390,105);
    glVertex2f(99999,107);
    glEnd();
    glPopMatrix();
}



///To draw water wave
void water2()
{
    glPushMatrix();
    //glPushMatrix();
    glTranslated(w,0,0.0);
    glColor3ub(28,163,236);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(0,190);
    glVertex2f(10,196);
    glVertex2f(25,198);
    glVertex2f(39,194);
    glVertex2f(50,192);
    glVertex2f(70,198);
    glVertex2f(85,195);
    glVertex2f(95,196);
    glVertex2f(110,199);
    glVertex2f(128,197);
    glVertex2f(139,195);
    glVertex2f(145,197);
    glVertex2f(155,199);
    glVertex2f(172,195);
    glVertex2f(195,196);
    glVertex2f(212,195);
    glVertex2f(254,192);
    glVertex2f(284,196);
    glVertex2f(344,198);
    glVertex2f(360,193);
    glVertex2f(390,194);
    glVertex2f(410,199);
    glVertex2f(450,194);
    glVertex2f(485,190);
    glVertex2f(502,192);
    glVertex2f(552,192);
    glVertex2f(592,196);
    glVertex2f(630,200);
    glVertex2f(680,193);
    glVertex2f(720,197);
    glVertex2f(750,193);
    glVertex2f(800,195);
    glVertex2f(850,197);
    glVertex2f(880,200);
    glVertex2f(900,196);
    glVertex2f(920,193);
    glVertex2f(950,199);
    glVertex2f(980,192);
    glVertex2f(1000,199);
    glVertex2f(1030,192);
    glVertex2f(1050,197);
    glVertex2f(1080,199);
    glVertex2f(1110,195);
    glVertex2f(1140,198);
    glVertex2f(1170,196);
    glVertex2f(1190,197);
    glVertex2f(1220,195);
    glVertex2f(1240,192);
    glVertex2f(1260,199);
    glVertex2f(1280,195);
    glVertex2f(1300,198);
    glVertex2f(1310,196);
    glVertex2f(1330,193);
    glVertex2f(1350,198);
    glVertex2f(1370,192);
    glVertex2f(1390,195);
    glVertex2f(99999,197);
    glEnd();
    glPopMatrix();
}



void sky()
{
    glColor3ub(210, 237, 253);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(1400,0);
    glVertex2f(1400,1000);
    glVertex2f(0,1000);
    glEnd();
}

void night()
{
    glColor3ub(12, 20, 69);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(1400,0);
    glVertex2f(1400,1000);
    glVertex2f(0,1000);
    glEnd();
}


void shipChimneyLeft()
{
    glColor3ub(255,191,0);///chimney
    glBegin(GL_POLYGON);//1
    glVertex2f(8.5,16.0);
    glVertex2f(8.5,12.5);
    glVertex2f(9.9,12.5);
    glVertex2f(9.9,16.0);
    glEnd();
    glColor3ub(50,50,50);
    glBegin(GL_POLYGON);
    glVertex2f(8.6,16.5);
    glVertex2f(8.5,15.8);
    glVertex2f(9.9,15.8);
    glVertex2f(9.8,16.5);
    glEnd();


    glColor3ub(255,191,0);//2
    glBegin(GL_POLYGON);
    glVertex2f(12.9,16.0);
    glVertex2f(12.9,12.5);
    glVertex2f(14.3,12.5);
    glVertex2f(14.3,16.0);
    glEnd();
    glColor3ub(50,50,50);
    glBegin(GL_POLYGON);
    glVertex2f(13.0,16.5);
    glVertex2f(12.9,15.8);
    glVertex2f(14.3,15.8);
    glVertex2f(14.2,16.5);
    glEnd();
}


void shipChimneyRight()
{
    glColor3ub(255,191,0);//3
    glBegin(GL_POLYGON);
    glVertex2f(17.3,16.0);
    glVertex2f(17.3,12.5);
    glVertex2f(18.7,12.5);
    glVertex2f(18.7,16.0);
    glEnd();
    glColor3ub(50,50,50);
    glBegin(GL_POLYGON);
    glVertex2f(17.4,16.5);
    glVertex2f(17.3,15.8);
    glVertex2f(18.7,15.8);
    glVertex2f(18.6,16.5);
    glEnd();


    glColor3ub(255,191,0);//4
    glBegin(GL_POLYGON);
    glVertex2f(21.7,16.0);
    glVertex2f(21.7,12.5);
    glVertex2f(23.1,12.5);
    glVertex2f(23.1,16.0);
    glEnd();
    glColor3ub(50,50,50);
    glBegin(GL_POLYGON);
    glVertex2f(21.8,16.5);
    glVertex2f(21.7,15.8);
    glVertex2f(23.1,15.8);
    glVertex2f(23.0,16.5);
    glEnd();
}


void ship()
{
    glScaled(20,25,25);


    glColor3ub(0,0,40); ///down-mid
    glBegin(GL_POLYGON);
    glVertex2f(3.0,8.0);
    glVertex2f(1.0,3.0);
    glVertex2f(30.3,3.0);
    glVertex2f(30.8,8.0);
    glEnd();

    glColor3ub(0,0,0);///uper mid
    glBegin(GL_POLYGON);//black m
    glVertex2f(1.75,8.6);
    glVertex2f(1.75,7.4);
    glVertex2f(29.35,7.4);
    glVertex2f(29.35,8.6);
    glEnd();

    glColor3ub(0,0,0);//black l
    glBegin(GL_POLYGON);
    glVertex2f(0.75,8.4);
    glVertex2f(0.75,7.6);
    glVertex2f(1.75,7.4);
    glVertex2f(1.75,8.6);
    glEnd();
    circle(0.4,0.4,0.75,8);

    glColor3ub(0,0,0);//black r
    glBegin(GL_POLYGON);
    glVertex2f(29.35,8.6);
    glVertex2f(29.35,7.4);
    glVertex2f(30.35,7.6);
    glVertex2f(30.35,8.4);
    glEnd();
    circle(0.5,0.4,30.35,8);


    glColor3ub(250,250,250);//white m
    glBegin(GL_POLYGON);
    glVertex2f(1.75,8.4);
    glVertex2f(1.75,7.6);
    glVertex2f(29.35,7.6);
    glVertex2f(29.35,8.4);
    glEnd();

    glColor3ub(250,250,250);//white l
    glBegin(GL_POLYGON);
    glVertex2f(0.75,8.1);
    glVertex2f(0.75,7.9);
    glVertex2f(1.75,7.6);
    glVertex2f(1.75,8.4);
    glEnd();

    glColor3ub(250,250,250);//white r
    glBegin(GL_POLYGON);
    glVertex2f(29.35,8.4);
    glVertex2f(29.35,7.6);
    glVertex2f(30.35,7.8);
    glVertex2f(30.35,8.2);
    glEnd();

    /*glColor3ub(0,0,0); ///up-mid
    circle(15.3,0.6,15.55,8);
    glColor3ub(250,250,250);
    circle(14.8,0.4,15.55,8);*/

    circle(0.33,0.33,0.8,3.3);//down-mid back
    circle(0.33,0.33,1,3.3);

    glColor3ub(139,0,0);//down back
    circle(0.33,0.33,0.8,2.9);

    glColor3ub(0,0,40);//down-mid back
    circle(1,1,1.5,3.3);
    circle(1,1,1.5,3.8);
    circle(1,1,1.6,4.3);
    circle(1,1,1.8,4.8);
    circle(1,1,2.0,5.3);
    circle(1,1,2.5,5.8);
    circle(1,1,2.7,6.0);


    glColor3ub(139,0,0); ///down
    glBegin(GL_POLYGON);
    glVertex2f(1.0,3.0);
    glVertex2f(2.0,1);
    glVertex2f(30.0,1);
    glVertex2f(30.3,3.0);
    glEnd();

    circle(0.33,0.33,0.8,2.7);//down back
    circle(0.5,0.5,1,2.5);
    circle(0.5,0.5,1.05,2.3);
    circle(0.5,0.5,1.1,2.1);
    circle(0.5,0.5,1.1,1.9);
    circle(0.5,0.75,1.15,1.9);
    circle(0.5,0.5,1,2.3);
    circle(0.5,0.3,2,1.6);


    glColor3ub(219,225,221);///up
    glBegin(GL_POLYGON);
    glVertex2f(4.0,9.0);
    glVertex2f(4.0,8.0);
    glVertex2f(25.0,8.0);
    glVertex2f(25.0,9.0);
    glEnd();

    glColor3ub(255,255,240);
    glBegin(GL_POLYGON);
    glVertex2f(4.0,9.5);
    glVertex2f(4.0,9.0);
    glVertex2f(25.0,9.0);
    glVertex2f(25.0,9.5);
    glEnd();

    glColor3ub(219,225,221);
    glBegin(GL_POLYGON);
    glVertex2f(6.0,10.5);
    glVertex2f(6.0,9.5);
    glVertex2f(24.8,9.5);
    glVertex2f(24.8,10.5);
    glEnd();

    glColor3ub(255,255,240);
    glBegin(GL_POLYGON);
    glVertex2f(6.0,11.0);
    glVertex2f(6.0,10.5);
    glVertex2f(24.8,10.5);
    glVertex2f(24.8,11.0);
    glEnd();

    glColor3ub(219,225,221);
    glBegin(GL_POLYGON);
    glVertex2f(7.0,12.0);
    glVertex2f(7.0,11.0);
    glVertex2f(24.6,11.0);
    glVertex2f(24.6,12.0);
    glEnd();

    glColor3ub(255,255,240);
    glBegin(GL_POLYGON);
    glVertex2f(7.0,12.5);
    glVertex2f(7.0,12.0);
    glVertex2f(24.6,12.0);
    glVertex2f(24.6,12.5);
    glEnd();


    shipChimneyLeft();
    shipChimneyRight();



    glColor3ub(115, 147, 175); ///down-mid window
    circle(0.15,0.18,1.5,3.75);//1st row
    circle(0.15,0.18,2.5,3.75);
    circle(0.15,0.18,3.5,3.75);
    circle(0.15,0.18,4.5,3.75);
    circle(0.15,0.18,5.5,3.75);
    circle(0.15,0.18,6.5,3.75);
    circle(0.15,0.18,7.5,3.75);
    circle(0.15,0.18,8.5,3.75);
    circle(0.15,0.18,9.5,3.75);
    circle(0.15,0.18,10.5,3.75);
    circle(0.15,0.18,11.5,3.75);

    circle(0.15,0.18,13.5,4.15);
    circle(0.15,0.18,14.5,4.15);
    circle(0.15,0.18,15.5,4.15);
    circle(0.15,0.18,16.5,4.15);
    circle(0.15,0.18,17.5,4.15);
    circle(0.15,0.18,18.5,4.15);

    circle(0.15,0.18,20.5,3.75);
    circle(0.15,0.18,21.5,3.75);
    circle(0.15,0.18,22.5,3.75);
    circle(0.15,0.18,23.5,3.75);
    circle(0.15,0.18,24.5,3.75);
    circle(0.15,0.18,25.5,3.75);
    circle(0.15,0.18,26.5,3.75);
    circle(0.15,0.18,27.5,3.75);
    circle(0.15,0.18,28.5,3.75);
    circle(0.15,0.18,29.5,3.75);


    circle(0.15,0.18,1.2,4.70);//2nd row
    circle(0.15,0.18,2.0,4.70);
    circle(0.15,0.18,3.0,4.70);
    circle(0.15,0.18,4.0,4.70);
    circle(0.15,0.18,5.0,4.70);
    circle(0.15,0.18,6.0,4.70);
    circle(0.15,0.18,7.0,4.70);
    circle(0.15,0.18,8.0,4.70);
    circle(0.15,0.18,9.0,4.70);
    circle(0.15,0.18,10.0,4.70);
    circle(0.15,0.18,11.0,4.70);
    circle(0.15,0.18,12.0,4.70);

    circle(0.15,0.18,14.0,5.3);
    circle(0.15,0.18,15.0,5.3);
    circle(0.15,0.18,16.0,5.3);
    circle(0.15,0.18,17.0,5.3);
    circle(0.15,0.18,18.0,5.3);

    circle(0.15,0.18,20.0,4.70);
    circle(0.15,0.18,21.0,4.70);
    circle(0.15,0.18,22.0,4.70);
    circle(0.15,0.18,23.0,4.70);
    circle(0.15,0.18,24.0,4.70);
    circle(0.15,0.18,25.0,4.70);
    circle(0.15,0.18,26.0,4.70);
    circle(0.15,0.18,27.0,4.70);
    circle(0.15,0.18,28.0,4.70);
    circle(0.15,0.18,29.0,4.70);
    circle(0.15,0.18,30.0,4.70);


    circle(0.15,0.18,2.0,6.1);//3rd row
    circle(0.15,0.18,2.8,6.1);
    circle(0.15,0.18,3.8,6.1);
    circle(0.15,0.18,4.8,6.1);
    circle(0.15,0.18,5.8,6.1);
    circle(0.15,0.18,6.8,6.1);
    circle(0.15,0.18,7.8,6.1);
    circle(0.15,0.18,8.8,6.1);
    circle(0.15,0.18,9.8,6.15);
    circle(0.15,0.18,10.8,6.2);
    circle(0.15,0.18,11.8,6.25);

    circle(0.15,0.18,13.8,6.6);
    circle(0.15,0.18,14.8,6.6);
    circle(0.15,0.18,15.8,6.6);
    circle(0.15,0.18,16.8,6.6);
    circle(0.15,0.18,17.8,6.6);

    circle(0.15,0.18,19.8,6.25);
    circle(0.15,0.18,20.8,6.2);
    circle(0.15,0.18,21.8,6.15);
    circle(0.15,0.18,22.8,6.1);
    circle(0.15,0.18,23.8,6.1);
    circle(0.15,0.18,24.8,6.1);
    circle(0.15,0.18,25.8,6.1);
    circle(0.15,0.18,26.8,6.1);
    circle(0.15,0.18,27.8,6.1);
    circle(0.15,0.18,28.8,6.1);
    circle(0.15,0.18,29.8,6.1);


    circle(0.15,0.18,3,7.2);//4th row
    circle(0.15,0.18,4,7.2);
    circle(0.15,0.18,5,7.15);
    circle(0.15,0.18,6,7.15);
    circle(0.15,0.18,7,7.1);
    circle(0.15,0.18,8,7.1);
    circle(0.15,0.18,9,7.05);

    circle(0.15,0.18,23,7.05);
    circle(0.15,0.18,24,7.05);
    circle(0.15,0.18,25,7.1);
    circle(0.15,0.18,26,7.1);
    circle(0.15,0.18,27,7.15);
    circle(0.15,0.18,28,7.15);
    circle(0.15,0.18,29,7.2);
    circle(0.15,0.18,30,7.2);



    circle(0.3,0.5,4.5,8.5);///up door

    circle(0.3,0.5,6.5,8.5);//1st
    circle(0.3,0.5,7.2,8.5);

    circle(0.3,0.5,9.2,8.5);
    circle(0.3,0.5,9.9,8.5);

    circle(0.3,0.5,11.9,8.5);
    circle(0.3,0.5,12.6,8.5);

    circle(0.3,0.5,14.6,8.5);
    circle(0.3,0.5,15.3,8.5);

    circle(0.3,0.5,17.3,8.5);
    circle(0.3,0.5,18.0,8.5);

    circle(0.3,0.5,20.0,8.5);
    circle(0.3,0.5,20.7,8.5);

    circle(0.3,0.5,22.7,8.5);
    circle(0.3,0.5,23.4,8.5);



    circle(0.3,0.5,7,10);//2nd
    circle(0.3,0.5,9,10);
    circle(0.3,0.5,11,10);
    circle(0.3,0.5,13,10);
    circle(0.3,0.5,15,10);
    circle(0.3,0.5,17,10);
    circle(0.3,0.5,19,10);
    circle(0.3,0.5,21,10);
    circle(0.3,0.5,23,10);


    glColor3ub(115, 147, 175);//3rd
    glBegin(GL_POLYGON);
    glVertex2f(7.7,12.0);
    glVertex2f(7.7,11.0);
    glVertex2f(8.2,11.0);
    glVertex2f(8.2,12.0);
    glEnd();

    glColor3ub(115, 147, 175);
    glBegin(GL_POLYGON);
    glVertex2f(11.1,12.0);
    glVertex2f(11.1,11.0);
    glVertex2f(11.6,11.0);
    glVertex2f(11.6,12.0);
    glEnd();

    glColor3ub(115, 147, 175);
    glBegin(GL_POLYGON);
    glVertex2f(11.8,12.0);
    glVertex2f(11.8,11.0);
    glVertex2f(12.3,11.0);
    glVertex2f(12.3,12.0);
    glEnd();

    glColor3ub(115, 147, 175);
    glBegin(GL_POLYGON);
    glVertex2f(15.2,12.0);
    glVertex2f(15.2,11.0);
    glVertex2f(15.7,11.0);
    glVertex2f(15.7,12.0);
    glEnd();

    glColor3ub(115, 147, 175);
    glBegin(GL_POLYGON);
    glVertex2f(18.6,12.0);
    glVertex2f(18.6,11.0);
    glVertex2f(19.1,11.0);
    glVertex2f(19.1,12.0);
    glEnd();

    glColor3ub(115, 147, 175);
    glBegin(GL_POLYGON);
    glVertex2f(19.3,12.0);
    glVertex2f(19.3,11.0);
    glVertex2f(19.8,11.0);
    glVertex2f(19.8,12.0);
    glEnd();

    glColor3ub(115, 147, 175);
    glBegin(GL_POLYGON);
    glVertex2f(22.7,12.0);
    glVertex2f(22.7,11.0);
    glVertex2f(23.2,11.0);
    glVertex2f(23.2,12.0);
    glEnd();

}


void shipCrackLeft()
{
    glScaled(20,25,25);


    glColor3ub(0,0,40); ///down-mid
    glBegin(GL_POLYGON);
    glVertex2f(3.0,8.0);
    glVertex2f(1.0,3.0);
    glVertex2f(15.4,3.0);
    glVertex2f(16.4,8.0);
    glEnd();


    glColor3ub(0,0,0);///uper mid
    glBegin(GL_POLYGON);//black m
    glVertex2f(1.75,8.6);
    glVertex2f(1.75,7.4);
    glVertex2f(16.3,7.4);
    glVertex2f(16.1,8.6);
    glEnd();

    glColor3ub(0,0,0);//black l
    glBegin(GL_POLYGON);
    glVertex2f(0.75,8.4);
    glVertex2f(0.75,7.6);
    glVertex2f(1.75,7.4);
    glVertex2f(1.75,8.6);
    glEnd();
    circle(0.4,0.4,0.75,8);


    glColor3ub(250,250,250);//white m
    glBegin(GL_POLYGON);
    glVertex2f(1.75,8.4);
    glVertex2f(1.75,7.6);
    glVertex2f(16.35,7.6);
    glVertex2f(16.4,8.4);
    glEnd();

    glColor3ub(250,250,250);//white l
    glBegin(GL_POLYGON);
    glVertex2f(0.75,8.1);
    glVertex2f(0.75,7.9);
    glVertex2f(1.75,7.6);
    glVertex2f(1.75,8.4);
    glEnd();


    circle(0.33,0.33,0.8,3.3);//down-mid back
    circle(0.33,0.33,1,3.3);

    glColor3ub(139,0,0);//down back
    circle(0.33,0.33,0.8,2.9);

    glColor3ub(0,0,40);//down-mid back
    circle(1,1,1.5,3.3);
    circle(1,1,1.5,3.8);
    circle(1,1,1.6,4.3);
    circle(1,1,1.8,4.8);
    circle(1,1,2.0,5.3);
    circle(1,1,2.5,5.8);
    circle(1,1,2.7,6.0);


    glColor3ub(139,0,0); ///down
    glBegin(GL_POLYGON);
    glVertex2f(1.0,3.0);
    glVertex2f(2.0,1);
    glVertex2f(15.5,1);
    glVertex2f(15.4,3.0);
    glEnd();

    circle(0.33,0.33,0.8,2.7);//down back
    circle(0.5,0.5,1,2.5);
    circle(0.5,0.5,1.05,2.3);
    circle(0.5,0.5,1.1,2.1);
    circle(0.5,0.5,1.1,1.9);
    circle(0.5,0.75,1.15,1.9);
    circle(0.5,0.5,1,2.3);
    circle(0.5,0.3,2,1.6);


    glColor3ub(219,225,221);///up
    glBegin(GL_POLYGON);
    glVertex2f(4.0,9.0);
    glVertex2f(4.0,8.0);
    glVertex2f(16.45,8.0);
    glVertex2f(16.15,9.0);
    glEnd();

    glColor3ub(255,255,240);
    glBegin(GL_POLYGON);
    glVertex2f(4.0,9.5);
    glVertex2f(4.0,9.0);
    glVertex2f(16.15,9.0);
    glVertex2f(16.5,9.5);
    glEnd();

    glColor3ub(219,225,221);
    glBegin(GL_POLYGON);
    glVertex2f(6.0,10.5);
    glVertex2f(6.0,9.5);
    glVertex2f(16.5,9.5);
    glVertex2f(16.25,10.5);
    glEnd();

    glColor3ub(255,255,240);
    glBegin(GL_POLYGON);
    glVertex2f(6.0,11.0);
    glVertex2f(6.0,10.5);
    glVertex2f(16.25,10.5);
    glVertex2f(16.35,11.0);
    glEnd();

    glColor3ub(219,225,221);
    glBegin(GL_POLYGON);
    glVertex2f(7.0,12.0);
    glVertex2f(7.0,11.0);
    glVertex2f(16.35,11.0);
    glVertex2f(16.85,12.0);
    glEnd();

    glColor3ub(255,255,240);
    glBegin(GL_POLYGON);
    glVertex2f(7.0,12.5);
    glVertex2f(7.0,12.0);
    glVertex2f(16.85,12.0);
    glVertex2f(16.1,12.5);
    glEnd();


    shipChimneyLeft();


    glColor3ub(115, 147, 175); ///down-mid window
    circle(0.15,0.18,1.5,3.75);//1st row
    circle(0.15,0.18,2.5,3.75);
    circle(0.15,0.18,3.5,3.75);
    circle(0.15,0.18,4.5,3.75);
    circle(0.15,0.18,5.5,3.75);
    circle(0.15,0.18,6.5,3.75);
    circle(0.15,0.18,7.5,3.75);
    circle(0.15,0.18,8.5,3.75);
    circle(0.15,0.18,9.5,3.75);
    circle(0.15,0.18,10.5,3.75);
    circle(0.15,0.18,11.5,3.75);

    circle(0.15,0.18,13.5,4.15);
    circle(0.15,0.18,14.5,4.15);
    circle(0.15,0.18,15.5,4.15);


    circle(0.15,0.18,1.2,4.70);//2nd row
    circle(0.15,0.18,2.0,4.70);
    circle(0.15,0.18,3.0,4.70);
    circle(0.15,0.18,4.0,4.70);
    circle(0.15,0.18,5.0,4.70);
    circle(0.15,0.18,6.0,4.70);
    circle(0.15,0.18,7.0,4.70);
    circle(0.15,0.18,8.0,4.70);
    circle(0.15,0.18,9.0,4.70);
    circle(0.15,0.18,10.0,4.70);
    circle(0.15,0.18,11.0,4.70);
    circle(0.15,0.18,12.0,4.70);

    circle(0.15,0.18,14.0,5.3);
    circle(0.15,0.18,15.0,5.3);


    circle(0.15,0.18,2.0,6.1);//3rd row
    circle(0.15,0.18,2.8,6.1);
    circle(0.15,0.18,3.8,6.1);
    circle(0.15,0.18,4.8,6.1);
    circle(0.15,0.18,5.8,6.1);
    circle(0.15,0.18,6.8,6.1);
    circle(0.15,0.18,7.8,6.1);
    circle(0.15,0.18,8.8,6.1);
    circle(0.15,0.18,9.8,6.15);
    circle(0.15,0.18,10.8,6.2);
    circle(0.15,0.18,11.8,6.25);

    circle(0.15,0.18,13.8,6.6);
    circle(0.15,0.18,14.8,6.6);
    circle(0.15,0.18,15.8,6.6);


    circle(0.15,0.18,3,7.2);//4th row
    circle(0.15,0.18,4,7.2);
    circle(0.15,0.18,5,7.15);
    circle(0.15,0.18,6,7.15);
    circle(0.15,0.18,7,7.1);
    circle(0.15,0.18,8,7.1);
    circle(0.15,0.18,9,7.05);


    circle(0.3,0.5,4.5,8.5);///up door

    circle(0.3,0.5,6.5,8.5);//1st
    circle(0.3,0.5,7.2,8.5);
    circle(0.3,0.5,9.2,8.5);
    circle(0.3,0.5,9.9,8.5);
    circle(0.3,0.5,11.9,8.5);
    circle(0.3,0.5,12.6,8.5);
    circle(0.3,0.5,14.6,8.5);
    circle(0.3,0.5,15.3,8.5);


    circle(0.3,0.5,7,10);//2nd
    circle(0.3,0.5,9,10);
    circle(0.3,0.5,11,10);
    circle(0.3,0.5,13,10);
    circle(0.3,0.5,15,10);


    glColor3ub(115, 147, 175);//3rd
    glBegin(GL_POLYGON);
    glVertex2f(7.7,12.0);
    glVertex2f(7.7,11.0);
    glVertex2f(8.2,11.0);
    glVertex2f(8.2,12.0);
    glEnd();

    glColor3ub(115, 147, 175);
    glBegin(GL_POLYGON);
    glVertex2f(11.1,12.0);
    glVertex2f(11.1,11.0);
    glVertex2f(11.6,11.0);
    glVertex2f(11.6,12.0);
    glEnd();

    glColor3ub(115, 147, 175);
    glBegin(GL_POLYGON);
    glVertex2f(11.8,12.0);
    glVertex2f(11.8,11.0);
    glVertex2f(12.3,11.0);
    glVertex2f(12.3,12.0);
    glEnd();

    glColor3ub(115, 147, 175);
    glBegin(GL_POLYGON);
    glVertex2f(15.2,12.0);
    glVertex2f(15.2,11.0);
    glVertex2f(15.7,11.0);
    glVertex2f(15.7,12.0);
    glEnd();
}


void shipCrackRight()
{
    glScaled(20,25,25);
    glColor3ub(0,0,40); ///down-mid
    glBegin(GL_POLYGON);
    glVertex2f(16.4,8.0);
    glVertex2f(15.4,3.0);
    glVertex2f(30.3,3.0);
    glVertex2f(30.8,8.0);
    glEnd();

    glColor3ub(0,0,0);///uper mid
    glBegin(GL_POLYGON);//black m
    glVertex2f(16.5,8.6);
    glVertex2f(16.3,7.4);
    glVertex2f(29.35,7.4);
    glVertex2f(29.35,8.6);
    glEnd();


    glColor3ub(0,0,0);//black r
    glBegin(GL_POLYGON);
    glVertex2f(29.35,8.6);
    glVertex2f(29.35,7.4);
    glVertex2f(30.35,7.6);
    glVertex2f(30.35,8.4);
    glEnd();
    circle(0.5,0.4,30.35,8);


    glColor3ub(250,250,250);//white m
    glBegin(GL_POLYGON);
    glVertex2f(16.4,8.4);
    glVertex2f(16.35,7.6);
    glVertex2f(29.35,7.6);
    glVertex2f(29.35,8.4);
    glEnd();

    glColor3ub(250,250,250);//white r
    glBegin(GL_POLYGON);
    glVertex2f(29.35,8.4);
    glVertex2f(29.35,7.6);
    glVertex2f(30.35,7.8);
    glVertex2f(30.35,8.2);
    glEnd();



    glColor3ub(139,0,0); ///down
    glBegin(GL_POLYGON);
    glVertex2f(15.4,3.0);
    glVertex2f(15.5,1);
    glVertex2f(30.0,1);
    glVertex2f(30.3,3.0);
    glEnd();


    glColor3ub(219,225,221);///up
    glBegin(GL_POLYGON);
    glVertex2f(16.15,9.0);
    glVertex2f(16.45,8.0);
    glVertex2f(25.0,8.0);
    glVertex2f(25.0,9.0);
    glEnd();

    glColor3ub(255,255,240);
    glBegin(GL_POLYGON);
    glVertex2f(16.5,9.5);
    glVertex2f(16.15,9.0);
    glVertex2f(25.0,9.0);
    glVertex2f(25.0,9.5);
    glEnd();

    glColor3ub(219,225,221);
    glBegin(GL_POLYGON);
    glVertex2f(16.25,10.5);
    glVertex2f(16.5,9.5);
    glVertex2f(24.8,9.5);
    glVertex2f(24.8,10.5);
    glEnd();

    glColor3ub(255,255,240);
    glBegin(GL_POLYGON);
    glVertex2f(16.35,11.0);
    glVertex2f(16.25,10.5);
    glVertex2f(24.8,10.5);
    glVertex2f(24.8,11.0);
    glEnd();

    glColor3ub(219,225,221);
    glBegin(GL_POLYGON);
    glVertex2f(16.85,12.0);
    glVertex2f(16.35,11.0);
    glVertex2f(24.6,11.0);
    glVertex2f(24.6,12.0);
    glEnd();

    glColor3ub(255,255,240);
    glBegin(GL_POLYGON);
    glVertex2f(16.1,12.5);
    glVertex2f(16.85,12.0);
    glVertex2f(24.6,12.0);
    glVertex2f(24.6,12.5);
    glEnd();

    glColor3ub(115, 147, 175); ///down-mid window
    circle(0.15,0.18,16.5,4.15);//1st row
    circle(0.15,0.18,17.5,4.15);
    circle(0.15,0.18,18.5,4.15);

    circle(0.15,0.18,20.5,3.75);
    circle(0.15,0.18,21.5,3.75);
    circle(0.15,0.18,22.5,3.75);
    circle(0.15,0.18,23.5,3.75);
    circle(0.15,0.18,24.5,3.75);
    circle(0.15,0.18,25.5,3.75);
    circle(0.15,0.18,26.5,3.75);
    circle(0.15,0.18,27.5,3.75);
    circle(0.15,0.18,28.5,3.75);
    circle(0.15,0.18,29.5,3.75);

    circle(0.15,0.18,16.0,5.3);//2nd row
    circle(0.15,0.18,17.0,5.3);
    circle(0.15,0.18,18.0,5.3);

    circle(0.15,0.18,20.0,4.70);
    circle(0.15,0.18,21.0,4.70);
    circle(0.15,0.18,22.0,4.70);
    circle(0.15,0.18,23.0,4.70);
    circle(0.15,0.18,24.0,4.70);
    circle(0.15,0.18,25.0,4.70);
    circle(0.15,0.18,26.0,4.70);
    circle(0.15,0.18,27.0,4.70);
    circle(0.15,0.18,28.0,4.70);
    circle(0.15,0.18,29.0,4.70);
    circle(0.15,0.18,30.0,4.70);

    circle(0.15,0.18,16.8,6.6);//3rd row
    circle(0.15,0.18,17.8,6.6);

    circle(0.15,0.18,19.8,6.25);
    circle(0.15,0.18,20.8,6.2);
    circle(0.15,0.18,21.8,6.15);
    circle(0.15,0.18,22.8,6.1);
    circle(0.15,0.18,23.8,6.1);
    circle(0.15,0.18,24.8,6.1);
    circle(0.15,0.18,25.8,6.1);
    circle(0.15,0.18,26.8,6.1);
    circle(0.15,0.18,27.8,6.1);
    circle(0.15,0.18,28.8,6.1);
    circle(0.15,0.18,29.8,6.1);

    circle(0.15,0.18,23,7.05);//4th row
    circle(0.15,0.18,24,7.05);
    circle(0.15,0.18,25,7.1);
    circle(0.15,0.18,26,7.1);
    circle(0.15,0.18,27,7.15);
    circle(0.15,0.18,28,7.15);
    circle(0.15,0.18,29,7.2);
    circle(0.15,0.18,30,7.2);

    circle(0.3,0.5,17.3,8.5);///up door
    circle(0.3,0.5,18.0,8.5);//1st

    circle(0.3,0.5,20.0,8.5);
    circle(0.3,0.5,20.7,8.5);

    circle(0.3,0.5,22.7,8.5);
    circle(0.3,0.5,23.4,8.5);

    circle(0.3,0.5,17,10);//2nd
    circle(0.3,0.5,19,10);
    circle(0.3,0.5,21,10);
    circle(0.3,0.5,23,10);

    glColor3ub(115, 147, 175);//3rd
    glBegin(GL_POLYGON);
    glVertex2f(18.6,12.0);
    glVertex2f(18.6,11.0);
    glVertex2f(19.1,11.0);
    glVertex2f(19.1,12.0);
    glEnd();

    glColor3ub(115, 147, 175);
    glBegin(GL_POLYGON);
    glVertex2f(19.3,12.0);
    glVertex2f(19.3,11.0);
    glVertex2f(19.8,11.0);
    glVertex2f(19.8,12.0);
    glEnd();

    glColor3ub(115, 147, 175);
    glBegin(GL_POLYGON);
    glVertex2f(22.7,12.0);
    glVertex2f(22.7,11.0);
    glVertex2f(23.2,11.0);
    glVertex2f(23.2,12.0);
    glEnd();

}


void rock()
{
    glPushMatrix();
    glTranslated(800,80,0.0);
    glScaled(20,8,0);
    glColor3ub(134,214,216);

    if(c>0)
    {
        glPushMatrix();
        glTranslated(0,x/10,0);
        glPushMatrix();
        glTranslated(7,2,0.0);
        glRotated(-x/10,0,0,1);
        glTranslated(-7,-2,0.0);

        glBegin(GL_POLYGON);
        glVertex2f(8.1,1);
        glVertex2f(7.89,1.23);
        glVertex2f(11.26,18);
        glVertex2f(13.23,21.33);
        glVertex2f(14.23,2.53);
        glEnd();

        glPopMatrix();
        glPushMatrix();

        glTranslated(12,3,0.0);
        glRotated(x/10,0,0,1);
        glTranslated(-12,-3,0.0);

        glBegin(GL_POLYGON);
        glVertex2f(11.1,3.5);
        glVertex2f(13.2,18.7);
        glVertex2f(16.4,18.5);
        glVertex2f(18.12,3.65);
        glVertex2f(19.21,1.25);
        glEnd();

        glPopMatrix();
        glPopMatrix();
    }
    else
    {
        glBegin(GL_POLYGON);
        glVertex2f(8.1,1);
        glVertex2f(7.89,1.23);
        glVertex2f(11.26,18);
        glVertex2f(13.23,21.33);
        glVertex2f(14.23,2.53);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(11.1,3.5);
        glVertex2f(13.2,18.7);
        glVertex2f(16.4,18.5);
        glVertex2f(18.12,3.65);
        glVertex2f(19.21,1.25);
        glEnd();
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(950,75,0.0);
    glScaled(25,13,0);
    glColor3ub(134,214,216);
    glBegin(GL_POLYGON);
    glVertex2f(5.5,2.5);
    glVertex2f(12.5,19.5);
    glVertex2f(15,19.5);
    glVertex2f(12.5,19.5);
    glVertex2f(13.5,18.5);
    glVertex2f(16.5,20.5);
    glVertex2f(17.5,18.5);
    glVertex2f(18.5,3.5);
    glVertex2f(19,3);
    glVertex2f(19.5,2.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(5.5,2.5);
    glVertex2f(6,3);
    glVertex2f(8.25,3.5);
    glVertex2f(8.5,18.5);
    glVertex2f(12,15);
    glVertex2f(13,17);
    glVertex2f(12.5,19.5);
    glVertex2f(8.5,9.5);
    glVertex2f(12.5,2.5);
    glVertex2f(5.5,2.5);
    glEnd();
    glPopMatrix();
}

void shipCrack()
{
    glPushMatrix();
    glScaled(1,1,1);

    if(c>0)
    {
        glPushMatrix();
        glTranslated(0,x/10,0);
        glPushMatrix();
        glTranslated(7,2,0.0);
        glRotated(-x/10,0,0,1);
        glTranslated(-7,-2,0.0);

        shipCrackLeft();
        glPushMatrix();
        glRotated(10,0,0,1);
        glTranslated(0,x/10.0-3,0);
        shipChimneyRight();
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslated(12,3,0.0);
        glRotated(x/10,0,0,1);
        glTranslated(-12,-3,0.0);
        shipCrackRight();
        glPopMatrix();

        glPopMatrix();
    }
    else
    {
        shipCrackLeft();
        //glPushMatrix();
        //glRotated(10,0,0,1);
        //glTranslated(0,x/10,0);

        //glPopMatrix();
        shipCrackRight();
    }
    glPopMatrix();
}


void myinit()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1400.0,0.0,1000.0);
}

int main(int argc, char* argv[])

{
    printf("OpenGL Project By Shadman & Roni\n");
    printf("\n------------------------------------------------------------------\n");
    printf("Hit Enter\n");
    getchar();


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1350.0,700.0);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Ship Sinking");
    glutDisplayFunc(display);
    myinit();
    glutTimerFunc(100,update,0);
    glutMainLoop();
    return 0;
}
