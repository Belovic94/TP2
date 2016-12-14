#include "lib.h"
#include "hash.h"
#include "cola.h"
#include "strutil.h"

/* ***************************************************************************
 *                             FUNCIONES AUXILIARES                          *
 * ***************************************************************************/

/* Crea una copia de la clave pasada por parametro*/
char *strdup (const char *clave) {
	char *copia_clave = malloc (strlen (clave) + 1);
  if (copia_clave) strcpy (copia_clave,clave);
  return copia_clave;
}

/*Recibe un vector de cadenas, una cola y un hash.
  Aumenta la cantidad de apariciones de aquellas palabras que esten en el hash
	y agrega las que no están. Estas últimas tambien son agregadas a la cola*/
void contar_palabras(char *vec_cadenas[], hash_t *hash, cola_t *cola, int pos){
	if(!vec_cadenas[pos]) return;
	int *dato = malloc(sizeof(int));
	int *dato_aux = hash_obtener(hash, vec_cadenas[pos]);
	if(!dato_aux){
		*dato = 0;
		char *cadena = strdup(vec_cadenas[pos]);
		cola_encolar(cola, cadena);
	}
	else *dato = *dato_aux;
	*dato += 1;
	hash_guardar(hash, vec_cadenas[pos], dato);
	contar_palabras(vec_cadenas, hash, cola, pos + 1);
}

/*Muestra por pantalla las palabras y sus apariciones hasta que la cola ya no tenga palabras*/
void mostrar_por_pantalla(cola_t *cola, hash_t *hash){
	char *clave;
	int *valor;
	while(!cola_esta_vacia(cola)){
		clave = cola_desencolar(cola);
		valor = hash_borrar(hash, clave);
		printf("%d %s\n", *valor, clave);
		free(valor);
		free(clave);
	}
}

/* ***************************************************************************
 *                                UNIQ-COUNT                                 *
 * ***************************************************************************/

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
    modificar_caracter(&linea, '\n', '\0'); //Saco el salto de linea.
    vec_cadenas = split(linea, sep);
    //Recorro cada palabra del arreglo creado por split.
		contar_palabras(vec_cadenas, hash, cola, 0);
    free_strv(vec_cadenas);
  }
  free(linea);//libero la linea

	//muestro por pantalla.
	mostrar_por_pantalla(cola, hash);

  //Cierro el archivo y elimino las estructuras auxiliares.
  fclose(archivo);
  hash_destruir(hash);
  cola_destruir(cola, free);
  return EXIT_SUCCESS;
}
