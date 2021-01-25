/**
 * @file sys_hsearch.c
 * Non-reentrant hsearch.
 */
#include <search.h>
#include <assert.h>
#include <stddef.h>

int main(void)
{
    int err = 0;

    /*
     * Create a **global** hashing table for the entire program.
     * Must only use one hashing table at a time.
     * The size of the hashing table is fixed!
     */
    size_t n_elements = 42;
    err = hcreate(n_elements);
    assert(err != 0);

    /*
     * Create entries
     */
    ENTRY entry1 = {
        .key = "1",
        .data = "1",
    };
    ENTRY entry2 = {
        .key = "2",
        .data = "2",
    };

    ENTRY* result = NULL;

    /*
     * Add entries
     */
    result = hsearch(entry1, ENTER);
    assert(result->key == entry1.key);
    assert(result->data == entry1.data);

    result = hsearch(entry2, ENTER);
    assert(result->key == entry2.key);
    assert(result->data == entry2.data);

    /*
     * Find an entry
     */
    result = hsearch(entry1, FIND);
    assert(result->key == entry1.key);
    assert(result->data == entry1.data);

    /*
     * Find searches by key only
     */
    ENTRY entry_dup = {
        .key = "1",
        .data = NULL,
    };
    result = hsearch(entry_dup, FIND);
    // The entry is passed by value (copied) so
    // the result *will not* contain the entry's address
    assert(result != &entry1);
    assert(result->key == entry1.key);
    assert(result->data == entry1.data);

    /*
     * If key is not found, FIND returns NULL
     */
    ENTRY entry_dne = {
        .key = "0",
        .data = NULL,
    };
    result = hsearch(entry_dne, FIND);
    assert(result == NULL);

    /*
     * Entries are not updated
     */
    ENTRY entry_mod = {
        .key = "2",
        .data = "two",
    };
    result = hsearch(entry_mod, ENTER);
    assert(result->key == entry2.key);
    assert(result->data == entry2.data);

    result = hsearch(entry_mod, FIND);
    assert(result->key == entry2.key);
    assert(result->data == entry2.data);

    /*
     * Destroy the global hashing table.
     */
    hdestroy();
}
