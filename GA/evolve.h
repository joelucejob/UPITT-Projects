/*
 * evolve.h
 *      Author: Joseph
 */
void crossover(schedule*, schedule*, int, int, int, int, int);
void mutate(schedule*, int, int, int);
int findAvg(int**, int, int);
int selectParent(int**, int, int, int);
int findMin(int*, int);
int findMax(int*, int);
