#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define NB_CAR 28
#define TAILLE_MOT 30

typedef struct node{
  char car;
  bool fin;
  struct node *fils[NB_CAR];
} Node;

Node * init_tree(){
  Node *pn=malloc(sizeof(Node));
  pn->fin=false;
  pn->fils=NULL;
  return pn;
}

/*Fonction de recherche renvoyant la position dans le mot cherché jusqu'à laquelle
un mot a été trouvé dans le dictionnaire
Exemple : mot recherché 'we' ; mot existant dans le dico 'were'
L'indice renvoyé sera '1'
Si le mot n'est pas présent, renvoie -1
*/
int recherche(Node *pn, char mot[TAILLE_MOT])
  if
