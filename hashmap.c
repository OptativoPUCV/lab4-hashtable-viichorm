#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

/*

Calcula la posición utilizando la función hash.
Itera hasta encontrar una casilla disponible.
Verifica si la clave ya existe en el mapa, en cuyo caso no inserta.
Inserta el nuevo par en la casilla encontrada.
Actualiza el índice current y el tamaño del mapa según corresponda.

*/



void insertMap(HashMap * map, char * key, void * value) {
    if(map==NULL || key==NULL) return;
  long position = hash(key, map->capacity);
  while(map->buckets[position]!=NULL && map->buckets[position]->key!=NULL){

    if (strcmp(map->buckets[position]->key, key) == 0){
      return;
    }
  }

  position = (position + 1) % map->capacity;

  map->buckets[position] = createPair(key, value);

  map->current = position;

  map->size++;

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}

/*
Se declara una variable de tipo HashMap llamada map.
Se asigna memoria dinámica para la estructura HashMap.
Se inicializa el arreglo de buckets con casillas nulas.
Se inicializan las variables size, capacity y current.
Se retorna el mapa creado.
*/

HashMap * createMap(long capacity) {

    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
  if (map == NULL) {
    exit(EXIT_FAILURE);
  }

  map->buckets = (Pair **)calloc(capacity, sizeof(Pair *));
  if (map->buckets == NULL){
    exit(EXIT_FAILURE);
  }


  map->size = 0;
  map->capacity = capacity;
  map->current = -1;
  
    return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
