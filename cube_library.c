#include <stdio.h>
#include <stdlib.h>

#include "CUBE_LIBRARY.h"
#include "CUBE.h"

Library initLibrary() {
  Library l = safeMalloc(sizeof(struct librarystruct));
  l->tr = NULL;
  l->insertions = 0;
  l->checks = 0;
}


Tree initTreenode(){
  Tree tr = safeMalloc(sizeof(struct treenode));
  tr->child = safeMalloc(sizeof(Tree) *4);
  for (int i =0; i < 4 ; i++){
    tr->child[i] = NULL;
  }
  return tr;
}

void insertInLibrary(Cube c, Library lib) {
  Tree tr = lib->tr;

  if (tr == NULL){
    tr = initTreenode();
  }

  for (int i =0; i < 3; i ++){
    if (tr->child[])

  }


}
