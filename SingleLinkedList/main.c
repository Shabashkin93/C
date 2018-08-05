/* Copyright ProsoftSystems Homework_1. All right not reserved
 * Author: Shabashkin.o
 * 2017
 * */

// function printListDebug using for view statistic and visualisated sequences
// nodes

#include "sll.h"

void runTestInt();
void runTestChar();
void runTestFloat();
void runTestStruct();
void printStruct(struct ab *value);

int main() {
  printf("run test with int data\n");
  runTestInt();
  printf("\n\nrun test with string data\n");
  runTestChar();
  printf("\n\nrun test with float data\n");
  runTestFloat();
  printf("\n\nrun test with float struct\n");
  runTestStruct();
  return 0;
}

void runTestInt() {
  LinksList *list = createList(sizeof(int));
  int a = 10;
  int b = 20;
  int c = 30;
  int d = 88;
  int e = 77;
  int f = 66;
  int h = 777;
  int k = 333;
  int l = 2;
  pushFirst(list, &a);
  pushFirst(list, &b);
  pushFirst(list, &c);
  pushEnd(list, &d);
  pushEnd(list, &e);
  pushEnd(list, &f);
  deleteFirst(list);
  deleteEnd(list);
  printListDebug(list, printInt);
  pushAfter(list, &d, &h);
  printListDebug(list, printInt);
  pushBefore(list, &d, &k);
  printListDebug(list, printInt);
  deleteAfter(list, &d);
  printListDebug(list, printInt);
  deleteBefore(list, &d);
  printListDebug(list, printInt);
  deleteFind(list, &l);
  deleteFind(list, &d);
  printListDebug(list, printInt);
  found(list, &l, printInt);
  deleteList(&list);
}
void runTestChar() {
  char a[3] = "ab";
  char b[3] = "bc";
  char c[3] = "de";
  char d[3] = "fg";
  char e[3] = "hj";
  char f[3] = "jl";
  char h[4] = "lk";
  char k[4] = "pq";
  LinksList *list = createList(sizeof(char[2]));
  pushFirst(list, &a);
  pushFirst(list, &b);
  pushFirst(list, &c);
  pushEnd(list, &d);
  pushEnd(list, &e);
  pushEnd(list, &f);
  deleteFirst(list);
  deleteEnd(list);
  pushAfter(list, &d, &h);
  pushBefore(list, &d, &k);
  deleteAfter(list, &d);
  deleteBefore(list, &d);
  deleteFind(list, &d);
  found(list, &a, printString);
  deleteList(&list);
}
void runTestFloat() {
  LinksList *list = createList(sizeof(float));
  float a = 10.01;
  float b = 20.02;
  float c = 30.03;
  float d = 88.04;
  float e = 77.05;
  float f = 66.06;
  float h = 777.07;
  float k = 333.08;
  pushFirst(list, &a);
  pushFirst(list, &b);
  pushFirst(list, &c);
  pushEnd(list, &d);
  pushEnd(list, &e);
  pushEnd(list, &f);
  printListDebug(list, printFloat);
  deleteFirst(list);
  deleteEnd(list);
  printListDebug(list, printFloat);
  pushAfter(list, &d, &h);
  pushBefore(list, &d, &k);
  printListDebug(list, printFloat);
  deleteAfter(list, &d);
  printListDebug(list, printFloat);
  deleteBefore(list, &d);
  printListDebug(list, printFloat);
  deleteFind(list, &d);
  printListDebug(list, printFloat);
  found(list, &a, printFloat);
  deleteList(&list);
}

void runTestStruct() {
  LinksList *list = createList(sizeof(struct ab));
  struct ab a = {0, 1};
  struct ab b = {0, 2};
  struct ab c = {0, 3};
  struct ab d = {0, 4};
  struct ab e = {0, 5};
  struct ab f = {0, 6};
  struct ab h = {0, 7};
  struct ab k = {0, 8};
  pushFirst(list, &a);
  pushFirst(list, &b);
  pushFirst(list, &c);
  pushEnd(list, &d);
  pushEnd(list, &e);
  pushEnd(list, &f);
  deleteFirst(list);
  deleteEnd(list);
  printListDebug(list, printStruct);
  pushAfter(list, &d, &h);
  printListDebug(list, printStruct);
  pushBefore(list, &d, &k);
  printListDebug(list, printStruct);
  deleteAfter(list, &d);
  printListDebug(list, printStruct);
  deleteBefore(list, &d);
  printListDebug(list, printStruct);
  deleteFind(list, &d);
  printListDebug(list, printStruct);
  found(list, &b, printStruct);
  deleteList(&list);
}

void printStruct(struct ab *value) {
  printf("a=%d\tb=%d\n", value->a, value->b);
}
