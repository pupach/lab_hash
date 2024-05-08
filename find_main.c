#include "hash_cep.h"
#include "hash_lin.h"
#include "PerfectHashFind.h"

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


TestTimeAll DoOneTest(int size, int max_size, int amount_find)
{
    TestTimeAll ret = {};

    HashTableListCep hash_cep = {};
    hash_cep.load_factor = (double) 8 / (double) 10;
    InitTableList(&hash_cep, size * 2, &MainHashFuncCep);

    HashTable hash_lin = {};
    hash_lin.load_factor = (double) 8 / (double) 10;
    InitTable(&hash_lin, size * 2, &MainHashFunc);

    HashTable hash_qud = {};
    hash_qud.load_factor = (double) 8 / (double) 10;
    InitTable(&hash_qud, size * 2, &MainHashFunc);

    int *data = (int *)calloc(size, sizeof(int));
    int *ind_to_find = (int *)calloc(amount_find, sizeof(int));

    srand(clock());

    HashTablePerfect hash_pefect = {};
    InitTablePerfect(&hash_pefect, (int)sqrt((double) size) * 2, &MainHashFuncPerfect, true);

    for(int i = 0; i < size; i++)
    {
        data[i] = rand() % max_size;
        AddElemTableList(&hash_cep, data[i]);
        AddElemTableLin(&hash_lin, data[i]);
        AddElemTableQuad(&hash_qud, data[i]);
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

    GenFirstHashFunc(&hash_pefect, data, size, 4 * hash_pefect.capacity);
    for(int i = 0; i < hash_pefect.capacity; i++)
    {
        GenFirstHashFunc(hash_pefect.arr[i].val, hash_pefect.arr[i].arr, hash_pefect.arr[i].step, 8 * hash_pefect.arr[i].size);
    }
    ret.hash_two.Insert = clock();
    for(int i = 0; i < size; i++)
    {
        FindElemTablePerfect(&hash_pefect, data[ind_to_find[i]]);
    }
    ret.hash_two.Insert = clock() - ret.hash_two.Insert;


    free(hash_pefect.arr);



    return ret;
}

#define SIZE 5

int main() {
    TestTimeAll time;
    FILE *stream_hash_lin   = fopen("hash_lin_find.txt",    "w");
    FILE *stream_cep_Hash = fopen("Cep_Hash_find.txt", "w");
    FILE *stream_hash_quad  = fopen("hash_quad_find.txt",  "w");
    FILE *stream_Two_Hash    = fopen("Perfect_find.txt",    "w");
    double time_insert[SIZE][4] = {};
    double time_remove[SIZE][4] = {};
    //DoOneTest(1000, 1000, 10000);

    for(int i = 1; i < SIZE + 1; i += 1)
    {
        for(int j = 0; j < 3; j++) {
            time = DoOneTest(100000, 1000000, 10000000);

            time_insert[i - 1][0] += ((double) time.hash_lin.Insert) / (double) CLOCKS_PER_SEC / 3;
            time_insert[i - 1][1] += ((double) time.hash_cep.Insert) / (double) CLOCKS_PER_SEC / 3;
            time_insert[i - 1][2] += ((double) time.hash_qud.Insert) / (double) CLOCKS_PER_SEC / 3;
            time_insert[i - 1][3] += ((double) time.hash_two.Insert) / (double) CLOCKS_PER_SEC / 3;
        }
    }

    for(int i = 0; i < SIZE; i++)
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
