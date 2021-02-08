/**
 * @file hash_table1.h
 * Naive hash table implementation.
 * Collision resolution uses separate chaining with linked lists.
 *
 * There is no separate abstraction for a bucket; the hash table tracks items directly.
 * @{
 */
#ifndef HASH_TABLE1_H_INCLUDED
#define HASH_TABLE1_H_INCLUDED

#include <stdlib.h>

typedef char* ht1_key_t;
typedef int ht1_value_t;

enum HashTable1Result
{
    HT1_ERROR = -1,
    HT1_KEY_NOT_FOUND = 0,
    HT1_KEY_FOUND,
};

struct HashTable1Item
{
    ht1_key_t key;
    ht1_value_t value;
    // Linked list for handling hash collisions
    struct HashTable1Item* next;
};


struct HashTable1
{
    struct HashTable1Item** items;
    size_t size;
};

struct HashTable1* ht1_create(size_t size);
void ht1_destroy(struct HashTable1* table);
void ht1_insert(struct HashTable1* table, ht1_key_t key, ht1_value_t value);
void ht1_delete(struct HashTable1* table, ht1_key_t key);
enum HashTable1Result ht1_lookup(struct HashTable1* table, ht1_key_t key, ht1_value_t* value);

#endif

/** @} */
