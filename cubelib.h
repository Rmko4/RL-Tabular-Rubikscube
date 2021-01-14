#ifndef CUBE_LIBRARY_H_INCLUDED
#define CUBE_LIBRARY_H_INCLUDED

#include "cube.h"

typedef struct treenode *Tree;

struct treenode {
  Tree child[4];
  float *Q;
  float heuristic;
  int timesReevaluate;
};

typedef struct librarystruct {
  Tree tr;
  int insertions;
} * Library;

void initLibrary(Library *lib);
void freeLibrary(Library lib);

Tree initTreenode();
void freeTree(Tree tr);

int getNode(Library lib, Cube c, Tree *tr);
int insertCount(Library lib);

#endif