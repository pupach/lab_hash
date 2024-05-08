#include "hash_cep.h"
#include "hash_lin.h"
#include "Perfect_Hash.h"

#include <stdio.h>
#include <stdlib.h>
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


TestTimeAll DoOneTest(int size, int max_size, int capacity, double load_factor)
{
    TestTimeAll ret = {};

    HashTableListCep hash_cep = {};
    hash_cep.load_factor = load_factor;
    InitTableList(&hash_cep, capacity, &MainHashFuncCep);

    HashTable hash_lin = {};
    hash_lin.load_factor = load_factor;
    InitTable(&hash_lin, capacity, &MainHashFunc);

    HashTable hash_qud = {};
    hash_qud.load_factor = load_factor;
    InitTable(&hash_qud, capacity, &MainHashFunc);

    HashTable hash_two = {};
    hash_two.load_factor = load_factor;
    InitTable(&hash_two, capacity, &MainHashFunc);

    int *data = (int *)calloc(size, sizeof(int));

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
    for(int i = 0; i < size; i++)
    {
        AddElemTableLin(&hash_lin, data[i]);
    }
    ret.hash_lin.Insert = clock() - ret.hash_lin.Insert;

    fprintf(stderr, "hash_lin ready\n");

    ret.hash_qud.Insert = clock();
    for(int i = 0; i < size; i++)
    {
        AddElemTableQuad(&hash_qud, data[i]);
    }
    ret.hash_qud.Insert = clock() - ret.hash_qud.Insert;

    fprintf(stderr, "hash_qud ready\n");

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
    free(hash_qud.arr);
    free(hash_two.arr);
    free(hash_lin.arr);
    free(hash_cep.arr);
    free(data);


    return ret;
}

#define SIZE 23

int main() {
    TestTimeAll time;
    FILE *stream_hash_lin   = fopen("hash_lin.txt",    "w");
    FILE *stream_cep_Hash   = fopen("Cep_Hash.txt", "w");
    FILE *stream_hash_quad  = fopen("hash_quad.txt",  "w");
    FILE *stream_Two_Hash   = fopen("Two_Hash.txt",    "w");
    double time_insert[SIZE][4] = {};
    double time_remove[SIZE][4] = {};
    //DoOneTest(1000, 1000, 10000);

    for(int i = 1; i < SIZE + 1; i += 1)
    {
        for(int j = 0; j < 3; j++) {
            time = DoOneTest(100000, 10000000, 1000,  (double) 6 / (double) (i + 7) );

            time_insert[i - 1][0] += ((double) time.hash_lin.Insert) / (double) CLOCKS_PER_SEC / (double)3;
            time_insert[i - 1][1] += ((double) time.hash_cep.Insert) / (double) CLOCKS_PER_SEC / (double)3;
            time_insert[i - 1][2] += ((double) time.hash_qud.Insert) / (double) CLOCKS_PER_SEC / (double)3;
            time_insert[i - 1][3] += ((double) time.hash_two.Insert) / (double) CLOCKS_PER_SEC / (double)3;
        }
    }

    for(int i = 0; i < SIZE; i++)
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
