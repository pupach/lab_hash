#include "hash_chain.h"
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

}TestTimeOne;

typedef struct{
    TestTimeOne hash_lin;
    TestTimeOne hash_qud;
    TestTimeOne hash_cep;
    TestTimeOne hash_two;

}TestTimeAll;


TestTimeAll DoTest(int size, int max_size, int capacity, double load_factor)
{
    TestTimeAll ret = {};

    HashTableListCep hash_cep = {};
    InitTableList(&hash_cep, capacity, &MainHashFuncCep, load_factor);

    HashTable hash_lin = {};
    InitTable(&hash_lin, capacity, &MainHashFuncOpenAdress, load_factor);

    HashTable hash_qud = {};
    InitTable(&hash_qud, capacity, &MainHashFuncOpenAdress, load_factor);

    HashTable hash_two = {};
    InitTable(&hash_two, capacity, &MainHashFuncOpenAdress, load_factor);

    int (*data)[2] = (int *)calloc(size, sizeof(int[2]));

    srand(clock());
    for(int i = 0; i < size; i++)
    {
        data[i][0] = rand() % 8;
        data[i][1] = rand() % max_size;
    }

    ret.hash_cep.Insert = clock();
    for(int i = 0; i < size; i++)
    {
        if(data[i][0] == 0) {
            FindTableElemCep(&hash_cep, data[i][1]);
        }
        else if(data[i][0] == 1)
        {
            RemoveTableElemCep(&hash_cep, data[i][1]);
        }
        else
        {
            AddElemTableList(&hash_cep, data[i][1]);
        }
    }
    ret.hash_cep.Insert = clock() - ret.hash_cep.Insert;

    ret.hash_lin.Insert = clock();
    for(int i = 0; i < size; i++)
    {
        if(data[i][0] == 0) {
            FindElemTableLin(&hash_lin, data[i][1]);
        }
        else if(data[i][0] == 1)
        {
            RemoveElemTableLin(&hash_lin, data[i][1]);
        }
        else
        {
            AddElemTableLin(&hash_lin, data[i][1]);
        }
    }
    ret.hash_lin.Insert = clock() - ret.hash_lin.Insert;

    ret.hash_qud.Insert = clock();
    for(int i = 0; i < size; i++)
    {
        if(data[i][0] < 3) {
            FindElemTableQuad(&hash_qud, data[i][1]);
        }
        else if(data[i][0] < 6)
        {
            RemoveElemTableQuad(&hash_qud, data[i][1]);
        }
        else
        {
            AddElemTableQuad(&hash_qud, data[i][1]);
        }
    }
    ret.hash_qud.Insert = clock() - ret.hash_qud.Insert;

    ret.hash_two.Insert = clock();
    for(int i = 0; i < size; i++)
    {
        if(data[i][0] == 0) {
            FindElemTableQuad(&hash_qud, data[i][1]);
        }
        else if(data[i][0] == 1)
        {
            RemoveElemTableQuad(&hash_qud, data[i][1]);
        }
        else
        {
            AddElemTableQuad(&hash_qud, data[i][1]);
        }
    }
    ret.hash_two.Insert = clock() - ret.hash_two.Insert;

    for(int i = 0; i < hash_cep.capacity; i++)
    {
        free(hash_cep.arr[i].arr);
    }
    free(hash_qud.arr);
    free(hash_two.arr);
    free(hash_lin.arr);
    free(data);
    free(hash_cep.arr);


    return ret;
}

#define SIZE 100

int main() {
    TestTimeAll time;
    FILE *stream_hash_lin   = fopen("../data/hash_lin_random_025.txt",    "w");
    FILE *stream_cep_Hash = fopen("../data/Cep_Hash_random_025.txt", "w");
    FILE *stream_hash_quad  = fopen("../data/hash_quad_random_025.txt",  "w");
    FILE *stream_Two_Hash    = fopen("../data/Two_Hash_random_025.txt",    "w");
    double time_insert[SIZE][4] = {};
    double time_remove[SIZE][4] = {};
    //DoTest(1000, 1000, 10000);

    for(int i = 1; i < SIZE + 1; i += 1)
    {
        for(int j = 0; j < 3; j++) {
            fprintf(stderr, "%d\n", i);
            time = DoTest(10000 * i, 10000000, 1000, (double) 5 / (double) 12);

            time_insert[i - 1][0] += ((double) time.hash_lin.Insert) / (double) CLOCKS_PER_SEC / 3;
            time_insert[i - 1][1] += ((double) time.hash_cep.Insert) / (double) CLOCKS_PER_SEC / 3;
            time_insert[i - 1][2] += ((double) time.hash_qud.Insert) / (double) CLOCKS_PER_SEC / 3;
            time_insert[i - 1][3] += ((double) time.hash_two.Insert) / (double) CLOCKS_PER_SEC / 3;
        }
    }

    for(int i = 0; i < SIZE; i++)
    {
        fprintf(stream_hash_lin, "%d,%lf\n", (10000 * (i + 1)), time_insert[i][0]);
        fprintf(stream_cep_Hash, "%d,%lf\n", (10000 * (i + 1)), time_insert[i][1]);
        fprintf(stream_hash_quad, "%d,%lf\n", (10000 * (i + 1)), time_insert[i][2]);
        fprintf(stream_Two_Hash, "%d,%lf\n", (10000 * (i + 1)), time_insert[i][3]);
    }
    fclose(stream_hash_lin);
    fclose(stream_cep_Hash);
    fclose(stream_hash_quad);
    fclose(stream_Two_Hash);

    return 0;
}
