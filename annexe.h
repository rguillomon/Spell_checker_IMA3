//Code source par Rémi GUILLOMON
//Mai 2019

#include <string.h>
#include <stdio.h>
#include "tree.h"


/*Fonction renvoyant l'indice jusqu'auquel le mot est présent dans le dictionnaire
Exemple : mot recherché 'we' ; mot existant dans le dico 'were'
L'indice renvoyé sera '1'
Si le mot n'est pas présent, renvoie -1
*/
int indice(Node *pn, char mot[TAILLE_MOT]);


/* Fonction récursive affichant le contenu d'un tableau */
int affiche_tab(tableau_pt *pt, char mot[TAILLE_MOT]);
