#include "tp3.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_CAPACITY 16
#define RESIZE_FACTOR 2  // agrandar tabla 
#define LOAD_FACTOR 0.7
#define INITIAL_SEED 4

typedef struct dictionary_pair{
  char *key; 
  void *value;
  bool is_deleted; 
}dictionary_pair_t; 

struct dictionary {
  int size; //la cantidad de elementos que hay en el diccionario
  int capacity; //la capacidad actual de la tabla de hash (tamano del arreglo)
  destroy_f destroy; //funcion para liberar la memoria de los valores almacenados en la tabla de hash
  dictionary_pair_t *table; //el arreglo de elementos del diccionario
};

/*
 * Punto extra de operable dict, suma 3 puntos como máximo.
 */

/*
 * Inserta o pisa en dictionary1 todas las claves y valores que están en dictionary2.
 * Las claves se mantienen independientes entre ambos diccionarios, pero los valores no.
 * (las claves nuevas de agregar dictionary2 en dictionary1 deben ser punteros distintos
 * pero los valores son el mismo puntero).
 * La operación es atómica, si falla dictionary1 queda en el mismo estado que estaba antes del update.
 * Devuelve true si funcionó, false si fayó.
 */

bool dictionary_update(dictionary_t *dictionary1, dictionary_t *dictionary2){
    if(!dictionary2){return false;}

    dictionary_pair_t *table_copy = calloc(dictionary1 -> capacity, sizeof(dictionary_pair_t)); 
    if (!table_copy) {
        return false;
    }

    for(int i = 0; i < dictionary1 -> capacity; i++){
        if(dictionary1 -> table[i].key != NULL){
            table_copy[i].key = dictionary1 -> table[i].key; 
            table_copy[i].value = dictionary1 -> table[i].value; 
            table_copy[i].is_deleted = dictionary1 -> table[i].is_deleted; 
        }
    }
    for(int j = 0; j < dictionary2 -> capacity; j++){
        if(dictionary2 -> table[j].key != NULL){
            if(dictionary_put(dictionary1, dictionary2 -> table[j].key, dictionary2 -> table[j].value)){
                continue;
            }else{
                for(int w = j; w > 0; w--){
                    free(dictionary1 -> table[w].key);
                }
                free(dictionary1 -> table); 
                dictionary1 -> table = table_copy; 
                return false;
            } 
        }
    }
    free(table_copy); 
    return true; 
} 


/*
 * Combina ambos diccionarios en uno nuevo que contiene solo las claves que están presentes en ambos.
 * En todos los casos se conservan los valores del dictionary1.
 * Devuelve NULL si falla.
 */
dictionary_t* dictionary_and(dictionary_t *dictionary1, dictionary_t *dictionary2){
    dictionary_t *dictionary3 = dictionary_create(dictionary1 -> destroy); 
    if(!dictionary3) {return NULL;}
    
    for(int i = 0; i < dictionary1 -> capacity; i++){
        for(int j = 0; j < dictionary2 -> capacity; j++){
            if((dictionary1 -> table[i].key) && (dictionary2 -> table[j].key)){
                if(strcmp(dictionary1->table[i].key, dictionary2->table[j].key) == 0){
                    if(dictionary_put(dictionary3, dictionary1 -> table[i].key, dictionary1 -> table[i].value)){
                        continue; 
                    }else{
                        for(int w = j; w > 0; w--){
                            free(dictionary1 -> table[w].key);
                        }
                        return NULL; 
                    }
                }
            
            }
        }
    } 
    return dictionary3; 
}

/*
 * Combina ambos diccionarios en uno nuevo que contiene todas las claves de ambos.
 * En caso de que ambos tengan una misma clave se conserva el valor de dictionary1.
 * Devuelve NULL si falla.
 */
dictionary_t* dictionary_or(dictionary_t *dictionary1, dictionary_t *dictionary2){
    dictionary_t *dictionary3 = dictionary_create(dictionary1 -> destroy); 
    if(!dictionary3) {return NULL;}

    for(int i = 0; i < dictionary1 -> capacity; i++){
        for(int j = 0; j < dictionary2 -> capacity; j++){
            if((dictionary1 -> table[i].key) && (dictionary2 -> table[j].key)){
                if(strcmp(dictionary1->table[i].key, dictionary2->table[j].key) == 0){
                    if(dictionary_put(dictionary3, dictionary1 -> table[i].key, dictionary1 -> table[i].value)){
                        continue; 
                    }else{
                        for(int w = j; w > 0; w--){
                            free(dictionary1 -> table[w].key);
                        }
                        return NULL; 
                    }
                }else{
                    if((!dictionary_put(dictionary3, dictionary1 -> table[i].key, dictionary1 -> table[i].value)) || (!dictionary_put(dictionary3, dictionary2 -> table[j].key, dictionary2 -> table[j].value))){
                        for(int w = j; w > 0; w--){
                            free(dictionary1 -> table[w].key);
                        }
                        return NULL;
                    }
                }
            }
        }
    } 
    return dictionary3; 
}


/*
 * Devuelve true si ambos diccionarios son iguales. Dos diccionarios son iguales sí:
 *  - Las claves son iguales aunque puedan tener distinta posición en memoria.
 *  - Los values son los mismos punteros para cada clave
 *  - Tienen la misma cantidad de claves
 */
bool dictionary_equals(dictionary_t *dictionary1, dictionary_t *dictionary2){
    for(int i = 0; i < dictionary1 -> capacity; i++){
        for(int j = 0; j < dictionary2 -> capacity; j++){
            if((dictionary1 -> table[i].key) && (dictionary2 -> table[j].key)){
                if((strcmp(dictionary1->table[i].key, dictionary2->table[j].key) == 0) && (dictionary1 -> table[i].value == dictionary2 -> table[j].value) && (dictionary1 -> size == dictionary2 -> size)){
                    return true;
                }
            }
        }
    }
    return false; 
}
