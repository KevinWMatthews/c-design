/**
 * @file hash_table2.h
 * Naive hash table implementation.
 * Collision resolution uses separate chaining with linked lists.
 *
 * There is separate abstraction for a bucket; the bucket contains the head of a linked list.
 * @{
 */
#ifndef HASH_TABLE2_H_INCLUDED
#define HASH_TABLE2_H_INCLUDED

#include <stdlib.h>

typedef char* ht2_key_t;
typedef int ht2_value_t;

enum HashTable2Result
{
    HT2_ERROR = -1,
    HT2_KEY_NOT_FOUND = 0,
    HT2_KEY_FOUND,
};

struct HashTable2Item
{
    ht2_key_t key;
    ht2_value_t value;
    // Linked list for handling hash collisions
    struct HashTable2Item* next;
};

struct HashTable2Bucket
{
    struct HashTable2Item* item;
};

struct HashTable2
{
    struct HashTable2Bucket* bucket_list;
    size_t size;
};

struct HashTable2* ht2_create(size_t size);
void ht2_destroy(struct HashTable2* table);
void ht2_insert(struct HashTable2* table, ht2_key_t key, ht2_value_t value);
void ht2_delete(struct HashTable2* table, ht2_key_t key);
enum HashTable2Result ht2_lookup(struct HashTable2* table, ht2_key_t key, ht2_value_t* value);

#endif

/** @} */
