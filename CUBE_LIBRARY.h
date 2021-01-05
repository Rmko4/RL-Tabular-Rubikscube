#ifndef CUBE_LIBRARY_H_INCLUDED
#define CUBE_LIBRARY_H_INCLUDED

#include "CUBE.h"
#include "CUBE_LIBRARY.h"

typedef struct treenode *Tree;

struct treenode {
  Tree child[4];
  float value;
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

#endif