#include <stdio.h>
#include <stdlib.h>
#include "tp1.h"

/*
 * Determina si un número es primo.
 */

bool is_prime(int x){
   if (x == 2) {
    return true;
   }

   if (x <= 1 || x % 2 == 0) {
    return false;
   }

   for (int i = 3; i*i <= x; i+=2) { //salteo los numeros pares
        if (x % i == 0) {
            return false;
        }
   }
   return true;
}

/*
 * Dado el volumen de un deposito D y el volumen de un producto V
 * la función calcula cuantos productos entran en el depósito.
 */
int storage_capacity(float d, float v){
    if (v > d) {
        return 0;
    }
    return (int) (d / v);
}

/*
 * Intercambia dos valores de enteros.
 */
void swap(int *x, int *y) {
    if (x && y) { //me aseguro de que no sean NULL
        int aux = *x;
        *x = *y;
        *y = aux;
    }
    return;
    
}

/*
 * Devuelve el máximo de un arreglo de enteros.
 */
int array_max(const int *array, int length){
    if (array && length > 0) {
        int max = array[0];
        for (int i = 1; i < length;  i++) {
            if (array[i] > max) {
                max = array[i];
            }
        }
        return max;
    }
    return -1;
}

/*
 * Aplica la función a cada elemento de un arreglo de enteros.
 */
void array_map(int *array, int length, int f(int)) {
    if (array && f) {
        for (int i = 0; i < length; i++) {
            array[i] = f(array[i]);
        }
    }
    return;
}

/*
 * Copia un arreglo de enteros en memoria dinámica.
 * Si el arreglo es NULL devuelve NULL.
 */
int *copy_array(const int *array, int length){
    if (array) {
        int *dynamic_array = (int *) malloc(sizeof(int)*length);
        if (!dynamic_array) { //si no se pudo hacer el malloc
            return NULL;
        }
        for (int i = 0; i < length; i++) {
            dynamic_array[i] = array[i];
            
        }
        return dynamic_array;   
    }
    return NULL;
}

/*
 * Hace bubble sort sobre un arreglo de enteros ascendentemente.
 * Si el arreglo es NULL, no hace nada.
 */
void bubble_sort(int *array, int length){
    if (array) {
        int aux;
        for (int i = 1; i < length; i++) {
            for (int j = 0; j < length - i; j++) {
                if (array[j] > array[j+1]) {
                    aux = array[j];
                    array[j] = array[j+1]; 
                    array[j+1] = aux;
                }
            }
        }
    }
    return;
}

/*
 * Determina si dos arreglos de enteros son identicamente iguales.
 * En el caso de que alguno sea NULL solo devuelve true si el otro tambien lo es.
 */
bool array_equal(const int *array1, int length1,
                 const int *array2, int length2){

    if (!array1 && !array2) { //ambos son null
        return true;
    }

    if (array1 && array2) {
        if(length1 == length2) {
            for (int i = 0; i < length1; i++) {
                if (array1[i] != array2[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    return false;
}

/*
 * Determina si dos arrays de enteros son análogos a un anagrama para textos (en algun orden particular, son el mismo arreglo).
 * Si alguno es NULL devuelve false.
 */


bool integer_anagrams(const int *array1, int length1,
                      const int *array2, int length2){
    if (array1 && array2) {
        if (length1 == length2) {
            int *array1d = copy_array(array1, length1);
            int *array2d = copy_array(array2, length2);
            bubble_sort(array1d, length1);
            bubble_sort(array2d, length2); 
            for (int i = 0; i < length1; i++) {
                if (array1d[i] != array2d[i]) {
                    free(array1d);
                    free(array2d);
                    return false;
                }
            }
            free(array1d);
            free(array2d);
            return true;
        }
    }
    return false;
}

/*
 * Copia un arreglo de arreglos de enteros en memoria dinámica.
 * Si alguno de ellos en NULL, continua siendo NULL.
 * Si el arreglo de arreglos es NULL, devuelve NULL.
 *
 * array_of_arrays: un arreglo de punteros a arreglos de enteros
 * array_lenghts: un arreglo con los largos de cada arreglo en array_of_arrays
 * array_amount: la cantidad de arreglos
 */

int **copy_array_of_arrays(const int **array_of_arrays,const int *array_lenghts, int array_amount){ 
    if (array_of_arrays && array_lenghts) {
        int **dynamic_m = (int **) malloc(sizeof(int *)*array_amount);
        if (dynamic_m) {
            for (int i = 0; i < array_amount; i++) {
                dynamic_m[i] = (int *) malloc(sizeof(int)*(array_lenghts[i])); 
                if (!dynamic_m[i]) {
                    for (int j = 0; j < i; j++) {
                        free(dynamic_m[j]);
                    }
                    free(dynamic_m);
                    return NULL;
                }
                
                for (int j = 0; j < array_lenghts[i]; j++) {
                    if (!array_of_arrays[i]) {
                        free(dynamic_m[i]);
                        dynamic_m[i] = NULL;
                        
                    } else {
                        dynamic_m[i][j] = array_of_arrays[i][j];
                    }
                    
                }
            }
            return dynamic_m;
        }
    }
    
    return NULL;
}

/*
 * Libera toda la memoria asociada a un arreglo de arreglos.
 *
 * array_of_arrays: un arreglo de punteros a arreglos de enteros
 * array_lenghts: un arreglo con los largos de cada arreglo en array_of_arrays
 * array_amount: la cantidad de arreglos
 */
void free_array_of_arrays(int **array_of_arrays, int *array_lenghts, int array_amount){
    if (array_of_arrays && array_lenghts) {
        for(int i = 0; i < array_amount; i ++) {
            if (array_of_arrays[i]) {
                free(array_of_arrays[i]);
            }
        }
        free(array_lenghts); 
        free(array_of_arrays);
    }
    return;
}
    

