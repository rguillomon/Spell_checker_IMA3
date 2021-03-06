//Code source par Rémi GUILLOMON
//Mai 2019

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

/* Fonction créant un noeud */
void new_node(Node **pn);

/* Fonction initialisant les composantes d'un noeud */
void init_node(Node **pn, char car, bool fin);

/* Fonction initialisant un tableau de pointeurs de noeuds ; chaque fils vaut 'NULL' */
void init_tableau_pt(tableau_pt **pt);

/* Libération récursive d'un arbre */
void free_tree(Node **pn);

/*Libération d'un tableau_pt */
void free_tableau_pt(tableau_pt **pt);

/* Fonction renvoyant l'indice du caractère dans tableau_pt */
int indice_tab(char c);

/* si le mot ne contient pas '\0', on revoie 0 */
int verif_taille_mot(char mot[TAILLE_MOT]);

/* Fonction vérifiant si chaque caractère du mot peut être ajouté */
int verif_caractere(char mot[TAILLE_MOT]);

/*Fonction qui met un mot en minuscules */
void casse(char mot[TAILLE_MOT]);

/* Fonction déterminant si un mot donné est présent dans un dictionnaire */
bool recherche(tableau_pt *dico, char mot[TAILLE_MOT]);

/* Fonction récursive ajoutant le mot (en MINUSCULE) à la suite de l'arbre */
int ajout_dico(tableau_pt **pt, char mot[TAILLE_MOT]);

/* Charge le dictionnaire mot à mot */
void charge_dico(FILE *fichier, tableau_pt **pt);

/* Fonction chargeant le fichier à analyser et le met dans un tableau_pt de réception */
int charge_texte(FILE *fichier, tableau_pt **dico);

