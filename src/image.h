#ifndef _IMAGE_H
#define _IMAGE_H

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdint.h>
#include<stdbool.h>
#include<time.h>
#include"lodepng.h"

typedef struct myimage{
	uint32_t hauteur;
	uint32_t largeur;
	uint8_t** tab;
}myimage;

typedef struct maillon{
	uint32_t i;
	uint32_t j;
	struct maillon* suivant;
}maillon;

typedef struct clpe{
	uint32_t taille;
	maillon* debut;
}clpe;

typedef struct tab_clpe{
	clpe* tab[256];
}tab_clpe;


myimage *Allouerimage(uint32_t hauteur,uint32_t largeur);
myimage* lireimage(char* nom_fichier);
void Ecrireimage(myimage* im,char* nom_fichier);
void LibererImage(myimage* im);
myimage *CalculerGradient(myimage *im, uint32_t r);
tab_clpe* newtabclpe();
maillon* newmaillon(uint32_t i,uint32_t j);
void ajouter_pixel(tab_clpe* L,uint32_t i,uint32_t j,uint8_t gradient);
_Bool estvide(tab_clpe* L);
maillon* retirer_pexel(tab_clpe* L);
void CalculerLPE(myimage* Gradient, myimage* M);
void EcrireimageclpeColeur(myimage* im,char* nom_fichier);
void EcrireimageContourRouge(myimage* im,myimage* M,char* nom_fichier);


#endif
