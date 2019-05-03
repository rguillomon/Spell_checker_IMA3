Code source par Rémi GUILLOMON

Mai 2019

#Vérificateur orthographique

##Description rapide

Ce programme est un vérificateur d'orthographe qui compte et affiche les mots non reconnus par un dictionnaire dans un texte.

Le dictionnaire et le texte à analyser sont à fournir mais `eng_list.txt` (dictionnaire anglais) et `text.txt` peuvent servir d'exemple.

Si un mot du texte est plus grand que TAILLE_MOT (défini dans tree.h), alors le programme affiche un message d'erreur et le processus est annulé.

##Mode d'emploi

Voici les fichiers nécessaires au fonctionnement du programme:
- `annexe.c` et `annexe.h`
- `tree.c` et `tree.h`
- `main.c`
- `Makefile`
- votre dictionnaire et votre fichier à analyser. On prendra ici `eng_list.txt` et `text.txt` pour l'exemple.

Tout d'abord, ouvrez un terminal dans le dossier contenant ces fichiers.
Puis compilez le tout en tapant ceci:
> make

Puis exécuter avec vos fichiers :
> ./exe eng_list.txt text.txt

Voilà, le tour est joué !

