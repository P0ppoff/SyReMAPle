#include <stdio.h>
// #include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "rdjpeg.h"

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

int main(int argc, char *argv[])
{
	int i,j;
	CIMAGE cim;
	float histogramme_cubique[TAILLE_HISTO];
	
	read_cimage(argv[1],&cim);
	init_tab(histogramme_cubique, TAILLE_HISTO);
	make_histo(histogramme_cubique, &cim);
	normalize(histogramme_cubique, &cim);
	print_histo(histogramme_cubique);
	
	exit(0);
}