#ifndef _CULORI_H_
#define _CULORI_H_

typedef struct RGB_t
{
	int red;
	int green;
	int blue;
} RGB_t;

// functii
void RGB_Random_Init(RGB_t *color1, RGB_t *color2);
void RGB_Random_Init_Nisip(RGB_t *color);

#endif /* _CULORI_H_ */