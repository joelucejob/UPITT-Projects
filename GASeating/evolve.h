/*
 * evolve.h
 *      Author: Joseph
 */
void mutate(chromosome, int, int);
void crossover(generation*, generation*, int, int, int, int, int, int, int);
int findAvg(generation*, int);
int selectParent(generation*, int, int);

