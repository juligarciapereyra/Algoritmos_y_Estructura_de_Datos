#include "test_malloc.h"
#include "testing.h"
#include "operable_dict.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Acá implementa tus tests

void print_dict(dictionary_t *dict);


bool test_NULL_update() {
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  dictionary_t *dict1 = dictionary_create(NULL);
  dictionary_t *dict2 = NULL;

  tests_result &= test_assert("dictionary_update devuelve false si el segundo diccionario es NULL", !dictionary_update(dict1, dict2));

  dict2 = dictionary_create(NULL);

  dictionary_destroy(dict1);
  dictionary_destroy(dict2);

  return tests_result;
}

bool test_simple_update() {
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);

  bool tests_result = true;
  dictionary_t *dict1 = dictionary_create(NULL);
  dictionary_t *dict2 = dictionary_create(NULL);

  char *key1 = "key1";
  char *key2 = "key2";
  char *key3 = "key3";

  char *value1 = "value1";
  char *value2 = "value2";
  char *value2mod = "value2mod";
  char *value3 = "value3";
  dictionary_put(dict1, key1, value1);
  dictionary_put(dict1, key2, value2);

  dictionary_put(dict2, key2, value2mod);
  dictionary_put(dict2, key3, value3);
  bool err;
  tests_result &= test_assert("dictionary_update devuelve true si el update fue exitoso", dictionary_update(dict1, dict2));
  tests_result &= test_assert("dictionary_update no modifica key1", strcmp(dictionary_get(dict1, key1, &err), value1) == 0);
  tests_result &= test_assert("dictionary_update modifica key2", strcmp(dictionary_get(dict1, key2, &err), value2mod) == 0);
  tests_result &= test_assert("dictionary_update agrega key3", strcmp(dictionary_get(dict1, key3, &err), value3) == 0);
  dictionary_destroy(dict1);
  dictionary_destroy(dict2);

  return tests_result;
}

bool test_simple_and(){
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  dictionary_t *dict1 = dictionary_create(NULL);
  dictionary_t *dict2 = dictionary_create(NULL);

  char *key1 = "key1";
  char *key2 = "key2";
  char *key3 = "key3";

  char *value1 = "value1";
  char *value2 = "value2";
  char *value2mod = "value2mod";
  char *value3 = "value3";

  dictionary_put(dict1, key1, value1);
  dictionary_put(dict2, key3, value3);

  bool err;

  dictionary_t *dict3 = dictionary_and(dict1, dict2);
  tests_result &= test_assert("dictionary_and devuelve un diccionario", dict3 != NULL);
  tests_result &= test_assert("dictionary_and devuelve un diccionario vacío si no hay claves en común", dictionary_size(dict3) == 0);

  dictionary_put(dict1, key2, value2);
  dictionary_put(dict2, key2, value2mod);


  dictionary_destroy(dict3);

  dict3 = dictionary_and(dict1, dict2);

  tests_result &= test_assert("dictionary_and devuelve un diccionario con las claves en común", dictionary_size(dict3) == 1);

  tests_result &= test_assert("dictionary_and devuelve un diccionario con los valores correctos", strcmp(dictionary_get(dict3, key2, &err), value2) == 0);

  dictionary_destroy(dict1);
  dictionary_destroy(dict2);
  dictionary_destroy(dict3);

  return tests_result;
}


bool test_simple_or(){
   printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bool tests_result = true;
  dictionary_t *dict1 = dictionary_create(NULL);
  dictionary_t *dict2 = dictionary_create(NULL);

  char *key1 = "key1";
  char *key2 = "key2";
  char *key3 = "key3";

  char *value1 = "value1";
  char *value2 = "value2";
  char *value2mod = "value2mod";
  char *value3 = "value3";

  dictionary_put(dict1, key1, value1);
  dictionary_put(dict1, key2, value2);

  dictionary_put(dict2, key2, value2mod);
  dictionary_put(dict2, key3, value3);

  dictionary_t *dict3 = dictionary_or(dict1, dict2);

  bool err;

  tests_result &= test_assert("dictionary_or devuelve un diccionario", dict3 != NULL);

  tests_result &= test_assert("dictionary_or devuelve un diccionario con las claves de ambos", dictionary_size(dict3) == 3);

  tests_result &= test_assert("dictionary_or devuelve un diccionario con los valores correctos", strcmp(dictionary_get(dict3, key1, &err), value1) == 0);

  dictionary_destroy(dict1);
  dictionary_destroy(dict2);
  dictionary_destroy(dict3);

  return tests_result;
}

// int main(void) {
//   srand(117);
//   int return_code = 0;
//   return_code += !test_NULL_update();
//   return_code += !test_simple_update();
//   return_code += !test_simple_and();
//   return_code += !test_simple_or();
//   exit(return_code);
// }