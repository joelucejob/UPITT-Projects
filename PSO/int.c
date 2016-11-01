/*
 * int.c
 *      Author: Joseph
 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "pso.h"
#define MAX_FILENAME 80

//array of particles within the solution space
particle_t particles[MAX_PARTICLES];
particle_t pbest[MAX_PARTICLES];

//global Best particle
particle_t gbest;

void storePbest(int index )
{
  //save the particle to its personal best
  memcpy( (void *)&pbest[index], (void *)&particles[index],
           sizeof(particle_t) );

  //if this pbest is better than the gbest, save it
  if (pbest[index].fitness > gbest.fitness) {
    gbest.position.x = pbest[index].position.x;
    gbest.position.y = pbest[index].position.y;
    gbest.fitness    = pbest[index].fitness;
  }
  return;
}

void closePopulation()
{
  int i;

  for ( i = 0 ; i < MAX_PARTICLES ; i++ ) {

    fclose( particles[i].fp );

  }
  return;
}

void initPopulation()
{
  int i;
  char filename[MAX_FILENAME+1];
  extern double checkFitness( double, double );
  gbest.fitness = (double)-9999.0;

  for ( i = 0 ; i < MAX_PARTICLES ; i++ )
  {
    //initialize the output file pointer
    sprintf( filename, "particle%02d.txt", i );
    particles[i].fp = fopen( filename, "w" );

    //initialize a particle's starting point and fitness
    particles[i].position.x = getPoint();
    particles[i].position.y = getPoint();
    particles[i].fitness =
      checkFitness( particles[i].position.x, particles[i].position.y );

    //initialize the particle's dimensional velocity
    particles[i].velocity.x = (getSRand() / (double)10.0);
    particles[i].velocity.y = (getSRand() / (double)10.0);

    //since this is the only fitness value, store this as pbest
    storePbest( i );

    //store this position to the particles trace file
    fprintf( particles[i].fp, "%lg, %lg, %lg\n",
             particles[i].position.x, particles[i].position.y,
             particles[i].fitness );
  }
  return;
}
