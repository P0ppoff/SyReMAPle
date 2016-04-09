#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "proc.h"

#define TAILLE_LIGNE 1000
#define INPUT 150

char* traitement_caracteristique(char *ligne){
	const char delim[2] = ";"; 
	char *tag = strtok(ligne, delim);
	char *caracteristiques = strtok(NULL, delim);
	return caracteristiques;
}

void read_sift(char *name_sift, FILE *sample){
	/*-----------------------------*/
	/* lecture d'un sift 		   */
	/*-----------------------------*/
	char *command;
	char *ligne;
	int nb_ligne;
	size_t nb_lu;
	FILE *fp;
	/*-------------------------------------------------*/
	/* commande de récupération         			   */ 
	/*-------------------------------------------------*/  
	asprintf(&command, "wget -O - \"%s\" -o /dev/null | cat ", name_sift);
	/*-----------------------------------*/
	/* lecture d'une image au format PPM */
	/*-----------------------------------*/
	if ((fp = popen(command,"r")) == NULL) {
		fprintf(stderr,"Can't open PBM file from \"%s\" command, exiting",command);
		exit(1);
	}
	free(command);
	nb_ligne = 0;
	ligne = NULL;
	while(!feof(fp)){
		getline(&ligne, &nb_lu, fp);
		nb_ligne++;
		if(nb_ligne%INPUT == 0){
			fprintf(sample, "%s\n", traitement_caracteristique(ligne));
		}
		free(ligne);
		ligne = NULL;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3){
		printf("\t2 arguments : la liste de sift,\n");
		printf("\tet le fichier de stockage.\n");
		exit(1);
	}

	FILE *sample;
	char **list_file_name;
	int nb_images, i;
	char *name_image_found;

	sample = fopen(argv[2], "w");
	list_file_name = readList(argv[1], &nb_images);

	for(i=0 ; i<nb_images ; i++){
		name_image_found = list_file_name[i];
		printf("\tTraitement de %s…\n", name_image_found);
		read_sift(name_image_found, sample);
	}

	freeList(list_file_name, nb_images);
	fclose(sample);

	return 0;
}
