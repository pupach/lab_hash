#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#include "DoubleHash.h"

double  GiveLoadFactor(Table* table)
{
    double load_factor = (table->size) / (table->capacity);
    return load_factor;
}

int hash1(int key, size_t table_size)
{
    return (key % table_size);
}

int hash2(int key, int table_size)
{
    int hash = table_size + 1 - (key % table_size);
    if (hash % 2 == 0)
    {
        return hash + 1;
    }
    return hash;
}

Table* TableCtor(size_t capacity)
{
    //ABOBA;
    assert(capacity > 0);

    Table* table      = (Table*)calloc(1, sizeof(Table));
    if (table == NULL)
    {
        return (Table*)ERROR_OF_ALLOCATING_MEMORY;
    }

    table->size       = 0;
    table->capacity   = capacity;

    table->hash_table = (Node**)calloc(table->capacity, sizeof(Node*));
    if (table->hash_table == NULL)
    {
        return (Table*)ERROR_OF_ALLOCATING_MEMORY;
    }
    return table;
}

void TableDtor(Table* table)
{
    assert(table != NULL);
    //ABOBA;

    table->size     = 0;
    table->capacity = 0;

    free(table->hash_table);
    free(table);
}

Table* add(Table* table, int key, double load_factor)
{
    assert(table != NULL);

    int hash_index = hash1(key, table->capacity);
    int i = 1;

    while (table->hash_table[hash_index] != NULL)
    {
        int hash2_value = hash2(key, table->capacity);
        hash_index = (hash1(key, table->capacity) + i * hash2_value) % table->capacity;
        i++;
    }

    Node* new_node = (Node*)calloc(1, sizeof(Node));
    new_node->value = key;

    table->hash_table[hash_index] = new_node;
    table->size++;

    if (GiveLoadFactor(table) >= load_factor)
    {
        table = Rehash(table, load_factor);
    }

    return table;
}



Table* Rehash(Table* table, double load_factor)
{
    assert(table != NULL);
    //ABOBA;

    int new_capacity  = 2 * (table->capacity);
    Table* new_table  = TableCtor(new_capacity);
    for (int i  = 0; i < table->capacity; i++)
    {
        if (table->hash_table[i] != NULL)
        {
            new_table = add(new_table, table->hash_table[i]->value, load_factor);
        }
    }
    TableDtor(table);
    return new_table;
}

bool check(Table* table, int key)
{
    assert(table != NULL);

    int hash_index = hash1(key, table->capacity);
    int i = 1; // Счетчик попыток, начинается с 1

    while (table->hash_table[hash_index] != NULL)
    {
        if (table->hash_table[hash_index]->value == key)
        {
            return true; // Ключ найден
        }

        int hash2_value = hash2(key, table->capacity);
        hash_index = (hash1(key, table->capacity) + i * hash2_value) % table->capacity;
        i++;
    }

    return false; // Ключ не найден
}

void delete(Table* table, int key)
{
    assert(table != NULL);

    int hash_index = hash1(key, table->capacity);
    int i = 1; // Счетчик попыток, начинается с 1

    while (table->hash_table[hash_index] != NULL)
    {
        if (table->hash_table[hash_index]->value == key)
        {
            free(table->hash_table[hash_index]);
            table->hash_table[hash_index] = NULL;
            table->size--;
            break;
        }

        int hash2_value = hash2(key, table->capacity);
        hash_index = (hash1(key, table->capacity) + i * hash2_value) % table->capacity;
        i++;
    }
}



void LoadFactorTester(int capacity, double load_factor)
{
    assert(capacity > 0);
    //ABOBA;

    FILE* res_file = fopen("result/open_load_factor", "a");
    if (res_file == NULL)
    {
        return;
    }
    Table* table = TableCtor(capacity);

    double time_spent = 0.0;
    clock_t begin     = clock();

    for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
    {
        int data = i;
        table = add(table, data, load_factor);
    }

    clock_t end       = clock();
    time_spent       += (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(res_file, "%lg %lg\n", load_factor, time_spent);

    TableDtor(table);
}

void FirstTest()
{
    FILE* test_file = fopen(FIRST_TEST_FILE, "w");
    if (test_file == NULL)
    {
    return;
    }
    for (int size = 10000; size < 1000000; size += 10000)
    {
    Table* table = TableCtor(size);

    double time_spent = 0.0;
    clock_t begin     = clock();

    for (int i = 0; i < size; i++)
    {
    int data = rand();

    if (data % SECOND_MOD == 0)
    {
    table = add(table, data, MAX_LOAD_FACTOR);
    }
    else if (data % SECOND_MOD == 2)
    {
    check(table, data);
    }
    else if (data % SECOND_MOD == 1)
    {
    delete(table, data);
    }
    }

    clock_t end       = clock();
    time_spent       += (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(test_file, "%d %lg\n", size, time_spent);
    TableDtor(table);
    }
    fclose(test_file);
}
void SecondTest()
{
    FILE* test_file = fopen(SECOND_TEST_FILE, "w");
    if (test_file == NULL)
    {
        return;
    }
    for (int size = 10000; size < 1000000; size += 10000)
    {
        Table* table = TableCtor(size);

        double time_spent = 0.0;
        clock_t begin     = clock();

        for (int i = 0; i < size; i++)
        {
            int data = rand();

            if (data % (SECOND_MOD / 2) == 0)
            {
                table = add(table, data, MAX_LOAD_FACTOR);
            }
            else if (data % SECOND_MOD == 2)
            {
                check(table, data);
            }
            else
            {
                delete(table, data);
            }
        }

        clock_t end       = clock();
        time_spent       += (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(test_file, "%d %lg\n", size, time_spent);
        TableDtor(table);
    }
    fclose(test_file);
}

int main()
{
/*
    for (double load_factor = 0.1; load_factor < 1; load_factor += 0.05)
    {
        int capacity = NUMBER_OF_ELEMENTS / load_factor;
        LoadFactorTester(capacity, load_factor);
    }
*/
    //FirstTest();
    SecondTest();

    return 0;
}