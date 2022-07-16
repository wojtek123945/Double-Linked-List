#include "stdlib.h"
#include "stdio.h"
#include "doubly_linked_list.h"

struct doubly_linked_list_t* dll_create(){
    struct doubly_linked_list_t *temp = calloc(1, sizeof(struct doubly_linked_list_t));
    if(!temp)
        return NULL;
    return temp;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value){
    if(!dll)
        return 1;
    struct node_t *temp = calloc(1,sizeof(struct node_t));
    if(!temp)
        return 2;
    temp->data = value;
    if(dll->head == NULL){
        dll->head = temp;
        dll->tail = temp;
        return 0;
    }
    struct node_t* prev_tail = dll->tail;
    dll->tail->next = temp;
    dll->tail = temp;
    dll->tail->prev = prev_tail;
    return 0;
}
int dll_push_front(struct doubly_linked_list_t* dll, int value){
    if(!dll)
        return 1;
    struct node_t* need_add = calloc(1,sizeof(struct node_t));
    if(!need_add)
        return 2;
    need_add->data = value;

    struct node_t* head_in_list = dll->head;
    if(head_in_list == NULL){
        dll->head = need_add;
        dll->tail = need_add;
    }
    dll->head->prev = need_add;
    dll->head = need_add;
    dll->head->next = head_in_list;
    dll->head->prev=NULL;
    return 0;
}
int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code){
    if(!dll || !dll->head){
        if(err_code)
            *err_code = 1;
        return 0;
    }
    struct node_t* after_first = dll->head->next;
    int val = dll->head->data;
    free(dll->head);
    if(after_first == NULL){
        dll->tail = NULL;
        dll->head = NULL;
    }else{
        dll->head = after_first;
        dll->head->prev = NULL;
    }
    if(err_code)
        *err_code = 0;
    return val;
}
int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code){
    if(!dll || !dll->tail){
        if(err_code)
            *err_code = 1;
        return 0;
    }
    int val = dll->tail->data;
    struct node_t* prev_tail = dll->tail->prev;
    free(dll->tail);
    dll->tail = prev_tail;
    if(dll->tail==NULL){
        dll->head = NULL;
    }else{
        dll->tail->next = NULL;
    }
    if(err_code)
        *err_code=0;
    return val;
}

int dll_front(const struct doubly_linked_list_t* dll, int *err_code){
    if(!dll || !dll->head){
        if(err_code)
            *err_code = 1;
        return 0;
    }
    int val = dll->head->data;
    if(err_code)
        *err_code = 0;
    return val;
}
int dll_back(const struct doubly_linked_list_t* dll, int *err_code){
    if(!dll || !dll->tail){
        if(err_code)
            *err_code = 1;
        return 0;
    }
    int val = dll->tail->data;
    if(err_code)
        *err_code = 0;
    return val;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll){
    if(!dll || !dll->head)
        return NULL;
    return dll->head;
}
struct node_t* dll_end(struct doubly_linked_list_t* dll){
    if(!dll || !dll->tail)
        return NULL;
    return dll->tail;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
    if(!dll || (int)index >= dll_size(dll)){
        if(err_code)
            *err_code = 1;
        return 0;
    }
    struct  node_t *t = dll->head;
    for (int i = 0; i < (int)index; ++i) {
        t = t->next;
    }
    if(err_code)
        *err_code = 0;
    return t->data;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value){
    if(!dll || (int)index > dll_size(dll) || (int)index < 0){
        return 1;
    }
    int size = dll_size(dll);
    if((int)index == size){
        return dll_push_back(dll, value);
    }else if(index == 0){
        return dll_push_front(dll, value);
    }

    ///JAZDA
    //struct  node_t *previous_new_node = ll->head;
    struct node_t *new_node = calloc(1, sizeof(struct node_t));
    if(!new_node)
        return 2;
    new_node->data = value;
    struct node_t* current = dll->head;
    for (int i = 0; i < (int)index-1; ++i) {
        current = current->next;
    }
    // |current
    // 2 - 5 - 12
    struct node_t *after_new_node = current->next;
    struct  node_t *previous_new_node = current;
    new_node->next =after_new_node;
    new_node->prev = previous_new_node;
    current->next = new_node;
    if(after_new_node)
        after_new_node->prev = new_node;
    return 0;
}
int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code){
    if(!dll || (int)index > dll_size(dll) || (int)index<0){
        if(err_code)
            *err_code = 1;
        return 0;
    }
    int size = dll_size(dll);
    if((int)index == size-1){
        return dll_pop_back(dll, err_code);
    }else if(index == 0){
        return dll_pop_front(dll, err_code);
    }

    //struct  node_t *previous_new_node = ll->head;
    //     |current
    // 2 - 5 - 12
    struct node_t* current = dll->head;
    for (int i = 0; i < (int)index; ++i) {
        current = current->next;
    }
    struct node_t *previous_current = current->prev;
    struct node_t *after_current = current->next;
    int val = current->data;
    free(current);
    if(previous_current)
        previous_current->next = after_current;
    if(after_current)
        after_current->prev = previous_current;
    if(err_code)
        *err_code = 0;
    return val;
}

int dll_size(const struct doubly_linked_list_t* dll){
    if(!dll)
        return -1;
    struct node_t* current = dll->head;
    int size=0;
    while (current){
        size++;
        current=current->next;
    }
    return size;
}
int dll_is_empty(const struct doubly_linked_list_t* dll){
    if(!dll)
        return -1;
    if(dll->head!=NULL)
        return 0;
    else
        return 1;
}

void dll_display(const struct doubly_linked_list_t* dll){
    if(!dll)
        return;
    struct node_t* current = dll->head;
    while (current!=NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    return;
}
void dll_clear(struct doubly_linked_list_t* dll){
    if(!dll){
        return;
    }
    struct node_t *t = dll->head;
    while (t!=NULL){
        struct node_t *next = t->next;
        free(t);
        t=next;
    }
    dll->head = NULL;
    dll->tail = NULL;
}

void dll_display_reverse(const struct doubly_linked_list_t* dll){
    if(dll){
        struct node_t* prev = dll->tail;
        while (prev!=NULL){
            printf("%d ", prev->data);
            prev = prev->prev;
        }
    }
}