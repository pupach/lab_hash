//
// Created by pupach on 03.05.24.
//

#ifndef LAB_HASH_HASH_OPEN_ADRESS
#define LAB_HASH_HASH_OPEN_ADRESS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define PowerUniverse 2147483647
#define MAX_SIZE_TABLE 1000000
#define MAX_SIZE_CONSTS 10
#define MAX_SIZE_COM 2
#define POISON_VAL -1


#define CHECK_RES_CALLOC(ptr) \
    if(ptr == NULL) exit(-1);

typedef int ElemToUse;

void swap(ElemToUse *l1, ElemToUse *l2);

typedef struct
{
    ElemToUse val;
    int step;
} ElemTable;

typedef struct{
    int size;
    int capacity;
    double load_factor;
    int consts[MAX_SIZE_CONSTS];
    int (*HashFunc)(struct HashTable *, ElemToUse);
    ElemTable *arr;

} HashTable;

int MainHashFuncOpenAdress(HashTable *table, ElemToUse ElenToHash);

int SecondHashFunc(HashTable *table, ElemToUse ElenToHash);

void InitTable(HashTable *table, int capacity, int(*HashFunc)(HashTable *, int), double load_factor);

int MainHashFuncPerfectHashTable(HashTable *table, ElemToUse ElenToHash);

#endif //LAB_HASH_HASH_LIN_H
