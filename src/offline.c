#include <stdio.h>
// #include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "rdjpeg.h"
#include "proc.h"

#define NB_INTER 4
#define NIVEAU_COLOR 256
#define TAILLE_HISTO NB_INTER * NB_INTER * NB_INTER

void make_histo (float *hist, CIMAGE *image){
	int R, G, B, k, i, j;
	for(i=0 ; i<image->nx ; i++){
		for(j=0 ; j<image->ny ; j++){
			R = image->r[i][j] / (NIVEAU_COLOR/NB_INTER);
			G = image->g[i][j] / (NIVEAU_COLOR/NB_INTER);
			B = image->b[i][j] / (NIVEAU_COLOR/NB_INTER);
			k = R + G*4 + B*16;
			hist[k]++;
		}
	}	
}

void normalize (float *hist, CIMAGE *image){
	int i;
	float nb_pixel = image->ny * image->nx;
	for(i=0 ; i<TAILLE_HISTO ; i++){
		hist[i] = hist[i]/nb_pixel;
	}
}

void init_tab (float *tab, int taille){
	int i;
	for(i=0; i<taille ; i++){
		tab[i] = 0.0;
	}
}

void print_histo (float *hist){
	int i;
	float sum = 0.0;
	for(i=0 ; i<TAILLE_HISTO ; i++){
		printf("[%i] -> %f\n", i, hist[i]);
		sum += hist[i];
	}
	printf("Sum : %f\n", sum);
}

void traitement (char *name){
	CIMAGE cim;
	float histogramme_cubique[TAILLE_HISTO];

	printf("Traitement %s\n", name);
	
	read_cimage(name, &cim);
	init_tab(histogramme_cubique, TAILLE_HISTO);
	make_histo(histogramme_cubique, &cim);
	normalize(histogramme_cubique, &cim);
	print_histo(histogramme_cubique);
	free_cimage(NULL, &cim);
}

void traitement_multi (char *filename){

	int i;
	int nb_images;
	char **list_file_name;
	
	list_file_name = readList(filename, &nb_images);
	for (i=0; i<nb_images; i++){
		traitement(list_file_name[i]);
	}
	freeList(list_file_name, nb_images);
}

int main(int argc, char *argv[])
{
	traitement_multi(argv[1]);	
	exit(0);
}
