#include "vector_dinamico.h"

void vector_destruir(vector_t* vector){
  free(vector->datos);
  free(vector);
}
void *vector_borrar(vector_t *vector, size_t pos){
  if(!vector) return NULL;
  if(pos < 0 || pos >= vector->cantidad) return NULL;
  vector->cantidad--;
  return vector->datos[pos];
}
void *vector_obtener(vector_t* vector, size_t pos){
  // verifica que el vector exista y que la posicion sea valida
  if (!vector || ((pos < 0) || (pos >= vector->cantidad))) return NULL;
  return vector->datos[pos];
}

bool vector_guardar(vector_t* vector, void *dato){
  // verifica que el vector exista y que haya espacio en el vector
  if(!vector) return false;
  if ((vector->cantidad + 1) > vector->tam)
    if(!vector_redimensionar(vector, vector->tam * 2)) return false;

  vector->datos[vector->cantidad] = dato;
  vector->cantidad++;
  return true;
}

void vector_swap(vector_t *vector, size_t pos1, size_t pos2){
  if(!vector) return;
  if (((pos1 < 0) || (pos1 >= vector->cantidad)) ||
     ((pos2 < 0) || (pos2 >= vector->cantidad))) return;
  void *dato_aux = vector->datos[pos1];

  vector->datos[pos1] = vector->datos[pos2];
  vector->datos[pos2] = dato_aux;
}

vector_t* vector_crear(size_t tam){
  vector_t* vector = malloc(sizeof(vector_t));

  if(!vector) return NULL;
  vector->datos = malloc(tam * sizeof(void*));

  if (tam > 0 && !vector->datos){
    free(vector);
    return NULL;
  }
  vector->tam = tam;
  vector->cantidad = 0;
  return vector;
}

bool vector_redimensionar(vector_t* vector, size_t tam_nuevo) {
    void** datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(void*));

    // Cuando tam_nuevo es 0, es correcto si se devuelve NULL.
    // En toda otra situación significa que falló el realloc.
    if (tam_nuevo > 0 && !datos_nuevo){
        return false;
    }

    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}
