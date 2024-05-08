//
// Created by pupach on 06.05.24.
//

#include "Hash_Perfect.h"

int MainHashFuncPerfect(HashTablePerfect *table, ElemToUse ElenToHash)
{
    int hash = (((ElenToHash * table->consts[0] + table->consts[1])
                ) % table->consts[2] % table->capacity + table->capacity) % table->capacity;
    LOG("MainHashFunc hash = %d, ElenToHash = %d const0 = %d const1 = %d cop = %d\n", hash, ElenToHash, table->consts[0], table->consts[1], table->capacity);
    return hash;
}

void InitTablePerfect(HashTablePerfect *table, int capacity, int(*HashFunc)(struct HashTablePerfect *, ElemToUse), bool head_table)
{
    if(capacity == 0) return;
    table->capacity = capacity;
    table->size = 0;
    table->nul = false;
    table->arr = (ElemTablePerfect *)calloc(capacity, sizeof(ElemTablePerfect));
    if(head_table) {
        HashTablePerfect *arr = (HashTablePerfect *) calloc(capacity, sizeof(HashTablePerfect));
        for (int i = 0; i < capacity; i++) {
            table->arr[i].val = arr + i;
        }
    }
    table->HashFunc = HashFunc;
}

bool FindElemTablePerfect(HashTablePerfect *table, ElemToUse ElemToFind)
{
    if(table->capacity == 0)  return false;
    int hash = table->HashFunc(table, ElemToFind);
    if(table->arr[hash].size == 0)         return false;
    HashTablePerfect *t = table->arr[hash].val;

    if(t->capacity == 0)  return false;
    int hash_new = table->HashFunc(table->arr[hash].val, ElemToFind);
    if(t->arr[hash_new].size == 0)  return false;


    LOG("FindElemTablePerfect size = %d t->arr[hash_new].step = %d el = %d\n",t->arr[hash_new].size, t->arr[hash_new].arr[0] , ElemToFind);
    LOG("hash = %d new_hash = %d\n", hash, hash_new);
    if(t->arr[hash_new].arr[0] != ElemToFind)
    {return false;}
    return true;
}

int FindCollision(HashTablePerfect *table, int* val, int len_val);

void GenFirstHashFunc(HashTablePerfect *table, int *val, int AmountCom, int ogranich)
{
    int cnt1 = 0;
    if(table->capacity == 0)  return;
    if(ogranich == 0)  return;
    if(AmountCom == 0)  return;
    int cnt = 0;
    do{
        cnt1++;
        table->consts[0] = rand() % table->capacity;
        table->consts[1] = rand() % table->capacity;
        table->consts[2] = (rand() + table->capacity) % (3 * table->capacity + 1) + 1;
        LOG("const 1 = %d 2 = %d\n", table->consts[0], table->consts[1]);
        cnt = FindCollision(table, val, AmountCom);

        LOG("\n GenFirstHashFunc cnt = %d, ogranich = %d \n", cnt, ogranich);
    }while(cnt > ogranich);

    for(int i = 0; i < AmountCom; i++)
    {
        int hash = table->HashFunc(table, val[i]);
        table->arr[hash].size++;
    }

    for(int i = 0; i < table->capacity; i++) {
        if (table->arr[i].size != 0) {
            table->arr[i].arr = (int *) calloc(sizeof(int), table->arr[i].size);
            InitTablePerfect(table->arr[i].val, table->arr[i].size * 4, &MainHashFuncPerfect, true);

        }
    }
    for(int i = 0; i < AmountCom; i++)
    {
        int hash = table->HashFunc(table, val[i]);
        table->arr[hash].arr[table->arr[hash].step] = val[i];
        table->arr[hash].step++;
    }
}

int FindCollision(HashTablePerfect *table, int* val, int len_val)
{
    int *arr = (int *)calloc(table->capacity, sizeof(int));
    LOG("begin FindCollision table->capacity = %d\n", table->capacity);
    for(int i = 0; i < len_val; i++)
    {
        int hash = table->HashFunc(table, val[i]);
        LOG("hash = %d val = %d |", hash, val[i]);
        arr[hash]++;
    }
    int cnt = 0;
    for(int i = 0; i < table->capacity; i++)
    {
        cnt += (arr[i] * arr[i]);
    }
    free(arr);
    return cnt;
}