#include "lnkedlist.h"
#include <stdlib.h>
#include <string.h>

struct lnkedlist* newlist() {
    struct lnkedlist* list =  (struct lnkedlist*)malloc(sizeof(struct lnkedlist*));
    list->root = NULL;
    list->last = NULL;
    return list;
}

struct node* newnode() {
    struct node* nd = (struct node*)malloc(sizeof(struct node*));
    nd->data = NULL;
    nd->next = NULL;
    nd->prev = NULL;
    return nd;
}

void deletelist(struct lnkedlist* list) {
    if(list != NULL) {
        deleteall(list);
        free(list);
    }
}


struct node* getat(struct lnkedlist* restrict list, unsigned index) {
    struct node* currentnode = list->root;
    if(!index) {
        return list->root;
    }
    for(unsigned i = 0; i < index; ++i) {
        if(currentnode == NULL) {
            return NULL;
        }
        currentnode = currentnode->next;
    }
}

struct node* findlast(struct node* restrict nd) {
    struct node* currentnode = nd;
    if(currentnode == NULL) {
        return NULL;
    }
    while(currentnode->next != NULL) {
        currentnode = currentnode->next;
    }
    return currentnode;
}

void setnull(struct lnkedlist* restrict list) {
    struct node* currentnode = list->root;
    while(currentnode != NULL) {
        currentnode->data = NULL;
        currentnode = currentnode->next;
    }
    return;
}

void deleteall(struct lnkedlist* list) {
    struct node* temp;
    while(list->root != NULL) {
        temp = list->root->next;
        free(list->root->data);
        free(list->root);
        list->root = temp;
    }
    list->last = NULL;
    return;
}

char deleteat(struct lnkedlist* list, unsigned index) {
    struct node* nd = getat(list, index);
    if(nd == NULL) {
        return 1;
    }
    
    if(nd == list->root) {
        list->root = nd->next;
    }
    if(nd == list->last) {
        list->last = nd->prev;
    }

    deletenode(nd);
    return 0;
}

void deletenode(struct node* nd) {
    if(nd != NULL) {
        if(nd->next != NULL) {
            nd->next->prev = nd->prev;
        }
        if(nd->prev != NULL) {
            nd->prev->next = nd->next;
        }
        free(nd->data);
        free(nd);
    }
}

void deletelast(struct lnkedlist* list) {
    if(list->last == NULL) {
        list->last = findlast(list->root);
    }
    struct node* temp;
    temp = list->last->prev;
    deletenode(list->last);
    list->last = temp;
}

void insert(struct lnkedlist* list, void* data) {
    struct node* nd = newnode();
    nd->data = data;
    
    if(list->root == NULL) {
        list->root = nd;
        list->last = nd;
        return;
    }
    
    if(list->last == NULL) {
        list->last = findlast(list->root); //root cannot be null at this point
    }

    list->last->next = nd;
    nd->prev = list->last;
    list->last = nd;
    return;
}

char insertat(struct lnkedlist* list, void* data, unsigned index) {
    struct node* newnd = newnode();
    newnd->data = data;
    if(index == 0) {
        if(list->root != NULL) {
            list->root->prev = newnd;
            newnd->next = list->root;
            list->root = newnd;
        } else {
            insert(list, data);
            free(newnd); //I know what I'm doing
        }
        return 0;
    }
    
    struct node* nd = getat(list, index);
    if(nd == NULL) {
        return 1;
    }
    newnd->prev = nd->prev;
    newnd->next = nd;
    nd->prev->next = nd;
    nd->prev = newnd;
    return 0;
}


void insertc(struct lnkedlist* list, const void* data, unsigned size) {
    void* datacpy = malloc(size);
    memcpy(datacpy, data, size);
    insert(list, datacpy);
    return;
}

char insertcat(struct lnkedlist* list, const void* data, unsigned size, unsigned index) {
    void* datacpy = malloc(size);
    memcpy(datacpy, data, size);
    if(insertat(list, datacpy, index)) //if index not in range
    {
        free(datacpy);
        return 1;
    }
    return 0;
}
