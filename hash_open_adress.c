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

int MainHashFunc(HashTable *table, ElemToUse ElenToHash)
{
    int hash = ElenToHash% table->capacity;
    return hash;
}

int HashFunc(HashTable *table, ElemToUse ElenToHash)
{
    int hash = table->capacity + 1 - (ElenToHash % table->capacity);
    if (hash % 2 == 0)
    {
        return hash + 1;
    }
    return hash;
}


void ReHashLin(HashTable *table)
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
        if(old_arr->val != POISON_VAL)
        {
            AddElemTableLin(table, old_arr->val);
        }
    }

    free(old_arr);
}

void ReHashQuad(HashTable *table)
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
        if(old_arr->val != POISON_VAL)
        {
            AddElemTableQuad(table, old_arr->val);
        }
    }
    free(old_arr);
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


void AddElemTableLin(HashTable *table, ElemToUse ElemToAdd)
{
    if((table->size + 2) > (int)(((double )table->capacity) * table->load_factor))
    {
        ReHashLin(table);
    }
    int hash = MainHashFunc(table, ElemToAdd);

    int step = 0;
    while(table->arr[hash].val != POISON_VAL && (table->arr[hash].val != ElemToAdd))
    {
        step++;
        hash = (hash + 1) % table->capacity;
    }

    if(table->arr[hash].val == POISON_VAL) table->size++;
    table->arr[hash].val  = ElemToAdd;
    table->arr[hash].step  = step;
    return;
}

void AddElemTableQuad(HashTable *table, ElemToUse ElemToAdd)
{
    if((table->size + 2) > (int)(((double )table->capacity) * table->load_factor))
    {
        ReHashQuad(table);
    }
    int hash = table->HashFunc(table, ElemToAdd);
    int step = 0;
    while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToAdd))
    {
        hash = (hash + step * table->consts[2] + step * step * table->consts[3]) % table->capacity;
        step++;
    }

    if(table->arr[hash].val == POISON_VAL) table->size++;
    table->arr[hash].val  = ElemToAdd;
    table->arr[hash].step = step;
    return;
}

void AddElemTableTwo(HashTable *table, ElemToUse ElemToAdd)
{
    if((table->size + 2) > (int)(((double )table->capacity) * table->load_factor))
    {
        ReHashTwo(table);
    }
    int hash2 = MainHashFunc(table, ElemToAdd);
    int hash1 = HashFunc(table, ElemToAdd);
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

void RemoveElemTableQuad(HashTable *table, ElemToUse ElemToRemove)
{
    int hash = table->HashFunc(table, ElemToRemove);
    int step = 0;
    while(table->arr[hash].val != POISON_VAL && (table->arr[hash].val != ElemToRemove))
    {
        step++;
        hash = (hash + step * table->consts[2] + step * step * table->consts[3]) % table->capacity;
    }
    step++;
    if(table->arr[hash].val == POISON_VAL) return;
    table->arr[hash].val = POISON_VAL;
    table->arr[hash].step = 0;

    while(table->arr[(hash + step * table->consts[2] + step * step * table->consts[3]) % table->capacity].step > 0)
    {
        swap(&(table->arr[hash].val), &(table->arr[(hash + step * table->consts[2] + step * step * table->consts[3]) % table->capacity].val));
        hash = (hash + step * table->consts[2] + step * step * table->consts[3]) % table->capacity;
        step++;
    }
}


void RemoveElemTableLin(HashTable *table, ElemToUse ElemToRemove)
{
    int hash = table->HashFunc(table, ElemToRemove);
    while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToRemove))
    {
        hash = (hash + 1) % table->capacity;
    }
    if(table->arr[hash].val == POISON_VAL) return;
    table->arr[hash].val = POISON_VAL;
    table->arr[hash].step = 0;
    hash = (hash + 1) % table->capacity;
    while(table->arr[hash].step > 0)
    {
        swap(&(table->arr[hash].val), &(table->arr[(hash - 1) % table->capacity].val));
        hash = (hash + 1) % table->capacity;
    }
}

void RemoveElemTableTwo(HashTable *table, ElemToUse ElemToRemove)
{
    int hash1 = table->HashFunc(table, ElemToRemove);
    int step = 0;
    int hash = hash1;
    while(table->arr[hash].val != POISON_VAL && (table->arr[hash].val != ElemToRemove))
    {
        step++;
        hash = ((((ElemToRemove * table->consts[0] + table->consts[1])
                 % PowerUniverse) % table->capacity) * step + hash1) %  table->capacity;
    }
    step++;
    if(table->arr[hash].val == POISON_VAL) return;
    table->arr[hash].val = POISON_VAL;
    table->arr[hash].step = 0;
    hash = ((((ElemToRemove * table->consts[0] + table->consts[1]) % PowerUniverse) % table->capacity) * step + hash1) % table->capacity;
    while(table->arr[ (((ElemToRemove * table->consts[0] + table->consts[1]) % PowerUniverse) % table->capacity) * step + hash1].step > 0)
    {
        swap(&(table->arr[hash].val), &(table->arr[((((ElemToRemove * table->consts[0] + table->consts[1]) % PowerUniverse) % table->capacity) * step + hash1) % table->capacity].val));
        hash = ((((ElemToRemove * table->consts[0] + table->consts[1]) % PowerUniverse) % table->capacity) * step + hash1) % table->capacity;
        step++;
    }
}


bool FindElemTableQuad(HashTable *table, ElemToUse ElemToFind)
{
    int hash = MainHashFunc(table, ElemToFind);
    int step = 0;
    while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToFind))
    {
        hash = (hash + step * table->consts[2] + step * step * table->consts[3]) % table->capacity;
        step++;
    }

    if(table->arr[hash].val == POISON_VAL)  return false;
    return true;
}

bool FindElemTableTwo(HashTable *table, ElemToUse ElemToFind)
{
    int hash = MainHashFunc(table, ElemToFind);
    int hash1 = HashFunc(table, ElemToFind);
    int step = 0;
    while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToFind))
    {
        step++;
        hash = ((((ElemToFind * table->consts[0] + table->consts[1])
                  % PowerUniverse) % table->capacity) * step + hash1) %  table->capacity;
    }

    if(table->arr[hash].val == POISON_VAL)  return false;
    return true;
}

bool FindElemTableLin(HashTable *table, ElemToUse ElemToFind)
{
    int hash = MainHashFunc(table, ElemToFind);
    while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToFind))
    {
        hash = (hash + 1) % table->capacity;
    }
    if(table->arr[hash].val == POISON_VAL)  return false;
    return true;
}