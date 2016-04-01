#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "histogramme.h"

int main(int argc, char *argv[])
{
	FILE *binaire;
	float *histo_search;
	float **tab_histo;
	CIMAGE image_search;
	if (argc != 3){
		printf("2 arguments : le nom/url de l'image recherchée, et le fichier binaire de stockage\n");
		exit(1)
	}
	binaire = fopen(argv[2], "r");
	init_tab(histo_search);
	read_cimage(argv[1], &image_search);
	make_histo(histo_search, &image_search);
	normalize(histo_search, &image_search);

	free_cimage(&image_search);
	fclose(binaire);
	exit(0);
}
