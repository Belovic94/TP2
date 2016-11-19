#include "lib.h"
#include "hash.h"
#include "cola.h"
#include "strutil.h"

char *strdup (const char *clave) {
	char *copia_clave = malloc (strlen (clave) + 1);
  if (copia_clave) strcpy (copia_clave,clave);
  return copia_clave;
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
  char **vec_cadenas, *cadena;
  int * dato, *dato_aux;
  //Recorro las lineas del archivo.
  while(getline(&linea, &capacidad, archivo) != FIN_ARCHIVO){
    modificar_caracter(&linea, '\n', '\0');
    vec_cadenas = split(linea, sep);
    //Recorro cada palabra del arreglo creado por split.
    for (int i = 0; vec_cadenas[i]; i++){
      dato = malloc(sizeof(int));
      dato_aux = hash_obtener(hash, vec_cadenas[i]);
      if(!dato_aux){
        *dato = 0;
        cadena = strdup(vec_cadenas[i]);
        cola_encolar(cola, cadena);
      }
      else *dato = *dato_aux;
      *dato += 1;
      hash_guardar(hash, vec_cadenas[i], dato);
    }
    free_strv(vec_cadenas);
  }
  free(linea);

  //muestro por pantalla.
  char *clave;
  int *valor;
  while(!cola_esta_vacia(cola)){
    clave = cola_desencolar(cola);
    valor = hash_borrar(hash, clave);
    printf("%d %s\n", *valor, clave);
    free(valor);
    free(clave);
  }

  //Cierro el archivo y elimino las estructuras auxiliares.
  fclose(archivo);
  hash_destruir(hash);
  cola_destruir(cola, free);
  return EXIT_SUCCESS;
}
