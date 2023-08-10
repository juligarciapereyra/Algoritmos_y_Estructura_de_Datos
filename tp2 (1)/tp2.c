#include "tp2.h"
#include <stdlib.h>
#include <stdbool.h>


struct node;
typedef struct node node_t;

struct node {
    void* value;
    node_t* next;
    node_t* prev;
};

struct list {
    node_t* head;
    node_t* tail;
    size_t size;
};

struct list_iter {
    list_t* list;
    node_t* curr;
};


node_t* node_new(void* value){
    node_t* node = (node_t*) malloc(sizeof(node_t)); 
    if(!node) return NULL; 
    
    node -> value = value; 
    node -> next = NULL; 
    node -> prev = NULL; 

    return node; 
}

list_t *list_new(){
    list_t* list = (list_t*) malloc(sizeof(list_t)); 
    if(!list) return NULL;

    list -> head = NULL; 
    list -> tail = NULL; 
    list -> size = 0;  

    return list; 
}

size_t list_length(const list_t *list){
    return list -> size;   
}

bool list_is_empty(const list_t *list){
    return(list_length(list) == 0);
}

bool list_insert_head(list_t *list, void *value){
    node_t* new_head = node_new(value); 
    if(!new_head) return false;
    
    if(list -> head){
        new_head -> next = list -> head; 
        list -> head -> prev = new_head; 
    }else{
        list -> tail = new_head;
    }
       
    list -> head = new_head; 
    list -> size++; 

    return true;
}

bool list_insert_tail(list_t *list, void *value){
    node_t* new_tail = node_new(value);  
    if(!new_tail) return false; 

    if(list -> tail){
        new_tail -> prev = list -> tail; 
        list -> tail -> next = new_tail;
    }else{ 
        list -> head = new_tail; 
    }

    list -> tail = new_tail; 
    list -> size++; 

    return true;
}

void *list_peek_head(const list_t *list){
    if(list_is_empty(list)) return NULL; 
    return list -> head -> value; 
}

void *list_peek_tail(const list_t *list){
    if(list_is_empty(list)) return NULL; 
    return list -> tail -> value; 
}

void *list_pop_head(list_t *list){
    if(list_is_empty(list)) return NULL;
    
    void* value = list -> head -> value;
    node_t* next = list -> head -> next; 

    free(list -> head); 
    list -> head = next; 

    if(next){
        next -> prev = NULL; 
    }else{
        list -> tail = NULL; 
    } 

    list -> size--; 
    return value; 

}

void *list_pop_tail(list_t *list){
    if(list_is_empty(list)) return NULL; 

    void* value = list -> tail -> value; 
    node_t* prevoius = list -> tail -> prev; 

    free(list -> tail); 
    list -> tail = prevoius; 

    if(prevoius){
        prevoius -> next = NULL; 
    }else{
        list -> head = NULL; 
    }

    list -> size--; 
    return value; 
}

void list_destroy(list_t *list, void destroy_value(void *)){ 
    node_t* current = list -> head; 

    while(current){ 
        node_t* next = current -> next; 

        if(destroy_value){
            destroy_value(current -> value);
        }
        free(current); 
        current = next; 
    }

    free(list); 
    return;
}

list_iter_t *list_iter_create_head(list_t *list){
    list_iter_t* iter_head = (list_iter_t*) malloc(sizeof(list_iter_t)); 
    if(!iter_head) return NULL;
  
    iter_head -> list = list;
    iter_head -> curr =  list -> head; 

    return iter_head; 
}

list_iter_t *list_iter_create_tail(list_t *list){
    list_iter_t* iter_tail = (list_iter_t*) malloc(sizeof(list_iter_t)); 
    if(!iter_tail) return NULL; 

    iter_tail -> list = list;
    iter_tail -> curr =  list -> tail; 

    return iter_tail; 
}

bool list_iter_forward(list_iter_t *iter){
    if((iter->curr) && (iter -> curr -> next)){ 
        iter -> curr = iter -> curr -> next; 
            return true; 
        }
    return false; 
}

bool list_iter_backward(list_iter_t *iter){
    if((iter->curr) && (iter -> curr -> prev)){
        iter -> curr = iter -> curr -> prev; 
            return true;
        }
    return false; 
}

void *list_iter_peek_current(const list_iter_t *iter){
    if(list_is_empty(iter -> list)) return NULL; 

    if(iter-> curr) return iter -> curr -> value; 
    
    return NULL; 
}

bool list_iter_at_last(const list_iter_t *iter){
    return((iter -> curr) == (iter -> list -> tail));
 
}

bool list_iter_at_first(const list_iter_t *iter){
    return((iter -> curr) == (iter -> list -> head));
      
}


void list_iter_destroy(list_iter_t *iter){
    free(iter); 
    return;
}



bool list_iter_insert_after(list_iter_t *iter, void *value){


    if(list_is_empty(iter -> list)){
        list_insert_tail(iter -> list, value); 
        iter -> curr = iter -> list -> tail; 
        return true;  
    }else{
        if(list_iter_at_last(iter)){
            list_insert_tail(iter -> list, value); 
            return true;  
        }else{
            node_t* new_node = node_new(value); 
            if(!new_node) return false; 
            new_node -> prev = iter -> curr; 
            new_node -> next = iter -> curr -> next;
            iter -> curr -> next -> prev = new_node; 
            iter -> curr -> next = new_node; 
            iter -> list -> size++;
            return true; 
     
        }

    }

  
}


bool list_iter_insert_before(list_iter_t *iter, void *value){
    
    if(list_is_empty(iter -> list)){
        list_insert_head(iter -> list, value);
        iter -> curr = iter -> list -> head; 
            
    }else{
        if(list_iter_at_first(iter)){  
            list_insert_head(iter -> list, value); 
        }else{
            node_t* new_node = node_new(value);  
            if(!new_node) return false; 
            new_node -> next = iter -> curr; 
            new_node -> prev = iter -> curr -> prev;
            iter -> curr -> prev -> next = new_node; 
            iter -> curr -> prev = new_node; 
            iter -> list -> size++;
        }

    }

    return true;  
}


void *list_iter_delete(list_iter_t *iter){
    if(list_is_empty (iter -> list)) return NULL; 
     
    void* value = list_iter_peek_current(iter);  
    node_t* current = iter -> curr; 

    if(list_iter_at_first(iter)){
        iter -> curr = iter -> curr -> next; 
        list_pop_head(iter -> list); 

    }else if(list_iter_at_last(iter)){
        iter -> curr = iter -> curr -> prev; 
        list_pop_tail(iter -> list); 

    }else{
        iter -> curr -> next -> prev = iter -> curr -> prev; 
        iter -> curr -> prev -> next = iter -> curr -> next; 
        iter -> curr = iter -> curr -> next;
        free(current); 
        iter -> list -> size--; 
    }
   
    return value;     
}







