#include "heap.h"
#include <stdlib.h>
#include <stdio.h>


int comparar (const void *a, const void *b){
  return *(int*)a - *(int*)b;
 }

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
    heap_encolar(heap, datos[i]);
    heap_desencolar(heap);
  }
  for (size_t i = (k - 1); i + 1 > 0; i--){
    vector[i] = heap_desencolar(heap);
  }
  heap_destruir(heap, NULL);
  return vector;
}

int main(void){
  void *auxiliar[10];
  int vec[10] = {19, 12, 23, 45, 32, 11, 7, 39, 51, 13};
  for (int i = 0; i < 10; i++){
    auxiliar[i] = &vec[i];
  }
  void **vector = top_k(15, auxiliar, 10, comparar);
  for (int i = 0; i < 15; i++){
    if (vector[i])
      printf("%d\n", *(int*)vector[i]);
  }
  free(vector);
  return 0;
}
