# Ligne_de_partage_des_eaux
Un programme qui permet de détecter un objet dans une image NB

Membre de binome:
* BEN YAHIA Ilyes
* EL AMRANI Ismail

Vous trouvez dans ce fichier les etapes a suivre pour compiler le programme.

Dans ce repertoire il y a trois dossier et deux fichier:
-Images : Contient les images noir et blanc et leur marqueur
-Resultat : Contient les images de resultat
-src : Contient les fichiers de code source (main.c, image.c, image.h, lodepng.c, lodepng.h)
-makefile : le fichier qui gere la compilation des codes sources.
-README : ce fichier



*Pour Compiler:
	*Ouvrire un terminal dans le repertoire courant et taper "make" pour compiler le programme
	==> un fichier executable qui s'appel "image.exe" il sera creer dans le meme repertoire
	
*Pour Executer le fichier taper:
	./image.exe ./Images/Nom_image.png ./Images/Nom_image_marqueurs.png
		
	-Exempel: ./image.exe ./Images/route.png ./Images/route_marqueurs.png
	
	
==> Quatre images qui vont etre creer dans le repertoire "Resultat":
	*"gradient.png" l'image qui represente les resultat de la fonction qui calcul le gradient d'une image.
	*"clpeGris.png" l'image qui represente les resultat de l'algorithme de calcule de la ligne de partage des eaux en niveaux de gris.
	*"clpeCouleur.png" l'image qui represente les resultat de l'algorithme de calcule de la ligne de partage des eaux en couleur aleatoir.
	*"ObjetContourRouge.png" l'image qui represente l'image initiale avec un contour rouge sur les objets de l’image.

