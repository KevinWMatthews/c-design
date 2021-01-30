# POSIX hsearch

POSIX hash search tables.

## Notes

* Can not be used for binary data?
  - GNU specifies `ENTRY.data` as `char *` and states: "It is not possible to handle general binary data."
    + I believe the GNU [docs are incorrect](https://sourceware.org/bugzilla/show_bug.cgi?id=17183)
  - POSIX 2017 specifies `ENTRY.data` as `void *` and makes no mention of binary data.
  - Linux specifies `ENTRY.data` as `void *` and makes no mention of binary data.
* Can not delete items from the hash table

## glibc Implementation

* Adjusts the table size under the hood: must be `> 3 and prime.
* Uses `calloc()`.

Request to [change hashing algorithm](https://sourceware.org/bugzilla/show_bug.cgi?id=25924).

## TODO

Run examples Linux docs:

* https://man7.org/linux/man-pages/man3/hsearch.3.html
* https://man7.org/linux/man-pages/man3/hsearch.3p.html
* https://man7.org/linux/man-pages/man3/hsearch_r.3.html
