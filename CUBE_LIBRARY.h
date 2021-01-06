#ifndef CUBE_LIBRARY_H_INCLUDED
#define CUBE_LIBRARY_H_INCLUDED

#include "CUBE.h"

typedef struct treenode *Tree;

struct treenode {
  float heuristic;
  int timesReevaluate;
  Tree child[4];
};

typedef struct librarystruct {
  Tree tr;
  int insertions;
} * Library;

Library initLibrary();

int libraryNumberInsertions(Library lib);

void freeLibrary(Library lib);

void freeTree(Tree tr);

Tree initTreenode();

int checkInLibrary(Library lib, Cube c);

void insertInLibrary(Cube c, Library lib);

Tree getleave(Cube c, Library lib);

#endif