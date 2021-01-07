#ifndef CUBE_LIBRARY_H_INCLUDED
#define CUBE_LIBRARY_H_INCLUDED

#include "cube.h"

typedef struct treenode *Tree;

struct treenode {
  Tree child[4];
  float *value;
};

typedef struct librarystruct {
  Tree tr;
  int insertions;
} * Library;

void initLibrary(Library *lib);
void freeLibrary(Library lib);

Tree initTreenode();
void freeTree(Tree tr);

int libraryNumberInsertions(Library lib);
int inLibrary(Library lib, Cube c);
int nodeInLibrary(Cube c, Library lib, Tree *tr);

#endif