#include <stdio.h>
#include <stdlib.h>

#include "CUBE_LIBRARY.h"
#include "CUBE.h"

Library initLibrary() {
  Library l = safeMalloc(sizeof(struct librarystruct));
  l->tr = NULL;
  l->insertions = 0;
}

int libraryNumberInsertions(Library lib){
  return lib->insertions;
}

void freeLibrary(Library lib){
  freeTree(lib->tr);
  free(lib);
}

void freeTree(Tree tr){
  if (tr == NULL){
    return;
  }
  for (int i =0; i < 4; i++){
    freeTree(tr->child[i]);
  }
  free(tr);
}


Tree initTreenode(){
  Tree tr = safeMalloc(sizeof(struct treenode));
  for (int i =0; i < 4 ; i++){
    tr->child[i] = NULL;
  }
  return tr;
}

int checkInLibrary(Library lib, Cube c){
  Tree tr = lib->tr;
  if (tr ==NULL){
    return 0;
  }

  for (int i =0; i < NCORNER; i ++){

    //4th corner can be skipped because it is forced
    if (i %4 == 3){
      continue;
    }
    if (tr->child[c->corner[i]] == NULL){
      return 0;
    }
    tr = tr->child[c->corner[i]];
  }

  for (int i =0; i < NEDGE; i ++){

    //4th edge can be skiiped because it is last in its set and therfore forced
    if (i %4 == 3){
      continue;
    }
    if (tr->child[c->edge[i]] == NULL){
      return 0;
    }
    tr = tr->child[c->edge[i]];
  }

  return tr ==  NULL ? 0 : 1;
}

void insertInLibrary(Cube c, Library lib) {
  Tree tr = lib->tr;

  lib ->insertions +=1;

  if (tr == NULL){
    tr = initTreenode();
  }

  for (int i =0; i < NCORNER; i ++){

    //4th corner can be skiiped because it is last in its set and therfore forced
    if (i %4 == 3){
      continue;
    }
    if (tr->child[c->corner[i]] == NULL){
      tr->child[c->corner[i]] = initTreenode();
    }
    tr = tr->child[c->corner[i]];
  }

  for (int i =0; i < NEDGE; i ++){

    //4th edge can be skiiped because it is last in its set and therfore forced
    if (i %4 == 3){
      continue;
    }
    if (tr->child[c->edge[i]] == NULL){
      tr->child[c->edge[i]] = initTreenode();

      
    }else if (i == NEDGE -2){
      //last node alreaddy exists so cube was in library before:
      printf("Cube was alreaddy in library!\n");
      freeLibrary(lib);
      exit(0);
    }
    tr = tr->child[c->edge[i]];
  }

}
