/* Code Source by Rémi GUILLOMON */

#include "tree.h"


/* Fonction créant un noeud */
void new_node(Node **pn){
  if (*pn==NULL) *pn=malloc(sizeof(Node));
  (*pn)->car=0;
  (*pn)->fin=false;
  (*pn)->fils=NULL;
  return ;
}


/* Fonction initialisant les composantes d'un noeud */
void init_node(Node **pn, wchar_t car, bool fin){
  if (*pn==NULL)    new_node(pn);
  (*pn)->car = car;
  (*pn)->fin = fin;
}


/* Fonction initialisant un tableau de pointeurs de noeuds ; chaque fils vaut 'NULL' */
void init_tableau_pt(tableau_pt **pt){
  if (*pt == NULL)  *pt = malloc(sizeof(tableau_pt));
  for (int i=0 ; i<NB_CAR ; i++){
    (*pt)->T[i] = NULL;
  }
}


/* Libération récursive d'un arbre */
void free_tree(Node **pn){
  if (*pn == NULL) return ;
  if ((*pn)->fils != NULL) free_tableau_pt(&(*pn)->fils);
  free(*pn);
  *pn=NULL;
  return;
}


/*Libération d'un tableau_pt */
void free_tableau_pt(tableau_pt **pt){
  if (*pt == NULL) return ;
  for (int i=0 ; i<NB_CAR ;i++){
    if ((*pt)->T[i] != NULL)      free_tree(&(*pt)->T[i]);
  }
  free(*pt);
  *pt = NULL;
  return ;
}


/* Fonction renvoyant l'indice du caractère dans tableau_pt */
int indice_tab(wchar_t c){
  int i=-1;
  if (c >= 'a' && c<= 'z') i = c -'a';      //lettres de a à z
  if (c == '-') i = 26;                    // cas du trait d'union -> case 26 du tableau
  if (c == 39)  i = 27;                     // cas de l'apostrophe  -> case 27 du tableau
  if (c == L'à') i = 28;
  if (c == L'â') i = 29;
  if (c == L'ä') i = 30;
  if (c == L'æ') i = 31;
  if (c == L'ç') i = 32;
  if (c == L'è' || c==L'ë') i = c-50055;      // de 33 à 36
  if (c == L'î' || c==L'ï') i = c-50057;      // de 37 à 38
  if (c == L'ô') i = 39;
  if (c == L'ö') i = 40;
  if (c == L'ù') i = 41;
  if (c == L'û' || c==L'ü') i = c-50065;      // de 42 à 43
  if (c == L'œ') i = 44;
  
  return i;
}


/*Fonction qui met un mot en minuscules */
void casse(wchar_t mot[TAILLE_MOT]){
  int taille = wcslen(mot);
  wchar_t c;
  for (int i=0; i<taille; i++){
  	c=mot[i];
    if (c >= 65 && c<=90) mot[i] += 32;  //Lettres sans accent
    if (c==L'À' || c==L'È' || c==L'É' || c==L'Ê') mot[i] += 32;  //Lettres avec accent
    if (c==L'Ç') mot[i] += 32;  //Cas de la cédille
    if (c==L'Œ') mot[i] +=1;    // cas de œ
  }
  return ;
}


/* si le mot ne contient pas '\0', on revoie 0 */
int verif_taille_mot(char mot[TAILLE_MOT]){ 
	if(TAILLE_MOT-1 < strlen(mot)) return 0;
	else return 1;
}


/* Fonction vérifiant si chaque caractère du mot peut être ajouté */
int verif_caractere(char mot[TAILLE_MOT]){
  int taille = strlen(mot);
  for (int i=0; i<taille; i++){
    int i_car = indice_tab(mot[i]);
      if (i_car==-1){
	//printf("Caractère '%c' non reconnu.\n",mot[0]);                
	return 0;
      }
  }
  return 1;
}

/* Fonction déterminant si un mot donné est présent dans un dictionnaire */
bool recherche(tableau_pt *dico, wchar_t mot[TAILLE_MOT]){
  tableau_pt *pt = dico;
  int taille = wcslen(mot);
  int i=0;                      //position dans le mot
  int j;
  bool fin;

  if (taille==0) return false;
  
  while ((pt !=NULL) && i<taille){
    j = indice_tab(mot[i]);
    if (j==-1) return false;                //caractère non reconnu
      
    if (pt->T[j] == NULL) return false ;      // le caractère mot[i] n'est pas trouvé donc le mot n'est pas dans le dictionnaire
    else{
      i++;
      if (i==taille) fin = pt->T[j]->fin;
      pt = pt->T[j]->fils;
    }
  }
  if ((pt != NULL) || ((i == taille) && fin)) return true;      // si mot se trouve dans le dictionnaire et que son dernier caractère est la fin d'un mot
  else{
    return false;
    printf("mot non reconnu : %ls\n",mot);
  }
}


/* Fonction récursive ajoutant le mot (en MINUSCULE) à la suite de l'arbre */

int ajout_dico(tableau_pt **pt, wchar_t mot[TAILLE_MOT]){
  if (*pt == NULL) init_tableau_pt(pt);

  int i = indice_tab(mot[0]);
  
  if ((*pt)->T[i] == NULL){            //ajout du caractère mot[0] au dictionnaire s'il n'est pas déjà présent
    new_node(&(*pt)->T[i]);
    (*pt)->T[i]->car = mot[0];
  }

  if (wcslen(mot) == 1){                     // si le mot ne contient qu'un seul caractère
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


/* Charge le dictionnaire mot à mot */
void charge_dico(FILE *fichier, tableau_pt **pt){
  wchar_t mot[TAILLE_MOT];
  while (fscanf(fichier, "%ls", mot) == 1){
    casse(mot);
    if (verif_taille_mot(mot) && verif_caractere(mot))
      {
	ajout_dico(pt, mot); //Si le mot n'est pas trop long et si tous les caractères peuvent être ajoutés
      }
    //else printf("Le mot n'a pas pu être ajouté");
  }
  return ;
}


/* Fonction chargeant le fichier à analyser et le met dans un tableau_pt de réception */
int charge_texte(FILE *fichier, tableau_pt **dico){
  int c=fgetwc(fichier);
  int i=0;
  int erreur=0;
  wchar_t mot[TAILLE_MOT] = L"";

  while (c != EOF){
    if (c=='.' || c==' ' || c==',' || c==':' || c==';' || c=='!' || c=='?' || c=='(' || c==')' || c=='"'  || c=='\n'){      // cas de terminaison d'un mot
      mot[i]='\0';
      casse(mot);
      if (!recherche(*dico, mot) && (strlen(mot) != 0)){
	erreur++;
	printf("Mot incorrect : %ls\n",mot);
      }
      i=0;
      c=fgetwc(fichier);
    }
    else{
      if (i==TAILLE_MOT-1){                                          //cas d'un mot à charger trop long
	printf(" Erreur de chargement : un mot est trop long.\n");
	return -1;
      }
      else{
	mot[i]=c;
	i++;
	c=fgetwc(fichier);
      }
    }
  }
  mot[i]='\0';
  casse(mot);
  if (!recherche(*dico, mot) && (strlen(mot) != 0)){
    erreur++;
    printf("Mot incorrect : %ls\n",mot);
  }
  return erreur;
}
