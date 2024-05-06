//
// Created by pupach on 05.05.24.
//

#include "Perfect_Hash.h"

int MainHashFuncPerfect(HashTableHash *table, ElemToUse ElenToHash)
{
    int hash = (((ElenToHash * table->consts[0] + table->consts[1])
                ) % table->consts[2] % table->capacity + table->capacity) % table->capacity;
    LOG("MainHashFuncPerfect hash = %d, ElenToHash = %d const0 = %d const1 = %d cop = %d\n", hash, ElenToHash, table->consts[0], table->consts[1], table->capacity);
    return hash;
}

void InitTablePerfect(HashTableHash *table, int capacity, int(*HashFunc)(struct HashTableHash *, ElemToUse), bool head_table)
{
    if(capacity == 0) return;

    table->consts[0] = 3;
    table->consts[1] = 1;
    table->consts[2] = 5;
    table->capacity = capacity;
    table->size = 0;
    table->nul = false;
    table->arr = (ElemTableHash *)calloc(capacity, sizeof(ElemTableHash));

    for (int i = 0; i < capacity; i++) {
        table->arr[i].arr = POISON_VAL;
    }
    if(head_table) {
        HashTableHash *arr = (HashTableHash *) calloc(capacity, sizeof(HashTableHash));
        for (int i = 0; i < capacity; i++) {
            table->arr[i].val = arr + i;
            table->arr[i].arr = POISON_VAL;
            InitTablePerfect(arr + i, capacity, HashFunc, 0);
        }
    }
    table->HashFunc = HashFunc;
}

bool FindElemTableHashHash(HashTableHash *table, ElemToUse ElemToFind)
{
    int hash = table->HashFunc(table, ElemToFind);
    int step = 0;
    while((table->arr[hash].arr != POISON_VAL) && (table->arr[hash].arr != ElemToFind))
    {
        hash = (hash + 1) % table->capacity;
        step++;
        if(step == table->size) return false;
    }
    if(table->arr[hash].arr == POISON_VAL)  return false;
    return true;
}
bool FindAndDelElemTableHashHash(HashTableHash *table, ElemToUse ElemToFind)
{
    int hash = table->HashFunc(table, ElemToFind);
    while((table->arr[hash].arr != POISON_VAL) && (table->arr[hash].arr != ElemToFind))
    {
        hash = (hash + 1) % table->capacity;
    }
    if(table->arr[hash].arr == POISON_VAL)  return false;

    table->arr[hash].arr = POISON_VAL;
    table->size--;

    return true;
}

void AddElemTableHash(HashTableHash *table, ElemToUse ElemToAdd)
{
    int hash = table->HashFunc(table, ElemToAdd);
    HashTableHash *t = table->arr[hash].val;
    while(1 == 1)
    {
        hash = (hash + 1) % table->capacity;
        t = table->arr[hash].val;
        if(t->capacity == t->size) {
            bool res = FindElemTableHashHash(t, ElemToAdd);
            if (res) return;
        }
        else
        {
            break;
        }
    }
    int hash_new = table->HashFunc(table->arr[hash].val, ElemToAdd);
    int val = t->arr[hash_new].arr;

    while((t->arr[hash_new].arr != POISON_VAL) && (t->arr[hash_new].arr != ElemToAdd))
    {
        hash_new = (hash_new + 1) % t->capacity;
    }

    t->arr[hash_new].arr = ElemToAdd;
    t->size++;
    return;
}

void RemoveElemTableHashHash(HashTableHash *table, ElemToUse ElemToAdd)
{
    int hash = table->HashFunc(table, ElemToAdd);

    HashTableHash *t = table->arr[hash].val;
    while(t->capacity == t->size)
    {

        hash = (hash + 1) % table->capacity;
        t = table->arr[hash].val;
        bool res = FindElemTableHashHash(t, ElemToAdd);
        if(res) return;
    }
    FindElemTableHashHash(t, ElemToAdd);
    return;
}