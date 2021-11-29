#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<GL/freeglut.h>
#include "textures.c"

//TEXTURES
#define num_textures 3
GLuint textureID[num_textures];
//unsigned char *data;        //FROM FILE
//unsigned int width[num_textures],height[num_textures];  //FROM FILE
void DrawTexturedRect(int x,int y,int w,int h,GLuint texture,unsigned int fading,unsigned int i,unsigned int ill_change);
unsigned int fade_color[num_textures],fade_swap[num_textures];

unsigned char display_screen=0;  //Type Of Interface To Display

void opengl_info(void);
char gl_info_string[6][50];
void *font = GLUT_BITMAP_9_BY_15;
void *font1 = GLUT_BITMAP_HELVETICA_10;
void *font2 = GLUT_BITMAP_HELVETICA_12;
unsigned char vendor_info=0;

void smooth_input(void);  //Smooth Input By Taking Advantage Of glutSpecialUpFunc
unsigned char flag_left_arrow=0,flag_right_arrow=0,flag_up_arrow=0;  //Flags To Check If Keys Are Pressed
unsigned long int bullets_fired=0;
float shb_delay=0.1;
clock_t shb_time1=0;
double shb_timediff=0.0;

void display_string(int x,int y,void *font_to_use,char *string_to_display)
{
	glRasterPos2i(x,y);
	glutBitmapString(font_to_use,(unsigned char*)string_to_display);
}

void resize(int width,int height)
{
	glutReshapeWindow(500,500);
}
void render(void);
clock_t time1=0,time2=0,time3=0;
double timediff,fps_timediff,fps=60.0,delta_time=0.0166666666666667;
unsigned long int frame_count=0;

void splash_screen(void);
unsigned char splash_screen_to_display=0;

void main_menu_screen(void);
unsigned char menu_option=0,difficulty_option=0;
unsigned char difficulty_score_multiplier=10;

void options_screen(void);
unsigned char options_screen_option=0;
unsigned char dynamic_background=1;  //STATIC 0 or DYNAMIC 1
unsigned char objects_theme=0;

void game_screen(void);

void game_hud(void);
unsigned long int game_score=0,game_high_score=0,wave_count=0;
unsigned char new_high_score_flag=0;
float accuracy=0.0;

unsigned char digit_count(unsigned long int num);

void paused_screen(void);
unsigned char paused_option=0;

void wave_completed_screen(void);
unsigned char wave_completed_screen_option=0;

void game_over_screen(void);

void keyPress(unsigned char key, int x, int y);
void specialKeyPress(int key, int x, int y);
void SpecialKeysUp(int key, int x, int y);

void star_background(unsigned char);
#define num_stars 501
struct stars
{
	float star_x_pos;
	float star_y_pos;
}star[num_stars];

void color_change(void);
int red=255,green=0,blue=0;
float cc_time_delay=0.01;
clock_t cc_time1=0;
double cc_timediff=0.0;

void shuttle(void);
float shuttle_x_pos=225.0,shuttle_y_pos=10.0;
int shuttle_hitpoints=3;
unsigned char shuttle_i_got_hit=0;

void shuttle_bullet(void);
#define max_bullets 50
struct shuttle_bullet
{
	float x_pos,y_pos;
	unsigned char allocated;
}sh_bullet[max_bullets];

float triangle_area(float x1,float y1,float x2,float y2,float x3,float y3);
unsigned char collision_with_shuttle(float x1,float y1,float x2,float y2,float x3,float y3,float x,float y);
float shuttle_area;

void circular_aliens(void);
#define num_cir_aliens 50
unsigned char ca_movement_type=1;
float alien_x_pos,alien_y_pos,r=10.0,angle;
struct circular_aliens
{
	float alien_initial_x_pos,alien_initial_y_pos,alien_min_x_pos,alien_max_x_pos;
	unsigned char alien_hitpoints,i_got_hit,alien_direction,go;
}cir_alien[num_cir_aliens];

void create_ca_alive_list(void);
unsigned char ca_alive_count;
int ca_alive[num_cir_aliens];

void ca_bullet_alloc(void);
unsigned char alien_that_will_shoot=0;
float ca_bullet_alloc_time_delay=0.5;
clock_t ca_time1=0;
double ca_timediff=0.0;

void cir_alien_bullet(void);
//USES max_bullets OF shuttle_bullets
struct cir_alien_bullet
{
	float x_pos,y_pos;
	unsigned char allocated;
}ca_bullet[max_bullets];

void new_wave_initialization(void)
{
	int i,j=0;

//WAVE
	wave_count++;

//WAVE COMPLETED SCREEN
	wave_completed_screen_option=0;

//SHUTTLE
	red=255,green=0,blue=0;
	shuttle_x_pos=225.0,shuttle_y_pos=10.0;
	shuttle_i_got_hit=0;

//CIRCULAR ALIENS
	ca_movement_type=rand()%3;
	for(i=0;i<50;i++)
	{
		cir_alien[i].alien_initial_x_pos=(60.0+((i%10)*26.0)); //Add x amount
		if(ca_movement_type==0 || ca_movement_type==2)
		{
			cir_alien[i].alien_min_x_pos=cir_alien[i].alien_initial_x_pos;
			cir_alien[i].alien_max_x_pos=cir_alien[i].alien_min_x_pos+146.0; //Decrease by 3*x the amount
		}
		else if(ca_movement_type==1)
		{
			cir_alien[i].alien_min_x_pos=60.0;
			cir_alien[i].alien_max_x_pos=440.0;
		}

		if(i>9 && i%10==0)j++;
		cir_alien[i].alien_initial_y_pos=(440.0-(j*26.0)); //Add x amount
		cir_alien[i].alien_hitpoints=3;
		cir_alien[i].i_got_hit=0;
		cir_alien[i].alien_direction=cir_alien[i].go=1;
	}

//INITIALIZE BULLET SPACES BY DE-ALLOCATION FLAG
	for(i=0;i<max_bullets;i++)
	{
		sh_bullet[i].allocated=0;
		ca_bullet[i].allocated=0;
	}
}

void new_game_initialization(void)
{
//FRAME
	frame_count=0;

//OPENGL INFO
	vendor_info=0;

//OPTIONS SCREEN
	options_screen_option=0;

//PAUSED SCREEN
	paused_option=0;

//GAME SCORE
	game_score=0;
	new_high_score_flag=0;

//BULLETS FIRED
	bullets_fired=0;

//ACCURACY
	accuracy=0.0;

//GAME DIFFICULTY
	if(difficulty_option==0)  //EASY
	{
		shuttle_hitpoints=10;
		difficulty_score_multiplier=10;
		ca_bullet_alloc_time_delay=0.5;
	}
	else if(difficulty_option==1)  //MODERATE
	{
		shuttle_hitpoints=6;
		difficulty_score_multiplier=20;
		ca_bullet_alloc_time_delay=0.3;
	}
	else if(difficulty_option==2)  //HARD
	{
		shuttle_hitpoints=3;
		difficulty_score_multiplier=30;
		ca_bullet_alloc_time_delay=0.2;
	}

//WAVE
	wave_count=0;

	new_wave_initialization();
}

int main(int argc,char **argv)
{

	int i;
//TEXTURE FADING INITIALIZATION
	for(i=0;i<num_textures;i++)
	{
		fade_color[i]=1;
		fade_swap[i]=1;
	}

//STAR BACKGROUND INTIAL POSITION GENERATION
	for(i=0;i<num_stars;i++)
	{
		star[i].star_x_pos=rand()%501;
		star[i].star_y_pos=(int)(i*(501.0/num_stars))%501;
	}

//NEW GAME
	new_game_initialization();

//AREA OF TRIANGULAR SHUTTLE
	shuttle_area=triangle_area(shuttle_x_pos,shuttle_y_pos,shuttle_x_pos+25.0,shuttle_y_pos+21.6506350946,shuttle_x_pos+50.0,shuttle_y_pos);

//OPENGL INITIALIZATIONS
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH))/2-250,(glutGet(GLUT_SCREEN_HEIGHT))/2-250);
	glutCreateWindow("Space Invaders v1.0");
	gluOrtho2D(0.0,500.0,0.0,500.0);
	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutReshapeFunc(resize);
	glutSpecialFunc(specialKeyPress);
	glutSpecialUpFunc(SpecialKeysUp);
	glutKeyboardFunc(keyPress);

//GRAPHICS QUALITY
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_MULTISAMPLE);

//LOAD TEXTURES (Note The Loading After Glut Initialization)
	glGenTextures(num_textures,textureID);

	//data=load_BMP_raw("nvidia.tex",&width[0],&height[0]);                                                                       //FROM FILE
	//free(data);                                                                                                                 //FROM FILE
	//printf("Width:%u Height:%u TextureID:%u\n",width[0],height[0],textureID[0]);                                                //FROM FILE
	glBindTexture(GL_TEXTURE_2D,textureID[0]);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,nvidia_tex.width,nvidia_tex.height,0,GL_RGB,GL_UNSIGNED_BYTE,nvidia_tex.pixel_data);      //EMBEDDED
	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width[0],height[0],0,GL_RGB,GL_UNSIGNED_BYTE,data);                                     //FROM FILE

	//data=load_BMP_raw("title.tex",&width[1],&height[1]);                                                                        //FROM FILE
	//free(data);                                                                                                                 //FROM FILE
	//printf("Width:%u Height:%u TextureID:%u\n",width[1],height[1],textureID[1]);                                                  //FROM FILE
	glBindTexture(GL_TEXTURE_2D,textureID[1]);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,title_tex.width,title_tex.height,0,GL_RGB,GL_UNSIGNED_BYTE,title_tex.pixel_data);       //EMBEDDED
	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width[1],height[1],0,GL_RGB,GL_UNSIGNED_BYTE,data);                                     //FROM FILE

	//data=load_BMP_raw("esrb.tex",&width[2],&height[2]);                                                                         //FROM FILE
	//free(data);                                                                                                                 //FROM FILE
	//printf("Width:%u Height:%u TextureID:%u\n",width[2],height[2],textureID[2]);                                                //FROM FILE
	glBindTexture(GL_TEXTURE_2D,textureID[2]);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,esrb_tex.width,esrb_tex.height,0,GL_RGB,GL_UNSIGNED_BYTE,esrb_tex.pixel_data);            //EMBEDDED
	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width[2],height[2],0,GL_RGB,GL_UNSIGNED_BYTE,data);                                     //FROM FILE


//OPENGL INFORMATION
	strcpy(gl_info_string[0],(char*)glGetString(GL_VERSION));
	strcpy(gl_info_string[1],(char*)glGetString(GL_VENDOR));
	strcpy(gl_info_string[2],(char*)glGetString(GL_RENDERER));
	strcpy(gl_info_string[4],"Press F2 For OpenGL Information");

	glutMainLoop();

	return 0;
}

void opengl_info(void)
{
	glColor3ub(255,255,255);
	if(vendor_info)
	{
		display_string(0,490,font2,gl_info_string[0]);  //GL_VERSION
		display_string(0,475,font2,gl_info_string[1]);  //GL_VENDOR
		display_string(0,460,font2,gl_info_string[2]);  //GL_RENDERER
		sprintf(gl_info_string[3],"Frame:%lu FPS:%f",frame_count,fps);
		display_string(0,445,font2,gl_info_string[3]);  //FRAME and FPS
		sprintf(gl_info_string[5],"Limit FPS:\n1>> 15FPS\n2>> 30FPS\n3>> 60FPS\n4>> No Limit");
		display_string(0,430,font2,gl_info_string[5]);
	}
	else
	{
		display_string(0,490,font2,gl_info_string[4]);  //MORE INFO
	}
}

void smooth_input(void)
{
//LEFT ARROW
	if(flag_left_arrow==1)
	{
		shuttle_x_pos=shuttle_x_pos-((60.0/fps)*4.0);
		if(shuttle_x_pos<0.0)shuttle_x_pos=0.0;
	}

//RIGHT ARROW
	if(flag_right_arrow==1)
	{
		shuttle_x_pos=shuttle_x_pos+((60.0/fps)*4.0);
		if(shuttle_x_pos>450.0)shuttle_x_pos=450.0;
	}

//UP ARROW
	shb_timediff=(double)(time2-shb_time1)/CLOCKS_PER_SEC;
	if(flag_up_arrow==1 && shb_timediff>=shb_delay)
	{
		shb_time1=clock();
		int i;
		for(i=0;i<max_bullets;i++)
		{
			if(sh_bullet[i].allocated==0)
			{
				sh_bullet[i].x_pos=shuttle_x_pos+25.0;
				sh_bullet[i].y_pos=shuttle_y_pos+21.6506350946;
				sh_bullet[i].allocated=1;
				bullets_fired++;
				break;
			}
		}
	}
}

void render(void)
{
	time2=clock();  //Common For FRAME LIMITER and FPS CALCULATOR
	timediff=(double)(time2-time1)/CLOCKS_PER_SEC;  //Common For FRAME LIMITER and FPS CALCULATOR

	if(timediff>=delta_time)
	{
		time1=clock();

		glClear(GL_COLOR_BUFFER_BIT);

		if(display_screen==2)game_screen();
		else if(display_screen==0)splash_screen();
		else if(display_screen==1)main_menu_screen();
		else if(display_screen==3)options_screen();
		else if(display_screen==4)paused_screen();
		else if(display_screen==5)wave_completed_screen();
		else if(display_screen==6)game_over_screen();

		fps=(1.0/timediff);
		if(fps<10.0)fps=10.0;  //FORCE 10.0 FPS

		glutSwapBuffers();
	}

}

void game_screen(void)
{
	star_background(dynamic_background);

	shuttle_bullet();

	create_ca_alive_list();
	ca_bullet_alloc();
	cir_alien_bullet();
	circular_aliens();

	smooth_input();
	shuttle();
	game_hud();

	opengl_info();
	frame_count++;
}

void game_hud(void)
{
	char game_hud_string[5][25];

//HIGH SCORE
	if(game_score>game_high_score)
	{
		new_high_score_flag=1;
		game_high_score=game_score;
	}
	sprintf(game_hud_string[0],"HIGH SCORE: %lu",game_high_score);
	glColor3ub(0,255,0);
	display_string(200,475,font2,game_hud_string[0]);

//WAVE
	sprintf(game_hud_string[1],"WAVE: %lu",wave_count);
	glColor3ub(0,255,0);
	display_string(400,475,font2,game_hud_string[1]);

//INVASION LINE
	glColor3ub(red,green,blue);
	glBegin(GL_LINES);
	glVertex2f(0,50);
	glVertex2f(500,50);
	glEnd();

//ACCURACY
	if(bullets_fired==0)accuracy=0.0;
	else accuracy=(((wave_count*50.0*3.0)-(ca_alive_count*3.0))/bullets_fired)*100.0;
	sprintf(game_hud_string[2],"ACCURACY: %f%%",accuracy);
	glColor3ub(128,255,0);
	display_string(0,38,font1,game_hud_string[2]);

//SCORE
	unsigned char digit_size=(digit_count(game_score))*6;
	sprintf(game_hud_string[3],"%lu :SCORE",game_score);
	glColor3ub(0,255,255);
	display_string(shuttle_x_pos-45-digit_size,shuttle_y_pos,font1,game_hud_string[3]);

//HP
	sprintf(game_hud_string[4],"HP: %d",shuttle_hitpoints);
	if(shuttle_hitpoints>=3)glColor3ub(0,255,0);
	else if(shuttle_hitpoints==2)glColor3ub(255,255,0);
	else glColor3ub(255,0,0);
	display_string(shuttle_x_pos+55,shuttle_y_pos,font1,game_hud_string[4]);
}

void splash_screen(void)
{
		if(splash_screen_to_display==0)
		{
			//DrawTexturedRect(0,200,width[0],height[0],textureID[0],1,0,1);                //FROM FILE
			DrawTexturedRect(0,200,nvidia_tex.width,nvidia_tex.height,textureID[0],1,0,1);  //EMBEDDED

		}
		else if(splash_screen_to_display==1)
		{
			//DrawTexturedRect(105,230,width[1],height[1],textureID[1],1,1,0);              //FROM FILE
			//DrawTexturedRect(-10,5,width[2],height[2],textureID[2],1,2,1);                //FROM FILE
			DrawTexturedRect(105,230,title_tex.width,title_tex.height,textureID[1],1,1,0);  //EMBEDDED
			DrawTexturedRect(-10,5,esrb_tex.width,esrb_tex.height,textureID[2],1,2,1);      //EMBEDDED
		}
		else if(splash_screen_to_display==2)
		{
//DUMMY LOADING PROGRESS BAR
			char splash_string[3][15];
			static float splash_x=0;

			glColor3ub(0,136,24);
			glLineWidth(3.0);
			glBegin(GL_LINES);
			glVertex2f(0,5);
			glColor3ub(0,255,0);
			glVertex2f(splash_x,5);
			glEnd();

			sprintf(splash_string[0],"Jeevan PN");
			display_string(205,250,font,splash_string[0]);

			sprintf(splash_string[1],"1CE12CS027");
			display_string(201,235,font,splash_string[1]);

			sprintf(splash_string[2],"%.2f%%",((splash_x/500.0)*100));
			display_string(430,10,font,splash_string[2]);
			splash_x=splash_x+((60.0/fps)*1.8);

			if(splash_x>499.0)
			{
				glLineWidth(1.0);
				display_screen=1;
				glDeleteTextures(num_textures,textureID);
			}

		}
}

void DrawTexturedRect(int x,int y,int w,int h,GLuint texture,unsigned int fading,unsigned int i,unsigned int ill_change)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if(fading==1)
	{
		glColor3ub(fade_color[i],fade_color[i],fade_color[i]);
		if(fade_swap[i]==1)
		{
			fade_color[i]++;
			if(fade_color[i]==255)fade_swap[i]=!fade_swap[i];
		}
		else
		{
			fade_color[i]--;
			fade_color[i]--;
			if(fade_color[i]==1 && ill_change==1)splash_screen_to_display++;
		}
	}
	//SWITCHING TO NEXT SCREEN IN STATIC MODE NOT IMPLEMENTED YET
	else glColor3ub(255,255,255);

	glBegin(GL_QUADS);
    glTexCoord2i(0,0); glVertex2i(x,y);
    glTexCoord2i(1,0); glVertex2i(x+w,y);
    glTexCoord2i(1,1); glVertex2i(x+w,y+h);
    glTexCoord2i(0,1); glVertex2i(x,y+h);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void main_menu_screen(void)
{
	char menu_string[9][30];
	sprintf(menu_string[0],"HIGH SCORE : %lu",game_high_score);
	strcpy(menu_string[1],"New Game");
	strcpy(menu_string[2],"Difficulty:");
	strcpy(menu_string[3],"Easy");
	strcpy(menu_string[4],"Moderate");
	strcpy(menu_string[5],"Hard");
	strcpy(menu_string[6],"Options");
	strcpy(menu_string[7],"Quit");
	strcpy(menu_string[8],"1.0");

	star_background(dynamic_background);

//HIGH SCORE
	if(game_high_score>0)
	{
		glColor3ub(0,255,0);
		display_string(200,475,font2,menu_string[0]);
	}

//NEW GAME
	if(menu_option==0)glColor3ub(255,255,255);
	else glColor3ub(255,0,0);
	display_string(200,250,font,menu_string[1]);

//GAME DIFFICULTY
	if(menu_option==1)glColor3ub(255,255,255);
	else glColor3ub(255,0,0);
	display_string(200,235,font,menu_string[2]);
//EASY
	if(difficulty_option==0)
	{
		glColor3ub(0,255,0);
		display_string(305,235,font,menu_string[3]);

	}
//MODERATE
	else if(difficulty_option==1)
	{
		glColor3ub(255,255,0);
		display_string(305,235,font,menu_string[4]);
	}
//HARD
	else if(difficulty_option==2)
	{
		glColor3ub(255,0,0);
		display_string(305,235,font,menu_string[5]);
	}

//OPTIONS
    if(menu_option==2)glColor3ub(255,255,255);
    else glColor3ub(255,0,0);
    display_string(200,220,font,menu_string[6]);

//QUIT
    if(menu_option==3)glColor3ub(255,255,255);
    else glColor3ub(255,0,0);
    display_string(200,205,font,menu_string[7]);

//GAME VERSION
    glColor3ub(255,0,0);
    display_string(455,10,font,menu_string[8]);
}

void options_screen(void)
{
	char options_string[8][25];
	strcpy(options_string[0],"OPTIONS");
	strcpy(options_string[1],"DISPLAY");
	strcpy(options_string[2],"Dynamic Background: ");
	strcpy(options_string[3],"ON");
	strcpy(options_string[4],"OFF");
	strcpy(options_string[5],"Objects Theme:");
	strcpy(options_string[6],"SOLID POLYGONS");
	strcpy(options_string[7],"HOLLOW BRIGHT");

	star_background(dynamic_background);

//OPTIONS
	glColor3ub(255,0,0);
	display_string(210,310,font,options_string[0]);
//DISPLAY
	display_string(135,295,font,options_string[1]);

//DYNAMIC BACKGROUND
	if(options_screen_option==0)glColor3ub(255,255,255);
	else glColor3ub(255,0,0);
	display_string(135,280,font,options_string[2]);

	if(dynamic_background==1)  //ON
	{
		glColor3ub(0,255,0);  //Green Color
		display_string(315,280,font,options_string[3]);
	}
	else if(dynamic_background==0)  //OFF
	{
		glColor3ub(255,0,0);  //Red Color
		display_string(315,280,font,options_string[4]);
	}

//OBJECTS THEME
	if(options_screen_option==1)glColor3ub(255,255,255);
	else glColor3ub(255,0,0);
	display_string(135,265,font,options_string[5]);

	if(objects_theme==0)  //SOLID POLYGONS
	{
		glColor3ub(128,255,0);
		display_string(315,265,font,options_string[6]);
	}
	else if(objects_theme==1)  //HOLLOW BRIGHT
	{
		glColor3ub(255,255,0);
		display_string(315,265,font,options_string[7]);
	}

}

void paused_screen(void)
{
	char paused_string[3][50];
	strcpy(paused_string[0],"GAME PAUSED");
	strcpy(paused_string[1],"Resume");
	strcpy(paused_string[2],"Quit To Main Menu");

	star_background(dynamic_background);

//GAME PAUSED
	glColor3ub(255,0,0);
	display_string(200,250,font,paused_string[0]);

//RESUME
	if(paused_option==0)glColor3ub(255,255,255);
	else glColor3ub(255,0,0);
	display_string(200,235,font,paused_string[1]);

//QUIT
	if(paused_option==1)glColor3ub(255,255,255);
	else glColor3ub(255,0,0);
	display_string(200,220,font,paused_string[2]);
}

void wave_completed_screen(void)
{
	char wave_completed_string[5][25];
	strcpy(wave_completed_string[0],"WAVE COMPLETED!");
	strcpy(wave_completed_string[3],"Next Wave >>>");
	strcpy(wave_completed_string[4],"Quit To Main Menu");

	star_background(dynamic_background);

//WAVE COMPLETED
	glColor3ub(0,255,0);
	display_string(180,300,font,wave_completed_string[0]);

//SCORE
	glColor3ub(238,130,238);
	if(new_high_score_flag==1)sprintf(wave_completed_string[1],"Score: %lu  *NEW HIGH SCORE*",game_high_score);
	else sprintf(wave_completed_string[1],"Score: %lu",game_score);
	display_string(180,270,font,wave_completed_string[1]);

//ACCURACY
	glColor3ub(0,255,255);
	sprintf(wave_completed_string[2],"Accuracy: %f%%",accuracy);
	display_string(180,240,font,wave_completed_string[2]);

//NEXT WAVE
	if(wave_completed_screen_option==0)glColor3ub(255,255,255);
	else glColor3ub(255,0,0);
	display_string(180,190,font,wave_completed_string[3]);

//QUIT TO MAIN MENU
	if(wave_completed_screen_option==1)glColor3ub(255,255,255);
	else glColor3ub(255,0,0);
	display_string(180,175,font,wave_completed_string[4]);
}

void game_over_screen(void)
{
	char game_over_string[4][25];
	strcpy(game_over_string[0],"GAME OVER!");
	strcpy(game_over_string[3],"<<< Back To Main Menu");

	star_background(dynamic_background);

//GAME OVER
	glColor3ub(255,0,0);
	display_string(180,300,font,game_over_string[0]);

//SCORE
	glColor3ub(238,130,238);
	if(new_high_score_flag==1)sprintf(game_over_string[1],"Score: %lu  *NEW HIGH SCORE*",game_high_score);
	else sprintf(game_over_string[1],"Score: %lu",game_score);
	display_string(180,270,font,game_over_string[1]);

//ACCURACY
	glColor3ub(0,255,255);
	sprintf(game_over_string[2],"Accuracy: %f%%",accuracy);
	display_string(180,240,font,game_over_string[2]);

//BACK TO MAIN MENU
	glColor3ub(255,255,255);
	display_string(135,190,font,game_over_string[3]);
}

void keyPress(unsigned char key, int x, int y)
{
//GAME SCREEN
	if(display_screen==2)
	{
		switch(key)
		{
		case '1':
             delta_time=0.0666666666666667;  //For 15fps
             break;
        case '2':
        	delta_time=0.0333333333333333;  //For 30fps
             break;
        case '3':
        	delta_time=0.0166666666666667;  //For 60fps
        	break;
        case '4':
        	delta_time=0.0;  //No Frame Limit,Although glutSwapBuffers waits for vSync
        	break;

		case 27 :
            display_screen=4;  //Switch To Paused Screen (Pause Game)
		}
	}

//SPLASH SCREEN
	else if(display_screen==0)
	{
		if((splash_screen_to_display==0 || splash_screen_to_display==1) && key==27)
		{
			splash_screen_to_display++;
		}
	}

//MAIN MENU
	else if(display_screen==1)
    {
    	switch(key)
   		{
   		case 13:  //Press Enter Key To Select Option
   			if(menu_option==0){new_game_initialization();display_screen=2;}  //New Game -> Game Screen
   			else if(menu_option==2)display_screen=3; //Options -> Options Screen
   			else if(menu_option==3)exit(0);  //Quit
   		}
    }

//OPTIONS SCREEN
	else if(display_screen==3)
    {
    	switch(key)
    	{
    	case 27:
    		display_screen=1;
    	}
    }

//PAUSED SCREEN
	else if(display_screen==4)
    {
    	switch(key)
    	{
    	case 13:
    		if(paused_option==0)display_screen=2;  //Paused Screen -> Game Screen (Resume Game)
    		else if(paused_option==1)display_screen=1; //Quit To Main Menu
    	}
    }

//WAVE COMPLETED SCREEN
	else if(display_screen==5)
    {
    	switch(key)
    	{
    	case 13:
    		if(wave_completed_screen_option==0)
    		{
    			new_wave_initialization();
    			display_screen=2;  //Start New Wave
    		}
    		else
    			display_screen=1;  //Quit To Main Menu
    	}
    }

//GAME OVER SCREEN
	else if(display_screen==6)
    {
    	switch(key)
    	{
    	case 13:
    		display_screen=1;  //Back To Main Menu
    	}
    }
}

void specialKeyPress(int key, int x, int y)
{
//GAME SCREEN
	if(display_screen==2)
	{
		if(GLUT_KEY_LEFT==key)flag_left_arrow=1;
		else if(GLUT_KEY_RIGHT==key)flag_right_arrow=1;
		else if(GLUT_KEY_UP==key)flag_up_arrow=1;

		else if(GLUT_KEY_F2==key)vendor_info=!vendor_info; //Negate 0->1 (or) 1->0
	}

//MAIN MENU
	else if(display_screen==1)
	{
		switch(key)
		{
		case GLUT_KEY_UP:
			menu_option=(menu_option-1)%4;
			if(menu_option==255)menu_option=3;  //Unsigned char,(0-1)=255
			break;
		case GLUT_KEY_DOWN:
			menu_option=(menu_option+1)%4;
			break;
		case GLUT_KEY_LEFT:
			if(menu_option==1)
			{
				difficulty_option=(difficulty_option-1)%3;
				if(difficulty_option==255)difficulty_option=2;
			}
			break;
		case GLUT_KEY_RIGHT:
			if(menu_option==1)
			{
				difficulty_option=(difficulty_option+1)%3;
			}
			break;
		}
	}

//OPTIONS SCREEN
	else if(display_screen==3)
	{
		switch(key)
		{
		case GLUT_KEY_UP:
			options_screen_option=!options_screen_option;
			break;
		case GLUT_KEY_DOWN:
			options_screen_option=!options_screen_option;
			break;

		case GLUT_KEY_LEFT:
			if(options_screen_option==0)dynamic_background=!dynamic_background;  //ON or OFF
			else if(options_screen_option==1)objects_theme=!objects_theme;  //POLYGONS or HOLLOW BRIGHT
			break;
		case GLUT_KEY_RIGHT:
			if(options_screen_option==0)dynamic_background=!dynamic_background;  //ON or OFF
			else if(options_screen_option==1)objects_theme=!objects_theme;  //POLYGONS or HOLLOW BRIGHT
			break;
		}
	}

//PAUSED SCREEN
	else if(display_screen==4)
	{
		switch(key)
		{
		case GLUT_KEY_UP:
			paused_option=(paused_option-1)%2;
			if(paused_option==255)paused_option=1;  //Unsigned char,(0-1)=255
			break;
		case GLUT_KEY_DOWN:
			paused_option=(paused_option+1)%2;
			break;
		}
	}
//WAVE COMPLETED SCREEN
	else if(display_screen==5)
	{
		switch(key)
		{
		case GLUT_KEY_UP:
			wave_completed_screen_option=!wave_completed_screen_option;
			break;
		case GLUT_KEY_DOWN:
			wave_completed_screen_option=!wave_completed_screen_option;
			break;
		}
	}
}

void SpecialKeysUp(int key, int x, int y)
{
	 if(GLUT_KEY_LEFT==key)flag_left_arrow=0;
	 else if(GLUT_KEY_RIGHT==key)flag_right_arrow=0;
	 else if(GLUT_KEY_UP==key)flag_up_arrow=0;
}

void star_background(unsigned char option)
{
//STATIC STAR BACKGROUND
	if(option==0)
	{
		int i;
		glColor3ub(128,128,128); //White Color
		glPointSize(2.0);

		glBegin(GL_POINTS);
		for(i=0;i<num_stars;i++)
		{
			glVertex2f(star[i].star_x_pos,star[i].star_y_pos);  //Draw Stars
		}
		glEnd();
	}

//DYNAMIC BACKGROUND
	else if(option==1)
	{
		int i=0;
		glColor3ub(128,128,128);  //White Color
		glPointSize(2.0);

		glBegin(GL_POINTS);
		while(i<num_stars)
		{
			glVertex2f(star[i].star_x_pos,star[i].star_y_pos);  //Draw Stars

			star[i].star_y_pos=star[i].star_y_pos-((60.0/fps)*1.0); //Decrease y_pos
			if(star[i].star_y_pos<0)star[i].star_y_pos=500;  // -1 -> 500
			else if(star[i].star_y_pos==0)star[i].star_x_pos=rand()%501; //Create New x_pos at y_pos=0

			i++;
		}
		glEnd();
	}
}

void color_change(void)
{
	cc_timediff=(double)(time2-cc_time1)/CLOCKS_PER_SEC;
    printf("%f\n",cc_timediff);
	if(cc_timediff>=cc_time_delay)
	{
		cc_time1=clock();

		if(red==255 && green<255 && blue==0)green++;
		else if(red>0 && green==255 && blue==0)red--;
		else if(red==0 && green==255 && blue<255)blue++;
		else if(red==0 && green>0 && blue==255)green--;
		else if(red<255 && green==0 && blue==255)red++;
		else if(red==255 && green==0 && blue>0)blue--;

	}
}

void shuttle(void)
{
	int i;
	for(i=0;i<max_bullets;i++)
	{
		if(ca_bullet[i].allocated==1 && ca_bullet[i].y_pos<50.0 && collision_with_shuttle(shuttle_x_pos,shuttle_y_pos,shuttle_x_pos+25.0,shuttle_y_pos+21.6506350946,shuttle_x_pos+50.0,shuttle_y_pos,ca_bullet[i].x_pos,ca_bullet[i].y_pos))
		{
			ca_bullet[i].allocated=0;

			shuttle_hitpoints=shuttle_hitpoints-1;
			if(shuttle_hitpoints<1)display_screen=6;  //GAME OVER

			shuttle_i_got_hit=shuttle_i_got_hit+5;
		}
	}

	color_change();
	if(shuttle_i_got_hit>0)
	{
		glColor3ub(255,255,255);
		shuttle_i_got_hit--;
	}
	else glColor3ub(red,green,blue);

	if(objects_theme==0)glBegin(GL_TRIANGLES);
	else if(objects_theme==1){glLineWidth(2.0);glBegin(GL_LINE_LOOP);}
	glVertex2f(shuttle_x_pos,shuttle_y_pos);
	glVertex2f(shuttle_x_pos+25.0,shuttle_y_pos+21.6506350946);
	glVertex2f(shuttle_x_pos+50.0,shuttle_y_pos);
	glEnd();
}

void shuttle_bullet(void)
{
	int i;
	glColor3ub(0,255,0);

	for(i=0;i<max_bullets;i++)
	{
		if(sh_bullet[i].allocated==1)
		{
			sh_bullet[i].y_pos=sh_bullet[i].y_pos+((60.0/fps)*5.0);
			if(sh_bullet[i].y_pos<500.0)
			{
				glBegin(GL_LINES);
				glVertex2f(sh_bullet[i].x_pos,sh_bullet[i].y_pos+10);
				glVertex2f(sh_bullet[i].x_pos,sh_bullet[i].y_pos);
				glVertex2f(sh_bullet[i].x_pos+1,sh_bullet[i].y_pos);
				glVertex2f(sh_bullet[i].x_pos+1,sh_bullet[i].y_pos+10);
				glEnd();
			}
			else sh_bullet[i].allocated=0;
		}
	}
}

float triangle_area(float x1,float y1,float x2,float y2,float x3,float y3)
{
	return fabs((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2))/2.0);
}

unsigned char collision_with_shuttle(float x1,float y1,float x2,float y2,float x3,float y3,float x,float y)
{
	float area1,area2,area3,area_sum,area_diff;

	area1=triangle_area(x,y,x2,y2,x3,y3);
	area2=triangle_area(x1,y1,x,y,x3,y3);
	area3=triangle_area(x1,y1,x2,y2,x,y);

	area_sum=area1+area2+area3;
	area_diff=shuttle_area-area_sum;

	return ((area_diff)>-1.0 && (area_diff)<1.0);
}

void circular_aliens(void)
{
	int i,j;

    for(i=0;i<num_cir_aliens;i++)  //Scan Through All Aliens
    {
    	if(cir_alien[i].alien_hitpoints>0)  //Only Aliens With HP>0
    	{
//COLLISION WITH BULLET
    		for(j=0;j<max_bullets;j++)  //Scan Through All Bullets
    		{
    			if(sh_bullet[j].allocated==1 && (pow(cir_alien[i].alien_initial_x_pos-sh_bullet[j].x_pos,2)+pow(cir_alien[i].alien_initial_y_pos-sh_bullet[j].y_pos,2))<=pow(r,2))  //Thank You Pythagoras :)
    			{
    				cir_alien[i].alien_hitpoints=cir_alien[i].alien_hitpoints-1;
    				cir_alien[i].i_got_hit=cir_alien[i].i_got_hit+5;
    		    	sh_bullet[j].allocated=0;
    		    	game_score=game_score+difficulty_score_multiplier;
    		    }
    		}
//DRAW CIRCULAR ALIENS

    		if(cir_alien[i].i_got_hit>0)
    		{
    			glColor3ub(255,255,255);
    			cir_alien[i].i_got_hit--;
    		}
    		else if(cir_alien[i].alien_hitpoints==3)glColor3ub(255,0,0);
    		else if(cir_alien[i].alien_hitpoints==2)glColor3ub(255,255,0);
    		else if(cir_alien[i].alien_hitpoints==1)glColor3ub(0,255,0);

    		if(objects_theme==0)glBegin(GL_POLYGON);  //FILLED POLYGONS
    		else if(objects_theme==1){glPointSize(2.0);glBegin(GL_POINTS);}  //HOLLOW

    		for(angle=0.0;angle<=6.28318531;angle=angle+0.1) //360 degrees
    		{
    			alien_x_pos=(r*cosf(angle))+cir_alien[i].alien_initial_x_pos;//calculate the x component
    			alien_y_pos=(r*sinf(angle))+cir_alien[i].alien_initial_y_pos;//calculate the y component
    			glVertex2f(alien_x_pos,alien_y_pos);//output vertex
    		}
    		glEnd();
    	}
    }

//ALIEN MOVEMENT
    if(ca_movement_type==0 || ca_movement_type==1)
    {
//ALL ALIENS HORIZONTAL MOVEMENT
//LEFT -> RIGHT
    	for(i=0;i<num_cir_aliens;i++)
        {
        	if(cir_alien[i].alien_initial_x_pos<=cir_alien[i].alien_max_x_pos && cir_alien[i].go==1) //Food Is On The Right:D
        	{
        		if(cir_alien[i].alien_direction==1)cir_alien[i].alien_initial_x_pos=cir_alien[i].alien_initial_x_pos+((60.0/fps)*0.8); //Go Get The Food Buddy!
        		if(cir_alien[i].alien_initial_x_pos>=cir_alien[i].alien_max_x_pos)
        		{
        			cir_alien[i].alien_initial_x_pos=cir_alien[i].alien_max_x_pos;
        			cir_alien[i].go=0; //Throw Food To The Left
        			cir_alien[i].alien_direction=!cir_alien[i].alien_direction; //Hamster Changes Direction
        			cir_alien[i].alien_initial_y_pos=cir_alien[i].alien_initial_y_pos-((60.0/fps)*5.0);  //Aliens Hop Down
        			if(cir_alien[i].alien_initial_y_pos<=50.0)display_screen=6; //Invasion Barrier Reached
        		}
        	}
//RIGHT -> LEFT
        	if(cir_alien[i].alien_initial_x_pos>=cir_alien[i].alien_min_x_pos && cir_alien[i].go==0) //Food Is On The Left :D
        	{
        		if(cir_alien[i].alien_direction==0)cir_alien[i].alien_initial_x_pos=cir_alien[i].alien_initial_x_pos-((60.0/fps)*0.8); //Go Get The Food Buddy!
        		if(cir_alien[i].alien_initial_x_pos<=cir_alien[i].alien_min_x_pos)
        		{
        			cir_alien[i].alien_initial_x_pos=cir_alien[i].alien_min_x_pos;
        			cir_alien[i].go=1; //Throw Food To The Right
        			cir_alien[i].alien_direction=!cir_alien[i].alien_direction; //Hamster Changes Direction
        			cir_alien[i].alien_initial_y_pos=cir_alien[i].alien_initial_y_pos-((60.0/fps)*5.0);  //Aliens Hop Down
        			if(cir_alien[i].alien_initial_y_pos<=50.0)display_screen=6;  //Invasion Barrier Reached
        		}
        	}
        }
    }

    if(ca_movement_type==2)
    {
//LEFT -> RIGHT
    	for(i=0;i<num_cir_aliens;i++)
        {
        	if(cir_alien[i].alien_initial_x_pos<=cir_alien[i].alien_max_x_pos && cir_alien[i].go==1) //Food Is On The Right:D
        	{
        		if(cir_alien[i].alien_direction==1)cir_alien[i].alien_initial_x_pos=cir_alien[i].alien_initial_x_pos+((60.0/fps)*0.8); //Go Get The Food Buddy!
        		if(cir_alien[i].alien_initial_x_pos>=cir_alien[i].alien_max_x_pos)
        		{
        			cir_alien[i].alien_initial_x_pos=cir_alien[i].alien_max_x_pos;
        			cir_alien[i].go=0; //Throw Food To The Left
        			cir_alien[i].alien_direction=!cir_alien[i].alien_direction; //Hamster Changes Direction
        			if(i%2==0)
        			{
        				cir_alien[i].alien_initial_y_pos=cir_alien[i].alien_initial_y_pos-((60.0/fps)*10.0);  //Aliens Hop Down
        				if(cir_alien[i].alien_initial_y_pos<=50.0)display_screen=6;  //Invasion Barrier Reached
        			}
        		}
        	}
//RIGHT -> LEFT
        	if(cir_alien[i].alien_initial_x_pos>=cir_alien[i].alien_min_x_pos && cir_alien[i].go==0) //Food Is On The Left :D
        	{
        		if(cir_alien[i].alien_direction==0)cir_alien[i].alien_initial_x_pos=cir_alien[i].alien_initial_x_pos-((60.0/fps)*0.8); //Go Get The Food Buddy!
        		if(cir_alien[i].alien_initial_x_pos<=cir_alien[i].alien_min_x_pos)
        		{
        			cir_alien[i].alien_initial_x_pos=cir_alien[i].alien_min_x_pos;
        			cir_alien[i].go=1; //Throw Food To The Right
        			cir_alien[i].alien_direction=!cir_alien[i].alien_direction; //Hamster Changes Direction
        			if(i%2!=0)
        			{
        				cir_alien[i].alien_initial_y_pos=cir_alien[i].alien_initial_y_pos-((60.0/fps)*5.0);  //Aliens Hop Down
        				if(cir_alien[i].alien_initial_y_pos<=50.0)display_screen=6;  //Invasion Barrier Reached
        			}
        		}
        	}
        }
    }
}

void create_ca_alive_list(void)
{
	int i,j;

//CREATE LIST OF CIRULAR ALIENS THAT ARE ALIVE
	for(i=0,j=0,ca_alive_count=0;i<num_cir_aliens;i++)
	{
		if(cir_alien[i].alien_hitpoints>0)
		{
			ca_alive[j]=i;
			j++;
			ca_alive_count++;
		}
	}
	if(ca_alive_count==0)display_screen=5;  //WAVE COMPLETED :)
}

void ca_bullet_alloc(void)
{
	ca_timediff=(double)(time2-ca_time1)/CLOCKS_PER_SEC;

	if(ca_timediff>=ca_bullet_alloc_time_delay && ca_alive_count>0)
	{
		ca_time1=clock();

		alien_that_will_shoot=ca_alive[rand()%ca_alive_count];

		if(ca_bullet[alien_that_will_shoot].allocated==0)
		{
			ca_bullet[alien_that_will_shoot].x_pos=cir_alien[alien_that_will_shoot].alien_initial_x_pos;
			ca_bullet[alien_that_will_shoot].y_pos=cir_alien[alien_that_will_shoot].alien_initial_y_pos-r;
			ca_bullet[alien_that_will_shoot].allocated=1;
		}
	}
}

void cir_alien_bullet(void)
{
	int i;
	glColor3ub(255,255,0);

//BULLET DRAW AND MOVEMENT
	for(i=0;i<max_bullets;i++)
	{
		if(ca_bullet[i].allocated==1)
		{
			ca_bullet[i].y_pos=ca_bullet[i].y_pos-((60.0/fps)*5.0);
			if(ca_bullet[i].y_pos>0.0)
			{
				glBegin(GL_LINES);
				glVertex2f(ca_bullet[i].x_pos,ca_bullet[i].y_pos);
				glVertex2f(ca_bullet[i].x_pos,ca_bullet[i].y_pos-10);
				glVertex2f(ca_bullet[i].x_pos-1,ca_bullet[i].y_pos);
				glVertex2f(ca_bullet[i].x_pos-1,ca_bullet[i].y_pos-10);
				glEnd();
			}
			else ca_bullet[i].allocated=0;
		}
	}
}

unsigned char digit_count(unsigned long int num)
{
	unsigned char count=1;
	while(num>9)
	{
		num=num/10;
		count++;
	}
	return count;
}
