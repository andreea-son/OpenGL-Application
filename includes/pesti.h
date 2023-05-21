#ifndef _PESTI_H_
#define _PESTI_H_
#include <stdbool.h>
#include "culori.h"
/* INCEPUT DECLARATII STRUCTURI */
typedef enum TipPeste
{
	PESTE_JUCATOR,
	PESTE_NORMAL,
	PESTE_RECHIN,
	PESTE_NR_PESTI,
	PESTE_NECUNOSCUT
} TipPeste;
 
typedef struct CampuriPesteJucator
{
	int scor_curent;
	int nr_vieti;
	int nr_pesti_mancati;
} CampuriPesteJucator;
 
typedef struct CampuriPesteNormal
{
	bool a_fost_mancat;
	int scor_adaugat;
	bool coliziune;
} CampuriPesteNormal;
 
typedef struct CampuriPesteRechin
{
	bool a_mancat_jucator;
	bool coliziune;
} CampuriPesteRechin;
 
typedef union CampuriPeste
{
	CampuriPesteJucator pesteJucator;
	CampuriPesteNormal pesteNormal;
	CampuriPesteRechin pesteRechin;
} CampuriPeste;
 
typedef struct Peste
{
	TipPeste tipPeste;
	CampuriPeste campuriPeste;
	double xPos;
	double yPos;
	double dx;
	double dy;
	int id;
	RGB_t color;
	RGB_t color2;
	bool isVisible;
} Peste;


/* INCEPUT CONSTRUCTORI */
// Peste PesteNormal_init(void);
// Peste PesteJucator_init(void);
// Peste PesteRechin_init(void);
Peste* Peste_init(TipPeste tipPeste);
/* SFARSIT CONSTRUCTORI */

void miscajos(void);
void miscasus(void);

void deseneazaPesteFinal(Peste *peste);
void deseneazaPesteCallback(Peste *peste);
void actualizeazaStareJoc(Peste *peste);
#endif /* _PESTI_H */