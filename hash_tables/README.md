# Hash Maps

## Articles

* [journaldev](https://www.journaldev.com/35238/hash-table-in-c-plus-plus)
* [leetcode exercise](https://leetcode.com/problems/design-hashmap/)
* [Nearly memory-optimal data structure for sets and mappings](https://dl.acm.org/doi/10.5555/1767111.1767120)

## Implementations

* POSIX: hsearch
  - [linux docs](https://man7.org/linux/man-pages/man3/hsearch.3.html)
  - [gnu docs](https://www.gnu.org/software/libc/manual/html_node/Hash-Search-Function.html)
  - implementation in `misc/search.h`/`misc/hsearch_r.c`
* glibc
  - implementation in `elf/stringtable.h`/`elf/stringtable.c`
  - see commit [785969a047](https://sourceware.org/git/?p=glibc.git;a=commit;h=785969a047ad2f23f758901c6816422573544453)
* gnulib
  - [module list](https://www.gnu.org/software/gnulib/MODULES.html#ansic_ext_container)
* Glib
  - [glib Hash Table docs](https://developer.gnome.org/glib/2.28/glib-Hash-Tables.html)
* Facebook folly (C++)
  - [AtomicHashMap.h](https://github.com/facebook/folly/blob/master/folly/AtomicHashMap.h)
* Google sparsehash
  - [C11 dense hash map](https://github.com/sparsehash/sparsehash-c11/blob/master/sparsehash/dense_hash_map)
  - [C11 sparse hash map](https://github.com/sparsehash/sparsehash-c11/tree/master/sparsehash)
  - [dense hash map](https://github.com/sparsehash/sparsehash/blob/master/src/sparsehash/dense_hash_map)
  - [sparse hash map](https://github.com/sparsehash/sparsehash/tree/master/src/sparsehash)
* Google [ccl](https://code.google.com/archive/p/ccl/) (C Container Library)
* Android
  - [hashmap.h](https://github.com/koush/android_system_core/blob/6c590a6db64dc8a74ec144bee90dd946cbc90cf3/include/cutils/hashmap.h)
  - [hashmap.c](https://github.com/koush/android_system_core/blob/6c590a6db64dc8a74ec144bee90dd946cbc90cf3/libcutils/hashmap.c)
* [Apple Core](https://developer.apple.com/documentation/corefoundation/cfdictionary-rum)
* [Apache Runtime](http://apr.apache.org/docs/apr/1.4/group__apr__hash.html)
* [Naval Postgraduate](http://npsml.sourceforge.net/)
  - [on sourceforge](https://sourceforge.net/p/npsml/code/ci/default/tree/)

  * [hash/](https://sourceforge.net/p/npsml/code/ci/default/tree/src/hash/)
* [C Interfaces and Implementations](http://drh.github.io/cii/)
* [sglib](http://sglib.sourceforge.net/)
* Judy arrays (?)
  - [index page](http://judy.sourceforge.net/index.html)
  - [hashing example](http://judy.sourceforge.net/examples/Judy_hashing.pdf)
* [uthash](http://troydhanson.github.io/uthash/)
* [libcfu](https://github.com/crees/libcfu)
* [strmap](http://pokristensson.com/strmap.html)
* [cmph](http://cmph.sourceforge.net/)
* [klib](https://github.com/attractivechaos/klib)
  - [attractive chaos](https://attractivechaos.wordpress.com/programs/)
* [libdict](https://github.com/fmela/libdict)
* [c-hashtable](https://github.com/dozylynx/C-hashtable)
* [hashmap C](https://github.com/KingHodor/HashMap)
* C/HashTables: https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html
* [map](https://github.com/rxi/map)
* [libghthash](https://github.com/SimonKagstrom/libghthash)
* [tommyds](https://www.tommyds.it/)
* sunrise data dictionary/sunrisedd (gone?)
* [john's blog](https://www.gnu.org/software/libc/manual/html_node/Hash-Search-Function.html)
* [program base library](http://www.mission-base.com/peter/source/pbl/doc/map.html)
* [stb ds](http://nothings.org/stb_ds/)
  - [on github](https://github.com/nothings/stb)

## Hashing

* [gperf](https://developer.ibm.com/tutorials/l-gperf/)
* [hashit](https://github.com/cjavad/hashit)

## Misc

* https://attractivechaos.wordpress.com/2008/10/07/another-look-at-my-old-benchmark/
