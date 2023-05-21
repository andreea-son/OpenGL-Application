#include "../includes/nisip.h"
#include "../includes/defines.h"
#include "../includes/helpers.h"
#include "../includes/culori.h"
#include <math.h>
#include <GL/freeglut.h>

// vectorul de bule de aer din ocean
Nisip cercuri_nisip[N_CERCURI_NISIP];

void drawCercuriNisip(int centerX, int centerY, int radius)
{
	int n = 100;
	float increment = (2 * M_PI) / n;
	glBegin(GL_POLYGON);
        for (float theta = 0; theta < 2 * M_PI; theta += increment)
        {
            float x1 = centerX + radius * cos(theta);
            float y1 = centerY + radius * sin(theta);
    
            float x2 = centerX + radius * cos(theta + increment);
            float y2 = centerY + radius * sin(theta + increment);
    
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        }
	glEnd();
}
 
void generateCercuriNisip(Nisip *cercuri_nisip)
{
	for (int i = 1; i <= N_CERCURI_NISIP; i++)
	{
		int x = random_range(LEFT_M, RIGHT_M);
		int y = random_range(BOTTOM - 100, BOTTOM + 10);
		int radius = random_range(2, 5);
        RGB_t color;
        RGB_Random_Init_Nisip(&color);
		cercuri_nisip[i].xPos = x;
		cercuri_nisip[i].yPos = y;
		cercuri_nisip[i].radius = radius;
        cercuri_nisip[i].culoare = color;
	}
}