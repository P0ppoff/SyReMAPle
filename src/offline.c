#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "histogramme.h"

int main(int argc, char *argv[])
{
	if (argc != 4){
		printf("3 arguments : le nom/url de l'image recherchée, et le fichier binaire de stockage, puis le nombre de histogramme\n");
		exit(1);
	}

	FILE *binaire;
	float *histo_search;
	float *histo_ref;
	CIMAGE image_search;
	int i;
	int nb_images = atoi(argv[3]);
	KEY tab_key[nb_images];

	binaire = fopen(argv[2], "r");
	init_tab(histo_search, TAILLE_HISTO);
	init_tab(histo_ref, TAILLE_HISTO);
	
	read_cimage(argv[1], &image_search);
	make_histo(histo_search, &image_search);
	normalize(histo_search, &image_search);

	for(i=0 ; i<nb_images ; i++){
		tab_key[i].k = i;
		read_histo_binary(histo_ref, binaire);
		tab_key[i].d = distance_euclidienne(histo_search, histo_ref);
	}
	qsort(tab_key, nb_images, sizeof(KEY), keyCompare);



	free_cimage(&image_search);
	fclose(binaire);
	exit(0);
}
