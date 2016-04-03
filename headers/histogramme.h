#ifndef _HISTO_H
#define _HISTO_H

#include <math.h>
#include <stdio.h>

#include "rdjpeg.h"
#include "proc.h"
#include "rdjpeg.h"

#define NB_INTER 4
#define NIVEAU_COLOR 256
#define TAILLE_HISTO NB_INTER * NB_INTER * NB_INTER

int distance_euclidienne (float *x, float *y);
void make_histo (float *hist, CIMAGE *image);
void print_histo (float *hist);
void print_histo_binary (float *hist, FILE *f);
void read_histo_binary (float *histo, FILE *f);
void normalize (float *hist, CIMAGE *image);
void init_tab (float *tab, int taille);

#endif