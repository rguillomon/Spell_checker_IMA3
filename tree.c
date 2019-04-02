#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NB_CAR 28
#define TAILLE_MOT 30

typedef struct tableau_pt{
  struct node *T[NB_CAR];
} tableau_pt;

typedef struct node{
  char car;
  bool fin;
  struct tableau_pt *fils;
} Node;

Node * init_tree(){
  Node *pn=malloc(sizeof(Node));
  pn->fin=false;
  pn->fils=NULL;
  return pn;
}

/* Libération récursive d'un noeud */
void free_node(Node **pn){
  if (*pn == NULL) return ;
  if ((*pn)->fils == NULL){
    free(*pn);
    *pn=NULL;
  }
  else{
    for (int i=0 ; i<NB_CAR ;i++){
      if ((*pn)->fils->T[i] != NULL){
	free_node(&(*pn)->fils->T[i]);
      }
    }
  }
  return;
}

/* Fonction initialisant un tableau de pointeurs de noeuds */
void init_tableau_pt(tableau_pt **pt){
  if (*pt == NULL)  *pt = malloc(sizeof(tableau_pt));
  for (int i=0 ; i<NB_CAR ; i++){
    free_node(&(*pt)->T[i]);
  }
}

void ajout_node(Node **pn, char car, bool fin){
  if (*pn==NULL)    *pn = malloc(sizeof(Node));
  (*pn)->car = car;
  (*pn)->fin = fin;
  (*pn)->fils = NULL;
}

/*Fonction renvoyant l'indice jusqu'auquel le mot est présent dans le dictionnaire
Exemple : mot recherché 'we' ; mot existant dans le dico 'were'
L'indice renvoyé sera '1'
Si le mot n'est pas présent, renvoie -1
*/
int indice(Node *pn, char mot[TAILLE_MOT]){
  if (pn==NULL) return -1;
  int taille = strlen(mot);
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





void ajout_dico(Node **dico, char mot[TAILLE_mot]){
  if (*dico == NULL){
    *dico = init_tree();
  }
  

}

int main(){
  //Node *dico=init_tree();
  


  
  return 0;
}


