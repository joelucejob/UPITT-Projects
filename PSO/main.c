/*
 * main.c
 *      Author: Joseph
 */
#include <stdio.h>
#include <time.h>
#include <iostream>
#include "pso.h"
using namespace std;

/* Acceleration and dt constants */
double dt = 0.1;

int main()
{
  int iter, N;
  double c1, c2;
  extern void initPopulation( void );
  extern void moveSwarm( void );
  extern void closePopulation( void );
  extern particle_t gbest;

  //seed the random number generator
  srand( time(NULL) );

  //ask for input
  cout << "c1?" << endl;
  cin >> c1 << endl;
  cout << "c2?" << endl;
  cin >> c2 >> endl;
  cout << "N?" << endl;
  cin >> N >> endl;

  //initialize the swarm
  initPopulation();

  //perform NUM_ITERATIONS number of iterations
  for (iter = 0 ; iter < NUM_ITERATIONS ; iter++)
  {
	  moveSwarm();
	  printf( "%lg\n", gbest.fitness );
  }

  //cleanup the swarm
  closePopulation();

  return 0;
}
