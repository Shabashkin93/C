/* Copyright ProsoftSystems Homework_1. All right not reserved
 * Author: Shabashkin.o
 * 2017
 * */
// version vitch using memcpy
#include "sll.h"

// static variable for statistic
//static int nodes_add, nodes_delete, nodes_memory, memory_one_nodes;

/* list creation function*/
LinksList *createList(size_t size_data) {
  LinksList *tmp =
      (LinksList *)malloc(sizeof(LinksList)); /*create member links*/
  tmp->head = tmp->tail = NULL;               /*links is empty*/
  tmp->size = 0;
  tmp->size_data = size_data;
  tmp->nodes_add = 0;
  tmp->nodes_delete = 0;
  tmp->nodes_memory = 0;
  tmp->memory_one_nodes = size_data;
  tmp->nodes_memory = sizeof (LinksList);
  return tmp;
}
/*list delete function
 *arguments:
 *list: point to list
 */
void deleteList(LinksList **list) {
  Node *prev = NULL; /*points on previous node*/
  while (
      (*list)
          ->head
          ->next) /*we pass on nodes until we meet the node pointing to NULL*/
  {
    prev = (*list)->head;                /*prev saved adress first node */
    (*list)->head = (*list)->head->next; /*move head right*/
    free(prev);                          /*delete previous node*/
  }
 // (*list)->nodes_delete += (*list)->nodes_add;//бесполезно тк после удаления листа мы не сможем посмотреть данную статистику
 // (*list)->nodes_memory += (*list)->memory_one_nodes;//бесполезно тк после удаления листа мы не сможем посмотреть данную статистику 
  free((*list)->head); /* delete head*/
  free(*list);
  *list = NULL;
}
/*function of inserting a new node into the beginning
 *arguments:
 *list: point to list
 *value: value
 */
void pushFirst(LinksList *list, void *value) {
  Node *tmp = (Node *)malloc(sizeof(Node)); /*create node*/
  if (tmp == NULL) {
    return;
  }
  log("adress push first %p\t size push %ld\n", tmp, list->size_data);
  tmp->next = list->head; /**/
  tmp->size_data = list->size_data;
  tmp->value = malloc(list->size_data);
  memcpy(tmp->value, value, list->size_data);
  list->head = tmp;       /*now the first node is tmp*/
  if (list->tail == NULL) /*if list empty*/
  {
    list->tail = tmp;
  }
  list->size++;
  list->nodes_add++;
  list->nodes_memory += list->memory_one_nodes;
}
/*print list function
 *arguments:
 *list: point to list
 *(*funcprint)(void*): callback function for print data
 */
void printList(LinksList *list, void (*functprint)(void *)) {
  Node *iter = list->head;
  printf(" ");
  while (iter) {
    functprint(iter->value);
    iter = iter->next;
  }
  printf("\n");
}

/*print list function
 *arguments:
 *list: point to list
 *(*funcprint)(void*): callback function for print data
 */
void printListDebug(LinksList *list, void (*functprint)(void *)) {
  Node *iter = list->head;
  while (iter) {
    printf("node\t%p\t", iter);
    printf("value = ");
    functprint(iter->value);
    printf("node->next\t%p\n", iter->next);
    iter = iter->next;
  }
  printf("nodes_add: %d\tnodes_delete: %d\tnodes_memory: %ld\n\n", list->nodes_add,
         list->nodes_delete, list->nodes_memory);
}

/*function of inserting a node at the end of the list
 *arguments:
 *list: point to list
 *value: value
 */
void pushEnd(LinksList *list, void *value) {
  Node *tmp = (Node *)malloc(sizeof(Node)); /*create node*/
  log("adress push end %p\t size push %ld\n", tmp, list->size_data);
  tmp->next = NULL;
  tmp->size_data = list->size_data;
  tmp->value = malloc(list->size_data);
  memcpy(tmp->value, value, list->size_data);
  if (list->tail) {
    list->tail->next = tmp;
  }
  list->tail = tmp;
  if (list->head == NULL) {
    list->head = tmp;
  }
  list->size++;
  list->nodes_add++;
  list->nodes_memory += list->memory_one_nodes;
}
/*delete the first node in the list
 *arguments:
 *list: point to list
 */
void deleteFirst(LinksList *list) {
  Node *tmp = NULL;
  if (list->head == NULL) {
    exit(-1);
  }
  tmp = list->head;
  log("adress delete first %p\t size push %ld\n", tmp, tmp->size_data);
  list->head = list->head->next;
  if (list->tail == tmp) {
    list->tail = NULL;
  }
  free(tmp);
  list->size--;
  list->nodes_delete++;
  list->nodes_memory -= list->memory_one_nodes;
}
/*function to delete the last node in the list
 *arguments:
 *list: point to list
 */
void deleteEnd(LinksList *list) {
  Node *tmp = list->head;
  while (tmp->next != list->tail) {
    tmp = tmp->next;
  }
  log("adress delete end %p\t size push %ld\n", tmp->next,
      tmp->next->size_data);
  list->tail = tmp;
  free(tmp->next);
  tmp->next = NULL;
  list->size--;
  list->nodes_delete++;
  list->nodes_memory -= list->memory_one_nodes;
}
/*function of inserting a new node after the node with the desired value
 *arguments:
 *list: point to list
 *value: sought value
 *value_new: value in the new node
 */
void pushAfter(LinksList *list, void *value, void *value_new) {
  Node *tmp = list->head;
  while (memcmp((char *)value, (char *)tmp->value, list->size_data)) {
    tmp = tmp->next;
    if (tmp == NULL) {
      break;
    }
  }
  Node *newtmp = (Node *)malloc(sizeof(Node)); /*create node*/
  newtmp->next = tmp->next;
  newtmp->size_data = list->size_data;
  log("adress push after %p\t size push %ld\n", newtmp, list->size_data);
  newtmp->value = malloc(list->size_data);
  memcpy(newtmp->value, value_new, list->size_data);
  tmp->next = newtmp;
  list->size++;
  list->nodes_add++;
  list->nodes_memory += list->memory_one_nodes;
}
/*function of inserting a new node before the node with the desired value
 *arguments:
 *list: point to list
 *value: sought value
 *value_new: value in the new node
 */
void pushBefore(LinksList *list, void *value, void *value_new) {
  Node *tmp = list->head;
  while (memcmp((char *)value, (char *)tmp->next->value, list->size_data)) {
    tmp = tmp->next;
    if (tmp == NULL) {
      break;
    }
  }
  Node *newtmp = (Node *)malloc(sizeof(Node)); /*create node*/
  newtmp->next = tmp->next;
  newtmp->size_data = list->size_data;
  log("adress push before %p\t size push %ld\n", newtmp, list->size_data);
  newtmp->value = malloc(list->size_data);
  memcpy(newtmp->value, value_new, list->size_data);
  tmp->next = newtmp;
  list->size++;
  list->nodes_add++;
  list->nodes_memory += list->memory_one_nodes;
}
/*function of delete a new node after the node with the desired value
 *arguments:
 *list: point to list
 *value: sought value
 */
void deleteAfter(LinksList *list, void *value) {
  Node *tmp = list->head;
  while (memcmp((char *)value, (char *)tmp->value, list->size_data)) {
    tmp = tmp->next;
    if (tmp == NULL) {
      break;
    }
  }
  log("adress delete after %p\t size push %ld\n", tmp->next,
      tmp->next->size_data);
  free(tmp->next);
  tmp->next = tmp->next->next;
  list->size--;
  list->nodes_delete++;
  list->nodes_memory -= list->memory_one_nodes;
}
/*function of delete a new node before the node with the desired value
 *arguments:
 *list: point to list
 *value: sought value
 */
void deleteBefore(LinksList *list, void *value) {
  Node *tmp = list->head;
  while (
      memcmp((char *)value, (char *)tmp->next->next->value, list->size_data)) {
    tmp = tmp->next;
    if (tmp == NULL) {
      break;
    }
  }
  log("adress delete before %p\t size push %ld\n", tmp->next,
      tmp->next->size_data);
  tmp->next = tmp->next->next;
  list->size--;
  list->nodes_delete++;
  list->nodes_memory -= list->memory_one_nodes;
}
/*function to delete a node with the desired value
 *arguments:
 *list: point to list
 *value: sought value
 */
void deleteFind(LinksList *list, void *value) {
  Node *tmp = list->head;
  tmp = tmp->next;
  if (tmp == NULL) {
    ;
  } else {
    for (int i = 0; (i - list->size) != 0; i++) {
      if (!memcmp((char *)value, (char *)tmp->next->value, list->size_data)) {
        log("adress delete find %p\t size push %ld\n", tmp->next,
            tmp->next->size_data);
        tmp->next = tmp->next->next;
        tmp = tmp->next;
        free(tmp->next);
        list->size--;
        list->nodes_delete++;
        list->nodes_memory -= list->memory_one_nodes;
        break;
      } else {
        printf("not found for delete\n\n");
        break;
      }
    }
  }
}
/*The function of searching a node for a stored value is used for debugging
*arguments:
list: point to list
*value: sought value
 *(*funcprint)(void*): callback function for print data
*/
void found(LinksList *list, const void *value, void (*functprint)(void *)) {
  Node *tmp = list->head;
  if (tmp == NULL) {
    printf("Empty list \n");
  }
  for (int step = 0; (step - list->size) != 0; step++) {
    if (memcmp((char *)tmp->value, (char *)value, list->size_data)) {
      tmp = tmp->next;
      printf("found node with the value\t");
      functprint(tmp->value);
      log("adress found %p\t size push %ld\n", tmp, tmp->size_data);
      break;
    } else {
      printf("Node not found\n");
      break;
    }
  }
}

/*The function for print value type "int"
 *arguments:
 *value: value
 */
void printInt(void *value) { printf("%d\t ", *((int *)value)); }

/*The function for print value type "float"
 *arguments:
 *value: value
 */
void printFloat(void *value) { printf("%f\t ", *((float *)value)); }

/*The function for print value type "char"
 *arguments:
 *value: value
 */
void printString(void *value) { printf("%s\t ", value); }
/*void printlog(void *value, char *description) {
  printf("adress %s %p\t size push %ld\n", description, value, sizeof(value));
}*/
