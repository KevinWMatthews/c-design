/**
 * @file hash_table2.c
 */
#include "hash_table2.h"
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>


static struct HashTable2Item* ht2_item_create(ht2_key_t key, ht2_value_t value);
static void ht2_item_destroy(struct HashTable2Item* item);
static bool ht2_key_is_match(ht2_key_t key1, ht2_key_t key2);
static ht2_key_t ht2_key_copy(ht2_key_t key);
static ht2_value_t ht2_value_copy(ht2_value_t value);
static unsigned long ht2_hash_function(char const* str, size_t index_range);

/*
 * Hash table API
 */
struct HashTable2* ht2_create(size_t size)
{
    struct HashTable2* table = calloc(1, sizeof(*table));
    assert(table);
    table->size = size;
    table->bucket_list = calloc(table->size, sizeof(*table->bucket_list));
    return table;
}

void ht2_destroy(struct HashTable2* table)
{
    assert(table);
    for (size_t i = 0; i < table->size; i++)
    {
        struct HashTable2Bucket* bucket = &table->bucket_list[i];
        struct HashTable2Item* item = bucket->item;
        while (item)
        {
            struct HashTable2Item* next = item->next;
            ht2_item_destroy(item);
            item = next;
        }
    }
    if (table->bucket_list)
    {
        free(table->bucket_list);
    }
    free(table);
}

void ht2_insert(struct HashTable2* table, ht2_key_t key, ht2_value_t value)
{
    assert(key);

    size_t index = ht2_hash_function(key, table->size);
    struct HashTable2Bucket* bucket = &table->bucket_list[index];
    struct HashTable2Item** slot = &bucket->item;
    struct HashTable2Item* item = *slot;
    while (item)
    {
        // Hash collision
        if (ht2_key_is_match(item->key, key))
        {
            // Item exists; update and exit
            item->value = value;
            return;
        }
        // Keep walking the linked list
        slot = &item->next;
        item = *slot;
    }
    // Found an empty slot in the linked list (or the first item)
    *slot = ht2_item_create(key, value);
}

void ht2_delete(struct HashTable2* table, ht2_key_t key)
{
    assert(table);
    assert(key);

    size_t index = ht2_hash_function(key, table->size);
    struct HashTable2Bucket* bucket = &table->bucket_list[index];
    struct HashTable2Item** slot = &bucket->item;
    while (slot)
    {
        struct HashTable2Item* item = *slot;
        if (ht2_key_is_match(item->key, key))
        {
            // Item found; remove it from linked list
            *slot = item->next;
            ht2_item_destroy(item);
            return;
        }
        // Keep walking the list
        slot = &item->next;
    }
    // Item not found?
}

enum HashTable2Result ht2_lookup(struct HashTable2* table, ht2_key_t key, ht2_value_t* value)
{
    assert(table);
    assert(key);
    assert(value);

    size_t index = ht2_hash_function(key, table->size);
    struct HashTable2Bucket* bucket = &table->bucket_list[index];
    struct HashTable2Item* item = bucket->item;

    while (item)
    {
        if (ht2_key_is_match(item->key, key))
        {
            *value = item->value;
            return HT2_KEY_FOUND;
        }
        else
        {
            item = item->next;
        }
    }
    return HT2_KEY_NOT_FOUND;
}

/*
 * Hash table item API
 */
struct HashTable2Item* ht2_item_create(ht2_key_t key, ht2_value_t value)
{
    assert(key);

    struct HashTable2Item* item = calloc(1, sizeof(*item));
    assert(item);
    item->key = ht2_key_copy(key);
    item->value = ht2_value_copy(value);
    item->next = NULL;
    return item;
}

void ht2_item_destroy(struct HashTable2Item* item)
{
    assert(item);
    if (item->key)
    {
        free(item->key);
    }
    free(item);
}

/*
 * Hash table key API
 */
static bool ht2_key_is_match(ht2_key_t key1, ht2_key_t key2)
{
    assert(key1);
    assert(key2);
    // In this example, the key type is required to be char *
    return strcmp(key1, key2) == 0;
}

static ht2_key_t ht2_key_copy(ht2_key_t key)
{
    assert(key);
    // In this example, the key type is required to be char *
    return strdup(key);
}

/*
 * Hash table value API
 */
static ht2_value_t ht2_value_copy(ht2_value_t value)
{
    // In this example, the value is known to be trivially copyable
    return value;
}

/*
 * Hash function
 * Naive implementation for simplicity
 */
// FIXME warnings if ht2_key_t is used
static unsigned long ht2_hash_function(char const* str, size_t index_range)
{
    size_t hash = 0;
    for (int j = 0; str[j]; j++)
    {
        hash += str[j];
    }
    return hash % index_range;
}
