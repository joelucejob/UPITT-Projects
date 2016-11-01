/*
 * fitness.c
 *      Author: Joseph
 */
#include <stdio.h>
#include <math.h>
#include "pso.h"

double checkFitness( double x, double y )
{
  //Fitness Function
	return (double)sin(2/x) +sin(2*x) +cos(x) +sin(20/y);
  //return ( (double)(6.0 * cos(sqrt(x*x+y*y))/(x*x+y*y+6.0)) );
}
