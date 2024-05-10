#include "hash_chain.h"
#include "Hash_Perfect.h"
#include "hash_open_adress.h"
#include "hash_lin.h"
#include "hash_quad_func.h"
#include "hash_two_func.h"


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>


typedef struct{
  clock_t Insert;

} TestTimeOne;

typedef struct{
  TestTimeOne hash_lin;
  TestTimeOne hash_qud;
  TestTimeOne hash_cep;
  TestTimeOne hash_two;

} TestTimeAll;

bool FindElem(int *arr, int size, int val)
{
  for(int i = 0; i < size; i++)
  {
    if(arr[i] == val) return true;
  }
  return false;
}



TestTimeAll DoTest(int size, int max_size, int amount_find, double probability)
{
  TestTimeAll ret = {};

  HashTableListCep hash_cep = {};

  InitTableList(&hash_cep, size * 2, &MainHashFuncCep, (double) 8 / (double) 10);

  HashTable hash_lin = {};
  InitTable(&hash_lin, size * 2, &MainHashFuncOpenAdress, (double) 8 / (double) 10);

  HashTable hash_qud = {};

  InitTable(&hash_qud, size * 2, &MainHashFuncOpenAdress, (double) 8 / (double) 10);

  int *data = (int *)calloc(size, sizeof(int));
  int *ind_to_find = (int *)calloc(amount_find, sizeof(int));
  CHECK_RES_CALLOC(ind_to_find)
  CHECK_RES_CALLOC(data)

  srand(clock());

  HashTablePerfect hash_pefect = {};
  InitTablePerfect(&hash_pefect,  size, &HashPerfect, true);

  for(int i = 0; i < size; i++)
  {
    data[i] = rand() % max_size + 1;

    if(FindElem(data, i, data[i])) i = i - 1;
    else {
      AddElemTableList(&hash_cep, data[i]);
      AddElemTableLin(&hash_lin, data[i]);
      AddElemTableQuad(&hash_qud, data[i]);
    }
  }

  for(int i = 0; i < amount_find; i++)
  {
    ind_to_find[i] = rand() % size;
  }

  ret.hash_cep.Insert = clock();
  for(int i = 0; i < amount_find; i++)
  {
    FindTableElemCep(&hash_cep, data[ind_to_find[i]]);
  }
  ret.hash_cep.Insert = clock() - ret.hash_cep.Insert;

  ret.hash_lin.Insert = clock();
  for(int i = 0; i < amount_find; i++)
  {
    FindElemTableLin(&hash_lin, data[ind_to_find[i]]);
  }
  ret.hash_lin.Insert = clock() - ret.hash_lin.Insert;

  ret.hash_qud.Insert = clock();
  for(int i = 0; i < amount_find; i++)
  {
    FindElemTableQuad(&hash_qud, data[ind_to_find[i]]);
  }
  ret.hash_qud.Insert = clock() - ret.hash_qud.Insert;

  for(int i = 0; i < hash_cep.capacity; i++)
  {
    free(hash_cep.arr[i].arr);
  }
  free(hash_qud.arr);
  free(hash_lin.arr);
  free(hash_cep.arr);

  fprintf(stderr, "done\n");

  GenFirstHashFunc(&hash_pefect, data, size, 4 * hash_pefect.capacity);

  ret.hash_two.Insert = clock();
  for(int i = 0; i < size; i++)
  {

    FindElemTablePerfect(&hash_pefect, data[ind_to_find[i]]);
  }
  ret.hash_two.Insert = clock() - ret.hash_two.Insert;


  free(hash_pefect.arr);



  return ret;
}

#define AMOUNT_TEST 4
#define AMOUNT_TRY 3
#define COUNT_HASH_TABLE 4

int main() {
  TestTimeAll time;
  FILE *stream_hash_lin   = fopen("../data/hash_lin_find.txt",    "w");
  FILE *stream_cep_Hash = fopen("../data/Cep_Hash_find.txt", "w");
  FILE *stream_hash_quad  = fopen("../data/hash_quad_find.txt",  "w");
  FILE *stream_Two_Hash    = fopen("../data/Perfect_find.txt",    "w");
  double time_insert[AMOUNT_TEST][COUNT_HASH_TABLE] = {};

  for(int i = 1; i < AMOUNT_TEST + 1; i += 1)
  {
    for(int j = 0; j < AMOUNT_TRY; j++) {
      fprintf(stderr, "%d\n", i);
      time = DoTest(100000, 1000000, 10000000, 1);

      time_insert[i - 1][0] += ((double) time.hash_lin.Insert) / (double) CLOCKS_PER_SEC / AMOUNT_TRY;
      time_insert[i - 1][1] += ((double) time.hash_cep.Insert) / (double) CLOCKS_PER_SEC / AMOUNT_TRY;
      time_insert[i - 1][2] += ((double) time.hash_qud.Insert) / (double) CLOCKS_PER_SEC / AMOUNT_TRY;
      time_insert[i - 1][3] += ((double) time.hash_two.Insert) / (double) CLOCKS_PER_SEC / AMOUNT_TRY;
    }
  }

  for(int i = 0; i < AMOUNT_TEST; i++)
  {
    fprintf(stream_hash_lin, "%d, %lf\n",1,  time_insert[i][0]);
    fprintf(stream_cep_Hash, "%d, %lf\n",1,  time_insert[i][1]);
    fprintf(stream_hash_quad, "%d, %lf\n",1,  time_insert[i][2]);
    fprintf(stream_Two_Hash, "%d, %lf\n",1, time_insert[i][3]);
  }
  fclose(stream_hash_lin);
  fclose(stream_cep_Hash);
  fclose(stream_hash_quad);
  fclose(stream_Two_Hash);

  return 0;
}
