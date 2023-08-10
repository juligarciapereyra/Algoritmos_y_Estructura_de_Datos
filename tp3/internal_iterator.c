#include "internal_iterator.h"

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
 * Punto extra de internal iterator, suma 1 punto como máximo.
 */


/*
 * Itera cada par clave-valor del diccionario pasandoselo a la función de iteración.
 * Recibe un parámetro extra que puede contener cualquier cosa para permitirle a la función guardar resultados.
 */
void iterate(dictionary_t* dict, iterate_f f, void* extra){
    for(int i = 0; i < dict -> capacity; i++){
        if((f) && (dict -> table[i].key)){
            f(dict -> table[i].key, dict -> table[i].value, extra); 
        }
    }
    return;
}
