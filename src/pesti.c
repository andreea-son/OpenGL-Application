#include "../includes/defines.h"
#include "../includes/pesti.h"
#include "../includes/culori.h"
#include "../includes/helpers.h"
#include "../includes/list.h"
#include "../includes/structs.h"
#include "../includes/glfunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/freeglut.h>


/*********************************************
******* INCEPUT VARIABLE GLOBALE **************
*********************************************/
// variabile ajutatoare pentru functii de update()
int varf_peste_x = 180;
int g_increment_scor = 1;
int coef_scalare_viteza = 5;
int g_scor_adaugat = 5;
double g_x_velocity = -1.2;
// pestele jucator - head-ul listei - poate fi facut local foarte usor
Peste *g_pesteJucator;
/*********************************************
******* SFARSIT VARIABLE GLOBALE **************
*********************************************/

// variable globale definite altundeva in cadrul proiectului
// culori.c
extern RGB_t culoareJucator;
extern RGB_t culoareJucator2;
extern RGB_t culoareRechin;
// id-ul ultimului peste - are sens mai mult aici decat in list.c?
extern int g_id; 
extern bool running;

static Peste PesteNormal_init(void)
{
	CampuriPesteNormal pesteNormal;
	Peste peste;
	pesteNormal.scor_adaugat = g_scor_adaugat;
	pesteNormal.a_fost_mancat = false;
	pesteNormal.coliziune = false;
 
	peste.tipPeste = PESTE_NORMAL;
	peste.campuriPeste.pesteNormal = pesteNormal;
	peste.dx = g_x_velocity;
	peste.dy = 0;
	peste.yPos = (double)random_range(BOTTOM, TOP);
	peste.xPos = RIGHT_M;
	RGB_Random_Init(&peste.color, &peste.color2);
	peste.id = g_id++;
	return peste;
}
 
static Peste PesteJucator_init(void)
{
	Peste peste;
	CampuriPesteJucator pesteJucator;
	pesteJucator.scor_curent = 0;
	pesteJucator.nr_vieti = 2;
	pesteJucator.nr_pesti_mancati = 0;
	peste.tipPeste = PESTE_JUCATOR;
	peste.campuriPeste.pesteJucator = pesteJucator;
	peste.dx = 0;
	peste.dy = 15;
	peste.xPos = -50;
	peste.yPos = abs(TOP_M - abs(BOTTOM_M)) / 2;
	peste.color = culoareJucator;
	peste.color2 = culoareJucator2;
	peste.id = g_id++;
	return peste;
}
 
static Peste PesteRechin_init(void)
{
	Peste peste;
	CampuriPesteRechin pesteRechin;
	pesteRechin.a_mancat_jucator = false;
	pesteRechin.coliziune = false;
	peste.tipPeste = PESTE_RECHIN;
	peste.campuriPeste.pesteRechin = pesteRechin;
	peste.dy = 0;
	peste.dx = g_x_velocity;
	peste.yPos = (int)random_range(BOTTOM, TOP);
	peste.xPos = RIGHT_M;
	peste.color = culoareRechin;
	peste.color2 = culoareRechin;
	peste.id = g_id++;
	return peste;
}
 
Peste* Peste_init(TipPeste tipPeste)
{
	Peste peste;
	peste.tipPeste = tipPeste;
	peste.isVisible = true;
	switch (peste.tipPeste)
	{
	case PESTE_NORMAL:
	{
		peste = PesteNormal_init();
		break;
	}
	case PESTE_JUCATOR:
	{
		peste = PesteJucator_init();
		break;
	}
	case PESTE_RECHIN:
	{
		peste = PesteRechin_init();
		break;
	}
	case PESTE_NECUNOSCUT:
	{
		printf("Nu ar trebui sa se ajunga aici\n");
		break;
	}
	default:
	{
		printf("Nu se intra niciodata pe ramura asta\n");
		break;
	}
	}
	Peste *p_peste = (Peste *)malloc(sizeof(Peste));
	p_peste[0] = peste;
	p_peste->isVisible = true;
	return p_peste;
}

void actualizeazaStareJoc(Peste *peste)
{
	if (peste == NULL)
	{
		exit(EXIT_FAILURE);
	}
	if (peste->isVisible == false)
		return;
 
	switch (peste->tipPeste)
	{
		case PESTE_JUCATOR:
		{
			Peste *pesteJucator = peste;
	
			break;
		}
		case PESTE_NORMAL:
		{
			Peste *pesteNormal = peste;
			pesteNormal->xPos += pesteNormal->dx * coef_scalare_viteza;
			if (pesteNormal->campuriPeste.pesteNormal.a_fost_mancat == true)
			{
				pesteNormal->isVisible = false;
				handle_nr_parasiri_si_refa_lista();
				g_pesteJucator->campuriPeste.pesteJucator.nr_vieti++;
				if (g_pesteJucator->campuriPeste.pesteJucator.nr_vieti > MAX_VIETI)
				{
					g_pesteJucator->campuriPeste.pesteJucator.nr_vieti = MAX_VIETI;
				}
				break;
			}
			if (pesteNormal->xPos <= LEFT_M - 100)
			{
				pesteNormal->isVisible = false;
				handle_nr_parasiri_si_refa_lista();
				if (pesteNormal->campuriPeste.pesteNormal.a_fost_mancat == true)
					break;
				g_pesteJucator->campuriPeste.pesteJucator.nr_vieti--;
				if (g_pesteJucator->campuriPeste.pesteJucator.nr_vieti <= 0)
				{
					handle_exit_program();
				}
				break;
			}
			else if (pesteNormal->xPos <= varf_peste_x && pesteNormal->campuriPeste.pesteNormal.coliziune == false)
			{
				int epsilon = 20;
				if (g_pesteJucator->yPos - epsilon <= pesteNormal->yPos &&
					g_pesteJucator->yPos + epsilon >= pesteNormal->yPos &&
					pesteNormal->campuriPeste.pesteNormal.a_fost_mancat == false)
				{
					pesteNormal->campuriPeste.pesteNormal.coliziune = true;
					g_pesteJucator->campuriPeste.pesteJucator.nr_pesti_mancati++;
					g_pesteJucator->campuriPeste.pesteJucator.scor_curent += pesteNormal->campuriPeste.pesteNormal.scor_adaugat;
					pesteNormal->campuriPeste.pesteNormal.a_fost_mancat = true;
				}
			}
			break;
		}
		case PESTE_RECHIN:
		{
			Peste *pesteRechin = peste;
			pesteRechin->xPos += pesteRechin->dx * coef_scalare_viteza;
	
			if (pesteRechin->campuriPeste.pesteRechin.a_mancat_jucator == true)
			{
				pesteRechin->isVisible = false;
				handle_nr_parasiri_si_refa_lista();
				g_pesteJucator->campuriPeste.pesteJucator.nr_vieti--;
				if (g_pesteJucator->campuriPeste.pesteJucator.nr_vieti == 0)
				{
					handle_exit_program();
				}
				break;
			}
			if (pesteRechin->xPos <= LEFT_M - 100)
			{
				pesteRechin->isVisible = false;
				handle_nr_parasiri_si_refa_lista();
				if (pesteRechin->campuriPeste.pesteRechin.a_mancat_jucator == false)
					break;
				g_pesteJucator->campuriPeste.pesteJucator.nr_vieti++;
				if (g_pesteJucator->campuriPeste.pesteJucator.nr_vieti > MAX_VIETI)
				{
					g_pesteJucator->campuriPeste.pesteJucator.nr_vieti = MAX_VIETI;
					pesteRechin->isVisible = false;
				}
				break;
			}
			if (pesteRechin->xPos <= varf_peste_x && pesteRechin->campuriPeste.pesteRechin.coliziune == false)
			{
				int epsilon = 20;
				if (g_pesteJucator->yPos - epsilon <= pesteRechin->yPos && g_pesteJucator->yPos + epsilon >= pesteRechin->yPos)
				{
					pesteRechin->campuriPeste.pesteRechin.coliziune = true;
					pesteRechin->campuriPeste.pesteRechin.a_mancat_jucator = true;
				}
			}
			break;
		}
		case PESTE_NECUNOSCUT:
		{
			printf("Nu ar trebui sa se ajunga aici\n");
			break;
		}
		default:
		{
			printf("Nu se intra niciodata pe ramura asta\n");
			break;
		}
	}
}

void deseneazaPesteFinal(Peste *peste)
{
	static int numcalls = 0;
	int initX, initY;
	initX = peste->xPos;
	initY = peste->yPos;
	float Xg = 0, Yg = 0;
	static double angle = 0;
	double dy = 2;
 
	glPushMatrix();
	glTranslated(initX, initY, 0);
	glRotated(angle, 0, 0, 1);
	glScaled(0.8, 0.8, 1);
	glTranslated(0, dy*numcalls, 0);
	glTranslated(-initX, -initY, 0);
	angle -= 2.6;
	numcalls++;
	glColor3f(0.88, 0.88, 0.88);
	glBegin(GL_TRIANGLES);
		glVertex2f(initX + 175, initY + 100);
		glVertex2f(initX + 50, initY + 50);
	 	glVertex2f(initX + 100, initY + 100);
		
		glVertex2f(initX + 50, initY + 150);
		glVertex2f(initX + 175, initY + 100);
	 	glVertex2f(initX + 100, initY + 100);
	glEnd();

	glPushMatrix();
	glTranslated(initX, initY, 0);
	glTranslated(-150, 0, 0);
	glTranslated(-initX, -initY, 0);
	glBegin(GL_TRIANGLES);
		glVertex2f(initX + 200, initY + 100);
		glVertex2f(initX + 170, initY + 100);
	 	glVertex2f(initX + 150, initY + 150);
		
		glVertex2f(initX + 200, initY + 100);
		glVertex2f(initX + 170, initY + 100);
	 	glVertex2f(initX + 150, initY + 50);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(initX, initY, 0);
	glTranslated(-200, 0, 0);
	glTranslated(-initX, -initY, 0);
	glBegin(GL_TRIANGLES);
		glVertex2f(initX + 200, initY + 100);
		glVertex2f(initX + 170, initY + 100);
	 	glVertex2f(initX + 150, initY + 140);
		
		glVertex2f(initX + 200, initY + 100);
		glVertex2f(initX + 170, initY + 100);
	 	glVertex2f(initX + 150, initY + 60);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(initX, initY, 0);
	glTranslated(-250, 0, 0);
	glTranslated(-initX, -initY, 0);
	glBegin(GL_TRIANGLES);
		glVertex2f(initX + 200, initY + 100);
		glVertex2f(initX + 170, initY + 100);
	 	glVertex2f(initX + 150, initY + 130);
		
		glVertex2f(initX + 200, initY + 100);
		glVertex2f(initX + 170, initY + 100);
	 	glVertex2f(initX + 150, initY + 70);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(initX, initY, 0);
	glTranslated(-80, 0, 0);
	glTranslated(-initX, -initY, 0);
	glBegin(GL_TRIANGLES);
		glVertex2f(initX, initY + 100);
		glVertex2f(initX + 200, initY + 110);
	 	glVertex2f(initX + 200, initY + 90);
	glEnd();
	glPopMatrix();
 
	glLineWidth(3);
	glBegin(GL_LINES);
        glColor3f(0.2, 0.2, 0.2);
        glVertex2i(initX + 120, initY + 115);
        glVertex2i(initX + 130, initY + 105);
    
        glVertex2i(initX + 120, initY + 105);
        glVertex2i(initX + 130, initY + 115);
	glEnd();
	glPopMatrix();
}

void deseneazaPesteCallback(Peste *peste)
{
	if (peste->isVisible == false)
		return;
    
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;
	const double TWO_PI = 2*M_PI;
	int initX, initY;
	initX = peste->xPos;
	initY = peste->yPos;
	int R, G, B;
	R = peste->color.red;
	G = peste->color.green;
	B = peste->color.blue;
	float Xg = 0, Yg = 0;
 
	switch(peste->tipPeste){
		case PESTE_RECHIN:
		{
			glColor3ub(R, G, B);
			glBegin(GL_POLYGON);
				for (k = 0; k < 50; k++)
				{
					hexTheta = TWO_PI * k / 50;
					hexVertex.x = initX + 100 * cos(hexTheta);
					hexVertex.y = initY + 40 * sin(hexTheta);
					glVertex2i(hexVertex.x, hexVertex.y);
					Xg = Xg + hexVertex.x;
					Yg = Yg + hexVertex.y;
				}
				Xg = Xg / 10;
				Yg = Yg / 10;
			glEnd();

			// semicerc gura
			int num_lines = 10;
			float theta_min2 = M_PI;
			float theta_max2 = 51*M_PI / 36;
			float d_theta2 = theta_max2 - theta_min2;
			glColor3ub(178, 34, 34);
			glPushMatrix();
			glTranslatef(initX, initY, 0);
			glTranslatef(-19, -5, 0);
			glTranslatef(-initX, -initY, 0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex2f(initX, initY);
			for (float theta = theta_min2; theta <= theta_max2; theta += d_theta2 / num_lines)
			{
				float x = initX + 80 * cos(theta);
				float y = initY + 32 * sin(theta);
				glVertex2f(x, y);
			}
			glEnd();
			glPopMatrix();

			// dinti sus
			glPushMatrix();
			glTranslatef(initX, initY, 0);
			glTranslatef(28, 6, 0);
			glTranslatef(-initX, -initY, 0);
			glColor3f(1, 1, 1);
			glBegin(GL_TRIANGLES);
				glVertex2f(initX - 64, initY - 11);
				glVertex2f(initX - 60, initY - 22);
				glVertex2f(initX - 48, initY - 11);

				glVertex2f(initX - 80, initY - 11);
				glVertex2f(initX - 76, initY - 22);
				glVertex2f(initX - 64, initY - 11);

				glVertex2f(initX - 96, initY - 11);
				glVertex2f(initX - 92, initY - 21);
				glVertex2f(initX - 80, initY - 11);

				glVertex2f(initX - 112, initY - 11);
				glVertex2f(initX - 108, initY - 21);
				glVertex2f(initX - 96, initY - 11);

				glVertex2f(initX - 128, initY - 11);
				glVertex2f(initX - 124, initY - 21);
				glVertex2f(initX - 112, initY - 11);
			glEnd();	
			glPopMatrix();
		
			// triunghi aripioara
			glColor3ub(R, G, B);
			glBegin(GL_TRIANGLES);
				glVertex2f(initX, initY - 30);
				glVertex2f(initX + 50, initY - 30);
				glVertex2f(initX + 75, initY - 80);
			glEnd();

			// triunghi superior
			glPushMatrix();
			glTranslatef(initX, initY, 0);
		    glScalef(0.85, 0.85, 1);
			glTranslatef(-initX, -initY, 0);
			glBegin(GL_TRIANGLES);
				glVertex2f(initX - 50, initY + 25);
				glVertex2f(initX + 45, initY + 25);
				glVertex2f(initX + 20, initY + 115);
			glEnd();
			glPopMatrix();

			// triunghi coada mare
			glPushMatrix();
			glTranslatef(initX, initY, 0);
		    glScalef(0.85, 0.85, 1);
			glTranslatef(-initX, -initY, 0);
			glBegin(GL_TRIANGLES);
				glVertex2f(initX + 170, initY + 130);
				glVertex2f(initX + 70, initY + 30);
				glVertex2f(initX + 120, initY - 20);
			glEnd();
			glPopMatrix();

			// triunghi coada mic
			glPushMatrix();
			glTranslatef(initX, initY, 0);
			glRotatef(180, 1, 0, 0);
			glScalef(0.5, 0.5, 1);
			glTranslatef(-initX, -initY, 0);
			glBegin(GL_TRIANGLES);
				glVertex2f(initX + 260, initY + 130);
				glVertex2f(initX + 160, initY + 30);
				glVertex2f(initX + 210, initY - 20);
			glEnd();
			glPopMatrix();

			// ochi
			glPushMatrix();
			glTranslatef(initX, initY, 0);
			glTranslatef(0, 5, 0);
			glTranslatef(-initX, -initY, 0);
			glBegin(GL_TRIANGLE_FAN);
				glColor3f(1.0, 1.0, 1.0);
				double radius = 10;
				double x, y;
				int num_vertices = 50;
				double theta3;
				for (int i = 0; i < num_vertices; i++)
				{
					theta3 = TWO_PI * i / num_vertices;
					x = radius * cos(theta3);
					y = radius * sin(theta3);
					glVertex2f(initX - 50 + x, initY + 5 + y);
				}
			glEnd();
 
			glBegin(GL_TRIANGLE_FAN);
				glColor3f(0.0, 0.0, 0.0);
				radius = 5;
				x = 0;
				y = 0;
				for (int i = 0; i < num_vertices; i++)
				{
					theta3 = TWO_PI * i / num_vertices;
					x = radius * cos(theta3);
					y = radius * sin(theta3);
					glVertex2f(initX - 50 + x, initY + 5 + y);
				}
			glEnd();
			glPopMatrix();
			break;
		}
		case PESTE_JUCATOR:
		case PESTE_NORMAL:
		{
			if (peste->tipPeste == PESTE_JUCATOR)
			{
				glPushMatrix();
				glRotated(180, 0, 1, 0);
			}
 
			if (peste->tipPeste == PESTE_NORMAL)
			{
				glPushMatrix();
				glTranslated(initX, initY, 0);
				glScalef(0.7, 0.7, 0);
				glTranslated(-initX, -initY, 0);
			}
 
			glColor3ub(R, G, B);
			glBegin(GL_POLYGON);
			for (k = 0; k < 50; k++)
			{
				hexTheta = TWO_PI * k / 50;
				hexVertex.x = initX + 70 * cos(hexTheta);
				hexVertex.y = initY + 30 * sin(hexTheta);
 
				RGB_t stripeColor = k % 2 == 0 ? peste->color : peste->color2;
				glColor3ub(stripeColor.red, stripeColor.green, stripeColor.blue);
 
				glVertex2i(hexVertex.x, hexVertex.y);
				Xg = Xg + hexVertex.x;
				Yg = Yg + hexVertex.y;
			}
			Xg = Xg / 10;
			Yg = Yg / 10;
			glEnd();

			// aripioare si coada

			float theta_min = -M_PI / 6;
			float theta_max = M_PI / 2 + M_PI / 6;
			float d_theta = theta_max - theta_min;
 
			int num_lines = 20;
			int i = 0;
			glPushMatrix();
			glTranslated(68, 0, 0);
			glTranslated(initX, initY, 0);
			glRotated(-45, 0, 0, 1);
			glTranslated(-initX, -initY, 0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex2f(initX, initY);
			for (float theta = theta_min; theta <= theta_max; theta += d_theta / num_lines, i++)
			{
				float x = initX + 50 * cos(theta);
				float y = initY + 50 * sin(theta);
				RGB_t stripeColor = i % 2 == 0 ? peste->color : peste->color2;
				glColor3ub(stripeColor.red, stripeColor.green, stripeColor.blue);
				glVertex2f(x, y);
			}
			glEnd();
			glPopMatrix();
	
			i = 0;
			num_lines = 10;
			float theta_min2 = -M_PI / 8;
			float theta_max2 = M_PI / 8;
			float d_theta2 = theta_max2 - theta_min2;
			glBegin(GL_TRIANGLE_FAN);
			glVertex2f(initX, initY);
			for (float theta = theta_min2; theta <= theta_max2; theta += d_theta2 / num_lines, i++)
			{
				float x = initX + 50 * cos(theta);
				float y = initY + 50 * sin(theta);
				RGB_t stripeColor = i % 2 == 0 ? peste->color : peste->color2;
				glColor3ub(stripeColor.red, stripeColor.green, stripeColor.blue);
				glVertex2f(x, y);
			}
			glEnd();
 
			// ochi
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(1.0, 1.0, 1.0);
			double radius = 8;
			double x, y;
			int num_vertices = 50;
			double theta3;
			for (int i = 0; i < num_vertices; i++)
			{
				theta3 = TWO_PI * i / num_vertices;
				x = radius * cos(theta3);
				y = radius * sin(theta3);
				glVertex2f(initX - 50 + x, initY + 5 + y);
			}
			glEnd();
 
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(0.0, 0.0, 0.0);
			radius = 4.0f;
			x = 0.0f;
			y = 0.0f;
			for (int i = 0; i < 50; i++)
			{
				hexTheta = TWO_PI * i / 50;
				x = radius * cosf(hexTheta);
				y = radius * sinf(hexTheta);
 
				glVertex2f(initX - 50 + x, initY + 5 + y);
			}
			glEnd();
 
			glPopMatrix();
			break;
		}
	}
}

// functii care misca pestele jucator sus/jos
void miscajos(void)
{
	if (running == false) {
		return;
	}
	if (g_pesteJucator->yPos > BOTTOM) {
		g_pesteJucator->yPos -= g_pesteJucator->dy;
	}
}
void miscasus(void)
{
	if (running == false) {
		return;
	}
	if (g_pesteJucator->yPos < TOP) {
		g_pesteJucator->yPos += g_pesteJucator->dy;
	}
}