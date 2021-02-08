/**
 * @file hash_table.c
 */
#include "hash_table1.h"
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>


static struct HashTable1Item* ht1_item_create(ht1_key_t key, ht1_value_t value);
static void ht1_item_destroy(struct HashTable1Item* item);
static bool ht1_key_is_match(ht1_key_t key1, ht1_key_t key2);
static ht1_key_t ht1_key_copy(ht1_key_t key);
static ht1_value_t ht1_value_copy(ht1_value_t value);
static unsigned long ht1_hash_function(char const* str, size_t index_range);

/*
 * Hash table API
 */
struct HashTable1* ht1_create(size_t size)
{
    struct HashTable1* table = calloc(1, sizeof(*table));
    assert(table);
    table->size = size;
    table->items = calloc(table->size, sizeof(struct HashTable1Item*));
    return table;
}

void ht1_destroy(struct HashTable1* table)
{
    assert(table);
    for (size_t i = 0; i < table->size; i++)
    {
        struct HashTable1Item* item = table->items[i];
        while (item)
        {
            struct HashTable1Item* next = item->next;
            ht1_item_destroy(item);
            item = next;
        }
    }
    if (table->items)
    {
        free(table->items);
    }
    free(table);
}

void ht1_insert(struct HashTable1* table, ht1_key_t key, ht1_value_t value)
{
    assert(key);

    size_t index = ht1_hash_function(key, table->size);
    struct HashTable1Item** slot = &table->items[index];
    struct HashTable1Item* item = *slot;
    while (item)
    {
        // Hash collision
        if (ht1_key_is_match(item->key, key))
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
    *slot = ht1_item_create(key, value);
}

void ht1_delete(struct HashTable1* table, ht1_key_t key)
{
    assert(table);
    assert(key);

    size_t index = ht1_hash_function(key, table->size);
    struct HashTable1Item** slot = &table->items[index];
    struct HashTable1Item* item = *slot;
    while (item)
    {
        if (ht1_key_is_match(item->key, key))
        {
            // Item found; remove it from linked list
            *slot = item->next;
            ht1_item_destroy(item);
            return;
        }
        // Keep walking the list
        slot = &item->next;
        item = *slot;
    }
    // Item not found?
}

enum HashTable1Result ht1_lookup(struct HashTable1* table, ht1_key_t key, ht1_value_t* value)
{
    assert(table);
    assert(key);
    assert(value);

    size_t index = ht1_hash_function(key, table->size);
    struct HashTable1Item* item = table->items[index];

    while (item)
    {
        if (ht1_key_is_match(item->key, key))
        {
            *value = item->value;
            return HT1_KEY_FOUND;
        }
        else
        {
            item = item->next;
        }
    }
    return HT1_KEY_NOT_FOUND;
}

/*
 * Hash table item API
 */
struct HashTable1Item* ht1_item_create(ht1_key_t key, ht1_value_t value)
{
    assert(key);

    struct HashTable1Item* item = calloc(1, sizeof(*item));
    assert(item);
    item->key = ht1_key_copy(key);
    item->value = ht1_value_copy(value);
    item->next = NULL;
    return item;
}

void ht1_item_destroy(struct HashTable1Item* item)
{
    assert(item);
    if (item->key)
    {
        free(item->key);
    }
    free(item);
}

static bool ht1_key_is_match(ht1_key_t key1, ht1_key_t key2)
{
    assert(key1);
    assert(key2);
    // In this example, the key type is required to be char *
    return strcmp(key1, key2) == 0;
}

static ht1_key_t ht1_key_copy(ht1_key_t key)
{
    assert(key);
    // In this example, the key type is required to be char *
    return strdup(key);
}

/*
 * Hash table value API
 */
static ht1_value_t ht1_value_copy(ht1_value_t value)
{
    // In this example, the value is known to be trivially copyable
    return value;
}

/*
 * Hash function
 * Naive implementation for simplicity
 */
// FIXME warnings if ht1_key_t is used
static unsigned long ht1_hash_function(char const* str, size_t index_range)
{
    size_t hash = 0;
    for (int j = 0; str[j]; j++)
    {
        hash += str[j];
    }
    return hash % index_range;
}

