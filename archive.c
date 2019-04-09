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
