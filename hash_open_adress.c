//
// Created by pupach on 03.05.24.
//

#include "hash_open_adress.h"

void swap(ElemToUse *l1, ElemToUse *l2)
{
  ElemToUse x = *l1;
  *l1 = *l2;
  *l2 = x;
}



int MainHashFuncOpenAdress(HashTable *table, ElemToUse ElenToHash)
{
    int hash = ElenToHash% table->capacity;
    return hash;
}

int SecondHashFunc(HashTable *table, ElemToUse ElenToHash)
{
    int hash = table->capacity + 1 - (ElenToHash % table->capacity);
    if (hash % 2 == 0)
    {
        return hash + 1;
    }
    return hash;
}


void ReHashTwo(HashTable *table)
{
    int old_cap = table->capacity;
    table->capacity *= 2;
    ElemTable *old_arr = table->arr;
    table->arr = (ElemTable *)calloc(sizeof(ElemTable), table->capacity);
    for(int i = 0; i < table->capacity; i++)
    {
        table->arr[i].val = POISON_VAL;
    }

    for(int i = 0; i < old_cap; i++)
    {
        if(old_arr[i].val != POISON_VAL)
        {
            AddElemTableTwo(table, old_arr[i].val);
        }
    }
    free(old_arr);
}


void AddElemTableTwo(HashTable *table, ElemToUse ElemToAdd)
{
    if((table->size + 2) > (int)(((double )table->capacity) * table->load_factor))
    {
        ReHashTwo(table);
    }
    int hash2 = MainHashFuncOpenAdress(table, ElemToAdd);
    int hash1 = SecondHashFunc(table, ElemToAdd);
    int hash = hash2;
    int step = 0;

    while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToAdd))
    {
        step++;
        hash = (int)(((long long int )hash1 * (long long int )step + (long long int )hash2) % table->capacity);
    }

    if(table->arr[hash].val == POISON_VAL) table->size++;
    table->arr[hash].val  = ElemToAdd;
    table->arr[hash].step = step;
    return;
}



void InitTable(HashTable *table, int capacity, int(*HashFunc)(HashTable *, int))
{
    table->consts[0] = 3;
    table->consts[1] = 7;
    table->consts[2] = 5;
    table->consts[3] = 1;
    table->capacity = capacity;
    table->size = 0;
    table->arr = (ElemTable *)calloc(capacity, sizeof(ElemTable));
    for(int i = 0; i < capacity; i++)
    {
        table->arr[i].val = POISON_VAL;
    }
    table->HashFunc = HashFunc;
}