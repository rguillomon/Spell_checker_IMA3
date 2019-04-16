#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NB_CAR 28
#define TAILLE_MOT 50

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

  int i=-1;
  if (mot[0] >= 'a' && mot[0]<= 'z') i = mot[0] -'a';
  if (mot[0] == '-') i = 26;                    // cas du trait d'union -> case 26 du tableau
  if (mot[0] == 39)  i = 27;                     // cas de l'apostrophe  -> case 27 du tableau
	if (i==-1){
		printf("Le caractère '%c' n'est pas reconnu, le mot n'a pas pu être ajouté.\n",mot[0]);
		return 0;
	}
  
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


/* Fonction récursive affichant le contenu d'un tableau */
int affiche_tab(tableau_pt *pt, char mot[TAILLE_MOT]){
  if (pt == NULL){
    printf("\n");
    return 0;
  }
  int affi = 0;
  int affj = 0;
  char motSuiv[TAILLE_MOT];
    
  for (int i=0; i<NB_CAR ; i++){

    
    if (pt->T[i] != NULL){                        //le tableau contient une lettre
      strcpy(motSuiv,mot);
      if (affj) printf("%s",mot);                     //si la lettre mot[j] change, on raffiche le mot jusqu'à mot[i]

      char caractere[TAILLE_MOT];                   //on affiche mot[j] à la suite
      caractere[0]=pt->T[i]->car;
      printf("%s",caractere);
      strcat(motSuiv,caractere);
      
      if (pt->T[i]->fin){                          // si la lettre est la fin d'un mot, on affiche ';' à la suite
	printf(";");
	strcat(motSuiv,";");
      }
      
      //printf("\n motSuiv : %s\n",motSuiv);

      if (affiche_tab(pt->T[i]->fils, motSuiv)){            // si une lettre suivante a été affichée
	affi=1;                                     // on saute à la ligne et on le note pour rafficher jusqu'à mot[i] pour la sortie de la fonction
	printf("\n");
      }
      affj = 1;
    }
  }
  return affi;
}


/*Fonction qui met un mot en minuscules */
void casse(char mot[TAILLE_MOT]){
  int taille = strlen(mot);
  for (int i=0; i<taille; i++){
    if (mot[i] >= 65 && mot[i]<=90) mot[i] += 32;
  }
  return ;
}


void charge_fichier(FILE *fichier, tableau_pt **pt){
  char mot[TAILLE_MOT];

  while (fscanf(fichier, "%s", mot) == 1){
    casse(mot);
    ajout_dico(pt, mot);
  }
  return ;
}

int main(){
  tableau_pt *dico = NULL;

  FILE *fichier;
  fichier = fopen("eng_list.txt","r");
  if (fichier != NULL){
    charge_fichier(fichier, &dico);
  }
  if (fichier !=NULL) fclose(fichier);
  
  //char mot[TAILLE_MOT] = "";
  //printf("\n");
  //affiche_tab(dico,mot);
  
  free_tableau_pt(&dico);
  return 0;
}

