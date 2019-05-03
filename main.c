//Code source par Rémi GUILLOMON
//Mai 2019

#include "annexe.h"

// main - usage: main <dictionnaire> <fichier_a_analyser>
int main(int argc, char *argv[]){

  if (argc < 3) printf("Erreur : nombre de fichiers insuffisants.\n");
  else{
    tableau_pt *dico = NULL;
    FILE *fichier1;
    FILE *fichier2;
    int erreur;
    
    fichier1 = fopen(argv[1],"r");             //Chargement du dictionnaire
    if (fichier1 != NULL){
      charge_dico(fichier1, &dico);
    }
    if (fichier1 !=NULL) fclose(fichier1);
    
    //printf("Dictionnaire chargé !\n");
    
    //char mot[TAILLE_MOT] = "";	//affichage du dictionnaire
    //printf("\n");
    //affiche_tab(dico,mot);
    
    fichier2 = fopen(argv[2],"r");			//Ouverture du texte à analyser
    if (fichier2 != NULL){
      erreur = charge_texte(fichier2, &dico);
    }
    if (fichier2 !=NULL) fclose(fichier2);

    if (erreur ==-1) printf("Une erreur est survenue lors de la lecture du fichier à analyser.\n");
    else  printf("Mot(s) non reconnu(s) par le dictionnaire : %d.\n",erreur);
    
    free_tableau_pt(&dico);
    return 0;
  }
}
