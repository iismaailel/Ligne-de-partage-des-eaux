#include"image.h"

int main (int argc, char ** argv){
	float temps1,temps2;
	clock_t t1, t2, t1b,t2b;
	t1 = clock();
	uint32_t h,l;
	myimage* im= lireimage(argv[1]);//Lire l'image initiale
	myimage* M= lireimage(argv[2]);//Lire l'image marqueurs
	myimage *gr=CalculerGradient(im,1);//Calculer le gradient de limage
	Ecrireimage(gr,"./Resultat/gradient.png");//Ecrire l'image de gradient
	printf("\nL'image de gradient a ete creer dans le dossier (Resultat) sous le nom (gradient.png)\n");
	t1b = clock();
	CalculerLPE(gr, M);//Calculer la ligne de partage des eaux
	t2b = clock();
	temps2 = (float)(t2b-t1b)/CLOCKS_PER_SEC;

	Ecrireimage(M,"./Resultat/clpeGris.png");//Calculer la ligne de partage des eaux
	EcrireimageclpeColeur(M,"./Resultat/clpeCouleur.png");//Ecrire l'image de la ligne de partage des eaux
	printf("Les images de la ligne de partage des eaux ont ete creer dans le dossier (Resultat) \n");
	printf("Sous le nom (clpeGris.png) Pour l'image en niveau de gris\n");
	printf("Sous le nom (clpeCouleur.png) Pour l'image en deux coleur different\n\n");
	
	EcrireimageContourRouge(im,M,"./Resultat/ObjetContourRouge.png");//Ecrire l'image initial avec des contour rouge
	printf("L'image de l'objet avec des contours rouge a ete creer dans le dossier (Resultat) sous le nom (ObjetContourRouge.png)\n\n\n");

	h=im->hauteur;
	l=im->largeur;
	//liberer la memoire
	LibererImage(gr);
	LibererImage(im);
	LibererImage(M);

	t2 = clock();
	temps1 = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("Pour une image de taille (%d p * %d p)\nLe temps d'execution de l'algorithme de calcule de ligne de partage des eaux est = %f\nLe temps d'execution de tout le programme est = %f\n\n",h,l,temps2,temps1);
	
	return EXIT_SUCCESS;
}
