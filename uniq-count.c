#define _POSIX_C_SOURCE 200809L
#include "hash.h"
#include "cola.h"
#include "strutil.h"
#include <stdio.h>
#define FIN -1

typedef struct nodo{
  char* clave;
  int dato;
}nodo_t;

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

int main(int argc, char *argv[]){
  if(argc != 2){//Verifico los parametros de entrada.
    fprintf(stderr, "La funcion solo acepta  un archivo\n");
    return EXIT_FAILURE;
  }
  FILE *archivo = abrir_archivo(argv[1]);
  if(!archivo)//si no se puede abrir el archivo, termino el programa.
    return EXIT_FAILURE;


  //Creo el hash y la cola.
  hash_t *hash = hash_crear(NULL);
  if(!hash){
    fclose(archivo);
    fprintf(stderr, "No se pudo crear el hash\n");
    return EXIT_FAILURE;
  }
  cola_t *cola = cola_crear();
  if(!cola){
    fclose(archivo);
      fprintf(stderr, "No se pudo crear la cola\n");
    return EXIT_FAILURE;
  }

  //Recorro las lineas
  size_t capacidad = 0;
  char* linea = NULL;
  char sep = ' ';
  char **vec_cadenas;
  int *dato;
  while(getline(&linea, &capacidad, archivo) != FIN){
    vec_cadenas = split(linea, sep);

    for (int i = 0; vec_cadenas[i]; i++){
      dato = hash_obtener(hash, vec_cadenas[i]);
      if(!dato){
        cola_encolar(cola, vec_cadenas[i]);
        *dato = 0;
      }
      *dato += 1;
      hash_guardar(hash, vec_cadenas[i], dato);
    }
  }
  free(linea);
  //muestro por pantalla.
  nodo_t *nodo;
  while(!cola_esta_vacia(cola)){
    clave = cola_desencolar(cola);
    printf("%d %s\n",*(int*)hash_borrar(hash, nodo->clave), nodo->clave);
  }
  //Cierro el archivo y elimino las estructuras auxiliares.
  fclose(archivo);
  hash_destruir(hash);
  cola_destruir(cola, NULL);
  free_strv(vec_cadenas);
  return EXIT_SUCCESS;
}
