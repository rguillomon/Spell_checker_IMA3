//Code source par Rémi GUILLOMON
//Mai 2019

#include "annexe.h"

/* Fonction récursive affichant le contenu d'un tableau */
int affiche_tab(tableau_pt *pt, char mot[TAILLE_MOT]){
  if (pt == NULL){
    printf("\n");
    return 0;
  }
  int new_aff = 0;  //désigne si mot doit être ré-affiché en sortant de la fonction
  int affj = 0;  //désigne si une lettre fille a déjà été affichée.
  char motSuiv[TAILLE_MOT];
    
  for (int i=0; i<NB_CAR ; i++){

    
    if (pt->T[i] != NULL){                        //le tableau contient une lettre
      strcpy(motSuiv,mot);
      if (affj) printf("%s",mot);                     //si une lettre fille a déjà été affichée, on raffiche le mot

      char caractere[TAILLE_MOT];                   //on affiche mot[j] à la suite
      caractere[0]=pt->T[i]->car;
      printf("%s",caractere);
      strcat(motSuiv,caractere);
      
      if (pt->T[i]->fin){                          // si la lettre est la fin d'un mot, on affiche ';' à la suite
	printf(";");
	strcat(motSuiv,";");
      }
      
      //printf("\n motSuiv : %s\n",motSuiv);

      if (affiche_tab(pt->T[i]->fils, motSuiv)){            // si le noeud fils a aussi des fils
	new_aff=1;                                     // on retourne à la ligne
	printf("\n");
      }
      affj = 1;
    }
  }
  return new_aff;
}
