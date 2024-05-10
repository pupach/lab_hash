//
// Created by pupach on 10.05.24.
//

#ifndef LAB_HASH_HASH_QUAD_FUNC_H
#define LAB_HASH_HASH_QUAD_FUNC_H
#include "hash_open_adress.h"

void AddElemTableQuad(HashTable *table, ElemToUse ElemToAdd);

bool FindElemTableQuad(HashTable *table, ElemToUse ElemToFind);

void RemoveElemTableQuad(HashTable *table, ElemToUse ElemToRemove);


#endif //LAB_HASH_HASH_QUAD_FUNC_H
