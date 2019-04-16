/* Code Source by Rémi GUILLOMON */

#include "annexe.h"


int main(){
  tableau_pt *dico = NULL;
  FILE *fichier;
  int erreur;
  
  fichier = fopen("eng_list.txt","r");             //Chargement du dictionnaire
  if (fichier != NULL){
    charge_dico(fichier, &dico);
  }
  if (fichier !=NULL) fclose(fichier);

  printf("Dictionnaire chargé !\n");

  fichier = fopen("text.txt","r");
  if (fichier != NULL){
    erreur = charge_texte(fichier, &dico);
  }
  if (fichier !=NULL) fclose(fichier);

  if (erreur ==-1) printf("Une erreur est survenue lors du chargement du fichier.\n");
  else  printf("Mot(s) non reconnu(s) par le dictionnaire : %d.\n",erreur);
  
  //char mot[TAILLE_MOT] = "";
  //printf("\n");
  //affiche_tab(dico,mot);
  
  free_tableau_pt(&dico);
  return 0;
}
