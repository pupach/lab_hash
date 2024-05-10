//
// Created by pupach on 03.05.24.
//

#include "hash_open_adress.h"


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

void InitTable(HashTable *table, int capacity, int(*HashFunc)(HashTable *, int), double load_factor)
{
  table->consts[0] = 3;
  table->consts[1] = 7;
  table->consts[2] = 5;
  table->consts[3] = 1;
  table->load_factor = load_factor;

  table->capacity = capacity;
  table->size = 0;
  table->arr = (ElemTable *)calloc(capacity, sizeof(ElemTable));
  CHECK_RES_CALLOC(table->arr)

  for(int i = 0; i < capacity; i++)
  {
      table->arr[i].val = POISON_VAL;
  }
  table->HashFunc = HashFunc;
}