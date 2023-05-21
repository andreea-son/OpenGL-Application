#include "../includes/bubbles.h"
#include "../includes/defines.h"
#include "../includes/helpers.h"
#include <math.h>
#include <GL/freeglut.h>

// vectorul de bule de aer din ocean
Bubble bubbles[N_BUBBLES];

void drawBubble(int centerX, int centerY, int radius)
{
	int n = 100;
	float increment = (2 * M_PI) / n;
	glColor4d(1, 1, 1, 0.2);
	glBegin(GL_LINES);
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

	glBegin(GL_LINES);
        float start = M_PI / 6;
        float end = M_PI / 2;
        increment = (end - start) / n;
        for (float theta = start; theta < end; theta += increment)
        {
            float x1 = centerX + (radius / 2) * cos(theta);
            float y1 = centerY + (radius / 2) * sin(theta);
    
            float x2 = centerX + (radius / 2) * cos(theta + increment);
            float y2 = centerY + (radius / 2) * sin(theta + increment);
    
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
	}
	glEnd();
}
 
void generateBubbles(Bubble *bubbles)
{
	for (int i = 1; i < N_BUBBLES; i++)
	{
		int x = random_range(LEFT_M, RIGHT_M);
		int y = random_range(BOTTOM + 50, TOP + 50);
		int radius = random_range(5, 20);
		bubbles[i].xPos = x;
		bubbles[i].yPos = y;
		bubbles[i].radius = radius;
	}
}