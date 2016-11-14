#include "strutil.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* **************************************************************
 *                     FUNCIONES AUXILIARES                     *
 * **************************************************************/

char* agregar_cadena(const char* str, size_t indice){
  char* str_aux = malloc(indice + 1);
  if(!str_aux)
    return NULL;
  strncpy(str_aux, str, indice);
  str_aux[indice] = '\0';
  return str_aux;
}

char *cadena_concatenar(char *str, char* str_cpy, char sep, size_t nueva_capacidad){
    char *str_aux = realloc(str, nueva_capacidad);
    if(!str_aux)
      return NULL;
    strcat(str_aux, str_cpy);
    str_aux[nueva_capacidad - 2] = sep;
    str_aux[nueva_capacidad - 1] = '\0';
    return str_aux;
}

/* **************************************************************
 *             FUNCIONES:  SPLIT JOIN Y FREE_STRV               *
 * **************************************************************/

char** split(const char* str, char sep){
  char* vector[strlen(str)];
  char *pal_aux = strchr(str, sep);
  size_t i = 0;
  while(pal_aux != NULL){
    vector[i] = agregar_cadena(str, strlen(str) - strlen(pal_aux));
    str = pal_aux + 1;
    pal_aux = strchr(str, sep);
    i++;
  }
  vector[i] = agregar_cadena(str, strlen(str));
  i++;
  vector[i] = NULL;
  //paso claves del vector local al vector hecho con malloc
  char **strv = malloc((i + 1) * sizeof(char*));
  if(!strv)
    return NULL;
  for(int j = 0; j <= i ; j++){
    strv[j] = vector[j];
  }
  return strv;

}

char* join(char** strv, char sep){
  if(!strv || sep == '\0')
    return NULL;
  size_t i = 0, str_largo;
  char *str = malloc(1);
  str[i] = '\0';
  for(i = 0; strv[i]; i++){
    str_largo = strlen(strv[i]);
    str = cadena_concatenar(str, strv[i], sep, strlen(str) + str_largo + 2);
    if(!str)
      return NULL;
  }
  if(strlen(str) > 0)//saca el separador del final.
    str[strlen(str) - 1] = '\0';
  return str;
}

void free_strv(char* strv[]){
  if(!strv)
    return;
  for(int i = 0; strv[i]; i++){
    free(strv[i]);
  }
  free(strv);
}
