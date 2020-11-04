#include"image.h"


/*Cette fonction prend en argument la largeur , et l'hauteur de l'image qu'on veut créer 
et renvoie une structure de données représentant une image vide de hauteur hauteur et largeur largeur*/
myimage *Allouerimage(uint32_t hauteur,uint32_t largeur){
	myimage *im=malloc(sizeof(myimage)); //Alloue une structure myimage
	if(im==NULL){
		fprintf(stderr,"Error : location memoire\n"); // On vérifie si l'allocation a réussi sinon on affiche une Erreur
		assert(0);
	}
	im->largeur=largeur; // quand l'allocation réussit , on donne à largeur de l'image largeur et l'hauteur de l'image hauteur
	im->hauteur=hauteur;
	im->tab=(uint8_t**) malloc(hauteur*sizeof(uint8_t*)); // On alloue un tableau de hauteur cases de type uint8_t*

	if(im->tab == NULL){
		printf("Erreur d’allocation memoire \n"); // On vérifie si l'allocation a réussi sinon on affiche une Erreur
		assert(0);
	}

	for(uint32_t i=0;i<hauteur;i++){
		im->tab[i]=(uint8_t*) calloc(largeur,sizeof(uint8_t)); // Pour chaque case du tableau alloué on alloue un tableau de largeur cases
		if(im->tab[i]==NULL){
			printf("Erreur d’allocation memoire \n"); // n vérifie si l'allocation a réussi sinon on affiche une Erreur
			assert(0);
		}
	}
	return im;
}


/*Cette fonction prend en argument le nom de fichier de l'image PNG qu'on veut lire
et la stocke dans la structure myimage */
myimage *lireimage(char* nom_fichier){
	uint32_t error,largeur,hauteur,i,j;
	unsigned char* image;

	/*La fonction lodepng_decode32_file permet de Charger un fichier PNG à partir du disque, à partir d'un fichier (nom_fichier) et de
	convertir les datas du fichier PNG à des datas pixel */
	error=lodepng_decode32_file(&image,&largeur,&hauteur,nom_fichier);
	if(error){
		fprintf(stderr,"Error : could not read %s\n",nom_fichier);
		assert(0);
	}

 	myimage *result=Allouerimage(hauteur,largeur);

	for(i=0;i<hauteur;i++){
		for(j=0;j<largeur;j++)
			result->tab[i][j]=image[(i*largeur+j)*4];
	}

	free(image);
	return result;
}


/*Cette fonction prend en argument la structure im renvoyée par la fonction
lireimage et un nom de fichier PNG et elle ecrit une image apartir de la structure im */
void Ecrireimage(myimage* im,char* nom_fichier){
	uint32_t error,i,j;
	unsigned char* image_array;

	//On alloue un tableau de 4*hauteur*largeur cases dont chaque 4 cases indiquent respectivement la couleur rouge ,vert ,bleu et  la transparence
	image_array=malloc(4*im->hauteur*im->largeur*sizeof(unsigned char));
	if(!image_array){
		fprintf(stderr,"Memory allocation error .\n"); // On vérifie si l'allocation a réussi sinon on affiche une Erreur
		assert(0);
	}

	for(i=0;i<im->hauteur;i++){
		for(j=0;j<im->largeur;j++){
			image_array[(i*im->largeur+j)*4]=im->tab[i][j];
			image_array[((i*im->largeur+j)*4)+1]=im->tab[i][j];
			image_array[((i*im->largeur+j)*4)+2]=im->tab[i][j];
			image_array[((i*im->largeur+j)*4)+3]=255;
		}
	}
	//cette fonction sert à convertir les datas pixels sur image_array à un fichier PNG de nom (nom_fichier)
	error = lodepng_encode32_file(nom_fichier, image_array, im->largeur, im->hauteur);
	if(error){
		fprintf(stderr,"Error lors de la creation de l'image %s\n",nom_fichier); //si l'appel à la fonction ne marche pas on affiche une erreur
		assert(0);
	}
	free(image_array);//Liberer le tableau
}


/*Cette fonction sert à liberer de la memoire de la structure de données im qui représentant l'image */
void LibererImage(myimage* im){
	for(uint32_t i=0; i<im->hauteur; i++)//Liberer tout les tableaux dans tab
		free(im->tab[i]);
	free(im->tab);//Liberer tab
	free(im);//Liberer la structure
}


/*Cette fonction prend en argument la structure de données im qui represente l'image
et un entier r qui represente le rayon , puis elle calcule le gradient de l'image
et le renvoie dans une structure myimage allouée par la fonction Allouerimage*/
myimage *CalculerGradient(myimage *im, uint32_t r){
	myimage *gradient=Allouerimage(im->hauteur,im->largeur); //On alloue une image vide qui a la meme largeur et hauteur que l'image im
	uint32_t i,j;
	int64_t k,l;
	uint8_t max,min;
	for(i=0;i<(im->hauteur);i++){
		for(j=0;j<(im->largeur);j++){
			//Pour chaque couple (i,j) on initialisr max à 0 et min à 255
			max=0;
			min=255;
			for(k=i-r;k<i+r;k++){
				for(l=j-r;l<j+r;l++){
					//Pour k de i-r à i+r et l de j-r à j+r On verifie que le picel(k,l) ne sort pas de l'image im , si oui on l'ignore
					if(k>=0 && k<im->hauteur && l>=0 && l<im->largeur){
						// On cherche le maximum et le minimum de im->tab pour pour k de i-r à i+r et l de j-r à j+r
						if(im->tab[k][l]>max)
					    		max=im->tab[k][l];
						if(im->tab[k][l]<min)
							min=im->tab[k][l];
					}
				}
			}
			gradient->tab[i][j]=max-min;
		}
	}
	return gradient;
}


/*Cette fonction cree nouvelle structure vide (Table de hachage)*/
tab_clpe* newtabclpe(){
	tab_clpe* res =malloc(sizeof(tab_clpe));
	for(uint16_t i =0 ; i<256;i++){//on doit prendre 16 bits car a chaque fin de boucle le i s'incremente donc on s'arrete avec i = 256
		res->tab[i]=malloc(sizeof(clpe));
		res->tab[i]->taille=0;
		res->tab[i]->debut=NULL;
	}
	return res;
}


/*Cette fonction cree nouvelle maillon initialser a i et j*/
maillon* newmaillon(uint32_t i,uint32_t j){
	maillon* m = (maillon*) malloc(sizeof(maillon));
	m->i=i;
	m->j=j;
	m->suivant=NULL;
	return m;
}


/*Cette fonction prend i et j les coordonne d'un pixel, 
creer un maillon avec la fonction newmaillon 
et l'insere dans le bonne postion selon ca valeur de gradient dans la structure L (ici un table d'hachage)*/
void ajouter_pixel(tab_clpe* L,uint32_t i,uint32_t j,uint8_t gradient){
	maillon* m = newmaillon(i,j);
	m->suivant=L->tab[gradient]->debut;
	L->tab[gradient]->debut=m;
	L->tab[gradient]->taille+=1;
}


/*Cette fonction verfier si la structure L est vide
renvoie 1 si elle est vide sinon 0*/
_Bool estvide(tab_clpe* L){
	uint16_t i=0;//on doit prendre 16 bits car il peut y avoir le i qui arrive jusqu'a 256 pour que la boucle while s'arrete quand la structure est vide
	bool res = true;
	while(i<256 && res){
		if(L->tab[i]->taille != 0)
			res=false;
		i++;
	}
	return res;
}


/*Cette fonction retire la premiere maillon de la structure L (contient le gradient le plus faible)
Sachant que on sait deja que L n'est pas vide parce que on a fait le test dans la fonction CalculerLPE*/
maillon* retirer_pexel(tab_clpe* L){
	maillon* m;
	bool recp = false;
	uint8_t i=0;
	while(!recp){//On rentre dans la boucle wahile tant qu'on a pas recuperer un maillon
		if(L->tab[i]->taille > 0){//on verefier a chaque fois si la liste de L->tab[i] contient des maillons
			//On initialise la variable recp a true poyur qu'on arret la boucle 
			//et on recupere premier maillon de la liste L->tab[i]
			//Il sera forcement le maillon au plus petit gradient dans notre structure
			recp=true;
			m=L->tab[i]->debut;
			L->tab[i]->debut=m->suivant;
			L->tab[i]->taille-=1;
		}
		i++;
	}
	return m;
}


/*l'Algorithme qui calcule  la ligne de partage des eaux*/
void CalculerLPE(myimage* Gradient, myimage* M){
	uint32_t i,j;
	int64_t l,k;

	tab_clpe* L = newtabclpe();

	for(i=0;i<M->hauteur;i++){
		for(j=0;j<M->largeur;j++){
			if(M->tab[i][j]!=0)
				ajouter_pixel(L,i,j,Gradient->tab[i][j]);
		}
	}

	while(!estvide(L)){
		maillon* m = retirer_pexel(L);
		i=m->i;
		j=m->j;
		free(m);
		for(k=i-1;k<=i+1;k++){
			for(l=j-1;l<=j+1;l++){
				if(k>=0 && k<M->hauteur && l>=0 && l<M->largeur){
					if(M->tab[k][l]==0){
						M->tab[k][l]=M->tab[i][j];
						ajouter_pixel(L,k,l,Gradient->tab[k][l]);
					}
				}
			}
		}
	}
}


/*Cette fonction prend en argument la structure im apres avoir appliquer l'algorithme de calcule de ligne de partage des eaux 
et un nom de fichier PNG et elle ecrit une image a partir de la structure im avec deux couleur different aleatoire*/

void EcrireimageclpeColeur(myimage* im,char* nom_fichier){
	uint32_t error,i,j;
	unsigned char* image_array;

	//On alloue un tableau de 4*hauteur*largeur cases dont chaque 4 cases indiquent respectivement la couleur rouge ,vert ,bleu et  la transparence
	image_array=malloc(4*im->hauteur*im->largeur*sizeof(unsigned char));
	if(!image_array){
		fprintf(stderr,"Memory allocation error .\n"); // On vérifie si l'allocation a réussi sinon on affiche une Erreur
		assert(0);
	}
	uint8_t r100,g100,b100,r200,g200,b200;
	srand (time (NULL));
	r100=rand()%256;
	g100=rand()%256;
	b100=rand()%256;
	r200=rand()%256;
	g200=rand()%256;
	b200=rand()%256;
	for(i=0;i<im->hauteur;i++){
		for(j=0;j<im->largeur;j++){
			if(im->tab[i][j]==100){
				image_array[(i*im->largeur+j)*4]=r100;
				image_array[((i*im->largeur+j)*4)+1]=g100;
				image_array[((i*im->largeur+j)*4)+2]=b100;
				image_array[((i*im->largeur+j)*4)+3]=255;
			}else{
				image_array[(i*im->largeur+j)*4]=r200;
				image_array[((i*im->largeur+j)*4)+1]=g200;
				image_array[((i*im->largeur+j)*4)+2]=b200;
				image_array[((i*im->largeur+j)*4)+3]=255;
			}
		}
	}
	//cette fonction sert à convertir les datas pixels sur image_array à un fichier PNG de nom (nom_fichier)
	error = lodepng_encode32_file(nom_fichier, image_array, im->largeur, im->hauteur);
	if(error){
		fprintf(stderr,"Error lors de la creation de l'image %s\n",nom_fichier); //si l'appel à la fonction ne marche pas on affiche une erreur
		assert(0);
	}
	free(image_array);//Liberer le tableau
}


/*Cette fonction prend en argument la structure im qui contient l'image initiale
la structure M qui contient le resultat apres avoir appliquer l'algorithme de calcule de ligne de partage des eaux sur l'image
et un nom de fichier PNG et elle recrit l'image initiale a partir de la structure im en en faisant ressortir le contour des objets en rouge*/
void EcrireimageContourRouge(myimage* im, myimage* M,char* nom_fichier){
	int32_t error,i,j;
	unsigned char* image_array;

	//On alloue un tableau de 4*hauteur*largeur cases dont chaque 4 cases indiquent respectivement la couleur rouge ,vert ,bleu et  la transparence
	image_array=malloc(4*im->hauteur*im->largeur*sizeof(unsigned char));
	if(!image_array){
		fprintf(stderr,"Memory allocation error .\n"); // On vérifie si l'allocation a réussi sinon on affiche une Erreur
		assert(0);
	}
	for(i=0;i<im->hauteur;i++){
		for(j=0;j<im->largeur;j++){
			image_array[(i*im->largeur+j)*4]=im->tab[i][j];
			image_array[((i*im->largeur+j)*4)+1]=im->tab[i][j];
			image_array[((i*im->largeur+j)*4)+2]=im->tab[i][j];
			image_array[((i*im->largeur+j)*4)+3]=255;
			if((i-1>=0)&&(i+1<M->hauteur)&&(j-1>=0)&&(j+1<M->largeur)){
				//Verfier si il y'a une deffirence de valeur entre le pixel et un de ses voisins pour voir les contour de l'objet et les mettre en rouge
				if((M->tab[i][j]!=M->tab[i-1][j]) || (M->tab[i][j]!=M->tab[i+1][j]) || (M->tab[i][j]!=M->tab[i][j-1]) || (M->tab[i][j]!=M->tab[i][j+1])){
					image_array[(i*im->largeur+j)*4]=255;
					image_array[((i*im->largeur+j)*4)+1]=0;
					image_array[((i*im->largeur+j)*4)+2]=0;
					image_array[((i*im->largeur+j)*4)+3]=255;
				}
			}
		}
	}
	//cette fonction sert à convertir les datas pixels sur image_array à un fichier PNG de nom (nom_fichier)
	error = lodepng_encode32_file(nom_fichier, image_array, im->largeur, im->hauteur);
	if(error){
		fprintf(stderr,"Error lors de la creation de l'image %s\n",nom_fichier); //si l'appel à la fonction ne marche pas on affiche une erreur
		assert(0);
	}
	free(image_array);//Liberer le tableau
}




