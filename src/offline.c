#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "histogramme.h"

int main(int argc, char *argv[])
{
	if (argc != 4){
		printf("\t3 arguments : le nom/url de l'image recherchée,\n");
		printf("\tet le fichier binaire de stockage,\n");
		printf("\tenfin la liste de nom/url des images de références.\n");
		exit(1);
	}

	FILE *binaire;
	float histo_search[TAILLE_HISTO];
	float histo_ref[TAILLE_HISTO];
	CIMAGE image_search;
	int i;
	char **list_file_name;
	int nb_images;
	char *name_image_found;
	
	list_file_name = readList(argv[3], &nb_images);
	// printf("Lecture de noms/urls -> DONE\n");
	KEY tab_key[nb_images];
	// printf("Création du tableau de taille %i -> DONE\n", nb_images);
	binaire = fopen(argv[2], "r");
	init_tab(histo_search, TAILLE_HISTO);
	init_tab(histo_ref, TAILLE_HISTO);
	// printf("Initialisation -> DONE\n");
	read_cimage(argv[1], &image_search);
	make_histo(histo_search, &image_search);
	normalize(histo_search, &image_search);
	// printf("Lecture de l'image recherchée -> DONE\n");
	for(i=0 ; i<nb_images ; i++){
		tab_key[i].k = i;
		read_histo_binary(histo_ref, binaire);
		// printf("lecture de l'histogramme no %i -> DONE\n", i);
		tab_key[i].d = distance_euclidienne(histo_search, histo_ref);
	}
	// printf("tableau de comparaison rempli avec %i images -> DONE\n", i);
	qsort(tab_key, nb_images, sizeof(KEY), keyCompare);
	/*
	for(i=0 ; i<nb_images ; i++){
		printf("%i %f \n", tab_key[i].k, tab_key[i].d);
	}
*/
	// printf("Tri -> DONE\n");
	printf("<html>\n\t<body>\n");
	for(i=0 ; i<10 ; i++){
		name_image_found = list_file_name[tab_key[i].k];
		printf("\t\t<p><img src=\"%s\"></p>\n", name_image_found);
	}
	printf("\t</body>\n</html>\n");

	free_cimage(&image_search);
	freeList(list_file_name, nb_images);
	fclose(binaire);
	exit(0);
}
