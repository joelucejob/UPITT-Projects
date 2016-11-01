/*
 * evolve.cpp
 *      Author: Joseph
 */
#include <iostream>
#include <cstdlib>
#include "main.h"
#include "evolve.h"
using namespace std;

void mutate(chromosome c, int tPop, int pm)
{
	//decide if mutation should occur
		if (pm > (rand() % 100))
		{
			c.tableIndex = rand() % tPop;
		}
}

void crossover(generation* g, generation* p, int curPop, int personPop, int p1, int p2, int pc, int pm, int t)
{
	int point;		//crossover point

	//decide if crossover will occur
	if ((pc-1) > rand() % 100)
	{
		//find a crossover point
		point = rand() % personPop;
		//create two children
		for (int i=0; i<point; i++)
		{
			g[curPop].list[i].tableIndex = p[p1].list[i].tableIndex;
			g[curPop+1].list[i].tableIndex = p[p2].list[i].tableIndex;
			mutate(g[curPop].list[i], t, pm);
			mutate(g[curPop+1].list[i], t, pm);
			//cout << g[pop].list[i].tableIndex << endl;
			//cout << g[pop+1].list[i].tableIndex << endl;
		}
		for (int i=point; i<personPop; i++)
		{
			g[curPop].list[i].tableIndex = p[p2].list[i].tableIndex;
			g[curPop+1].list[i].tableIndex = p[p1].list[i].tableIndex;
			mutate(g[curPop].list[i], t, pm);
			mutate(g[curPop+1].list[i], t, pm);
			//cout << g[pop].list[i].tableIndex << endl;
			//cout << g[pop+1].list[i].tableIndex << endl;
		}
	}
	//if no crossover, just copy parents over
	else
	{
		for (int i=0; i<personPop; i++)
		{
			g[curPop].list[i].tableIndex = p[p1].list[i].tableIndex;
			g[curPop+1].list[i].tableIndex = p[p2].list[i].tableIndex;
			mutate(g[curPop].list[i], t, pm);
			mutate(g[curPop+1].list[i], t, pm);
			//cout << g[pop].list[i].tableIndex << endl;
			//cout << g[pop+1].list[i].tableIndex << endl;
		}
	}
}

int findAvg(generation* g, int pop)
//finds the average score for all scores
{
	int sum = 0; 	//stores the sum of all fitness

	for (int i=0; i<pop; i++)
	{
		sum = g[i].fitness + sum;
		//cout << "f" <<g[i].fitness << endl;
	}
	//cout << "s" << sum << endl;
	return (sum/pop);
}

int selectParent(generation* g, int pop, int avg)
//finds a parent within the generation
//uses elitest selection
{
	int parent = rand() % pop;
	int count = pop;
	int fitness;

	while (count--)
	{
		fitness = g[parent].fitness;
		//cout << g[parent].fitness << " " << avg << endl;
		if (fitness >= avg)
		{
			return parent;
		}
		if (++parent >= pop)
		{
			parent = 0;
		}
	}
	return rand() % pop;
}



