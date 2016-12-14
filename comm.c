#include "lib.h"
#include "hash.h"

/* ***************************************************************************
 *                             FUNCIONES AUXILIARES                          *
 * ***************************************************************************/
/*Recibe un archivo y un hash.
  Guarda las lineas del archivo en el hash*/
void leer_archivo(FILE *archivo, hash_t *hash){
  char* linea = NULL;
  size_t tam = 0;
  ssize_t read = 0;  // valor devuelto por getline
  while (read != FIN_ARCHIVO){
      read = getline(&linea, &tam, archivo);
      hash_guardar(hash, linea, NULL);
  }
  free(linea);
}

/*Recibe 2 hash.
  Compara los 2 hash y elimina las lineas repetidas en ambos
  y las coloca en otro hash */
hash_t *sacar_repetidos(hash_t *hash1, hash_t *hash2){
  hash_t* hashc = hash_crear(NULL);
  hash_iter_t* iter = hash_iter_crear(hash1);
  const char* actual;

  while(!hash_iter_al_final(iter)){
      actual = hash_iter_ver_actual(iter);
      if (hash_pertenece(hash2, actual)){
          hash_guardar(hashc, actual, NULL);
          hash_borrar(hash2, actual);
          hash_borrar(hash1, actual);
      }
      hash_iter_avanzar(iter);
  }
  hash_iter_destruir(iter);
  return hashc;
}

/*Imprime por pantalla las lineas que se encuentran en el hash*/
void imprimir_por_pantalla(hash_t *hash){
  hash_iter_t *iter = hash_iter_crear(hash);
  while (!hash_iter_al_final(iter)){
      printf("%s",hash_iter_ver_actual(iter));
      hash_iter_avanzar(iter);
  }
  hash_iter_destruir(iter);
}

/* ***************************************************************************
 *                                    COMM                                   *
 * ***************************************************************************/

int main(int argc, char* argv[]){
    if (argc < 3 || argc > 4) {
      fprintf(stderr, "La funcion solo acepta 2 o 3 parametros \n");
      return EXIT_FAILURE;
    }
    long param_extra = 0;
    if (argc == 4){
      char* ptr;
      param_extra = strtol(argv[3], &ptr, 10);//verifico que el tercer parametro sea un numero entero.
      if( strcmp(ptr, "") != 0 || param_extra > -1 || param_extra < -2){
        fprintf(stderr, "El parametro extra tiene que ser un número entre (-1 y -2)\n");
        return EXIT_FAILURE;
      }
    }
    //abro archivos.
    FILE* arch1 = abrir_archivo(argv[1]);
    if (!arch1) return EXIT_FAILURE;
    FILE* arch2 = abrir_archivo(argv[2]);
    if (!arch2){
      fclose(arch1);
      return EXIT_FAILURE;
    }

    hash_t* hash1 = hash_crear(NULL);
    hash_t* hash2 = hash_crear(NULL);

    //leo ambos archivos
    leer_archivo(arch1, hash1);
    leer_archivo(arch2, hash2);

    //creo un nuevo hash con los valores repetidos de los hash anteriores.
    hash_t *hashc = sacar_repetidos(hash1, hash2);

    switch (param_extra){//decide de que hash va a leer las lineas.
      case -1:
          imprimir_por_pantalla(hash1);
          break;
      case -2:
          imprimir_por_pantalla(hash2);
          break;
      default:
          imprimir_por_pantalla(hashc);
    }

    //cierro archivos y destruyo estructuras.
    fclose(arch1);
    fclose(arch2);
    hash_destruir(hash1);
    hash_destruir(hash2);
    hash_destruir(hashc);
    return EXIT_SUCCESS;
}
