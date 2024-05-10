//
// Created by pupach on 10.05.24.
//

#include "hash_quad_func.h"


void ReHashQuad(HashTable *table)
{
  int old_cap = table->capacity;
  table->capacity *= 2;
  ElemTable *old_arr = table->arr;
  table->arr = (ElemTable *)calloc(sizeof(ElemTable), table->capacity);
  CHECK_RES_CALLOC(table->arr)

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

bool FindElemTableQuad(HashTable *table, ElemToUse ElemToFind)
{
  int hash = MainHashFuncOpenAdress(table, ElemToFind);
  int step = 0;
  while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToFind))
  {
    hash = (hash + step * table->consts[2] + step * step * table->consts[3]) % table->capacity;
    step++;
  }

  if(table->arr[hash].val == POISON_VAL)  return false;
  return true;
}