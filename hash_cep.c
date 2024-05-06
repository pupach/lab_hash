#include "hash_cep.h"

void List_init(List *list, int beg_capacity)
{
  list->capacity = beg_capacity;

  list->arr = (Elem_listCep *)calloc(sizeof(Elem_listCep), list->capacity + 1);

  list->arr[0].val = 1;
  list->arr[0].next = 0;
  list->arr[0].prev = 0;
  for(int i = 1; i < list->capacity + 1; i++)
  {
    list->arr[i].prev = i - 1;
    list->arr[i].next = i + 1;
  }
}

void Realloc_List(List *list, int new_capacity)
{

  if(new_capacity == -1)  new_capacity = list->capacity * 2;

  Elem_listCep *new_list_arr = (Elem_listCep *)realloc(list->arr, (new_capacity + 1) * sizeof(Elem_listCep));

  list->arr = new_list_arr;

  for(int i = list->capacity; i < new_capacity + 1; i++)
  {
    list->arr[i].prev = i - 1;
    list->arr[i].next = i + 1;
  }

  list->capacity = new_capacity;
}

bool find_Elem_in_list(List *list, int ind_to_find)
{
    int cur_ind = 0;

    for (int cur_Elem = 0; cur_Elem < list->capacity; cur_Elem++)
    {
        cur_ind = list->arr[cur_ind].next;
        if (list->arr[cur_ind].val == ind_to_find) return true;
    }

    return false;
}


void List_add_Elem_on_O1(List *list, long int val_Elem, int ind_to_ins)
{
  if(list->arr[0].val == list->capacity)
  {
    Realloc_List(list, -1);
  }
  Elem_listCep *free_elem = list->arr + list->arr[0].val;
  int next_free_Elem = free_elem->next;

  free_elem->val = (int )val_Elem;
  free_elem->prev = list->arr[ind_to_ins].prev;
  free_elem->next = ind_to_ins;

  list->arr[ind_to_ins].prev = list->arr[0].val;
  list->arr[free_elem->prev].next = list->arr[0].val;

  list->arr[0].val = next_free_Elem;

  list->arr[next_free_Elem].prev = list->arr[0].prev;
}

int MainHashFuncCep(HashTableListCep *table, ElemToUseList ElenToHash)
{
  int hash = (int)((ElenToHash * table->consts[0] + table->consts[1])
              % PowerUniverse) % table->capacity;
  return hash;
}
void ReHashCep(HashTableListCep *table);

void AddElemTableList(HashTableListCep *table, ElemToUseList ElemToAdd)
{
    if(table->size > (int)(((double )table->capacity) * table->load_factor))
    {
        ReHashCep(table);
    }

  int hash = table->HashFunc(table, ElemToAdd);

  if(table->arr[hash].arr[0].val == 1) table->size++;

  bool res = find_Elem_in_list(&table->arr[hash], ElemToAdd);
  if(res) return;

  List_add_Elem_on_O1(&table->arr[hash], ElemToAdd, table->arr[hash].arr[0].val);
  return;
}

void List_remove_Elem_on_O1(List *list, int ind_to_ins) {
  int next_free_Elem = ind_to_ins;

  list->arr[list->arr[ind_to_ins].prev].next = list->arr[ind_to_ins].next;
  list->arr[list->arr[ind_to_ins].next].prev = list->arr[ind_to_ins].prev;

  list->arr[ind_to_ins].prev = list->arr[0].prev;
  list->arr[ind_to_ins].next = list->arr[0].val;

  list->arr[list->arr[0].val].prev = ind_to_ins;

  list->arr[0].val = ind_to_ins;
}

void ReHashCep(HashTableListCep *table)
{
    int old_cap = table->capacity;
    table->capacity *= 2;
    ElemTableList *old_arr = table->arr;
    InitTableList(table, table->capacity, table->HashFunc);


    for(int i = 0; i < old_cap; i++)
    {
        if(old_arr[i].arr[0].val != 1)
        {
            Elem_listCep *cur_elem = old_arr[i].arr + old_arr[i].arr[0].next;

            while(cur_elem != old_arr[i].arr){
                AddElemTableList(table, cur_elem->val);
                cur_elem = old_arr[i].arr + cur_elem->next;
            }
            free(old_arr[i].arr);
        }
    }
    free(old_arr);
}


void RemoveTableElemCep(HashTableListCep *table, long int ElemToRemove)
{
  int hash = table->HashFunc(table, ElemToRemove);

  Elem_listCep *cur_elem = table->arr[hash].arr;
  int i = 0;

  do{
    cur_elem = table->arr[hash].arr + cur_elem->next;

    if(table->arr[hash].arr  == cur_elem) return;
  } while(cur_elem->val != ElemToRemove);

  List_remove_Elem_on_O1(table->arr + hash, (cur_elem - table->arr[hash].arr)/ sizeof(Elem_listCep));
}

bool FindTableElemCep(HashTableListCep *table, int ElemToRemove)
{
    int hash = table->HashFunc(table, ElemToRemove);

    return find_Elem_in_list(table->arr + hash, ElemToRemove);
}


void InitTableList(HashTableListCep *table, int capacity, int(*HashFunc)(HashTableListCep *, ElemToUseList))
{
    table->consts[0] = 3;
    table->consts[1] = 1;
  table->capacity = capacity;
  table->size = 0;
  table->arr = (ElemTableList *)calloc(capacity, sizeof(ElemTableList));
  for(int i = 0; i < capacity; i++)
  {
    List_init(table->arr + i, BEG_CAPACITY_LIST);
  }
  table->HashFunc = HashFunc;
}

