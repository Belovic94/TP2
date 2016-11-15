#include "lib.h"
#include "hash.h"
#include "cola.h"
#include "strutil.h"

void recorro_palabras(char **vec_palabras, size_t pos, hash_t *hash, cola_t *cola){
  if(!vec_palabras[pos]) return;
  int *dato = malloc(sizeof(int));
  int *dato_aux = hash_obtener(hash, vec_palabras[pos]);
  if(!dato_aux){
    *dato = 0;
    cola_encolar(cola, vec_palabras[pos]);
  }
  else *dato = *dato_aux;
  *dato += 1;
  hash_guardar(hash, vec_palabras[pos],dato);
  recorro_palabras(vec_palabras, pos + 1, hash, cola);
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
  hash_t *hash = hash_crear(free);
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


  size_t capacidad = 0;
  char* linea = NULL;
  char sep = ' ';
  char **vec_cadenas;
  //Recorro las lineas del archivo.
  while(getline(&linea, &capacidad, archivo) != FIN_ARCHIVO){
    modificar_caracter(&linea, '\n', '\0');
    vec_cadenas = split(linea, sep);
    //Recorro cada palabra del arreglo creado por split.
    recorro_palabras(vec_cadenas, 0, hash, cola);
    free_strv(vec_cadenas);
  }
  free(linea);

  //muestro por pantalla.
  char *clave;
  int *dato;
  while(!cola_esta_vacia(cola)){
    clave = cola_desencolar(cola);
    dato = hash_borrar(hash, clave);
    printf("%d %s\n", *dato, clave);
    free(dato);
    free(clave);
  }

  //Cierro el archivo y elimino las estructuras auxiliares.
  fclose(archivo);
  hash_destruir(hash);
  cola_destruir(cola, NULL);
  return EXIT_SUCCESS;
}
