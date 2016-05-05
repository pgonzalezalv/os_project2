#ifndef _READER_H
#define _READER_H

/*
 * reader lit un fichier sur l'entree standard et cree des fractales.
 * @fichier: le fichier a lire
 * @return: 0 si on a atteint la fin du fichier sans erreur,
 *          1 sinon.
 *
 * commentaires : Il faut un mutex pour chaque ligne lu
 */
void *reader(char *fichier);

#endif
