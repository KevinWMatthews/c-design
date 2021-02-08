/**
 * @file hash_table_intro1.c
 * Separate chaining with linked lists.
 */

#include "hash_table1.h"
#include <stdio.h>

void print_key_value_pair(struct HashTable1* table, ht1_key_t key)
{
    int value = 0;
    switch (ht1_lookup(table, key, &value))
    {
        case HT1_ERROR:
            fprintf(stderr, "Table1 search error\n");
            break;
        case HT1_KEY_FOUND:
            fprintf(stdout, "table[\"%s\"] = %d\n", key, value);
            break;
        case HT1_KEY_NOT_FOUND:
            fprintf(stdout, "table[\"%s\"] = not found\n", key);
            break;
    }
}

void insert_and_delete(void)
{
    size_t capacity = 123;
    struct HashTable1* table = ht1_create(capacity);

    ht1_insert(table, "one", 1);
    ht1_insert(table, "two", 2);
    ht1_insert(table, "collision", 42);
    ht1_insert(table, "collision", 43);
    ht1_insert(table, "three", 3);

    print_key_value_pair(table, "one");
    print_key_value_pair(table, "two");
    print_key_value_pair(table, "collision");
    print_key_value_pair(table, "dne");
    print_key_value_pair(table, "three");

    ht1_delete(table, "collision");
    print_key_value_pair(table, "collision");

    // TODO use a small hash table to verify insert/delete in the linked list
    ht1_delete(table, "two");
    print_key_value_pair(table, "two");

    ht1_destroy(table);
}

void fill_table(void)
{
    size_t capacity = 3;
    struct HashTable1* table = ht1_create(capacity);

    // Check hashing function to ensure that values actually fill the table
    ht1_insert(table, "0", 0);
    ht1_insert(table, "1", 1);
    ht1_insert(table, "2", 2);
    ht1_insert(table, "3", 3);
    ht1_insert(table, "4", 4);
    ht1_insert(table, "5", 5);

    print_key_value_pair(table, "0");
    print_key_value_pair(table, "1");
    print_key_value_pair(table, "2");
    print_key_value_pair(table, "3");
    print_key_value_pair(table, "4");
    print_key_value_pair(table, "5");

    ht1_destroy(table);
}

int main(void)
{
    insert_and_delete();
    // fill_table();
    return 0;
}
