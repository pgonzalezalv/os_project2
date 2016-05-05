#ifndef _READER_H
#define _READER_H

// maximal characters per line
#define SIZE_MAX 500

/*
 * reader lit un file sur l'entree standard et cree des fractales.
 * @file: le file a lire
 * @return: 0 si on a atteint la fin du file sans erreur,
 *          1 sinon.
 *
 * commentaires : Il faut un mutex pour chaque ligne lu
 */
void *reader(void *param);

#endif
