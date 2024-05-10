#include "Hash_Perfect.h"

#define CHECK_RES_CALLOC(ptr) \
    if(ptr == NULL) fprintf(stderr, "MEMPRY LIMIT ERROR\n");

int MainHashFuncPerfect(HashTablePerfect *table, ElemToUse ElenToHash)
{
  int hash = (((ElenToHash * table->consts[0] + table->consts[1])
              ) % table->consts[2] % table->capacity + table->capacity) % table->capacity;
  LOG("MainHashFunc hash = %d, ElenToHash = %d const0 = %d const1 = %d cop = %d\n", hash, ElenToHash, table->consts[0], table->consts[1], table->capacity);
  return hash;
}

int MainHashFuncPerfectHashTable(HashTable *table, ElemToUse ElenToHash)
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

  HashTablePerfect *arr = (HashTablePerfect *) calloc(capacity, sizeof(HashTable));
  CHECK_RES_CALLOC(arr)

  for (int i = 0; i < capacity; i++) {
    table->arr[i].val = arr + i;
  }
  table->HashFunc = HashFunc;
}

void GenSecondFunc()
{

}

bool FindElemTablePerfect(HashTablePerfect *table, ElemToUse ElemToFind)
{
  if(table->capacity == 0)  return false;
  int hash = table->HashFunc(table, ElemToFind);
  if(table->arr[hash].size == 0)         return false;
  HashTable *second_table = table->arr[hash].val;

  if(second_table->capacity == 0)  return false;
  int hash_new = MainHashFuncPerfectHashTable(table->arr[hash].val, ElemToFind);
  if(second_table->size == 0)  return false;


   LOG("hash = %d new_hash = %d\n", hash, hash_new);
  if(second_table->arr[hash_new].val != ElemToFind)
  {return false;}
  return true;
}

int FindCollisionHashTablePerfect(HashTablePerfect *table, int* val, int len_val);

void GenSecondHashFunc(HashTable *table, int *val, int AmountCom);

void InitTablePerfect1(HashTable *table, int capacity, int(*HashFunc)(HashTable *, int), double load_factor)
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

void GenFirstHashFunc(HashTablePerfect *table, int *val, int AmountCom, int ogranich)
{
  int cnt1 = 0;
  if(table->capacity == 0)  return;
  if(ogranich == 0)  return;
  if(AmountCom == 0)  return;
  int cnt = 0;
  do{
    cnt1++;
    table->consts[0] = rand() % table->capacity + 1;
    table->consts[1] = rand() % table->capacity + 1;
    table->consts[2] = (rand() + table->capacity) % (3 * table->capacity + 1) + 1;
    LOG("const 1 = %d 2 = %d\n", table->consts[0], table->consts[1]);
    cnt = FindCollisionHashTablePerfect(table, val, AmountCom);

    LOG("\n GenFirstHashFunc cnt = %d, ogranich = %d \n", cnt, ogranich);
  }while(cnt > ogranich);

  for(int i = 0; i < AmountCom; i++)
  {
    int hash = MainHashFuncPerfect(table, val[i]);
    table->arr[hash].size++;
  }

  for(int i = 0; i < table->capacity; i++)
  {
    table->arr[i].arr = (int *) calloc(sizeof(int), table->arr[i].size);
    table->arr[i].step = 0;
  }

  for(int i = 0; i < AmountCom; i++)
  {
    int hash = table->HashFunc(table, val[i]);
    table->arr[hash].arr[table->arr[hash].step] = val[i];
    table->arr[hash].step++;
  }
  int h = 0;
  for(int i = 0; i < table->capacity; i++) {
    if (table->arr[i].size != 0) {
      InitTablePerfect1(table->arr[i].val, table->arr[i].size * table->arr[i].size, &MainHashFuncPerfectHashTable, (double )100);
      GenSecondHashFunc(table->arr[i].val, table->arr[i].arr, table->arr[i].step);
    }
    else
    {
      InitTablePerfect1(table->arr[i].val, 1, &MainHashFuncPerfectHashTable, (double )100);
    }
  }

}

int FindCollisionHashTable(HashTable *table, int* val, int len_val);

void GenSecondHashFunc(HashTable *table, int *val, int AmountCom)
{
  srand(clock());
  int cnt1 = 0;
  if(table->capacity == 0)  return;
  if(AmountCom == 0)  return;

  int cnt = 0;
  do{
    cnt1++;
    table->consts[0] = rand() % table->capacity + 1;
    table->consts[1] = rand() % table->capacity + 1;
    table->consts[2] = rand() % 10000 + 10000 + 1;
    LOG("const 1 = %d 2 = %d\n", table->consts[0], table->consts[1]);
    cnt = FindCollisionHashTable(table, val, AmountCom);
    LOG("\nAmountCom = %d cnt = %d\n", AmountCom, cnt);

  }while(cnt > AmountCom );

  for(int i = 0; i < AmountCom; i++) {
    int hash = MainHashFuncPerfectHashTable(table, val[i]);

    table->arr[hash].val  = val[i];
  }

}

int FindCollisionHashTable(HashTable *table, int* val, int len_val)
{
  int *arr = (int *)calloc(table->capacity, sizeof(int));
  CHECK_RES_CALLOC(arr)
  LOG("begin FindCollisionHashTable table->capacity = %d\n", table->capacity);
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


int FindCollisionHashTablePerfect(HashTablePerfect *table, int* val, int len_val)
{
  int *arr = (int *)calloc(table->capacity, sizeof(int));
  LOG("begin FindCollisionHashTablePerfect table->capacity = %d\n", table->capacity);
  for(int i = 0; i < len_val; i++)
  {
    int hash = MainHashFuncPerfect(table, val[i]);
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