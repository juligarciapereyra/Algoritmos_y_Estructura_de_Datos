#include "test_malloc.h"
#include "testing.h"
#include "internal_iterator.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Acá implementa tus tests

bool test_NULL_iterate_function() {
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  dictionary_t *dict = dictionary_create(free);
  iterate(dict, NULL, NULL);
  dictionary_destroy(dict);
  return true;
}

//recibe un array de int, multiplica a value por 2 y lo guarda en el primer lugar libre del array
bool multiply_values(const char *key, void *value, void *arr) {
    int *array = (int *)arr;
    int *val = (int *)value;

    // Buscar el primer lugar libre en el array
    int i = 0;
    while (array[i] != 0) {
        i++;
    }

    // Multiplicar el valor por 2 y guardarlo en el primer lugar libre
    array[i] = (*val) * 2;
    return false;
  }

// agregar true al primer lugar libre del array si value no es NULL
bool add_true(const char *key, void *value, void *arr) {
    bool *array = (bool *)arr;

    // Buscar el primer lugar vacío en el array
    int i = 0;
    while (array[i] != false) {
        i++;
    }

    // Agregar true al primer lugar vacío si el valor no es NULL
    if (value != NULL) {
        array[i] = true;
    }

    return false;
}

bool test_simple_func(){
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  dictionary_t *dict = dictionary_create(NULL);
  char *key = "key1";
  char*value = "hola";
  dictionary_put(dict, key, value);
  char *key2 = "key2";
  char *value2 =  "chau";
  dictionary_put(dict, key2, value2);

  bool *array = calloc(3, sizeof(bool));


  iterate(dict, add_true, array);

  tests_result &= test_assert("el primer valor es true", array[0] == true);
  tests_result &= test_assert("el segundo valor es true", array[1] == true);
  
  free(array);
  dictionary_destroy(dict);

  return tests_result;
}



void print_dict(dictionary_t *dictionary);

bool test_iterate_multiply_values_save_array() {
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  dictionary_t *dict = dictionary_create(free);
  char *key = "key1";
  int *value = malloc(sizeof(int));
  *value = 1;
  dictionary_put(dict, key, value);
  char *key2 = "key2";
  int *value2 = malloc(sizeof(int));
  *value2 = 2;
  dictionary_put(dict, key2, value2);

  int *array = calloc(2, sizeof(int));

  //print_dict(dict);
  iterate(dict, multiply_values, array);

  //ordena el array de menor a mayor
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 2 - i - 1; j++){
      if (array[j] > array[j + 1]){
        int aux = array[j];
        array[j] = array[j + 1];
        array[j + 1] = aux;
      }
    }
  }

  tests_result &= test_assert("el valor es correcto", array[0] == 2);
  tests_result &= test_assert("el valor es correcto", array[1] == 4);

  free(array);
  dictionary_destroy(dict);
  return tests_result;


}

// int main(void) {
//   srand(117);
//   int return_code = 0;
//   return_code += !test_NULL_iterate_function();
//   return_code += !test_simple_func();
//   return_code += !test_iterate_multiply_values_save_array();

//   exit(return_code);
// }
