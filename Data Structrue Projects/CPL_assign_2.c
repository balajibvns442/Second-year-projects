#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>

typedef struct meta_data{
    size_t size;
    int free;
    struct meta_data* next;
} meta;

char memory[20000];
meta *free_list = (void *)memory;

void initialise(){
    free_list->size = 20000 - sizeof(meta);
    free_list->free = 1;
    free_list->next = NULL;
}

void divide_block(meta *fit, size_t size){
    meta* temp = (void *)(((void *)fit) + size + sizeof(meta));

    temp->size = (fit->size) - size - sizeof(meta);
    temp->free = 1;
    temp->next = fit->next;

    fit->size = size;
    fit->free = 0;
    fit->next = temp;
}

void *mem_alloc(size_t mem_req){
    meta *pres = NULL;
    meta *prev = NULL;
    void *res = NULL;

    if((free_list->size) == 0){
        initialise();
        printf("free_list is initialised\n");
    }

    pres = free_list;

    while(((pres->size < mem_req) || (pres->free == 0)) && pres->next != NULL){
        prev = pres;
        pres = pres->next;
    }

    if((pres->size) == mem_req){
        pres->free = 0;
        res = (void *)(++pres);
        printf("best fitting block found");
    }
    else if((pres->size) > (mem_req + sizeof(meta))){
        divide_block(pres, mem_req);
        res = (void *)(++pres);
        printf("block is larger than required\n");
    }
    else{
        printf("block of the size requirement is not found\n"); 
    }

    return (void*)res;
}

void merge(){
    meta *pres = NULL;
    meta *prev = NULL;

    pres = free_list;
    while((pres->next) != NULL){
        if((pres->free == 1) && (pres->next->free == 1)){
            pres->size += (pres->next)->size + sizeof(meta);
            pres->next = (pres->next)->next;
        }
        prev = pres;
        pres = pres->next;

        printf("loop  ");
    }
}

void delete(void *ptr){
    printf("entered delete\n");
    if(((void *)memory <= ptr) && (ptr <= (void *)(memory + 20000))){
        meta *pres = (meta *)ptr;
        --pres;
        pres->free = 1;
        printf("entering in merge()\n");
        merge();
        printf("block deleted\n");
    }
    else{
        printf("the memory you are trying to access is not in the RAM used for this program\n");
        printf("please provide a valid pointer\n");
    }
}

void Show_list(){
    meta *ptr = free_list;

    while(ptr != NULL){
        if(ptr->free == 0){
            printf("the block is occupied\n");
            printf("the size of the block is %zu\n", ptr->size);
        }
        else{
            printf("the block is free\n");
        }
        printf("------------------------------------\n");

        ptr = ptr->next;
    }
}

int main(){
    int *integer = (int *)mem_alloc(215 * sizeof(int));
    char *character = (char *)mem_alloc(117 * sizeof(char));
    float *decimal = (float *)mem_alloc(899 * sizeof(float));

    delete(integer);
    char *letter = (char *)mem_alloc(650 * sizeof(char));
    printf("character allocation done\n");
    int *num = (int *)mem_alloc(461 * sizeof(int));
    printf("\n");

    int* p=(int *)malloc(100*sizeof(int));
    delete(p);
    
    Show_list();
    printf("\n");
    printf("memory allocation and deallocation done\n");

    printf("size of meta block %zu",sizeof(meta));
    return 0;
}