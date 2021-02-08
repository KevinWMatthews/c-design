/**
 * @file hash_table_intro2.c
 */
#include "hash_table2.h"
#include <stdio.h>

void print_key_value_pair(struct HashTable2* table, ht2_key_t key)
{
    int value = 0;
    switch (ht2_lookup(table, key, &value))
    {
        case HT2_ERROR:
            fprintf(stderr, "Table2 search error\n");
            break;
        case HT2_KEY_FOUND:
            fprintf(stdout, "table[\"%s\"] = %d\n", key, value);
            break;
        case HT2_KEY_NOT_FOUND:
            fprintf(stdout, "table[\"%s\"] = not found\n", key);
            break;
    }
}

void insert_and_delete(void)
{
    size_t capacity = 123;
    struct HashTable2* table = ht2_create(capacity);

    ht2_insert(table, "one", 1);
    ht2_insert(table, "two", 2);
    ht2_insert(table, "collision", 42);
    ht2_insert(table, "collision", 43);
    ht2_insert(table, "three", 3);

    print_key_value_pair(table, "one");
    print_key_value_pair(table, "two");
    print_key_value_pair(table, "collision");
    print_key_value_pair(table, "dne");
    print_key_value_pair(table, "three");

    ht2_delete(table, "collision");
    print_key_value_pair(table, "collision");

    // TODO use a small hash table to verify insert/delete in the linked list
    ht2_delete(table, "two");
    print_key_value_pair(table, "two");

    ht2_destroy(table);
}

void fill_table(void)
{
    size_t capacity = 3;
    struct HashTable2* table = ht2_create(capacity);

    // Check hashing function to ensure that values actually fill the table
    ht2_insert(table, "0", 0);
    ht2_insert(table, "1", 1);
    ht2_insert(table, "2", 2);
    ht2_insert(table, "3", 3);
    ht2_insert(table, "4", 4);
    ht2_insert(table, "5", 5);

    print_key_value_pair(table, "0");
    print_key_value_pair(table, "1");
    print_key_value_pair(table, "2");
    print_key_value_pair(table, "3");
    print_key_value_pair(table, "4");
    print_key_value_pair(table, "5");

    ht2_destroy(table);
}

int main(void)
{
    insert_and_delete();
    // fill_table();
    return 0;
}
