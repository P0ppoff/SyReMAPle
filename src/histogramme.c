#include "histogramme.h"

int distance_euclidienne (float *x, float *y){
	int d = 0;
	int i;
	for(i=0 ; i<TAILLE_HISTO ; i++){
		d += pow((x[i]-y[i]),2) / (x[i]+y[i]);
	}
	return d;
}

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

void print_histo (float *hist){
	int i;
	float sum = 0.0;
	for(i=0 ; i<TAILLE_HISTO ; i++){
		printf("[%i] -> %f\n", i, hist[i]);
		sum += hist[i];
	}
	printf("Sum : %f\n", sum);
}

void print_histo_binary (float *hist, FILE *f){

	fwrite(hist, sizeof(hist), 64, f);
}

void normalize (float *hist, CIMAGE *image){
	int i;
	float nb_pixel = image->ny * image->nx;
	for(i=0 ; i<TAILLE_HISTO ; i++){
		hist[i] = hist[i]/nb_pixel;
	}
}