/* Copyright ProsoftSystems Homework_1. All right not reserved
 * Author: Shabashkin.o
 * 2017
 * */

//#ifndef SLL_H_
//#define SLL_H_

#define DEBUG// Comment this to disable log ---> // #define DEBUG
#ifdef DEBUG
#define log(...)   printf(__VA_ARGS__)
#else
#define log(...)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//struct node
typedef struct Node {
    void* value;          // void* get use any type
    struct Node* next;
    size_t size_data;
} Node;
//struct list
typedef struct LinksList {
  Node *head;  /*points on head*/
  Node *tail;  /*points on tail*/
  size_t size; /*size list*/
  size_t size_data;
  int nodes_add;
  int nodes_delete;
  size_t nodes_memory;
  size_t memory_one_nodes; 
} LinksList;
//struct for test
struct ab {
    int a;
    int b;
};
//function for list and nodes
LinksList *createList(size_t size_data);
void deleteList(LinksList **list);
void pushFirst      (LinksList *list, void *value);
void printList      (LinksList *list, void (*functprint)(void *));
void printListDebug(LinksList *list, void (*functprint)(void *) );
void pushEnd        (LinksList *list, void *value);
void deleteFirst    (LinksList *list);
void deleteEnd      (LinksList *list);
void pushAfter      (LinksList *list, void *value, void *value_new);
void pushBefore     (LinksList *list, void *value, void *value_new);
void deleteAfter    (LinksList *list, void *value);
void deleteBefore   (LinksList *list, void *value);
void deleteFind     (LinksList *list, void *value);
void found          (LinksList *list, const void *value, void (*functprint)(void *));
//callback function for print date variable type
void printInt       (void *value);
void printFloat     (void *value);
void printString    (void *value);
//void printlog(void *value,char *description);
//#endif  // SLL_H_
