# Python's Dictionary Implementation

TODO

* [dict-common.h](https://github.com/python/cpython/blob/master/Objects/dict-common.h)
* [dict-object.h](https://github.com/python/cpython/blob/master/Include/dictobject.h)
* [dict-object.c](https://github.com/python/cpython/blob/master/Objects/dictobject.c)
* [dict-notes.txt](https://github.com/python/cpython/blob/master/Objects/dictnotes.txt)

## Structure

```c
struct _dictkeysobject {
    Py_ssize_t dk_refcnt;
    dict_lookup_func dk_lookup;
    Py_ssize_t dk_usable;
    Py_ssize_t dk_nentries;
    char dk_indices[];
    // dk_entries[dk_usable];
};
```

[layout](https://github.com/python/cpython/blob/8dfe15625e6ea4357a13fec7989a0e6ba2bf1359/Objects/dictobject.c#L9)
