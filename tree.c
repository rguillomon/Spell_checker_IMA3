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


/* Fonction initialisant un arbre ; renvoie un pointeur de noeud*/
void init_tree(Node **pn){
  *pn=malloc(sizeof(Node));
  (*pn)->fin=false;
  (*pn)->fils=NULL;
  return ;
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


/* Fonction recherchant si un fils associé à un caractère existe */
bool recherche(Node *pn, char c){
  int i = c-'a';
  //bool condition = (pn->fils->T[i] == NULL);
  if (pn->fils->T[i] == NULL){
    return false;
  }
  else return true;
}



/* Fonction récursive ajoutant le mot (en MINUSCULE) à la suite de l'arbre*/
int ajout_dico(Node **noeud, char mot[TAILLE_MOT]){
  if (TAILLE_MOT-1 < strlen(mot)){                        // si le mot ne contient pas '\0', on revoie 0
    printf("Le mot n'a pas pu être ajouté.\n");
    return 0;
  }

  if (*noeud == NULL){                                   // le caractère à ajouter n'était pas présent dans le dico
    init_tree(noeud);
  }
  
  if (strlen(mot) == 1){                                 // si le mot ne contient qu'un caractère
    ajout_node(noeud, mot[0], true);
    return 1;    
  }
  else{
    int i =mot[0]-'a';
    if (!recherche(*noeud, mot[0])){                     //si le fils n'existe pas
      
      init_tree(&(*noeud)->fils->T[i]);
    }
    ajout_dico(&(*noeud)->fils->T[i], &mot[1]); 
  }
  return 1;
}


//TODO FONCTION CASSE qui met un mot en minuscules



int main(){
  Node *dico;
  init_tree(&dico);
  ajout_dico(&dico, "abc");
  ajout_dico(&dico, "ab");
  ajout_dico(&dico, "abb");

  free_node(&dico);
  return 0;
}


