#ifndef _NISIP_H_
#define _NISIP_H_

#include "../includes/nisip.h"
#include "../includes/culori.h"

typedef struct Nisip
{
	int xPos;
	int yPos;
	int radius;
    RGB_t culoare;
} Nisip;

void drawCercuriNisip(int centerX, int centerY, int radius);
void generateCercuriNisip(Nisip *ceruri_nisip);

#endif /* _NISIP_H_ */