#include "hash_chain/hash_chain.h"
#include "open_adress_hash/hash_open_adress.h"
#include "Hash_Perfect/Hash_Perfect.h"
#include "open_adress_hash/hash_lin.h"
#include "open_adress_hash/hash_quad_func.h"
#include "open_adress_hash/hash_two_func.h"

#define MAX_AMOUNT_TEST_DIR 100

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef struct{
    clock_t Insert;

} TestTimeOne;

typedef struct{
    TestTimeOne hash_lin;
    TestTimeOne hash_quad;
    TestTimeOne hash_cep;
    TestTimeOne hash_two;

} TestTimeAll;


TestTimeAll DoTest(int size, int max_size, int capacity, double load_factor)
{
    TestTimeAll ret = {};

    HashTableListCep hash_cep = {};
    InitTableList(&hash_cep, capacity, &MainHashFuncCep, load_factor);

    HashTable hash_lin = {};
    InitTable(&hash_lin, capacity, &MainHashFuncOpenAdress, load_factor);

    HashTable hash_quad = {};
    InitTable(&hash_quad, capacity, &MainHashFuncOpenAdress, load_factor);

    HashTable hash_two = {};
    InitTable(&hash_two, capacity, &MainHashFuncOpenAdress,load_factor );

    int *data = (int *)calloc(size, sizeof(int));
    CHECK_RES_CALLOC(data)
    
    srand(clock());
    for(int i = 0; i < size; i++)
    {
        data[i] = rand() % max_size;
    }

    ret.hash_cep.Insert = clock();
    for(int i = 0; i < size; i++)
    {
        AddElemTableList(&hash_cep, data[i]);
    }
    ret.hash_cep.Insert = clock() - ret.hash_cep.Insert;

    fprintf(stderr, "hash_cep ready\n");

    ret.hash_lin.Insert = clock();
    for(size_t i = 0; i < size; i++)
    {
        AddElemTableLin(&hash_lin, data[i]);
    }
    ret.hash_lin.Insert = clock() - ret.hash_lin.Insert;

    fprintf(stderr, "hash_lin ready\n");

    ret.hash_quad.Insert = clock();
    for(int i = 0; i < size; i++)
    {
        AddElemTableQuad(&hash_quad, data[i]);
    }
    ret.hash_quad.Insert = clock() - ret.hash_quad.Insert;

    fprintf(stderr, "hash_quad ready\n");

    ret.hash_two.Insert = clock();
    for(int i = 0; i < size; i++)
    {
        AddElemTableTwo(&hash_two, data[i]);
    }
    ret.hash_two.Insert = clock() - ret.hash_two.Insert;

    fprintf(stderr, "hash_two ready\n");


    for(int i = 0; i < hash_cep.capacity; i++)
    {
        free(hash_cep.arr[i].arr);
    }
    free(hash_quad.arr);
    free(hash_two.arr);
    free(hash_lin.arr);
    free(hash_cep.arr);
    free(data);

    return ret;
}

#define AMOUNT_TEST 23
#define COUNT_HASH_TABLE 4
#define AMOUNT_TRY 3

int main() {
    TestTimeAll time;
    FILE *stream_hash_lin   = fopen("../data/hash_lin.txt",    "w");
    FILE *stream_cep_Hash   = fopen("../data/Cep_Hash.txt", "w");
    FILE *stream_hash_quad  = fopen("../data/hash_quad.txt",  "w");
    FILE *stream_Two_Hash   = fopen("../data/Two_Hash.txt",    "w");
    double time_insert[AMOUNT_TEST][COUNT_HASH_TABLE] = {};

    for(int i = 1; i < AMOUNT_TEST + 1; i += 1)
    {
        for(int j = 0; j < AMOUNT_TRY; j++) {
            time = DoTest(100000, 10000000, 1000,  (double) 6 / (double) (i + 7) );

            time_insert[i - 1][0] += ((double) time.hash_lin.Insert) / (double) CLOCKS_PER_SEC / (double)AMOUNT_TRY;
            time_insert[i - 1][1] += ((double) time.hash_cep.Insert) / (double) CLOCKS_PER_SEC / (double)AMOUNT_TRY;
            time_insert[i - 1][2] += ((double) time.hash_quad.Insert) / (double) CLOCKS_PER_SEC / (double)AMOUNT_TRY;
            time_insert[i - 1][3] += ((double) time.hash_two.Insert) / (double) CLOCKS_PER_SEC / (double)AMOUNT_TRY;
        }
    }

    for(int i = 0; i < AMOUNT_TEST; i++)
    {
        fprintf(stream_hash_lin,  "%lf,%lf\n", (double) (i + 7) / (double) 6, time_insert[i][0]);
        fprintf(stream_cep_Hash,  "%lf,%lf\n", (double) (i + 7) / (double) 6, time_insert[i][1]);
        fprintf(stream_hash_quad, "%lf,%lf\n", (double) (i + 7) / (double) 6, time_insert[i][2]);
        fprintf(stream_Two_Hash,  "%lf,%lf\n", (double) (i + 7) / (double) 6, time_insert[i][3]);
    }
    fclose(stream_hash_lin);
    fclose(stream_cep_Hash);
    fclose(stream_hash_quad);
    fclose(stream_Two_Hash);

    return 0;
}
