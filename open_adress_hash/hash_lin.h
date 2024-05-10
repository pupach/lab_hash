//
// Created by pupach on 10.05.24.
//

#ifndef LAB_HASH_HASH_LIN_H
#define LAB_HASH_HASH_LIN_H
#include "hash_open_adress.h"

void AddElemTableLin(HashTable *table, ElemToUse ElemToAdd);

void RemoveElemTableLin(HashTable *table, ElemToUse ElemToRemove);

bool FindElemTableLin(HashTable *table, ElemToUse ElemToFind);

void ReHashLin(HashTable *table);

#endif //LAB_HASH_HASH_LIN_H
