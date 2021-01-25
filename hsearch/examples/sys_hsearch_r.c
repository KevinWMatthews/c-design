/**
 * @file sys_hsearch_r.c
 */

#ifndef _GNU_SOURCE
#error "Must define _GNU_SOURCE"
#endif

#include <search.h>
#include <assert.h>
#include <stddef.h>
#include <errno.h>

int main(void)
{
    int err = 0;

    /*
     * Create hash table
     * This hash table implementation allows for multiple tables.
     */
    struct hsearch_data htable = {0};
    size_t n_elements = 42;
    err = hcreate_r(n_elements, &htable);
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
    ENTRY* retval = NULL;

    /*
     * Add entries
     */
    err = hsearch_r(entry1, ENTER, &retval, &htable);
    assert(err != 0);
    assert(retval->key == entry1.key);
    assert(retval->data == entry1.data);

    err = hsearch_r(entry2, ENTER, &retval, &htable);
    assert(err != 0);
    assert(retval->key == entry2.key);
    assert(retval->data == entry2.data);

    /*
     * Find an entry
     */
    err = hsearch_r(entry1, FIND, &retval, &htable);
    assert(err != 0);
    assert(retval->key == entry1.key);
    assert(retval->data == entry1.data);

    /*
     * Find searches by key only
     */
    ENTRY entry_dup = {
        .key = "1",
        .data = NULL,
    };
    err = hsearch_r(entry_dup, FIND, &retval, &htable);
    // The entry is passed by value (copied) so
    // the result *will not* contain the entry's address
    assert(err != 0);
    assert(retval->key == entry1.key);
    assert(retval->data == entry1.data);

    /*
     * If key is not found, FIND returns NULL
     */
    ENTRY entry_dne = {
        .key = "0",
        .data = NULL,
    };
    retval = NULL;
    err = hsearch_r(entry_dne, FIND, &retval, &htable);
    assert(err == 0);
    assert(errno == ESRCH);
    assert(retval == NULL);

    // TODO fill the table and demonstrate ENOMEN when action == ENTER

    /*
     * Entries are not updated
     */
    ENTRY entry_mod = {
        .key = "2",
        .data = "two",
    };
    err = hsearch_r(entry_mod, ENTER, &retval, &htable);
    assert(err != 0);
    assert(retval->key == entry2.key);
    assert(retval->data == entry2.data);

    hdestroy_r(&htable);
    return 0;
}
