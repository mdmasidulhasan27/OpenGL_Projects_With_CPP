#include<windows.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int i =0.0,l;
int s,n,car1=0;
int t;
int glob=0;
int view=0;
int help=0;
int value=0;
float th=0.0;
float thx=1350;
float thy=915;
float fishX=-30;
GLint window1;

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


void boat()
{
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(50+n,500);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(30+n,565);
    glVertex2f(300+n,565);
    glVertex2f(280+n,500);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(70+n,565);
    glVertex2f(70+n,600);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(150+n,600);
    glVertex2f(150+n,565);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2d(70+n,600);
    glVertex2d(110+n,630);
    glVertex2d(150+n,600);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2d(260+n,565);
    glVertex2d(260+n,640);
    glVertex2d(265+n,640);
    glVertex2d(265+n,565);
    glEnd();

    glColor3f(1.3,0.3,0.0);
    glBegin(GL_POLYGON);
    glVertex2d(260+n,640);
    glVertex2d(300+n,600);
    glVertex2d(260+n,565);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex2d(90+n,575);
    glColor3f(1,1,0.15);
    glVertex2d(90+n,595);
    glColor3f(1.0,1.0,0.14);
    glVertex2d(130+n,595);
    glColor3f(0.0,0.0,0.0);
    glVertex2d(130+n,575);
    glEnd();
}

void Grass()
{
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(750,660);
    glVertex2f(740,670);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(750,660);
    glVertex2f(750,670);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(750,660);
    glVertex2f(760,670);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(725,660);
    glVertex2f(715,670);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(725,660);
    glVertex2f(725,670);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(725,660);
    glVertex2f(735,670);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(700,660);
    glVertex2f(690,670);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(700,660);
    glVertex2f(700,670);
    glEnd();

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(700,660);
    glVertex2f(710,670);
    glEnd();
}

void house1()
{
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(720,800);
    glVertex2f(720,900);
    glVertex2f(800,900);
    glVertex2f(800,800);
    glEnd();

    glColor3f(0.5, 0.1,0.1);
    glBegin(GL_TRIANGLES);
    glVertex2f(760,950);
    glVertex2f(800,900);
    glVertex2f(720,900);
    glEnd();

    glColor3f(0.556863, 0.137255,0.137255);
    glBegin(GL_POLYGON);
    glVertex2f(800,900);
    glVertex2f(760,950);
    glVertex2f(840,950);
    glVertex2f(865,900);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.858824,0.858824,0.439216);
    glVertex2f(865,800);
    glVertex2f(865,900);
    glVertex2f(800,900);
    glVertex2f(800,800);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0,0.49,0.00);
    glVertex2f(740,800);
    glVertex2f(740,850);
    glVertex2f(760,850);
    glVertex2f(760,800);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex2d(820,820);
    glColor3f(1.0,1.0,0.5);
    glVertex2d(820,860);
    glColor3f(1.0,1.0,0.7);
    glVertex2d(840,860);
    glColor3f(1.0,1.0,0.8);
    glVertex2d(840,820);
    glEnd();
}

void house2()
{
    glBegin(GL_POLYGON);
    glColor3f(1.0,1.0,0.0);
    glVertex2f(1000,700);
    glVertex2f(1100,700);
    glVertex2f(1100,780);
    glVertex2f(1000,780);
    glEnd();

    glColor3f(0.5, 0.1,0.1);
    glBegin(GL_TRIANGLES);
    glVertex2f(1000,780);
    glVertex2f(1050,840);
    glVertex2f(1100,780);
    glEnd();

    glColor3f(0.556863, 0.137255,0.137255);
    glBegin(GL_POLYGON);
    glVertex2f(1100,780);
    glVertex2f(1050,840);
    glVertex2f(1180,840);
    glVertex2f(1200,780);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.858824,0.858824,0.439216);
    glVertex2f(1200,780);
    glVertex2f(1200,700);
    glVertex2f(1100,700);
    glVertex2f(1100,780);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0,0.49,0.00);
    glVertex2f(1040,700);
    glVertex2f(1040,750);
    glVertex2f(1060,750);
    glVertex2f(1060,700);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0,.0,0.0);
    glVertex2f(1120,720);
    glColor3f(1.0,1.0,0.5);
    glVertex2f(1120,760);
    glColor3f(1.0,1.0,0.7);
    glVertex2f(1160,760);
    glColor3f(1.0,1.0,0.6);
    glVertex2f(1160,720);
    glEnd();
}

void windmill()
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(1300,750);
    glVertex2f(1400,750);
    glVertex2f(1375,900);
    glVertex2f(1325,900);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(1330,900);
    glVertex2f(1330,940);
    glVertex2f(1370,940);
    glVertex2f(1370,900);
    glEnd();
}

void windmill1()
{
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(800,950);
    glVertex2f(900,950);
    glVertex2f(890,1100);
    glVertex2f(810,1100);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(820,1100);
    glVertex2f(880,1100);
    glVertex2f(880,1150);
    glVertex2f(820,1150);
    glEnd();
}

void mountain()
{
    glColor3f(0.35,0.16,0.14);
    glBegin(GL_POLYGON);
    glVertex2f(0,600);
    glVertex2f(0,900);
    glVertex2f(120,980);
    glVertex2f(350,650);
    glEnd();

    glColor3f(0.35,0.16,0.14);
    glBegin(GL_POLYGON);
    glVertex2f(350,650);
    glVertex2f(200,850);
    glVertex2f(300,900);
    glVertex2f(450,650);
    glEnd();


    glColor3f(0.35,0.16,0.14);
    glBegin(GL_POLYGON);
    glVertex2f(450,650);
    glVertex2f(320,840);
    glVertex2f(450,950);
    glColor3f(0.35,0.26,0.20);
    glVertex2f(600,650);
    glEnd();
}

void sky()
{
    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.6);
    glVertex2f(0,850);
    glColor3f(0.0,0.0,0.0);
    glVertex2f(1500,850);
    glColor3f(0.0,0.3,0.0);
    glVertex2f(1500,1000);
    glVertex2f(0,1000);
    glEnd();
}


void sea()
{
    glColor3f(0.2,0.6,1.0);
    glBegin(GL_POLYGON);
    glVertex2f(0,350);
    glVertex2f(1500,350);
    glVertex2f(1500,650);
    glVertex2f(0,650);
    glEnd();
}

void shadow()
{
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex2f(0,-30);
    glVertex2f(-30,-25);
    glVertex2f(0,-20);
    glVertex2f(-30,-25);
    glEnd();
}

void fish()
{
    glColor3f(0.75,0,0.15);
    glBegin(GL_POLYGON);
    glVertex2f(0,-20);
    glVertex2f(-20,0);
    glVertex2f(0,20);
    glVertex2f(20,0);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(20,0);
    glVertex2f(40,20);
    glVertex2f(40,-20);
    glEnd();

    glColor3f(0.0,0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(160,490);
    glVertex2f(180,510);
    glVertex2f(180,470);
    glEnd();
}


void smallhouse()
{
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1200,680);
    glVertex2f(1200,780);
    glVertex2f(1400,780);
    glVertex2f(1400,680);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1150,780);
    glVertex2f(1150,790);
    glVertex2f(1450,790);
    glVertex2f(1450,780);
    glEnd();

    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    glVertex2d(1350,680);
    glVertex2d(1350,720);
    glVertex2d(1370,720);
    glVertex2d(1370,680);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.0,0.0,0.0);
    glVertex2d(1250,750);
    glColor3f(1,1,0.5);
    glVertex2d(1300,750);
    glColor3f(1,1,0.8);
    glVertex2d(1300,700);
    glColor3f(1,1,0.7);
    glVertex2d(1250,700);
    glEnd();
}

void smallhouse1()
{
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1200,680);
    glVertex2f(1200,780);
    glVertex2f(1400,780);
    glVertex2f(1400,680);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1150,780);
    glVertex2f(1150,790);
    glVertex2f(1450,790);
    glVertex2f(1450,780);
    glEnd();
}

void draw_pixel(GLint cx,GLint cy)
{
    glPolygonMode(GL_FRONT,GL_FILL);
    glBegin(GL_POINTS);
    glVertex2i(cx,cy);
    glEnd();
}

void plotpixels(GLint h,GLint k,GLint x,GLint y)
{
    draw_pixel(x+h,y+k);
    draw_pixel(-x+h,y+k);
    draw_pixel(x+h,-y+k);
    draw_pixel(-x+h,-y+k);

    draw_pixel(y+h,x+k);
    draw_pixel(-y+h,x+k);
    draw_pixel(y+h,-x+k);
    draw_pixel(-y+h,-x+k);
}

void circle_draw(GLint h,GLint k,GLint r)
{
    GLint d=1-r,x=0,y=r;
    while(y>x)
    {
        plotpixels(h,k,x,y);
        if(d<0)
            d+=2*x+3;
        else
        {
            d+=2*(x-y)+5;
            --y;
        }
        ++x;
    }
    plotpixels(h,k,x,y);
}

void redrawcar()
{
    if(car1==0)
    {
        if(n<1500)
        {
            n+=1;
            glutPostRedisplay();
        }
        else
        {
            n=n-2000;
            glutPostRedisplay();
        }
    }
}

void Newtree()
{
    glColor3f(0.5,0.35,0.05);
    glBegin(GL_POLYGON);
    glVertex2f(650,100);
    glVertex2f(650,250);
    glVertex2f(690,250);
    glVertex2f(690,100);
    glEnd();



    glColor3f(0.0,0.5,0);
    glBegin(GL_POLYGON);
    glVertex2f(620,250);
    glVertex2f(670,400);
    glVertex2f(730,250);

    glColor3f(0.0,0.7,0);
    glBegin(GL_POLYGON);
    glVertex2f(620,350);
    glVertex2f(670,500);
    glVertex2f(730,350);
    glEnd();
}

void Newtree1()
{
    glColor3f(0.5,0.35,0.05);
    glBegin(GL_POLYGON);
    glVertex2f(470,100);
    glVertex2f(470,250);
    glVertex2f(520,250);
    glVertex2f(520,100);
    glEnd();

    glColor3f(0.0,0.8,0.);
    glBegin(GL_POLYGON);
    glVertex2f(420,250);
    glVertex2f(500,400);
    glVertex2f(580,250);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(420,350);
    glVertex2f(500,500);
    glVertex2f(580,350);
    glEnd();
}



void tree1()
{
    glColor3f(0.5,0.35,0.05);
    glBegin(GL_POLYGON);
    glVertex2f(120,0);
    glVertex2f(120,180);
    glVertex2f(180,180);
    glVertex2f(180,0);
    glEnd();
    drawFiledCircle(150,240,100,8,0,200,0);
    drawFiledCircle(90,150,70,6,0,160,0);
    drawFiledCircle(220,150,60,5,0,250,0);

}
void riverview()
{
    glColor3f(.8,.37,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(1500,0);
    glColor3f(0.7,0.37,0.0);
    glVertex2f(0,1000);
    glColor3f(0.4,0.6,0.0);
    glVertex2f(0,0);
    glColor3f(0.4,0.6,0.0);
    glVertex2f(1500,0);
    glEnd();

    sky();
    windmill();
    sea();
    tree1();
    glPushMatrix();
    glTranslated(100,50,0);
    tree1();
    glPopMatrix();
    house1();

    glPushMatrix();
    glTranslatef(100,-600,0.0);
    house1();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.95,0.95,0.0);
    glTranslatef(70,-788,0.0);
    house1();
    glPopMatrix();

    glPointSize(9.0);
    glColor3f(0.9,1,0.7);
    circle_draw(300,920,50);
    glColor3f(0.9,1,0.7);
    circle_draw(300,920,40);
    glColor3f(0.9,1,0.8);
    circle_draw(300,920,30);
    glColor3f(0.9,1,0.8);
    circle_draw(300,920,20);
    glColor3f(0.9,1,0.9);
    circle_draw(300,920,10);
    glColor3f(0.9,1,1);
    circle_draw(300,920,5);
    mountain();
    boat();
    glPushMatrix();
    glTranslated(fishX,sinf(fishX/40)*60+450,0);
    glRotated(180+cosf(fishX/40)*15,0,0,1);
    if(sinf(fishX/40)>=0)
        fish();
    glPopMatrix();

    glPushMatrix();
    glTranslated(fishX,450,0);
    if(sinf(fishX/40)>=0)
        shadow();
    glPopMatrix();
    fishX+=.5;
    if(fishX>1600)
        fishX=0;

    Newtree();

    glPushMatrix();
    draw_pixel(thx,thy);
    glTranslatef(thx,thy,0.0);
    glRotatef(th+=0.1,0.0,0.0,1.0);
    glTranslatef(-thx,-thy,0.0);
    glColor3f(0.80,0.80,0.80);
    glBegin(GL_POLYGON);
    glVertex2f(1340,900);
    glVertex2f(1340,850);
    glVertex2f(1360,850);
    glVertex2f(1360,900);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    draw_pixel(thx,thy);
    glTranslatef(thx,thy,0.0);
    glRotatef(th+=0.1,0.0,0.0,1.0);
    glTranslatef(-thx,-thy,0.0);
    glColor3f(0.80,0.80,0.80);
    glBegin(GL_POLYGON);
    glVertex2f(1340,940);
    glVertex2f(1340,990);
    glVertex2f(1360,990);
    glVertex2f(1360,940);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    draw_pixel(thx,thy);
    glTranslatef(thx,thy,0.0);
    glRotatef(th+=0.1,0.0,0.0,1.0);
    glTranslatef(-thx,-thy,0.0);
    glColor3f(0.80,0.80,0.80);
    glBegin(GL_POLYGON);
    glVertex2f(1285,910);
    glVertex2f(1285,930);
    glVertex2f(1335,930);
    glVertex2f(1335,910);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    draw_pixel(thx,thy);
    glTranslatef(thx,thy,0.0);
    glRotatef(th+=0.1,0.0,0.0,1.0);
    glTranslatef(-thx,-thy,0.0);
    glColor3f(0.80,0.80,0.80);
    glBegin(GL_POLYGON);
    glVertex2f(1365,910);
    glVertex2f(1415,910);
    glVertex2f(1415,930);
    glVertex2f(1365,930);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.75,0.75,0.0);
    windmill1();
    glPopMatrix();

    glPushMatrix();
    draw_pixel(635,847);
    glTranslatef(635,847,0.0);
    glRotatef(th+=0.1,0.0,0.0,1.0);
    glTranslatef(-thx,-thy,0.0);
    glColor3f(0.80,0.80,0.80);
    glBegin(GL_POLYGON);
    glVertex2f(1340,940);
    glVertex2f(1340,990);
    glVertex2f(1360,990);
    glVertex2f(1360,940);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    draw_pixel(635,847);
    glTranslatef(635,847,0.0);
    glRotatef(th+=0.1,0.0,0.0,1.0);
    glTranslatef(-thx,-thy,0.0);
    glColor3f(0.80,0.80,0.80);
    glBegin(GL_POLYGON);
    glVertex2f(1285,910);
    glVertex2f(1285,930);
    glVertex2f(1335,930);
    glVertex2f(1335,910);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    draw_pixel(635,847);
    glTranslatef(635,847,0.0);
    glRotatef(th+=0.1,0.0,0.0,1.0);
    glTranslatef(-thx,-thy,0.0);
    glColor3f(0.80,0.80,0.80);
    glBegin(GL_POLYGON);
    glVertex2f(1365,910);
    glVertex2f(1415,910);
    glVertex2f(1415,930);
    glVertex2f(1365,930);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    draw_pixel(635,847);
    glTranslatef(635,847,0.0);
    glRotatef(th+=0.1,0.0,0.0,1.0);
    glTranslatef(-thx,-thy,0.0);
    glColor3f(0.80,0.80,0.80);
    glBegin(GL_POLYGON);
    glVertex2f(1340,900);
    glVertex2f(1340,850);
    glVertex2f(1360,850);
    glVertex2f(1360,900);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(980,600,0);
    glScalef(0.5,0.5,0.0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1200,600,0);
    glScalef(0.5,0.5,0.0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(800,795,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(760,795,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(720,795,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(840,795,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(880,800,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(880,803,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(810,260,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(850,260,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(890,260,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(930,260,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(760,-15,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(830,100,0);
    glScalef(0.4,0.4,0);
    Newtree1();
    glPopMatrix();

    house2();

    glPushMatrix();
    glTranslatef(340,610,0);
    glScalef(0.4,0.4,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(430,610,0);
    glScalef(0.4,0.4,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400,610,0);
    glScalef(0.4,0.4,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(370,610,0);
    glScalef(0.4,0.4,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(410,600,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(440,600,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(470,600,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(500,600,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1080,600,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1050,600,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1020,600,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(990,600,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(960,600,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(860,795,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(880,795,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(900,795,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(930,795,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(930,600,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(800,795,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(830,795,0);
    glScalef(0.5,0.5,0);
    Newtree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,180,0);
    Grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,160,0);
    Grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,140,0);
    Grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,120,0);
    Grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,100,0);
    Grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,80,0);
    Grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,60,0);
    Grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,40,0);
    Grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,20,0);
    Grass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(200,0,0);
    Grass();
    glPopMatrix();
    glPushMatrix();
    glTranslated(200,50,0);
    tree1();
    glPopMatrix();
    glPushMatrix();
    glTranslated(400,70,0);
    tree1();
    glPopMatrix();
}

void init()
{
    glClearColor(.8,.5,0.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,1500,0.0,1000,0,10);
    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    riverview();
    redrawcar();
    glFlush();
    glutSwapBuffers();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize(1500,1080);
    glutInitWindowPosition(0,0);
    glutCreateWindow("River View");
    glutDisplayFunc(display);
    glutAddMenuEntry("OLD RIVER VIEW",1);
    glutAddMenuEntry("EXIT",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    init();
    glutMainLoop();
    return 0;
}
