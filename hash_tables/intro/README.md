# Hashmap Intro

Based on a [tutorial on JournalDev](https://www.journaldev.com/35238/hash-table-in-c-plus-plus).

Source on GitHub:

* [original Gist](https://gist.github.com/kuriringohankamehameha/fceee2e3c126f37fd254ee0acf2b4633)
* [3rd-party update](https://gist.github.com/oschonrock/d0540347a5a6739a24c4648e724a3e96)

The original has issues:

* example leaks when updating the value
* author admits issues with the linked list implementation

The original author maintained a separate "bucket collision list". The update adds a linked list element to each node.
