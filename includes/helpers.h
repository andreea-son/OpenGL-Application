#ifndef _HELPERS_H_
#define _HELPERS_H_
#include "culori.h"
typedef float (*fct_t)(float);
int random_range(int a, int b);
float sine1func(float x);
float sine2func(float x);
float funcBottom_M(float x);
void drawCurve(int xmin, int ymin, int xmax, int ymax, float (*mathFuncCallback)(float x));
void fillBetweenCurves(int x1, int y1, int x2, int y2, float (*math1func)(float x), float (*math2func)(float x), RGB_t color);
 
#endif /* _HELPERS_H_ */