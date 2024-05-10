//
// Created by pupach on 06.05.24.
//

#ifndef LAB_HASH_PERFECTHASHFIND_H
#define LAB_HASH_PERFECTHASHFIND_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "hash_lin.h"
#define PowerUniverse 2147483647
#define MAX_RAND 1000000000
#define MAX_SIZE_TABLE 10000000
#define MAX_SIZE_CONSTS 5
#define MAX_SIZE_COM 5
#define LOG(args...) \
         //fprintf(stderr, args)

extern struct HashTablePerfect;

typedef int ElemToUse;

typedef struct
{
    HashTable *val;
    int *arr;
    int step;
    int size;
} ElemTablePerfect;

typedef struct{
    int size;
    int capacity;
    bool nul;
    int consts[3];
    int (*HashFunc)(struct HashTablePerfect *, ElemToUse);
    ElemTablePerfect *arr;

} HashTablePerfect;

bool FindElemTablePerfect(HashTablePerfect *table, ElemToUse ElemToFind);

void GenFirstHashFunc(HashTablePerfect *table, int *val, int AmountCom, int ogranich);

int HashPerfect(HashTablePerfect *table, ElemToUse ElenToHash);

void InitTablePerfect(HashTablePerfect *table, int capacity, int(*HashFunc)(struct HashTablePerfect *, ElemToUse), bool head_table);

#endif //LAB_HASH_PERFECTHASHFIND_H
