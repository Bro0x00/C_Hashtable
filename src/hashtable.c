#include "../include/hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int power(int x, unsigned n) {
    for(unsigned i = 0; i < n; ++i) {
        x *= x;
    }
    return x;
}

unsigned defaulthash(const void* data, unsigned size) {
    unsigned total = 0;
    for(unsigned i = 0; i < size; ++i) {
        total += (unsigned)power(*(char*)(data + i), 3);
    }
    return total;
}

char cmpdata(struct tabledata* data1, struct tabledata* data2) {
    if(memcmp(data1, data2, 2 * sizeof(unsigned))) //returns 0 if index sizes and datasizes are equal
    {
        return 0;
    }
    if(!memcmp(data1->index, data2->index, data1->indexsize) & !memcmp(data1->data, data2->data, data1->datasize)) {
        return 1;
    }
    return 0;
}

struct hashtable* newtable(unsigned size) {
    if(size == 0) {
        size = DEF_HTABLE_SIZE;
    }
    
    struct hashtable* newhtable = (struct hashtable*)malloc(sizeof(struct hashtable));
    
    newhtable->hashfunction = &defaulthash;
    newhtable->size = size;
    
    newhtable->lists = (struct lnkedlist*)malloc(size * sizeof(struct lnkedlist));
    //initialize linked lists
    for(unsigned i = 0; i < size; ++i) {
        newhtable->lists[i].root = NULL;
        newhtable->lists[i].last = NULL;
    }
    
    return newhtable;
}

struct tabledata* hgetat(struct hashtable* table, const void* index, unsigned indexsize) {
    unsigned location = table->hashfunction(index, indexsize) % table->size;
    struct node* currentnode = (struct node*)((char)NULL + 1);
    struct tabledata* data;
    for(unsigned i = 0; currentnode != NULL; ++i) {
        currentnode = getat(table->lists + location, i);
        
        if(currentnode == NULL) {
            return NULL;
        }
        data = (struct tabledata*)currentnode->data;
        
        if(data->indexsize == indexsize) {
            
            if(!memcmp(data->index, index, indexsize)) {
                return data;
            }
        }
        
    }

}

void insertctoh(struct hashtable* table, const void* index, unsigned indexsize, const void* data, unsigned datasize) {
    if(table == NULL) {
        return;
    }

    unsigned location = table->hashfunction(index, indexsize) % table->size;
    struct tabledata* tbdata = hgetat(table, index, indexsize);
    if(tbdata != NULL) //if something is already there, change its value
    {
        free(tbdata->data);
        tbdata->data = malloc(datasize);
        tbdata->datasize = datasize;
        memcpy(tbdata->data, data, datasize);
        return;
    }
    //otherwise, tbdata = NULL so there's nothing at that index
    tbdata = (struct tabledata*)malloc(sizeof(struct tabledata));

    tbdata->datasize = datasize;
    tbdata->indexsize = indexsize;

    tbdata->data = malloc(datasize);
    tbdata->index = malloc(indexsize);

    memcpy(tbdata->data, data, datasize);
    memcpy(tbdata->index, index, indexsize);
    
    insert(table->lists + location, tbdata);
    return; 
    
}

void deletecontents(struct hashtable* restrict table) {
    for(unsigned i = 0; i < table->size; ++i) {
        deleteall(table->lists + i);
    }
}

void deletetable(struct hashtable* table) {
    deletecontents(table);
    free(table->lists);
    free(table);
    return;
}

char hdeleteat(struct hashtable* table, const void* index, unsigned indexsize) {
    struct tabledata* tbdata = hgetat(table, index, indexsize);
    if(tbdata == NULL) {
        return 1;
    }
    //now we know there's somthing at that index

    unsigned location = table->hashfunction(index, indexsize) % table->size;
    struct node* currentnode = (table->lists + location)->root;
    for(unsigned i = 0; currentnode != NULL; ++i) {
        currentnode = getat(table->lists + location, i);
        if(cmpdata(tbdata, currentnode->data)) {
            
            deleteat(table->lists + location, i);
            
            return 0;
        }
    }
    return 1;
}