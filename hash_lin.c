//
// Created by pupach on 03.05.24.
//

#include "hash_lin.h"


void swap(ElemToUse *l1, ElemToUse *l2)
{
    ElemToUse x = *l1;
    *l1 = *l2;
    *l2 = x;
}

int MainHashFunc(HashTable *table, ElemToUse ElenToHash)
{
    int hash = ((ElenToHash * table->consts[0] + table->consts[1])
                % PowerUniverse) % table->capacity;
    return hash;
}

void AddElemTableLin(HashTable *table, ElemToUse ElemToAdd)
{
    int hash = table->HashFunc(table, ElemToAdd);
    while(table->arr[hash].val != POISON_VAL && (table->arr[hash].val != ElemToAdd))
    {
        hash = (hash + 1) % table->capacity;
    }

    table->arr[hash].val  = ElemToAdd;
    return;
}

void AddElemTableQuad(HashTable *table, ElemToUse ElemToAdd)
{
    int hash = table->HashFunc(table, ElemToAdd);
    int step = 0;
    while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToAdd))
    {
        hash = (hash + step * table->consts[2] + step * step * table->consts[3]) % table->capacity;
        step++;
    }

    table->arr[hash].val  = ElemToAdd;
    table->arr[hash].step = step;
    return;
}


void InitTable(HashTable *table, int capacity, int(*HashFunc)(HashTable *, int))
{
    table->consts[0] = 3;
    table->consts[1] = 1;
    table->consts[2] = 5;
    table->capacity = capacity;
    table->size = 0;
    table->arr = (ElemTable *)calloc(capacity, sizeof(ElemTable));
    for(int i = 0; i < capacity; i++)
    {
        table->arr[i].val = POISON_VAL;
    }
    table->HashFunc = HashFunc;
}

void RemoveElemTableQuad(HashTable *table, ElemToUse ElemToRemove)
{
    int hash = table->HashFunc(table, ElemToRemove);
    int step = 0;
    while(table->arr[hash].val != POISON_VAL && (table->arr[hash].val != ElemToRemove))
    {
        hash = (hash + step * table->consts[2] + step * step * table->consts[3]) % table->capacity;
        step++;
    }
    table->arr[hash].val = POISON_VAL;
    table->arr[hash].step = 0;
    hash = (hash + 1) % table->capacity;
    while(table->arr[hash].step > 0)
    {
        swap(&(table->arr[hash].val), &(table->arr[(hash - 1) % table->capacity].val));
        hash = (hash + 1) % table->capacity;
    }
}

void RemoveElemTableLin(HashTable *table, ElemToUse ElemToRemove)
{
    int hash = table->HashFunc(table, ElemToRemove);
    while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToRemove))
    {
        hash = (hash + 1) % table->capacity;
    }
    table->arr[hash].val = POISON_VAL;
}

bool FindElemTableQuad(HashTable *table, ElemToUse ElemToFind)
{
    int hash = table->HashFunc(table, ElemToFind);
    int step = 0;
    while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToFind))
    {
        hash = (hash + step * table->consts[2] + step * step * table->consts[3]) % table->capacity;
        step++;
    }

    if(table->arr[hash].val == POISON_VAL)  return false;
    return true;
}

bool FindElemTableLin(HashTable *table, ElemToUse ElemToFind)
{
    int hash = table->HashFunc(table, ElemToFind);
    while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToFind))
    {
        hash = (hash + 1) % table->capacity;
    }
    if(table->arr[hash].val == POISON_VAL)  return false;
    return true;
}