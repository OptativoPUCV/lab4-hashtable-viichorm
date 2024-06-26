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
Explicacion de la operacion (ejercicio 2):

Calcula la posición utilizando la función hash.
Itera hasta encontrar una casilla disponible.
Verifica si la clave ya existe en el mapa, en cuyo caso no inserta.
Inserta el nuevo par en la casilla encontrada.
Actualiza el índice current y el tamaño del mapa según corresponda.

*/



void insertMap(HashMap * map, char * key, void * value) {
    if(map==NULL || key==NULL || value==NULL) return;
  
  long position = hash(key, map->capacity);
  while(map->buckets[position] !=   NULL && map->buckets[position]->key != NULL){

    if (strcmp(map->buckets[position]->key, key) == 0){
      return;
    }

    position = (position + 1) % map->capacity;
  }

  map->buckets[position] = createPair(key, value);

  map->current = position;

  map->size++;

}


// Explciacion de la operacion (ejercicio 6):

// a - Crear una variable auxiliar para mantener el arreglo map->buckets (old_buckets)
// b - Duplicar el valor de la variable capacity
// c - Asignar a map->buckets un nuevo arreglo con la nueva capacidad
// d - Reinicializar size a 0
// e - Insertar los elementos del arreglo old_buckets en el mapa
// Liberar la memoria del arreglo antiguo
// porfin >,< .....
void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
  
  Pair ** old_buckets = map->buckets;
  long old_capacity = map->capacity;

  
  map->capacity *= 2;
  map->buckets = (Pair **)calloc(map->capacity, sizeof(Pair *));
  map->size = 0;

  
  for (long i = 0; i < old_capacity; i++) {
      if (old_buckets[i] != NULL && old_buckets[i]->key != NULL) {
          insertMap(map, old_buckets[i]->key, old_buckets[i]->value);
      }
  }

  
  free(old_buckets);
  }

/* Ojala lean las explicaciones... aunque no tendria sentido si quien revisa esto seguramente se lo sepa de memoria...

Explciacion de la operacion (ejercicio 1):

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

/*
Explicacion operacion (ejercicio 4):

Calcula la posición utilizando la función hash.
Itera hasta encontrar la clave o una casilla nula.
Si encuentra la clave, invalida el par asignando NULL a la clave.
Actualiza el índice current si se encontró la clave.
Decrementa el tamaño del mapa.

*/

void eraseMap(HashMap * map,  char * key) {    
  // long position = hash(char *key, long capacity); //(15:01) tambien sirve asi?... :O
  // ok, nvm no se puede xd

  long position = hash(key, map->capacity);

  while (map->buckets[position] != NULL) {
    if (strcmp(map->buckets[position]->key, key) == 0){

      map->buckets[position]->key = NULL;
      map->current = position;
      map -> size--;
      return;
    }
    position = (position + 1) % map->capacity;
  }
}

/* 

Explicacion de operacion (ejercicio 3):

Calcula la posición utilizando la función hash.
Itera hasta encontrar la clave o una casilla nula.
Si encuentra la clave, retorna el par asociado.
Si llega a una casilla nula, retorna NULL.
Actualiza el índice current si se encontró la clave.

*/


Pair * searchMap(HashMap * map,  char * key) {   
    if(map==NULL || key==NULL) return NULL;

  long position = hash(key, map->capacity);
  while(map->buckets[position] != NULL){

    if (strcmp(map->buckets[position]->key, key) == 0){
      map->current = position;
      return map->buckets[position];
    }

      position = (position + 1) % map->capacity;

    // se me brickeaba el replit si me faltaba esta linea xD!, con razon nunca me daba en console jadjajgaskdf
  }


    return NULL; //un return null mas... -.-
}

//Explicacion de operacion (ejercicio 5.1):

// Verifica si el mapa está correctamente inicializado y no está vacío.
// Itera sobre los buckets del mapa hasta encontrar el primer bucket no vacío.
// Actualiza el índice current del mapa al índice del bucket encontrado.
// Devuelve el primer par encontrado en el bucket.

Pair * firstMap(HashMap * map) {
    if (map == NULL || map->buckets == NULL) 
        return NULL;

    for (long i = 0; i < map->capacity; i++) {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i; 
            return map->buckets[i];
        }
    }

    return NULL; 
}

//Explicacion de operacion (ejercicio 5.2):

// Verificar si el mapa o los buckets son nulos
// Mover el índice current al siguiente par válido
// Actualizar el índice current
// Si no hay más pares válidos, retornar NULL

Pair * nextMap(HashMap * map) {
    if (map == NULL || map->buckets == NULL) 
        return NULL;

    
    for (long i = map->current + 1; i < map->capacity; i++) {
        if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
            map->current = i; 
            return map->buckets[i];
        }
    }

    return NULL; 
}
