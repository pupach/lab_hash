//
// Created by pupach on 05.05.24.
//

#ifndef LAB_HASH_PERFECT_HASH_H
#define LAB_HASH_PERFECT_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define PowerUniverse 2147483647
#define MAX_RAND 1000000000
#define MAX_SIZE_TABLE 10000000
#define MAX_SIZE_CONSTS 3
#define POISON_VAL -1
#define MAX_SIZE_COM 3
#define LOG(args...) \
    //      fprintf(stderr, args)

extern struct HashTableHash;

typedef int ElemToUse;

typedef struct
{
    struct HashTableHash *val;
    int arr;
    int step;
    int size;
}ElemTableHash;

typedef struct{
    int size;
    int capacity;
    bool nul;
    int consts[2];
    int (*HashFunc)(struct HashTableHash *, ElemToUse);
    ElemTableHash *arr;

}HashTableHash;

void InitTablePerfect(HashTableHash *table, int capacity, int(*HashFunc)(struct HashTableHash *, ElemToUse), bool head_table);


int MainHashFuncPerfect(HashTableHash *table, ElemToUse ElenToHash);

void AddElemTableHash(HashTableHash *table, ElemToUse ElemToAdd);

void RemoveElemTableHash(HashTableHash *table, ElemToUse ElemToAdd);
#endif //LAB_HASH_PERFECT_HASH_H
