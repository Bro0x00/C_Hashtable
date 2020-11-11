#ifndef MY_HASH_TABLE_H_
#define MY_HASH_TABLE_H_
#include "lnkedlist.h"

#define DEF_HTABLE_SIZE 16

/*size is the amount of linked lists in your hashtable 
(if you had enough space for two then size would equal 2)*/
unsigned defaulthash(const void* data, unsigned size);

struct tabledata {
    unsigned indexsize;
    unsigned datasize;
    void* index;
    void* data;
};

char cmpdata(struct tabledata*, struct tabledata*); //returns 1 if equal, 0 if not equal

struct hashtable {
    struct lnkedlist* lists;
    unsigned size; //amount of linked lists
    unsigned (*hashfunction)(const void*, unsigned);
};

struct hashtable* newtable(unsigned size); //returns NULL if size = 0

//insert a copy of data into hashtable
extern void insertctoh(struct hashtable*, const void* index, unsigned indexsize, const void* data, unsigned datasize);

extern void deletecontents(struct hashtable*);

extern void deletetable(struct hashtable*);

//gets at this index and returns 0. returns 1 if nothing shares index
extern struct tabledata* hgetat(struct hashtable*, const void* index, unsigned indexsize);

//deletes at index and returns 0. returns 1 if index out of range
extern char hdeleteat(struct hashtable*, const void* index, unsigned indexsize);

#endif

