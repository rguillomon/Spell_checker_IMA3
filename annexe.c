#include "annexe.h"

/*Fonction renvoyant l'indice jusqu'auquel le mot est présent dans le dictionnaire
Exemple : mot recherché 'we' ; mot existant dans le dico 'were'
L'indice renvoyé sera '1'
Si le mot n'est pas présent, renvoie -1
*/
int indice(Node *pn, wchar_t mot[TAILLE_MOT]){
  if (pn==NULL) return -1;
  int taille = wcslen(mot);
  int i=-1;    //indice de position qui sera renvoyé
  int k=0;     //compteur d'indice du tableau 'fils'
  while (k<NB_CAR){
    if (pn->car == mot[i+1]){       //le caractère en position i+1 est correct
      i++;
      if (i==taille-1) return i;            //cas où le mot exact est trouvé
      if (pn->fils->T[k] == NULL) return i;    //cas où il n'existe pas de mot plus grand que mot[0:i ]dans le dico
      else{
	pn = pn->fils->T[k];
	k=0;
      }
    }
    else k++;
  }
  return i;     //le caractère mot[i+1] n'est pas pas trouvé
}


/* Fonction récursive affichant le contenu d'un tableau */
int affiche_tab(tableau_pt *pt, wchar_t mot[TAILLE_MOT]){
  if (pt == NULL){
    printf("\n");
    return 0;
  }
  int affi = 0;
  int affj = 0;
  wchar_t motSuiv[TAILLE_MOT];
    
  for (int i=0; i<NB_CAR ; i++){
    
    if (pt->T[i] != NULL){                        //le tableau contient une lettre
      wcscpy(motSuiv,mot);
      if (affj) printf("%ls",mot);                     //si la lettre mot[j] change, on raffiche le mot jusqu'à mot[i]

      wchar_t caractere[TAILLE_MOT];                   //on affiche mot[j] à la suite
      caractere[0]=pt->T[i]->car;
      printf("%ls",caractere);
      wcscat(motSuiv,caractere);
      
      if (pt->T[i]->fin){                          // si la lettre est la fin d'un mot, on affiche ';' à la suite
	printf(";");
	wcscat(motSuiv,L";");
      }
      
      //printf("\n motSuiv : %ls\n",motSuiv);

      if (affiche_tab(pt->T[i]->fils, motSuiv)){            // si une lettre suivante a été affichée
	affi=1;                                     // on saute à la ligne et on le note pour rafficher jusqu'à mot[i] pour la sortie de la fonction
	printf("\n");
      }
      affj = 1;
    }
  }
  return affi;
}
