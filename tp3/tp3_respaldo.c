// #include "tp3.h"
// #include <stdlib.h>
// #include <stdint.h>
// #include <string.h>
// #include <stdio.h>

// #define INITIAL_CAPACITY 16
// #define RESIZE_FACTOR 2  // agrandar tabla 
// #define LOAD_FACTOR 0.7
// #define INITIAL_SEED 4

// struct dictionary {
//   int size; //la cantidad de elementos que hay en el diccionario
//   int capacity; //la capacidad actual de la tabla de hash (tamano del arreglo)
//   destroy_f destroy; //funcion para liberar la memoria de los valores almacenados en la tabla de hash
//   dictionary_pair_t *table; //el arreglo de elementos del diccionario
// };

// struct dictionary_pair{
//   char *key; 
//   void *value;
//   bool is_deleted; 
// };

// uint32_t murmur_hash(const char *key, uint32_t len, uint32_t seed) {
//     static const uint32_t c1 = 0xcc9e2d51;
//     static const uint32_t c2 = 0x1b873593;
//     static const uint32_t r1 = 15;
//     static const uint32_t r2 = 13;
//     static const uint32_t m = 5;
//     static const uint32_t n = 0xe6546b64;

//     uint32_t hash = seed;

//     const int nblocks = len / 4;
//     const uint32_t *blocks = (const uint32_t *) key;
//     int i;
//     for (i = 0; i < nblocks; i++) {
//         uint32_t k = blocks[i];
//         k *= c1;
//         k = (k << r1) | (k >> (32 - r1));
//         k *= c2;

//         hash ^= k;
//         hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
//     }

//     const uint8_t *tail = (const uint8_t *) (key + nblocks * 4);
//     uint32_t k1 = 0;

//     switch (len & 3) {
//     case 3:
//         k1 ^= tail[2] << 16;
//     case 2:
//         k1 ^= tail[1] << 8;
//     case 1:
//         k1 ^= tail[0];

//         k1 *= c1;
//         k1 = (k1 << r1) | (k1 >> (32 - r1));
//         k1 *= c2;
//         hash ^= k1;
//     }

//     hash ^= len;
//     hash ^= (hash >> 16);
//     hash *= 0x85ebca6b;
//     hash ^= (hash >> 13);
//     hash *= 0xc2b2ae35;
//     hash ^= (hash >> 16);

//     return hash;
// }

// char* strdup(const char* str) {
//   size_t len = strlen(str) + 1;
//   char* new_str = malloc(len);
//   if (new_str != NULL) {
//     memcpy(new_str, str, len);
//   }
//   return new_str;
// }


// dictionary_t *dictionary_create(destroy_f destroy) { 
//   dictionary_t *dict = (dictionary_t*) malloc(sizeof(dictionary_t)); 
//   if(!dict){ return NULL; }
  
//   dict -> size = 0; 
//   dict -> capacity = INITIAL_CAPACITY; 
//   dict -> destroy = destroy; 

//   dict -> table = calloc(dict -> capacity, sizeof(dictionary_pair_t)); 
  
//   if(!dict -> table){
//     free(dict); 
//     return NULL;
//   }

//   return dict; 
   
// }


// unsigned long int index_hash(const char *key, int capacity){
//   unsigned long int index = (murmur_hash(key, (uint32_t)strlen(key), (uint32_t)INITIAL_SEED) % (uint32_t)capacity); 
//   return index; 
// }


// unsigned long int index_key(const char *key, int capacity, dictionary_t *dictionary){
//   if(dictionary -> size != 0){
//     unsigned long int index = (murmur_hash(key, (uint32_t)strlen(key), (uint32_t)INITIAL_SEED) % (uint32_t)capacity);

//     for(int i = 0; i < dictionary -> capacity; i++){
//       unsigned long int position = (index + i) % dictionary->capacity;

//       if((dictionary->table[position].key != NULL) && (strcmp(dictionary->table[position].key, key) == 0)){
//         return position; 
//       }else if((dictionary -> table[position].is_deleted == false) && (dictionary -> table[position].key == NULL)){
//         return -1;
//       }
//     }
//   }
  
//   return -1; 
// }



// bool rehash_function(dictionary_t *dictionary) {
//   int capacity_2 = dictionary->capacity * RESIZE_FACTOR;
//   dictionary_pair_t *table_2 = calloc(capacity_2, sizeof(dictionary_pair_t)); 
//   if (!table_2) {
//     return false;
//   }

//   for (int i = 0; i < dictionary->capacity; i++) {
//     if (dictionary->table[i].key != NULL) {
//       unsigned long int index = index_hash(dictionary->table[i].key, capacity_2);

//       for(int j = 0; j < dictionary -> capacity; j++){
//         unsigned long int position = (index + j) % capacity_2;

//         if(table_2[position].key == NULL){
//           table_2[position].key = dictionary->table[i].key;  
//           table_2[position].value = dictionary->table[i].value;
//           break;
  
//         }  
//       }
//     }
//   }

//   free(dictionary->table);
//   dictionary -> table = table_2; 
//   dictionary -> capacity = capacity_2;
//   return true; 
// }


// bool dictionary_put(dictionary_t *dictionary, const char *key, void *value){
//   if(dictionary -> size >= ((double)LOAD_FACTOR * dictionary -> capacity)){
//     if(!rehash_function(dictionary)){
//       return false;
//     }
//   }

//   unsigned long int index = index_hash(key, dictionary -> capacity);  
//   unsigned long int pos = -1; 
  
//   for(int i = 0; i < dictionary -> capacity; i++){
//     unsigned long int position = (index + i) % dictionary->capacity;

//     if((dictionary -> table[position].key == NULL)&& (dictionary -> table[position].is_deleted == false)){
//       char *new_key = strdup(key);
//         if(!new_key){return false;}

//       if(pos == -1){
//         dictionary->table[position].key = new_key;
//         dictionary -> table[position].value = value; 
//         dictionary -> size++; 
//         return true;
//       }else{
//         dictionary->table[pos].key = new_key;
//         dictionary -> table[pos].value = value; 
//         dictionary -> size++; 
//         return true;
//       }

//     }else if((dictionary -> table[position].key == NULL) && (dictionary -> table[position].is_deleted == true)){
//       if(pos == -1){
//         pos = position;  
//       }
    
//     }else if(strcmp(dictionary->table[position].key, key) == 0){//dictionary_contains(dictionary, key)){
//       printf("pase el contains\n");
//       if (dictionary->destroy) {dictionary -> destroy(dictionary -> table[position].value);}
//       printf("borre bien\n");
//       dictionary -> table[position].value = value; 
//       printf("cambie el valor bien\n");
//       return true;  
//     }
//   }
//   return false; 
// } 


// // void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
// //   size_t index = index_hash(key, dictionary -> capacity); 

// //   for(int i = 0; i < dictionary -> capacity; i++){
// //     size_t position = (index + i) % dictionary->capacity;

// //     if((dictionary->table[position].key != NULL) && (strcmp(dictionary->table[position].key, key) == 0)){
// //       (*err) = false; 
// //       return dictionary -> table[position].value; 

// //     }else if((dictionary -> table[position].is_deleted == false) && (dictionary -> table[position].key == NULL)){
// //       (*err) = true; 
// //       return NULL;
// //     }
// //   }
// //   (*err) = true; 
// //   return NULL; 
// // }

// void *dictionary_get(dictionary_t *dictionary, const char *key, bool *err) {
//   unsigned long int index = index_key(key, dictionary -> capacity, dictionary); 
//   if(index == -1){
//     (*err) = true;
//     return NULL; 
//   }
//   (*err) = false;  
//   return dictionary -> table[index].value;   
// }

// // bool dictionary_delete(dictionary_t *dictionary, const char *key) {
// //   size_t index = index_hash(key, dictionary -> capacity); 

// //   if(dictionary -> size != 0){
// //     for(int i = 0; i < dictionary -> capacity; i++){
// //       size_t position = (index + i) % dictionary->capacity;

// //       if((dictionary->table[position].key != NULL) && (strcmp(dictionary->table[position].key, key) == 0)){
// //         free(dictionary -> table[position].key); 
// //         dictionary -> table[position].key = NULL; 
      
// //       if(dictionary -> destroy != NULL){
// //           dictionary -> destroy(dictionary -> table[position].value);
// //         }

// //         dictionary -> table[position].value = NULL; 
// //         dictionary -> table[position].is_deleted = true; 
// //         dictionary -> size --; 
// //         return true; 

// //       }else if((dictionary -> table[position].is_deleted == false) && (dictionary -> table[position].key == NULL)){
// //         return false;
// //       }
// //     }
// //   }
// //   return false; 
// // }


// bool dictionary_delete(dictionary_t *dictionary, const char *key) {
//   unsigned long int index = index_key(key, dictionary -> capacity, dictionary); 
//   if(index == -1){
//     return false; 
//   }else{
//     free(dictionary -> table[index].key); 
//     dictionary -> table[index].key = NULL; 

//     if(dictionary -> destroy != NULL){
//       dictionary -> destroy(dictionary -> table[index].value);
//     }

//     dictionary -> table[index].value = NULL; 
//     dictionary -> table[index].is_deleted = true; 
//     dictionary -> size --; 
//     return true; 
//   }
// }
  

// // void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err) {
// //   size_t index = index_hash(key, dictionary -> capacity); 

// //   if(dictionary -> size != 0){
// //     for(int i = 0; i < dictionary -> capacity; i++){
// //       size_t position = (index + i) % dictionary->capacity;

// //       if((dictionary->table[position].key != NULL) && (strcmp(dictionary->table[position].key, key) == 0)){
// //         free(dictionary -> table[position].key); 
// //         dictionary -> table[position].key = NULL; 
// //         void *value = dictionary -> table[position].value;
// //         dictionary -> table[position].value = NULL; 
// //         dictionary -> table[position].is_deleted = true; 
// //         dictionary -> size --;
// //         (*err) = false;  
// //         return value; 

// //       }else if((dictionary -> table[position].is_deleted == false) && (dictionary -> table[position].key == NULL)){
// //         (*err) = true; 
// //         return NULL;
// //       }
// //     }
// //   }

// //   (*err) = true;
// //   return NULL; 
// // }

// void *dictionary_pop(dictionary_t *dictionary, const char *key, bool *err){
//   unsigned long int index = index_key(key, dictionary -> capacity, dictionary); 
//   if(index == -1){
//     (*err) = true;
//     return NULL; 
//   }else{
//     free(dictionary -> table[index].key); 
//     dictionary -> table[index].key = NULL; 
//     void *value = dictionary -> table[index].value;
//     dictionary -> table[index].value = NULL; 
//     dictionary -> table[index].is_deleted = true; 
//     dictionary -> size --;
//     (*err) = false;  
//     return value; 
//   }
// }


// // bool dictionary_contains(dictionary_t *dictionary, const char *key) { 
// //   if(dictionary -> size != 0){
// //     size_t index = index_hash(key, dictionary -> capacity);

// //     for(int i = 0; i < dictionary -> capacity; i++){
// //       size_t position = (index + i) % dictionary->capacity;

// //       if((dictionary->table[position].key != NULL) && (strcmp(dictionary->table[position].key, key) == 0)){
// //         return true; 
// //       }else if((dictionary -> table[position].is_deleted == false) && (dictionary -> table[position].key == NULL)){
// //         return false;
// //       }
// //     }
// //   }
  
// //   return false; 
// // }


// bool dictionary_contains(dictionary_t *dictionary, const char *key) { 
//   if(index_key(key, dictionary -> capacity, dictionary) != -1){
//     return true;
//   }
//   return false; 
   
// }

// size_t dictionary_size(dictionary_t *dictionary) { return dictionary -> size; }


// void dictionary_destroy(dictionary_t *dictionary){
//  if(dictionary -> size != 0){
//     for(int i = 0; i < dictionary -> capacity; i++){
//       if (dictionary->table[i].key != NULL) {
//         free(dictionary->table[i].key);
//       }
//       if ((dictionary->destroy != NULL) && (dictionary->table[i].value != NULL)) {
//         dictionary->destroy(dictionary->table[i].value);
//       }
//     }
//   }
//   free(dictionary -> table); 
//   free(dictionary); 
//   return;
// }
