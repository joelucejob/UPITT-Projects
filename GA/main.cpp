/*
 * main.cpp
 *      Author: Joseph
 */
#include <iostream>
#include <cstdlib>
#include "main.h"
#include "fitness.h"
#include "evolve.h"
using namespace std;

int main()
{
	int N, Pc, Pm, MaxGen;		//population size, crossover probability, mutation probability, max amount of generations
	int avgScore;				//average score of all schedules
	int parent1, parent2;		//selected parents to create new generation
	schedule** generation;		//holds the generations of all schedules
	int** score;				//holds the scores of all schedules

	//ask for input
	cout << "What is population size?(Even Number)" << endl;
	cin >> N;
	cout << "How many generations?" << endl;
	cin >> MaxGen;
	cout << "What is crossover probability in percent integer?" << endl;
	cin >> Pc;
	cout << "What is mutation probability in percent integer?" << endl;
	cin >> Pm;
	cout << endl;

	//initialize and link dynamic two dimensional arrays
	generation = new schedule* [MaxGen];
	score = new int* [MaxGen];
	for (int i = 0; i<MaxGen; i++)
	{
		generation[i] = new schedule [N];
		score[i] = new int [N];
	}

	//seed random generator
	srand(time(NULL));

	//create first population
	for (int i=0; i<N; i++)
	{
		//cout << "Schedule " << i << ":" << endl;
		//cout << "CRN/Period/RoomID" << endl;
		for (int j=0; j<maxCourses; j++)
		{
			//create one new schedule
			generation[0][i].s[j] = createChromosome(j);
			//print the chromosome
			//printChromosome(generation, 0, i, j);
		}
		//save the score for this schedule
		setScore(generation, score, 0, i);
		//print the score for this schedule
		//printScore(score[0][i]);
		//cout << endl;
	}

	//calculates the average for selection
	avgScore = findAvg(score, 0, N);

	//outputs
	/*
	cout << endl << "Generation: " << 0 << endl;
	cout << "Min Score: " << findMin(score[0], N) << endl;
	cout << "Max Score: " << findMax(score[0], N) << endl;
	cout << "Average Score: " << avgScore << endl;
	cout << "================================" << endl << endl;
	*/

	for (int genNum=0; genNum<MaxGen-1; genNum++)
	{
		for(int popCount=0; popCount < N; popCount++)
		{
			//find two parents that arn't the same
			do
			{
				parent1 = selectParent(score, genNum, N, avgScore);
				parent2 = selectParent(score, genNum, N, avgScore);
			} while(parent1 == parent2);

			//start crossover for all chromosomes within parents
			crossover(generation[genNum], generation[genNum+1], parent1, parent2, popCount, Pc, Pm);

			//save all scores for new generation
			setScore(generation, score, genNum+1, popCount);
			setScore(generation, score, genNum+1, popCount+1);
			popCount++;
		}

		//print new schedules every 100 generations
		/*
		if((genNum+1) % 99 == 0)
		{
			for (int pop=0; pop<N; pop++)
			{
				cout << "Schedule " << pop << ":" << endl;
				cout << "CRN/Period/RoomID" << endl;
				printSchedule(generation[genNum+1], pop);
				printScore(score[genNum+1][pop]);
				cout << endl;
			}
			//outputs
			cout << "Generation: " << genNum+1 << endl;
			cout << "Min Score: " << findMin(score[genNum+1], N) << endl;
			cout << "Max Score: " << findMax(score[genNum+1], N) << endl;
			cout << "Average Score: " << avgScore << endl;
			cout << "================================" << endl << endl;
		}
		*/

		//calculates the average for new generation
		avgScore = findAvg(score, genNum+1, N);
	}


	for (int i=0; i<MaxGen; i++)
	{
		cout << "(" << i << "," << findMin(score[i], N) << ")";
	}
	cout << endl;
	for (int i=0; i<MaxGen; i++)
	{
		cout << "(" << i << "," << findMax(score[i], N) << ")";
	}
	cout << endl;
	for (int i=0; i<MaxGen; i++)
	{
		cout << "(" << i << "," << findAvg(score, i, N) << ")";
	}
	return 0;
}

chromosome createChromosome(int i)
{
	chromosome tempChromo;

	tempChromo.course = i;
	tempChromo.time = rand() % 14;
	tempChromo.room = rand() % 9;
	return tempChromo;
}

void printChromosome(schedule** gen, int gNum, int n, int i)
{
		cout << gen[gNum][n].s[i].course << " " << gen[gNum][n].s[i].time << " " << gen[gNum][n].s[i].room << endl;
}

void printSchedule(schedule* g, int pop)
//prints the entire schedule
{
	for (int i=0; i<maxCourses; i++)
	{
		cout << g[pop].s[i].course << " " << g[pop].s[i].time << " " << g[pop].s[i].room << endl;
	}
}

void printScore(int s)
{
		cout << "Fitness Score: " << s << endl;
}
