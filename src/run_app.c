#include "../includes/glfunctions.h"
#include "../includes/list.h"
#include "../includes/pesti.h"
#include "../includes/structs.h"
#include "../includes/nisip.h"
#include <GL/freeglut.h>

// variabile globale definite altundeva in cadrul proiectului
extern List list;               	// list.c
extern Peste* g_pesteJucator;   	// pesti.c
extern Bubble bubbles[N_BUBBLES];   // bubbles.c
extern Nisip cercuri_nisip[N_CERCURI_NISIP]; // nisip.c

extern int menuBackground; // glfunctions
extern int menuMain; // glfunctions

void run_app(int *p_argc, char **argv)
{
    list = List_Init();
	g_pesteJucator = Peste_init(PESTE_JUCATOR);
	List_append(&list, g_pesteJucator);
	generateBubbles(bubbles);
	generateCercuriNisip(cercuri_nisip);
	glutInit(p_argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Feed the gold fish! - MINI GAME");
	init();
	glutDisplayFunc(drawScene);
	glutReshapeFunc(reshape);
	glutTimerFunc(200, changeFrame, 0);
	glutMouseFunc(mouseCallback);
	glutSpecialFunc(keyboardSpecialCallback);
	glutKeyboardFunc(keyboardCallback);

	menuBackground = glutCreateMenu(callback_BackgroundColor);
	glutAddMenuEntry("Zi", 0);
	glutAddMenuEntry("Noapte", 1);

	menuMain = glutCreateMenu(callback_Main);

	glutAddSubMenu("Zi/Noapte", menuBackground);
	glutAddMenuEntry("Iesire ", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
}