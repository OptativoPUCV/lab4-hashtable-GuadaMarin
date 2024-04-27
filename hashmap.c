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


void insertMap(HashMap * map, char * key, void * value) {
  
  long pos = hash(key, map->capacity);
  while(map->buckets[pos]!=NULL && map->buckets[pos]->key!=NULL){
    if (is_equal(map->buckets[pos]->key, key)) return;
    pos= (pos + 1)% map->capacity;
  }
  if(map->buckets[pos]==NULL){
    map->buckets[pos]=createPair(key,value);
    map->size++;
    if ((double)map->size/ map->capacity >0.7) enlarge(map);
  }
   


}

void enlarge(HashMap * map) {
  long new_capacity= map->capacity*2;
  Pair** new_buckets= (Pair **)calloc(new_capacity, sizeof(Pair *));
  for(long i=0; i<map->capacity; i++){
    Pair * temp= map->buckets[i];
    if(temp!= NULL && temp->key != NULL){
      long new_pos= hash(temp->key, new_capacity);
      while (new_buckets[new_pos]!=NULL){
        new_pos= (new_pos +1) % new_capacity; 
      }
      new_buckets[new_pos]= temp;
    }
  }
  map->buckets= new_buckets;
  map->capacity= new_capacity;
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap * newMap= (HashMap*) malloc(sizeof(HashMap));
  newMap->buckets= (Pair**) malloc(sizeof(Pair*)*capacity);
  newMap->size=0;
  newMap->capacity=capacity;
  newMap->current=-1;

  return newMap;
}

void eraseMap(HashMap * map,  char * key) { 
  long pos= hash(key, map->capacity);
  while(map->buckets[pos]!=NULL){
    if(map->buckets[pos]->key != NULL && is_equal(map->buckets[pos]->key, key)){
      //free(map->buckets[pos]);
      map->buckets[pos]= NULL;
      map->size--;
    }
    pos= (pos+1) %map->capacity;
    while(map->buckets[next] != NULL)
  }


}

Pair * searchMap(HashMap * map,  char * key) {   
  long pos= hash(key, map->capacity);
  while(map->buckets[pos]!=NULL){
    if (strcmp(map-> buckets[pos]-> key, key)==0){
      map -> current = pos;
      return map -> buckets[pos];
    }
    pos= (pos + 1)% map->capacity;
  }
    return NULL;
}

Pair * firstMap(HashMap * map) {
  for (long i=0; i<  map->capacity; i++){
    if(map->buckets[i]!=NULL && map->buckets[i]->key != NULL){
      map->current= i;
      return map->buckets[i];
    }
  }

    return NULL;
}

Pair * nextMap(HashMap * map) {
  if(map->current == -1) return NULL;
  for(long i= map->current+1; i< map->capacity; i++){
    if(map->buckets[i]!=NULL && map->buckets[i]->key != NULL){
      map->current= i;
      return map->buckets[i];
    }
  }

    return NULL;
}



