#include "../includes/glfunctions.h"
#include "../includes/pesti.h"
#include "../includes/list.h"
#include "../includes/defines.h"
#include "../includes/bubbles.h"
#include "../includes/structs.h" // Timer & scrPt
#include "../includes/culori.h"
#include "../includes/helpers.h"
#include "../includes/nisip.h"
#include "../includes/culori.h"
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int menuBackground;
int menuMain;
int currentColor;

/*********************************************
******* INCEPUT SETARI APLICATIE *************
*********************************************/
// setari ale aplicatiei si main loop
int frameNumber = 0;
const int FPS = 33;
bool running = true;
time_t initial_time;
// afisarea timpului trecut de la inceputul jocului - structura ar putea fi in timer.h si functiile in timer.c
Timer timer = {.seconds = 0, .minutes = 0};
/*********************************************
******* SFARSIT SETARI APLICATIE *************
*********************************************/

// variabile globale definite altundeva in cadrul proiectului
extern List list;                   // list.c
extern Peste* g_pesteJucator;       // pesti.c
extern Bubble bubbles[N_BUBBLES];   // bubbles.c
extern Nisip cercuri_nisip[N_CERCURI_NISIP]; // nisip.c

void init(void)
{
	initial_time = time(NULL);
	glClearColor(0.11, 0.56, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(LEFT_M, RIGHT_M, BOTTOM_M, TOP_M, -1.0, 1.0);
}

void RenderString(float x, float y, void *font, const unsigned char *string)
{
	glRasterPos2f(x, y);
	glutBitmapString(font, string);
}

void changeFrame(int v)
{
	if (running == false)
		return;
	time_t current_time = time(NULL);
	int dt = current_time - initial_time;
	timer.seconds = dt % 60;
	timer.minutes = dt / 60;
	frameNumber++;
	if (frameNumber % 37 == 0)
	{
		Peste *peste = Peste_init(PESTE_NORMAL);
		List_append(&list, peste);
	}
	if (frameNumber % 149 == 0)
	{
		Peste *peste = Peste_init(PESTE_RECHIN);
		List_append(&list, peste);
	}
	List_ForEach(&list, actualizeazaStareJoc);
	glutPostRedisplay();
	glutTimerFunc(30, changeFrame, 0);
}
 
void draw_vieti(void)
{
	char str[64];
	sprintf(str, "Lives: %2d", g_pesteJucator->campuriPeste.pesteJucator.nr_vieti);
	RenderString(0.0f, 425.0f, GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char *)str);
}
 
void draw_score(void)
{
	char str[64];
	sprintf(str, "Score: %2d", g_pesteJucator->campuriPeste.pesteJucator.scor_curent);
	RenderString(200.0f, 425.0f, GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char *)str);
}
 
void draw_timer(void)
{
	char str[64];
	sprintf(str, "Elapsed time: %02d:%02d", timer.minutes, timer.seconds);
	RenderString(400.0f, 425.0f, GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char *)str);
}
 

void drawBackground(int x1, int y1, int x2, int y2)
{
	int nr_curbe = 5;
	int dy = (y2 - y1) / nr_curbe;
 
	fct_t sineFunctions[] = {sine2func, sine1func, sine2func, sine1func, sine2func};
	RGB_t colors[] = {
						(RGB_t){.red = 0, .green = 163, .blue = 255},
						(RGB_t){.red = 0, .green = 122, .blue = 255},
						(RGB_t){.red = 0, .green = 82, .blue = 255},
						(RGB_t){.red = 0, .green = 42, .blue = 255},
						(RGB_t){.red = 233, .green = 189, .blue = 58}
					};
	for (int y = y1, i = 0; y > y2; y += dy, i++)
	{
		if (i == nr_curbe)
		{
			break;
		}
		// nisipul
		if (i == nr_curbe - 1)
		{
			fillBetweenCurves(x1, y, x2, 0, sineFunctions[i], funcBottom_M, colors[i]);
			break;
		}
		fillBetweenCurves(x1, y, x2, y + dy, sineFunctions[i], sineFunctions[i + 1], colors[i]);
	}
}

void drawCloud(void)
{
	const double TWO_PI = 2*M_PI;
	if(currentColor == 0){
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else{
		glColor3ub(99, 102, 106);
	}
	
	glBegin(GL_POLYGON);
	float radius = 50.0f;
	float x, y;
	for (int i = 0; i < 360; i += 10) {
		float theta = i * TWO_PI / 360.0;
		x = radius * cos(theta);
		y = radius * sin(theta);
		glVertex2f(x + 150, y + 380);
	}
	radius = 60.0f; 
	for (int i = 0; i < 360; i += 10) {
		float theta = i * TWO_PI / 360.0;
		x = radius * cos(theta);
		y = radius * sin(theta);
		glVertex2f(x + 220, y + 380);
	}
	radius = 50.0f; 
	for (int i = 0; i < 370; i += 10) {
		float theta = i * TWO_PI / 360.0;
		x = radius * cos(theta);
		y = radius * sin(theta);
		glVertex2f(x + 290, y + 380);
	}
	glEnd();
}
 
void drawShells(void)
{
	RGB_t culoare1 = (RGB_t){.red = 102, .green = 102, .blue = 102};
	RGB_t culoare2 = (RGB_t){.red = 204, .green = 204, .blue = 204};

	float theta_min = -M_PI / 6;
	float theta_max = M_PI / 2 + M_PI / 6;
	float d_theta = theta_max - theta_min;

	int num_lines = 20;
	int i = 0;
	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(68, -125);
	for (float theta = theta_min; theta <= theta_max; theta += d_theta / num_lines, i++)
	{
		float x = 68 + 50 * cos(theta);
		float y = -125 + 50 * sin(theta);
		RGB_t stripeColor = i % 2 == 0 ? culoare1 : culoare2;
		glColor3ub(stripeColor.red, stripeColor.green, stripeColor.blue);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();

	i = 0;
	glPushMatrix();
	glTranslated(400, -100, 0);
	glRotated(60, 0, 0, 1);
	glScaled(0.85, 0.85, 1);
	glTranslated(-400, 100, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(400, -100);
	for (float theta = theta_min; theta <= theta_max; theta += d_theta / num_lines, i++)
	{
		float x = 400 + 50 * cos(theta);
		float y = -100 + 50 * sin(theta);
		RGB_t stripeColor = i % 2 == 0 ? culoare1 : culoare2;
		glColor3ub(stripeColor.red, stripeColor.green, stripeColor.blue);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();

	i = 0;
	glPushMatrix();
	glTranslated(0, -90, 0);
	glRotated(100, 0, 0, 1);
	glScaled(0.75, 0.75, 1);
	glTranslated(0, 90, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, -90);
	for (float theta = theta_min; theta <= theta_max; theta += d_theta / num_lines, i++)
	{
		float x = 50 * cos(theta);
		float y = -90 + 50 * sin(theta);
		RGB_t stripeColor = i % 2 == 0 ? culoare1 : culoare2;
		glColor3ub(stripeColor.red, stripeColor.green, stripeColor.blue);
		glVertex2f(x, y);
	}
	glEnd();
	glPopMatrix();
}

void drawScene(void)
{
	RGB_t color_nisip;
	if(currentColor == 0){
		glClearColor(0.52, 0.8, 0.98, 0);
		glColor3f(0.52, 0.8, 0.98);
	}
	else{
		glClearColor(0.0, 0.0, 0.54, 0);
		glColor3f(0.0, 0.0, 0.54);
	}
	glClear(GL_COLOR_BUFFER_BIT);
 
	// cer
	glBegin(GL_POLYGON);
	glVertex2i(-100, 300); // Stanga jos
	glVertex2i(700, 300);  // Dreapta jos
	glVertex2i(700, 460);  // Dreapta sus
	glVertex2i(-100, 460); // Stanga sus
	glEnd();

	drawCloud();

	if(currentColor == 0){
		glColor3ub(255, 191, 0);
	}
	else{
		glColor3f(0.85, 0.85, 0.85);
	}
	
	// soare / luna
	glBegin(GL_TRIANGLE_FAN);
		double radius = 50;
		double x, y;
		int num_vertices = 50;
		double theta3;
		for (int i = 0; i < num_vertices; i++)
		{
			theta3 = 2*M_PI * i / num_vertices;
			x = radius * cos(theta3);
			y = radius * sin(theta3);
			glVertex2f(500 + x, 400 + y);
		}
	glEnd();
 
	// background
	drawBackground(LEFT_M, TOP_M - 160, RIGHT_M, BOTTOM_M);
 
 	for (int i = 1; i <= N_CERCURI_NISIP; i++)
	{
		glColor3ub(cercuri_nisip[i].culoare.red, cercuri_nisip[i].culoare.green, cercuri_nisip[i].culoare.blue);
		drawCercuriNisip(cercuri_nisip[i].xPos, cercuri_nisip[i].yPos, cercuri_nisip[i].radius);
	}

	// bubbles
	for (int i = 1; i <= N_BUBBLES; i++)
	{
		drawBubble(bubbles[i].xPos, bubbles[i].yPos, bubbles[i].radius);
	}
	
	drawShells();

	if(currentColor == 0){
		glColor3f(0, 0, 0);
	}
	else{
		glColor3f(1, 1, 1);
	}
	// scor
	draw_score();
 
	// timer
	draw_timer();
 
	// vieti
	draw_vieti();
 
	// pesti
	List_ForEach(&list, deseneazaPesteCallback);
	
	// final functie
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}
 
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 700.0, -140.0, 460.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
  
void keyboardSpecialCallback(int key, int x, int y)
{
	switch (key)
	{
        case GLUT_KEY_UP:
            miscasus();
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            miscajos();
            glutPostRedisplay();
            break;
	}
}
 
void keyboardCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		miscasus();
		break;
	case 's':
	case 'S':
		miscajos();
		break;
	}
}

void mouseCallback(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("%d %d\n", x, y);
	}
}

void showExitScreen(void)
{
	static time_t local_current_time;
	static time_t local_final_time;
	static int numcalls = 0;
 
	if (numcalls == 0)
	{
		local_final_time = time(NULL) + 5;
		local_current_time = time(NULL);
		numcalls++;
	}
 
	if (local_current_time == local_final_time)
	{
		sleep(1);
		List_Free(&list);
		free(g_pesteJucator);
		exit(EXIT_SUCCESS);
	}
	
	if(currentColor == 0){
		glClearColor(0.52, 0.8, 0.98, 0);
		glColor3f(0.52, 0.8, 0.98);
	}
	else{
		glClearColor(0.0, 0.0, 0.54, 0);
		glColor3f(0.0, 0.0, 0.54);
	}

	glClear(GL_COLOR_BUFFER_BIT);
 
	// cer
	glBegin(GL_POLYGON);
        glVertex2i(-100, 300); // Stanga jos
        glVertex2i(700, 300);  // Dreapta jos
        glVertex2i(700, 460);  // Dreapta sus
        glVertex2i(-100, 460); // Stanga sus
	glEnd();

	drawCloud();

	if(currentColor == 0){
		glColor3ub(255, 191, 0);
	}
	else{
		glColor3f(0.85, 0.85, 0.85);
	}
	
	// soare / luna
	glBegin(GL_TRIANGLE_FAN);
		double radius = 50;
		double x, y;
		int num_vertices = 50;
		double theta3;
		for (int i = 0; i < num_vertices; i++)
		{
			theta3 = 2*M_PI * i / num_vertices;
			x = radius * cos(theta3);
			y = radius * sin(theta3);
			glVertex2f(500 + x, 400 + y);
		}
	glEnd();
 
	// background
	drawBackground(LEFT_M, TOP_M - 160, RIGHT_M, BOTTOM_M);

	for (int i = 1; i <= N_CERCURI_NISIP; i++)
	{
		glColor3ub(cercuri_nisip[i].culoare.red, cercuri_nisip[i].culoare.green, cercuri_nisip[i].culoare.blue);
		drawCercuriNisip(cercuri_nisip[i].xPos, cercuri_nisip[i].yPos, cercuri_nisip[i].radius);
	}

	drawShells();

	// bubbles
	for (int i = 1; i <= N_BUBBLES; i++)
	{
		drawBubble(bubbles[i].xPos, bubbles[i].yPos, bubbles[i].radius);
	}
 
	// peste final
	deseneazaPesteFinal(g_pesteJucator);
 
	char str[64];
	local_current_time = time(NULL);
	sprintf(str, "Game over, exiting in %ld\n", local_final_time - local_current_time);
	RenderString((RIGHT_M - abs(LEFT_M)) / 2, (TOP_M - abs(BOTTOM_M)) / 2, GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char *)str);
	
	if(currentColor == 0){
		glColor3f(0, 0, 0);
	}
	else{
		glColor3f(1, 1, 1);
	}
	draw_score();
 
	usleep(1000 * 50);
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void handle_exit_program(void)
{
	running = false;
	g_pesteJucator->xPos = 200;
	g_pesteJucator->yPos = abs(TOP_M - abs(BOTTOM_M)) / 2;
	glutDisplayFunc(showExitScreen);
	glutPostRedisplay();
}

void callback_BackgroundColor(int key)
{
	currentColor = key;
}

void callback_Main(int key)
{	
	if (key == 0)
	{
		handle_exit_program();
	}
}