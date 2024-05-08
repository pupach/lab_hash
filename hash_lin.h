//
// Created by pupach on 03.05.24.
//

#ifndef LAB_HASH_HASH_LIN_H
#define LAB_HASH_HASH_LIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define PowerUniverse 2147483647
#define MAX_SIZE_TABLE 1000000
#define MAX_SIZE_CONSTS 10
#define MAX_SIZE_COM 2
#define POISON_VAL -1


typedef int ElemToUse;

typedef struct
{
    ElemToUse val;
    int step;
}ElemTable;

typedef struct{
    int size;
    int capacity;
    double load_factor;
    int consts[MAX_SIZE_CONSTS];
    int (*HashFunc)(struct HashTable *, ElemToUse);
    ElemTable *arr;

}HashTable;

void InitTable(HashTable *table, int capacity, int(*HashFunc)(HashTable *, int));

void AddElemTableQuad(HashTable *table, ElemToUse ElemToAdd);

void AddElemTableLin(HashTable *table, ElemToUse ElemToAdd);

int MainHashFunc(HashTable *table, ElemToUse ElenToHash);

bool FindElemTableLin(HashTable *table, ElemToUse ElemToFind);

bool FindElemTableQuad(HashTable *table, ElemToUse ElemToFind);

void RemoveElemTableQuad(HashTable *table, ElemToUse ElemToRemove);

void RemoveElemTableLin(HashTable *table, ElemToUse ElemToRemove);

void AddElemTableTwo(HashTable *table, ElemToUse ElemToAdd);

bool FindElemTableLin(HashTable *table, ElemToUse ElemToFind);

void RemoveElemTableTwo(HashTable *table, ElemToUse ElemToRemove);
#endif //LAB_HASH_HASH_LIN_H
