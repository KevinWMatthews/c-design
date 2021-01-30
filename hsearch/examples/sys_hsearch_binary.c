/**
 * @file sys_hsearch_binary.c
 * Non-reentrant hsearch with binary data.
 * Historically, the glibc docs state that hsearch can only be used with string data.
 * This is incorrect.
 */
#include <search.h>
#include <assert.h>
#include <stddef.h>

int main(void)
{
    int err = 0;

    /*
     * Create a **global** hashing table for the entire program.
     */
    size_t n_elements = 42;
    err = hcreate(n_elements);
    assert(err != 0);

    /*
     * Create entries
     */
    int data1 = 1;
    ENTRY entry1 = {
        .key = "1",
        .data = &data1,
    };
    int data2 = 2;
    ENTRY entry2 = {
        .key = "2",
        .data = &data2,
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
    ENTRY entry_search = {
        .key = "1",
        .data = NULL,
    };
    result = hsearch(entry_search, FIND);
    // The entry is passed by value (copied) so
    // the result *will not* contain the entry's address
    assert(result != &entry1);
    assert(result->key == entry1.key);
    assert(result->data == entry1.data);
    assert(*(int*)result->data == data1);

    entry_search.key = "2";
    entry_search.data = NULL;
    result = hsearch(entry_search, FIND);
    assert(result != &entry2);
    assert(result->key == entry2.key);
    assert(result->data == entry2.data);
    assert(*(int*)result->data == data2);

    /*
     * Destroy the global hashing table.
     */
    hdestroy();
}
