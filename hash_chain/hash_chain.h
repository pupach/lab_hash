
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define PowerUniverse 2000000000
#define MAX_SIZE_TABLE 50000
#define MAX_SIZE_CONSTS 3
#define MAX_SIZE_COM 2
#define LOG(args...) \
        //fprintf(stderr, args)

#define CHECK_RES_CALLOC(ptr) \
    if(ptr == NULL) fprintf(stderr, "MEMPRY LIMIT ERROR\n");


typedef int ElemToUseList;

#define POISON_VAL NULL

static const int POISON_VAL_FOR_LIST = 5;

static const int BEG_CAPACITY_LIST = 100;

#define POISON_VAL '_'

typedef struct
{
    int val;
    int val1;
    int next;
    int prev;
}Elem_listCep;


typedef struct
{
    Elem_listCep *arr;
    int capacity;
}List;

typedef List  ElemTableList;

typedef struct{
    int size;
    int capacity;
    double load_factor;
    int hash_consts[MAX_SIZE_CONSTS];
    int (*HashFunc)(struct HashTableListCep *, ElemToUseList);
    ElemTableList *arr;

}HashTableListCep;

bool FindTableElemCep(HashTableListCep *table, int ElemToRemove);

void InitTableList(HashTableListCep *table, int capacity, int(*HashFunc)(HashTableListCep *, ElemToUseList), double load_factor);

void AddElemTableList(HashTableListCep *table, ElemToUseList ElemToAdd);

int MainHashFuncCep(HashTableListCep *table, ElemToUseList ElenToHash);

void RemoveTableElemCep(HashTableListCep *table, long int ElemToRemove);