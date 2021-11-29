#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

int random(int mi, int mx)
{
    return (rand()%(mx-mi+1))+mi;
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


void text(float x, float y, std::string s, int font, float r, float g, float b)
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
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, s[i]);
            break;
        case 2:
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
            break;
        case 3:
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
            break;
        case 4:
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
            break;
        case 5:
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
            break;
        case 6:
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, s[i]);
            break;
        default:
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
            break;
        }
    }
}
