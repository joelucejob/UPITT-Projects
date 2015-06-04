/*
 * pso.h
 *      Author: Joseph
 */
#include <stdlib.h>
#define MAX_PARTICLES	5
#define getSRand()	((double)rand() / (double)RAND_MAX)
#define PI		((double)3.1415926)
#define getPoint()	(((4.0 * PI) * getSRand()) - (2.0 * PI))
#define NUM_ITERATIONS	100

typedef struct
{
  double x;
  double y;
} vector_t;

typedef struct
{
  FILE *fp;
  vector_t position;
  vector_t velocity;
  double fitness;
} particle_t;
