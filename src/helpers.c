#include "../includes/helpers.h"
#include "../includes/defines.h"
#include "../includes/pesti.h"
#include "../includes/culori.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/freeglut.h>

int random_range(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

// callbacks pentru drawCurve() & flllBetweenCurves
float sine1func(float x)
{
	return sin(x / 10);
}
float sine2func(float x)
{
	return (sin(x / 10) + 8 * cos(x / 5) - 3 * sin(x / 8)) / 13;
}
float funcBottom_M(float x)
{
	return BOTTOM_M;
}

void drawCurve(int xmin, int ymin, int xmax, int ymax, float (*mathFuncCallback)(float x))
{
	glColor3f(1, 1, 1);
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
        int multiplier = 80;
        int dx = 10;
        double dt = (xmax - xmin) / (multiplier * dx);
        int count = 0;
        for (double i = 0; i <= multiplier * M_PI; i += M_PI / dx)
        {
            double x1 = xmin + count * dt;
            double y1 = ymin + 10 * mathFuncCallback(i);
            if (x1 >= xmax)
                break;
            glVertex2d(x1, y1);
            count++;
        }
	glEnd();
}
 

void fillBetweenCurves(int x1, int y1, int x2, int y2, float (*math1func)(float x), float (*math2func)(float x), RGB_t color)
{
	glLineWidth(1);
	glColor3ub(color.red, color.green, color.blue);
	glBegin(GL_LINES);
        int count = 0;
        int multiplier = 80;
        int dx = 10;
        double dt = (x2 - x1) / dx;
        int x = LEFT_M;
        for (double i = 0; i <= multiplier * M_PI; i += M_PI / dx)
        {
            double p1_y = y1 + 10 * math1func(i);
            glVertex2d(x, p1_y);
            double p2_y = y2 + 10 * math2func(i);
            glVertex2d(x, p2_y);
            x++;
        }
	glEnd();
}
 