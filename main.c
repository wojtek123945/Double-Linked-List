#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"
int main() {
    struct doubly_linked_list_t *list = dll_create();
    if(!list){
        printf("Failed to allocate memory");
        return 8;
    }
    while (1){
        int next_move;
        printf("Co chcesz zrobic: ");
        if(scanf("%d", &next_move)!=1){
            printf("Incorrect input");
            dll_clear(list);
            free(list);
            return 1;
        }
        while (getchar()!='\n');

        if(next_move < 0 || next_move>14){
            printf("Incorrect input data\n");
            continue;
        }

        if(next_move == 0){
            dll_clear(list);
            free(list);
            return 0;
        }else if(next_move == 1){
            int value;
            printf("Podaj wartosc: ");
            if(scanf("%d", &value)!=1){
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            while (getchar()!='\n');
            int error = dll_push_back(list, value);
            if(error == 2){
                dll_clear(list);
                free(list);
                printf("Failed to allocate memory");
                return 8;
            }
        }else if(next_move == 2){
            if(dll_is_empty(list) == 1){
                printf("List is empty\n");
                continue;
            }
            int error;
            int value = dll_pop_back(list, &error);
            if(error == 2){
                dll_clear(list);
                free(list);
                printf("Failed to allocate memory");
                return 8;
            }
            printf("%d\n", value);
        }else if(next_move == 3){
            int value;
            printf("Podaj wartosc: ");
            if(scanf("%d", &value)!=1){
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            while (getchar()!='\n');
            int error = dll_push_front(list, value);
            if(error == 2){
                dll_clear(list);
                free(list);
                printf("Failed to allocate memory");
                return 8;
            }
        }else if(next_move == 4){
            if(dll_is_empty(list) == 1){
                printf("List is empty\n");
                continue;
            }
            int error;
            int value = dll_pop_front(list, &error);
            if(error == 2){
                dll_clear(list);
                free(list);
                printf("Failed to allocate memory");
                return 8;
            }
            printf("%d\n", value);
        }else if(next_move == 5){
            int value, index;
            printf("Podaj wartosc: ");
            if(scanf("%d", &value)!=1){
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            while (getchar()!='\n');
            printf("Podaj index: ");
            if(scanf("%d", &index)!=1){
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            while (getchar()!='\n');
            if(index <0 || index > dll_size(list)){
                printf("Index out of range\n");
                continue;
            }
            int error = dll_insert(list, index, value);
            if(error == 2){
                dll_clear(list);
                free(list);
                printf("Failed to allocate memory");
                return 8;
            }
        }else if(next_move == 6){
            if(dll_is_empty(list) == 1){
                printf("List is empty\n");
                continue;
            }
            int value, index;
            printf("Podaj index: ");
            if(scanf("%d", &index)!=1){
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            while (getchar()!='\n');
            if(index <0 || index >= dll_size(list)){
                printf("Index out of range\n");
                continue;
            }
            int error;
            value = dll_remove(list, index, &error);
            printf("%d\n", value);
        }else if(next_move == 7){
            if(dll_is_empty(list) == 1){
                printf("List is empty\n");
                continue;
            }
            printf("%d\n", dll_back(list, NULL));
        }else if(next_move == 8){
            if(dll_is_empty(list) == 1){
                printf("List is empty\n");
                continue;
            }
            printf("%d\n", dll_front(list, NULL));
        }else if(next_move == 9){
            printf("%d\n", dll_is_empty(list));
        }else if(next_move == 10){
            printf("%d\n", dll_size(list));
        }else if(next_move == 11){
            dll_clear(list);
            //printf("List is clear\n");
        }else if(next_move == 12){
            if(dll_is_empty(list) == 1){
                printf("List is empty\n");
                continue;
            }
            int index;
            printf("Podaj index: ");
            if(scanf("%d", &index)!=1){
                printf("Incorrect input");
                dll_clear(list);
                free(list);
                return 1;
            }
            while (getchar()!='\n');
            if(index <0 || index-1 > dll_size(list)){
                printf("Index out of range\n");
                continue;
            }
            int value = dll_at(list, index, NULL);
            printf("%d\n", value);
        }else if(next_move == 13){
            if(dll_is_empty(list) == 1){
                printf("List is empty\n");
                continue;
            }
            dll_display(list);
            printf("\n");
        }else if(next_move == 14){
            if(dll_is_empty(list) == 1){
                printf("List is empty\n");
                continue;
            }
            dll_display_reverse(list);
            printf("\n");
        }
    }
    return 0;
}
