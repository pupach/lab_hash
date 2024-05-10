//
// Created by pupach on 10.05.24.
//

#include "hash_two_func.h"
void swap(ElemToUse *l1, ElemToUse *l2){
ElemToUse x = *l1;
*l1 = *l2;
*l2 = x;
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


bool FindElemTableTwo(HashTable *table, ElemToUse ElemToFind)
{
  int hash = MainHashFuncOpenAdress(table, ElemToFind);
  int hash1 = SecondHashFunc(table, ElemToFind);
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

void ReHashTwo(HashTable *table)
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


