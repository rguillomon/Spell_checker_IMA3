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


/* Libération récursive d'un arbre */
void free_tree(Node **pn){
  if (*pn == NULL) return ;
  if ((*pn)->fils != NULL) free_tableau_pt(&(*pn)->fils);
  free(*pn);
  *pn=NULL;

  return;
}

void free_tableau_pt(tableau_pt **pt){
  if (*pt == NULL) return ;
  for (int i=0 ; i<NB_CAR ;i++){
    if ((*pt)->T[i] != NULL)      free_tree(&(*pt)->T[i]);
  }
  free(*pt);
  *pt = NULL;
  return ;
}


/* Fonction initialisant les composantes d'un noeud */
void init_node(Node **pn, char car, bool fin){
  if (*pn==NULL)    *pn = malloc(sizeof(Node));
  (*pn)->car = car;
  (*pn)->fin = fin;
}


/* Fonction créant un noeud */
void new_node(Node **pn){
  if (*pn==NULL) *pn=malloc(sizeof(Node));
  (*pn)->car=0;
  (*pn)->fin=false;
  (*pn)->fils=NULL;
  return ;
}


/* Fonction initialisant un tableau de pointeurs de noeuds ; chaque fils vaut 'NULL' */
void init_tableau_pt(tableau_pt **pt){
  if (*pt == NULL)  *pt = malloc(sizeof(tableau_pt));
  for (int i=0 ; i<NB_CAR ; i++){
    (*pt)->T[i] = NULL;
  }
}


/* Fonction récursive ajoutant le mot (en MINUSCULE) à la suite de l'arbre*/
int ajout_dico(tableau_pt **pt, char mot[TAILLE_MOT]){
  if (TAILLE_MOT-1 < strlen(mot)){                        // si le mot ne contient pas '\0', on revoie 0
    printf("Le mot n'a pas pu être ajouté.\n");
    return 0;
  }

  if (*pt == NULL) init_tableau_pt(pt);

  int i = mot[0] -'a';
  if ((*pt)->T[i] == NULL){            //ajout du caractère mot[0] au dictionnaire s'il n'est pas déjà présent
    new_node(&(*pt)->T[i]);
    (*pt)->T[i]->car = mot[0];
  }

  if (strlen(mot) == 1){                     // si le mot ne contient qu'un seul caractère
    (*pt)->T[i]->fin = true;
    return 1;
  }

  else{                                                  // sinon, il y a d'autres caractères à ajouter
    if ((*pt)->T[i]->fils == NULL){                           // si le tableau fils n'est pas initialisé
      init_tableau_pt(&(*pt)->T[i]->fils);
    }
    
    ajout_dico(&(*pt)->T[i]->fils, &mot[1]);      // ajout du caractère suivant
  }
  return 1;
}




//TODO FONCTION CASSE qui met un mot en minuscules



int main(){
  tableau_pt *dico = NULL;
  ajout_dico(&dico, "abc");
  ajout_dico(&dico, "ab");
  ajout_dico(&dico, "abb");

  printf("%c\n", dico->T[0]->car);
  printf("%d\n", dico->T[0]->fin);
  printf("%p\n", dico->T[0]->fils->T[0]);
  printf("%c\n", dico->T[0]->fils->T[1]->car);
  printf("%d\n", dico->T[0]->fils->T[1]->fin);
  printf("%c\n", dico->T[0]->fils->T[1]->fils->T[1]->car);
  printf("%d\n", dico->T[0]->fils->T[1]->fils->T[2]->fin);
  
  free_tableau_pt(&dico);
  return 0;
}

//TODO initialiser dico en tant que tableau, non en tant que noeud
