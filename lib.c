#include "lib.h"

/*Recibe el nombre de un archivo.
 *En caso de que pueda abrir el archivo, lo devuelve.
 *Si no devuelve NULL.
 */
FILE *abrir_archivo(char *nom_arch){
  if(!nom_arch)
    return NULL;
  FILE *archivo = fopen(nom_arch, "r");
  if(!archivo){
    fprintf(stderr, "No se pudo abrir el archivo: %s\n", nom_arch);
    return NULL;
  }
  return archivo;
}
/*Recibe un puntero a una cadena y dos letras.
 *Modifica la letra que se encuentra en la cadena por la nueva.
 */
void modificar_caracter(char** cadena, char letra_ant, char letra_nueva){
  char *cadena_aux = strchr(*cadena, letra_ant);//encuentro la posicion de la letra a cambiar;
  (*cadena)[strlen(*cadena) - strlen(cadena_aux)] = letra_nueva;
}
