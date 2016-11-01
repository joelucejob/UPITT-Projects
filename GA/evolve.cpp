/*
 * evolve.cpp
 *      Author: Joseph
 */
#include <iostream>
#include <cstdlib>
#include "main.h"
#include "evolve.h"
using namespace std;

void crossover(schedule* g, schedule* n, int p1, int p2, int pop, int pc, int pm)
//does a crossover with the schedules
{
	int point;					//crossover point

	//decide if crossover will occur
	if ((pc-1) > rand() % 100)
	{
		//find a crossover point
		point = rand() % maxCourses;
		//start crossover
		for (int i=0; i<point; i++)
		{
			n[pop].s[i].course = i;
			n[pop+1].s[i].course = i;
			n[pop].s[i].time = g[p1].s[i].time;
			n[pop].s[i].room = g[p1].s[i].room;
			n[pop+1].s[i].time = g[p2].s[i].time;
			n[pop+1].s[i].room = g[p2].s[i].room;
			mutate(n, pop, i, pm);
			mutate(n, pop+1, i, pm);
		}
		for (int i=point; i<maxCourses; i++)
		{
			n[pop].s[i].course = i;
			n[pop+1].s[i].course = i;
			n[pop].s[i].time = g[p2].s[i].time;
			n[pop].s[i].room = g[p2].s[i].room;
			n[pop+1].s[i].time = g[p1].s[i].time;
			n[pop+1].s[i].room = g[p1].s[i].room;
			mutate(n, pop, i, pm);
			mutate(n, pop+1, i, pm);
		}
	}
	//if no crossover, just copy parents over
	else
	{
		for (int i=0; i<maxCourses; i++)
		{
			n[pop].s[i].course = i;
			n[pop+1].s[i].course = i;
			n[pop].s[i].time = g[p1].s[i].time;
			n[pop].s[i].room = g[p1].s[i].room;
			n[pop+1].s[i].time = g[p2].s[i].time;
			n[pop+1].s[i].room = g[p2].s[i].room;
			mutate(n, pop, i, pm);
			mutate(n, pop+1, i, pm);
		}
	}
}

void mutate(schedule* n, int pop, int i, int pm)
{
	//decide if mutation should occur
	if (pm > rand() % 1000)
	{
		n[pop].s[i].time = rand() % 14;
		n[pop].s[i].room = rand() % 9;
		//cout << "Mutated" << pop << " " << n[pop].s[i].time << " " << n[pop].s[i].room << endl;
	}
}

int findAvg(int** score, int gNum, int pop)
//finds the average score for all scores
{
	int sum = 0; 	//stores the sum of all scores

	for(int i=0; i<pop; i++)
	{
		sum = score[gNum][i] + sum;
	}
	return (sum/pop);
}

int selectParent(int** score, int gNum, int pop, int avg)
//finds a parent within the generation and returns the CRN
//uses elitest selection
{
	int parent = rand() % pop;
	int count = pop;
	int fitness;

	while (count--)
	{
		fitness = score[gNum][parent];
		if (fitness >= avg)
		{
			return parent;
		}
		if (++parent >= pop-1)
		{
			parent = 0;
		}
	}
	return rand() % pop;
}

int findMin(int* s, int maxPop)
//finds the min score for the entire generation
{
	int min = 9999;

	for (int i=0; i<maxPop; i++)
	{
		if (min > s[i])
		{
			min = s[i];
		}
	}
	return min;
}

int findMax(int* s, int maxPop)
//finds the max score for the entire generation
{
	int max = -9999;

	for (int i=0; i<maxPop; i++)
	{
		if (max < s[i])
		{
			max = s[i];
		}
	}
	return max;
}
