#include "tp1.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 


/*
 * Determina si un número es primo.
 */

//cambiar que 1 no es primo
bool is_prime(int x){
    int count = 0; 

    for(int i=1; i<=x; i++){
        if((x % i) == 0){
            count++; 
        }
    }
    if(count > 2){
        return false; 
    }
    return true; 
} 

/*
 * Dado el volumen de un deposito D y el volumen de un producto V
 * la función calcula cuantos productos entran en el depósito.
 */
int storage_capacity(float d, float v){
    if (v == 0){
        return 0;
    }
    return (int) (d / v);  
}

/*
 * Intercambia dos valores de enteros.
 */
void swap(int *x, int *y){
    if (!x && !y){ 
        return;
    }
    int a = *x;
    *x = *y; 
    *y = a;
    return;
}

/*
 * Devuelve el máximo de un arreglo de enteros.
 */
int array_max(const int *array, int length){ 

    int number_max = array[0];

    for(int i=1; i < length; i++){
        if(array[i] > number_max){
            number_max = array[i];
        }
    }
    return number_max;
}

/*
 * Aplica la función a cada elemento de un arreglo de enteros.
 */
void array_map(int *array, int length, int f(int)){  
    if(!f){
        return; 
    }
    for(int i=0; i<length; i++){
        array[i] = f(array[i]); 
    }
    return;
}

/*
 * Copia un arreglo de enteros en memoria dinámica.
 * Si el arreglo es NULL devuelve NULL.
 */
int *copy_array(const int *array, int length){
    if(!array){
        return NULL;
    }

    int *new_array = (int*) malloc(length * sizeof(int)); 
    if(!new_array){
        return NULL; 
    }

    for(int i=0; i<length; i++){
        new_array[i] = array[i]; 
    }

    return new_array;
}

/*
 * Hace bubble sort sobre un arreglo de enteros ascendentemente.
 * Si el arreglo es NULL, no hace nada.
 */
void bubble_sort(int *array, int length){
    if(!array){
        return; 
    }
    for(int i=0; i<length; i++){
        bool swapped = false; 
        for(int j=0; j<(length-1-i); j++){
            if(array[j]>array[j+1]){
                swap(&array[j], &array[j+1]); 
                swapped = true; 
            }
        }
        if(swapped == false){
            break;
        }
    }

    return; 
}

/*
 * Determina si dos arreglos de enteros son identicamente iguales.
 * En el caso de que alguno sea NULL solo devuelve true si el otro tambien lo es.
 */
bool array_equal(const int *array1, int length1, const int *array2, int length2){

    if(!array1 && !array2){
        return true;
    }
    else if(!array1 || !array2){
        return false;
    }
    
    int count = 0; 
    if(length1 == length2){
        for(int i=0; i<length1; i++){
            if(array1[i] == array2[i]){
                count++; 
            }   
        }
        if(count != length1){
            return false; 
        }
        return true; 
    }
    return false; 
}


/*
 * Determina si dos arrays de enteros son análogos a un anagrama para textos (en algun orden particular, son el mismo arreglo).
 * Si alguno es NULL devuelve false.
 */
bool integer_anagrams(const int *array1, int length1, const int *array2, int length2){ // chequear
    if((!array1) || (!array2) || (length1 != length2)){
        return false; 
    }

    int *new_array1 = copy_array(array1, length1); 
    int *new_array2 = copy_array(array2, length2); 

    bubble_sort(new_array1, length1); 
    bubble_sort(new_array2, length2); 

    bool result = array_equal(new_array1, length1, new_array2, length2); 

    free(new_array1); 
    free(new_array2);

    return result;  

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
int **copy_array_of_arrays(const int **array_of_arrays, const int *array_lengths, int array_amount){  //Usar funcion de copy hecha previamente?
    if(!array_of_arrays || !array_lengths){ // preguntar si con esto se atrapa el error
        return NULL;
    }

    int **copy = (int**) malloc(sizeof(int*) * array_amount); 
    if(!copy){
        return NULL;
    }
    

    for(int i=0; i<array_amount; i++){
        copy[i] = copy_array(array_of_arrays[i], array_lengths[i]);
        
        if(!copy[i] && array_of_arrays[i]){ 
            while(i--){
                free(copy[i]);
            }
            free(copy); 
            return NULL; 
        }          
        
    }
    return copy;
}

/*
 * Libera toda la memoria asociada a un arreglo de arreglos.
 *
 * array_of_arrays: un arreglo de punteros a arreglos de enteros
 * array_lenghts: un arreglo con los largos de cada arreglo en array_of_arrays
 * array_amount: la cantidad de arreglos
 */
void free_array_of_arrays(int **array_of_arrays, int *array_lenghts, int array_amount){
    if(!array_of_arrays || !array_lenghts){
        return; 
    }
    for(int i=0; i<array_amount; i++){
        free(array_of_arrays[i]); 
        }
    
    free(array_of_arrays);
    free(array_lenghts);  
    return;
}


