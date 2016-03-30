#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "histogramme.h"

void traitement_file (char *name, FILE *binaire){
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

void traitement_multi_file (char *filename, FILE *binaire){

	int i;
	int nb_images;
	char **list_file_name;
	
	list_file_name = readList(filename, &nb_images);
	for (i=0; i<nb_images; i++){
		traitement_file(list_file_name[i], binaire);
	}
	freeList(list_file_name, nb_images);
}

int main(int argc, char *argv[])
{
	FILE *binaire;
	if (argc != 3){
		printf("2 arguments : le fichier contenant le nom/url des images, et le fichier binaire de stockage\n");
		exit(1);
	}
	binaire = fopen(argv[2], "w");
	traitement_multi_file(argv[1], binaire);
	fclose(binaire);

	exit(0);
}
