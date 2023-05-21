#ifndef _GLFUNCTIONS_H_
#define _GLFUNCTIONS_H_

#include "../includes/glfunctions.h"
#include "../includes/pesti.h"
#include "../includes/list.h"
#include "../includes/defines.h"
#include "../includes/structs.h"
#include "../includes/culori.h"
#include <time.h>
#include <stdbool.h>
#include <GL/freeglut.h>
#include "structs.h"
#include "bubbles.h"

void init(void);
void changeFrame(int v);
void drawScene(void);
void keyboardSpecialCallback(int key, int x, int y);
void keyboardCallback(unsigned char key, int x, int y);
void mouseCallback(int button, int state, int x, int y);
void reshape(int w, int h);
void handle_exit_program(void);
void callback_BackgroundColor(int key);
void callback_Main(int key);

#endif /* _GL_FUNCTIONS_H_ */