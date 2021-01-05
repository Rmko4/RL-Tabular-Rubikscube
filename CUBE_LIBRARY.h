#ifndef CUBE_LIBRARY_H_INCLUDED
#define CUBE_LIBRARY_H_INCLUDED

#include "CUBE_LIBRARY.h"

typedef struct treenode *Tree;

typedef struct treenode {
  Tree child[4];
};

typedef struct librarystruct {
  Tree tr;
  int insertions;
  int checks;
} *Library;



Library initLibrary();

#endif