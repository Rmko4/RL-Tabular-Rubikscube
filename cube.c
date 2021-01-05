#include <stdio.h>
#include <stdlib.h>

#define NCORNER 8
#define NEDGE 12

typedef struct cubestruct
{
  int corner[NCORNER];
  int edge[NEDGE];
} * Cube;

void *safeMalloc(int n) {
  void *ptr = malloc(n);
  if (ptr == NULL) {
    perror("Allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

Cube initCube()
{
  Cube c; 
  size_t i;

  c = safeMalloc(sizeof(struct cubestruct));
  for (i = 0; i < NCORNER; i++)
  {
    c->corner[i] = i;
  }
  for (i = 0; i < NEDGE; i++)
  {
    c->edge[i] = i;
  }
  return c;
}

void freeCube(Cube c){
  free(c);
}

void printCube(Cube c){

  printf("Corners:");
  for (int i=0; i < NCORNER; i++){
    printf(" %d", c->corner[i]);
  }
  printf("\n");

  printf("Edges:");
  for (int i=0; i < NEDGE; i++){
    printf(" %d", c->edge[i]);
  }
  printf("\n");
}

int main(int argc, char const *argv[])
{
  /* code */
  Cube c = initCube();
  printCube(c);
  freeCube(c);
  return 0;
}