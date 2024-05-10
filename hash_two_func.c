//
// Created by pupach on 10.05.24.
//

#include "hash_two_func.h"


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