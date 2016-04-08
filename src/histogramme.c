#include "histogramme.h"

float distance_euclidienne (float *x, float *y){
	float d = 0.0;
	int i;
	for(i=0 ; i<TAILLE_HISTO ; i++){
		//d += pow((x[i]-y[i]),2) / (x[i]+y[i]);
		d += sqrt(((x[i]-y[i])*(x[i]-y[i])));
		//printf("%f \n", d);
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
	fwrite(hist, sizeof(hist), 1, f);
}

void read_histo_binary (float *histo, FILE *f){
	int nb_lu;
	int nb_a_lire = 1;
	nb_lu = fread(histo, sizeof(histo), nb_a_lire, f);
	if (nb_lu != nb_a_lire){
		printf("Nombre d'octets lus : %i\n", nb_lu);
		fclose(f);
		exit(1);
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
