#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

void** top_k(size_t k, void** datos, size_t tam_datos, cmp_func_t cmp){
  if (!datos) return NULL;
  void **vector = malloc(k * sizeof(void*));
  if (!vector) return NULL;
  size_t tam_heap = k;
  if (tam_datos < k){
    tam_heap = tam_datos;
    for(size_t i = tam_datos; i > k; i++){
      vector[i] = NULL;
    }
  }
  heap_t * heap = heap_crear_arr(datos, tam_heap, cmp);
  for (size_t i = k; i < tam_datos; i++){
    heap_encolar(heap, datos[i]);//Agrego un elemento, haciendo que se reordene el heap.
    heap_desencolar(heap);//Elimino el elemento más grande.
  }
  for (size_t i = (k - 1); i + 1 > 0; i--){
    vector[i] = heap_desencolar(heap);
  }
  heap_destruir(heap, NULL);
  return vector;
}
