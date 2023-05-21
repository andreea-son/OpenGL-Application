#include "../includes/culori.h"
#include <stdlib.h>
/*********************************************
********* INCEPUT VARIABILE CULORI ***********
*********************************************/
// culoare principala pesti
RGB_t g_color1[] = {
                    (RGB_t){.red = 41, .green = 205, .blue = 186},
					(RGB_t){.red = 159, .green = 201, .blue = 154},
					(RGB_t){.red = 90, .green = 37, .blue = 93},
					(RGB_t){.red = 40, .green = 51, .blue = 71},
					(RGB_t){.red = 161, .green = 65, .blue = 225},
					(RGB_t){.red = 107, .green = 150, .blue = 143},
					(RGB_t){.red = 50, .green = 175, .blue = 60},
					(RGB_t){.red = 254, .green = 67, .blue = 251},
					(RGB_t){.red = 40, .green = 51, .blue = 71},
					(RGB_t){.red = 60, .green = 124, .blue = 148},
					(RGB_t){.red = 158, .green = 9, .blue = 220},
					(RGB_t){.red = 132, .green = 127, .blue = 45},
					(RGB_t){.red = 190, .green = 180, .blue = 188}
                    };
// culoare secundara pesti
RGB_t g_color2[] = {
                    (RGB_t){.red = 171, .green = 242, .blue = 251},
					(RGB_t){.red = 183, .green = 49, .blue = 88},
					(RGB_t){.red = 233, .green = 94, .blue = 212},
					(RGB_t){.red = 178, .green = 205, .blue = 198},
					(RGB_t){.red = 252, .green = 103, .blue = 62},
					(RGB_t){.red = 236, .green = 176, .blue = 59},
					(RGB_t){.red = 84, .green = 236, .blue = 24},
					(RGB_t){.red = 250, .green = 170, .blue = 58},
					(RGB_t){.red = 41, .green = 209, .blue = 230},
					(RGB_t){.red = 117, .green = 216, .blue = 190},
					(RGB_t){.red = 170, .green = 212, .blue = 172},
					(RGB_t){.red = 173, .green = 212, .blue = 118},
					(RGB_t){.red = 68, .green = 120, .blue = 250}
                    };
// numarul de culori diferite posibile ale pestilor norma;i
int g_num_colors = sizeof(g_color1) / sizeof(RGB_t);

// culoare principala peste jucator
RGB_t culoareJucator = (RGB_t){.red = 255, .green = 191, .blue = 0};
// culoare secundara peste jucator
RGB_t culoareJucator2 = (RGB_t){.red = 166, .green = 124, .blue = 0};

// rechinul
RGB_t culoareRechin = (RGB_t){.red = 40, .green = 51, .blue = 71};

RGB_t culoriNisip[] = {
                    (RGB_t){.red = 166, .green = 124, .blue = 0},
					(RGB_t){.red = 191, .green = 155, .blue = 48},
					(RGB_t){.red = 255, .green = 191, .blue = 0},
					(RGB_t){.red = 255, .green = 207, .blue = 64},
                    };
int g_num_colors_nisip = sizeof(culoriNisip) / sizeof(RGB_t);
/*********************************************
********* SFARSIT VARIABILE CULORI ***********
*********************************************/

void RGB_Random_Init(RGB_t *color1, RGB_t *color2)
{
	int index = rand() % g_num_colors;
	*color1 = g_color1[index];
	*color2 = g_color2[index];
}

void RGB_Random_Init_Nisip(RGB_t *color)
{
	int index = rand() % g_num_colors_nisip;
	*color = culoriNisip[index];
}