/**
 * @file hash_table_intro.c
 * Separate chaining with linked lists.
 */

#include "hash_table.h"
#include <stdio.h>

void print_key_value_pair(struct HashTable* table, ht_key_t key)
{
    int value = 0;
    switch (ht_value_of(table, key, &value))
    {
        case HT_ERROR:
            fprintf(stderr, "Table search error\n");
            break;
        case HT_KEY_FOUND:
            fprintf(stdout, "table[\"%s\"] = %d\n", key, value);
            break;
        case HT_KEY_NOT_FOUND:
            fprintf(stdout, "table[\"%s\"] = not found\n", key);
            break;
    }
}

void insert_and_delete(void)
{
    size_t capacity = 123;
    struct HashTable* table = ht_create(capacity);

    ht_insert(table, "one", 1);
    ht_insert(table, "two", 2);
    ht_insert(table, "collision", 42);
    ht_insert(table, "collision", 43);
    ht_insert(table, "three", 3);

    print_key_value_pair(table, "one");
    print_key_value_pair(table, "two");
    print_key_value_pair(table, "collision");
    print_key_value_pair(table, "dne");
    print_key_value_pair(table, "three");

    ht_delete(table, "collision");
    print_key_value_pair(table, "collision");

    // TODO use a small hash table to verify insert/delete in the linked list
    ht_delete(table, "two");
    print_key_value_pair(table, "two");

    ht_destroy(table);
}

void fill_table(void)
{
    size_t capacity = 3;
    struct HashTable* table = ht_create(capacity);

    // Check hashing function to ensure that values actually fill the table
    ht_insert(table, "0", 0);
    ht_insert(table, "1", 1);
    ht_insert(table, "2", 2);
    ht_insert(table, "3", 3);
    ht_insert(table, "4", 4);
    ht_insert(table, "5", 5);

    print_key_value_pair(table, "0");
    print_key_value_pair(table, "1");
    print_key_value_pair(table, "2");
    print_key_value_pair(table, "3");
    print_key_value_pair(table, "4");
    print_key_value_pair(table, "5");

    ht_destroy(table);
}

int main(void)
{
    insert_and_delete();
    // fill_table();
    return 0;
}
