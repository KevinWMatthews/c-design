/**
 * @file hash_table2.c
 * FIXME insert/delete don't currently work
 */
#include "hash_table2.h"
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>


static struct HashTableItem* ht_item_create(ht_key_t key, ht_value_t value);
static void ht_item_destroy(struct HashTableItem* item);
static bool ht_is_key_match(ht_key_t key1, ht_key_t key2);
static ht_key_t ht_copy_key(ht_key_t key);
static ht_value_t ht_copy_value(ht_value_t value);
static unsigned long ht_hash_function(char const* str, size_t index_range);

struct HashTable* ht_create(size_t size)
{
    struct HashTable* table = calloc(1, sizeof(*table));
    assert(table);
    table->size = size;
    table->bucket_list = calloc(table->size, sizeof(*table->bucket_list));
    return table;
}

void ht_destroy(struct HashTable* table)
{
    assert(table);
    for (size_t i = 0; i < table->size; i++)
    {
        struct HashTableBucket* bucket = &table->bucket_list[i];
        struct HashTableItem* item = bucket->item;
        while (item)
        {
            struct HashTableItem* next = item->next;
            ht_item_destroy(item);
            item = next;
        }
    }
    if (table->bucket_list)
    {
        free(table->bucket_list);
    }
    free(table);
}

struct HashTableItem* ht_item_create(ht_key_t key, ht_value_t value)
{
    assert(key);

    struct HashTableItem* item = calloc(1, sizeof(*item));
    assert(item);
    item->key = ht_copy_key(key);
    item->value = ht_copy_value(value);
    item->next = NULL;
    return item;
}

void ht_item_destroy(struct HashTableItem* item)
{
    assert(item);
    if (item->key)
    {
        free(item->key);
    }
    free(item);
}

void ht_insert(struct HashTable* table, ht_key_t key, ht_value_t value)
{
    assert(key);

    size_t index = ht_hash_function(key, table->size);
    struct HashTableBucket* bucket = &table->bucket_list[index];
    struct HashTableItem** slot = &bucket->item;
    struct HashTableItem* item = *slot;
    while (item)
    {
        // Hash collision
        if (ht_is_key_match(item->key, key))
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
    *slot = ht_item_create(key, value);
}

void ht_delete(struct HashTable* table, ht_key_t key)
{
    assert(table);
    assert(key);

    size_t index = ht_hash_function(key, table->size);
    struct HashTableBucket* bucket = &table->bucket_list[index];
    struct HashTableItem** slot = &bucket->item;
    while (slot)
    {
        struct HashTableItem* item = *slot;
        if (ht_is_key_match(item->key, key))
        {
            // Item found; remove it from linked list
            *slot = item->next;
            ht_item_destroy(item);
            return;
        }
        // Keep walking the list
        slot = &item->next;
    }
    // Item not found?
}

enum HashTableResult ht_value_of(struct HashTable* table, ht_key_t key, ht_value_t* value)
{
    assert(table);
    assert(key);
    assert(value);

    size_t index = ht_hash_function(key, table->size);
    struct HashTableBucket* bucket = &table->bucket_list[index];
    struct HashTableItem* item = bucket->item;

    while (item)
    {
        if (ht_is_key_match(item->key, key))
        {
            *value = item->value;
            return HT_KEY_FOUND;
        }
        else
        {
            item = item->next;
        }
    }
    return HT_KEY_NOT_FOUND;
}

static bool ht_is_key_match(ht_key_t key1, ht_key_t key2)
{
    assert(key1);
    assert(key2);
    // In this example, the key type is required to be char *
    return strcmp(key1, key2) == 0;
}

static ht_key_t ht_copy_key(ht_key_t key)
{
    assert(key);
    // In this example, the key type is required to be char *
    return strdup(key);
}

static ht_value_t ht_copy_value(ht_value_t value)
{
    // In this example, the value is known to be trivially copyable
    return value;
}

// Naive hash function
// FIXME warnings if ht_key_t is used
static unsigned long ht_hash_function(char const* str, size_t index_range)
{
    size_t hash = 0;
    for (int j = 0; str[j]; j++)
    {
        hash += str[j];
    }
    return hash % index_range;
}

