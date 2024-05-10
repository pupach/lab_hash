//
// Created by pupach on 10.05.24.
//

#include "hash_lin.h"

void swap(ElemToUse *l1, ElemToUse *l2)
{
  ElemToUse x = *l1;
  *l1 = *l2;
  *l2 = x;
}

void AddElemTableLin(HashTable *table, ElemToUse ElemToAdd)
{
  if((table->size + 2) > (int)(((double )table->capacity) * table->load_factor))
  {
    ReHashLin(table);
  }
  int hash = MainHashFuncOpenAdress(table, ElemToAdd);

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

bool FindElemTableLin(HashTable *table, ElemToUse ElemToFind)
{
  int hash = MainHashFuncOpenAdress(table, ElemToFind);
  while((table->arr[hash].val != POISON_VAL) && (table->arr[hash].val != ElemToFind))
  {
    hash = (hash + 1) % table->capacity;
  }
  if(table->arr[hash].val == POISON_VAL)  return false;
  return true;
}