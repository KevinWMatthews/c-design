/**
 * @file hash_table.h
 * @{
 */
#ifndef HASH_TABLE_H_INCLUDED
#define HASH_TABLE_H_INCLUDED

#include <stdlib.h>

typedef char* ht_key_t;
typedef int ht_value_t;

enum HashTableResult
{
    HT_ERROR = -1,
    HT_KEY_NOT_FOUND = 0,
    HT_KEY_FOUND,
};

struct HashTableItem
{
    ht_key_t key;
    ht_value_t value;
    // Linked list for handling hash collisions
    struct HashTableItem* next;
};


struct HashTable
{
    struct HashTableItem** items;
    size_t size;
};

struct HashTable* ht_create(size_t size);
void ht_destroy(struct HashTable* table);
void ht_insert(struct HashTable* table, ht_key_t key, ht_value_t value);
void ht_delete(struct HashTable* table, ht_key_t key);
enum HashTableResult ht_value_of(struct HashTable* table, ht_key_t key, ht_value_t* value);

#endif

/** @} */
