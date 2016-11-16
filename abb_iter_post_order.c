#include "abb.h"



int main(void){
  bool es_hijo_izq(nodo_abb_t *desapilado, nodo_abb_t *tope_nuevo){
    return desapilado == tope_nuevo->izq;
  }

  void abb_traza_izq(pila_t *pila, nodo_abb_t *nodo_abb){
  	if(!nodo_abb)
  		return;
  	pila_apilar(pila, nodo_abb);
    if(nodo_abb->izq) abb_traza_izq(pila, nodo_abb->izq);
    else abb_traza_izq(pila, nodo_abb->der);
  }

  abb_iter_t *abb_iter_post_crear(const abb_t *arbol){
  	abb_iter_t *iter = malloc(sizeof(abb_iter_t));
  	if (!iter) return NULL;
  	iter->pila = pila_crear();
  	if(!iter->pila){
  		free(iter);
  		return NULL;
  	}
  	iter->arbol = arbol;
  	abb_traza_izq(iter->pila, iter->arbol->raiz);
  	return iter;
  }

  bool abb_iter_post_al_final(const abb_iter_t *iter){
  	return pila_esta_vacia(iter->pila);
  }

  const char *abb_iter_post_ver_actual(const abb_iter_t *iter){
  	if(abb_iter_in_al_final(iter))
  		return NULL;
    nodo_abb_t* tope = pila_ver_tope(iter->pila);
  	return tope->clave;
  }

  bool abb_iter_post_avanzar(abb_iter_t *iter){
  	if(abb_iter_in_al_final(iter))
  		return false;
    if(es_hijo_izq(pila_desapilar(iter->pila), pila_ver_tope(iter->pila)))
      abb_traza_izq(iter->pila, tope_nuevo->der);
  	return true;
  }

  void abb_iter_post_destruir(abb_iter_t* iter){
  	pila_destruir(iter->pila);
  	free(iter);
  }

  /******************************************************************
   *			               ITERADOR INTERNO ABB                       *
   ******************************************************************/

  void abb_post_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
  	pila_t* pila = pila_crear();
  	if(!pila)
  		return;
  	abb_traza_izq(pila, arbol->raiz);
  	nodo_abb_t *actual = pila_desapilar(pila);
  	while(actual && visitar(actual->clave, actual->dato, extra)){
      if(es_hijo_izq(actual, pila_ver_tope(pila))
        abb_traza_izq(pila, actual->der);
  		actual = pila_desapilar(pila);
  	}
  	pila_destruir(pila);
  }

}
