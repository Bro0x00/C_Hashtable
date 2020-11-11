#ifndef MY_LINKED_LIST_H_
#define MY_LINKED_LIST_H_

struct node {
    struct node* prev;
    struct node* next;
    void* data;
};

struct lnkedlist {
    struct node* root;
    struct node* last;
};

extern struct lnkedlist* newlist();

extern struct node* newnode();

extern void deletelist(struct lnkedlist* list);

//indexing starts at 0 for get/insert/delete functions

//returns NULL if out of range
extern struct node* getat(struct lnkedlist*, unsigned);

extern struct node* findlast(struct node*);

//sets all data values to null
extern void setnull(struct lnkedlist*);

//WARNING: ALL DELETE FUNCTIONS DELETE THE DATA STORED IN THE NODE(S)

extern void deleteall(struct lnkedlist*);

//returns 1 if index not in range, otherwise 0
extern char deleteat(struct lnkedlist*, unsigned);

extern void deletenode(struct node*);

extern void deletelast(struct lnkedlist*);

//inserts as last. inserts actual data, not copy
extern void insert(struct lnkedlist*, void*);

//returns 1 if index not in range, otherwise 0. inserts actual data, not copy
extern char insertat(struct lnkedlist*, void*, unsigned);

//inserc(at) inserts a copy of the data that will be dynamically allocated

extern void insertc(struct lnkedlist*, const void*, unsigned);

extern char insertcat(struct lnkedlist*, const void*, unsigned size, unsigned index);

#endif
