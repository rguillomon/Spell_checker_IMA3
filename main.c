/* Code Source by Rémi GUILLOMON */

#include "annexe.h"


int main(){
  tableau_pt *dico = NULL;
  FILE *fichier1;
  FILE *fichier2;
  int erreur;
  
  fichier1 = fopen("eng_list.txt","r");             //Chargement du dictionnaire
  if (fichier1 != NULL){
    charge_dico(fichier1, &dico);
  }
  if (fichier1 !=NULL) fclose(fichier1);

  //printf("Dictionnaire chargé !\n");
	
	//char mot[TAILLE_MOT] = "";	//affichage du dictionnaire
  //printf("\n");
  //affiche_tab(dico,mot);
	
  fichier2 = fopen("text.txt","r");			//Ouverture du texte à analyser
  if (fichier2 != NULL){
    erreur = charge_texte(fichier2, &dico);
  }
  if (fichier2 !=NULL) fclose(fichier2);

  if (erreur ==-1) printf("Une erreur est survenue lors de la lecture du fichier à analyser.\n");
  else  printf("Mot(s) non reconnu(s) par le dictionnaire : %d.\n",erreur);
  
  
  
  free_tableau_pt(&dico);
  return 0;
}
