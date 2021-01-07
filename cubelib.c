#include <stdio.h>
#include <stdlib.h>

#include "cube.h"
#include "cubelib.h"

void initLibrary(Library *l) {
  *l = safeMalloc(sizeof(struct librarystruct));
  (*l)->tr = initTreenode();
  (*l)->insertions = 0;
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
  if (tr->value != NULL) {
    free(tr->value);
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
  tr->value = NULL;
  return tr;
}

int inLibrary(Library lib, Cube c) {
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

int nodeInLibrary(Cube c, Library lib, Tree *trh) {
  Tree tr;
  int piece, inserted;

  tr = lib->tr;
  inserted = 0;
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

      if (i == NEDGE - 2) {
        inserted = 1;
        lib->insertions += 1;
      }
    }
    tr = tr->child[piece];
  }

  *trh = tr;
  return inserted;
}