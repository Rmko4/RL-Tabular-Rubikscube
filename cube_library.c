#include <stdio.h>
#include <stdlib.h>

#include "CUBE.h"
#include "CUBE_LIBRARY.h"

Library initLibrary() {
  Library l = safeMalloc(sizeof(struct librarystruct));
  l->tr = initTreenode();
  l->insertions = 0;
}

int libraryNumberInsertions(Library lib) { return lib->insertions; }

void freeLibrary(Library lib) {
  freeTree(lib->tr);
  free(lib);
}

void freeTree(Tree tr) {
  if (tr == NULL) {
    return;
  }
  for (int i = 0; i < 4; i++) {

    freeTree(tr->child[i]);
  }
  free(tr);
}

Tree initTreenode() {
  Tree tr = safeMalloc(sizeof(struct treenode));
  for (int i = 0; i < 4; i++) {
    tr->child[i] = NULL;
  }
  return tr;
}

int checkInLibrary(Library lib, Cube c) {
  Tree tr = lib->tr;
  int piece;
  for (int i = 0; i < NCORNER; i++) {

    // 4th corner can be skipped because it is forced
    if (i % 4 == 3) {
      continue;
    }
    piece = c->corner[i] % 4;
    if (tr->child[piece] == NULL) {
      return 0;
    }
    tr = tr->child[piece];
  }

  for (int i = 0; i < NEDGE; i++) {

    // 4th edge can be skiiped because it is last in its set and therfore forced
    if (i % 4 == 3) {
      continue;
    }
    piece = c->edge[i] % 4;
    if (tr->child[piece] == NULL) {
      return 0;
    }
    tr = tr->child[piece];
  }

  return tr == NULL ? 0 : 1;
}

void insertInLibrary(Cube c, Library lib) {
  Tree tr = lib->tr;
  int piece;

  lib->insertions += 1;

  for (int i = 0; i < NCORNER; i++) {

    // 4th corner can be skipped because it is last in its set and therfore
    // forced
    if (i % 4 == 3) {
      continue;
    }
    piece = c->corner[i] % 4;
    if (tr->child[piece] == NULL) {
      tr->child[piece] = initTreenode();
    }
    tr = tr->child[piece];
  }

  for (int i = 0; i < NEDGE; i++) {

    // 4th edge can be skiiped because it is last in its set and therfore forced
    if (i % 4 == 3) {
      continue;
    }
    piece = c->edge[i] % 4;
    if (tr->child[piece] == NULL) {
      tr->child[piece] = initTreenode();

    } else if (i == NEDGE - 2) {
      // last node alreaddy exists so cube was in library before:
      printf("Cube was alreaddy in library!\n");
      freeLibrary(lib);
      exit(0); // Wait why exactly
    }
    tr = tr->child[piece];
  }
}
