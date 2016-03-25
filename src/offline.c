#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "histogramme.h"

void init_tab (float *tab, int taille){
	int i;
	for(i=0; i<taille ; i++){
		tab[i] = 0.0;
	}
}

void traitement (char *name, FILE *binaire){
	CIMAGE cim;
	float histogramme_cubique[TAILLE_HISTO];

	printf("Traitement %s\n", name);
	read_cimage(name, &cim);
	init_tab(histogramme_cubique, TAILLE_HISTO);
	make_histo(histogramme_cubique, &cim);
	normalize(histogramme_cubique, &cim);
	print_histo(histogramme_cubique);
	print_histo_binary(histogramme_cubique, binaire);
	free_cimage(&cim);
}

void traitement_multi (char *filename, FILE *binaire){

	int i;
	int nb_images;
	char **list_file_name;
	
	list_file_name = readList(filename, &nb_images);
	for (i=0; i<nb_images; i++){
		traitement(list_file_name[i], binaire);
	}
	freeList(list_file_name, nb_images);
}

int main(int argc, char *argv[])
{
	FILE *binaire;
	if (argc == 3){
		binaire = fopen(argv[2], "w");
		traitement_multi(argv[1], binaire);
		fclose(binaire);
	}
	exit(0);
}
