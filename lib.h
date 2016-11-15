#ifndef LIB_H
#define LIB_H
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*Constantes a utilizar*/
#define FIN_ARCHIVO -1

FILE *abrir_archivo(char *);
void modificar_caracter(char**, char, char);
#endif //LIB_H
