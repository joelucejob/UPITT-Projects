/*
 * main.cpp
 *      Author: Joseph
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "main.h"
#include "fitness.h"
#include "evolve.h"

using namespace std;

int main()
{
	int tableNum, seatNum, genNum, pop, personPop = 0, Pc, Pm, personCount = 0, count = 0;
	generation** generations;
	person* peopleInfo;
	string tempStr[50];

	cout << "Enter amount of tables." << endl;
	cin >> tableNum;
	cout << "Enter amount of seats per table." << endl;
	cin >> seatNum;
	cout << "How many generations?" << endl;
	cin >> genNum;
	cout << "Population Size?(Even number)" << endl;
	cin >> pop;
	cout << "What is crossover probability in percent integer?" << endl;
	cin >> Pc;
	cout << "What is mutation probability in percent integer?" << endl;
	cin >> Pm;

	//read the file
	ifstream checklistFile;
	checklistFile.open("checklist.txt");
	//check how many people on the list
	while(!checklistFile.eof())
	{
		checklistFile >> tempStr[count];
		if (tempStr[count] == "Name:")
		{
			personPop++;
		}
	}
	checklistFile.close();

	//initialize generations and peopleInfo
	peopleInfo = new person[personPop];
	generations = new generation*[genNum];
	for (int i=0; i < genNum; i++)
	{
		generations[i] = new generation[pop];
		for (int j=0; j < pop; j++)
		{
			generations[i][j].list = new chromosome[personPop];
		}
	}

	string str;
	bool started = false;

	//store info
	checklistFile.open("checklist.txt");
	while(checklistFile >> str)
	{
		if (str == "Name:")
		{
			if (started == true)
			{
				personCount++;
			}
			checklistFile >> peopleInfo[personCount].name;
		}
		else if (str == "Age:")
		{
			checklistFile >> peopleInfo[personCount].age;
		}
		else if (str == "Profession:")
		{
			checklistFile >> peopleInfo[personCount].profession;
		}
		else if (str == "Likes:")
		{
			checklistFile >> count;
			peopleInfo[personCount].likes = new string[count];
			peopleInfo[personCount].likeCount = count;
			for (int i=0; i<count; i++)
			{
				checklistFile >> peopleInfo[personCount].likes[i];
				//cout << peopleInfo[personCount].likes[i] << endl;
			}
		}
		else if (str == "Dislikes:")
		{
			checklistFile >> count;
			peopleInfo[personCount].dislikes = new string[count];
			peopleInfo[personCount].dislikeCount = count;
			for (int i=0; i<count; i++)
			{
				checklistFile >> peopleInfo[personCount].dislikes[i];
				//cout << peopleInfo[personCount].dislikes[i] << endl;
			}
		}
		else if (str == "With:")
		{
			checklistFile >> count;
			peopleInfo[personCount].with = new string[count];
			peopleInfo[personCount].withCount = count;
			for (int i=0; i<count; i++)
			{
				checklistFile >> peopleInfo[personCount].with[i];
				//cout << peopleInfo[personCount].with[i] << endl;
			}
		}
		started = true;
	}
	checklistFile.close();

	//seed random generator
	srand(time(NULL));

	//intialize first population
	for (int i=0; i<personPop; i++)
	{
		for (int j=0; j<pop; j++)
		{
			generations[0][j].list[i].tableIndex = rand() % tableNum;
			//cout << generations[0][j].list[i].tableIndex << endl;
		}
	}

	//find fitness of population
	for (int i=0; i<pop; i++)
	{
		generations[0][i].fitness = calcFitness(generations[0][i], peopleInfo, personPop, tableNum, seatNum);
		//cout << generations[genCount][i].fitness << endl;
	}

	int avg;

	//calculate average score of population
	avg = findAvg(generations[0], pop);
	cout << avg << endl;

	/*
	//print seating
	//for each population
	cout << "Generation: " << genCount << endl;
	for (int i=0; i<pop; i++)
	{
		cout << "====" << endl;
		cout << "Population: " << i << endl;
		//for each table
		for(int t=0; t<tableNum; t++)
		{
			cout << "----" << endl;
			cout << "Table: " << t << endl;
			//search for person with same table
			for(int j=0; j<personPop; j++)
			{
				//if tables match
				if (generations[genCount][i].list[j].tableIndex == t)
				{
					cout << "Name: " << peopleInfo[j].name << endl;
				}
			}
		}
	}
	*/

	//outputs
	cout << endl << "Generation: " << 0 << endl;
	cout << "Average Score: " << avg << endl;
	cout << "================================" << endl << endl;

	int p1, p2;
	int highFit = -99999, bestg, bestp;

	for(int g=0; g<genNum-1; g++)
	{
		//find two parents to crossover
		//find two parents that arn't the same
		for(int i=0; i<pop; i++)
		{
			do
			{
				p1 = selectParent(generations[g], pop, avg);
				p2 = selectParent(generations[g], pop, avg);
			} while(p1 == p2);

			//start crossover for all chromosomes within parents for next generation
			crossover(generations[g+1], generations[g], i, personPop, p1, p2, Pc, Pm, tableNum);
			//cout << generations[genCount+1][0].list[0].tableIndex << endl;

			//save fitness
			generations[g+1][i].fitness = calcFitness(generations[g+1][i], peopleInfo, personPop, tableNum, seatNum);
			generations[g+1][i+1].fitness = calcFitness(generations[g+1][i+1], peopleInfo, personPop, tableNum, seatNum);
			i++;
		}

		//Calculate average fitness for a generation
		avg = findAvg(generations[g], pop);

		cout << endl << "Generation: " << g << endl;
		cout << "Average Score: " << avg << endl;
		cout << "================================" << endl << endl;

		//find best child
		for (int i=0; i<personPop; i++)
		{
			if (generations[g][i].fitness > highFit)
			{
				highFit = generations[g][i].fitness;
				bestg = g;
				bestp = i;
			}
		}
	}

	//display best seating
	cout << "Generation: " << bestg << endl;
		for(int t=0; t<tableNum; t++)
		{
			cout << "----" << endl;
			cout << "Table: " << t << endl;
			//search for person with same table
			for(int j=0; j<personPop; j++)
			{
				//if tables match
				if (generations[bestg][bestp].list[j].tableIndex == t)
				{
					cout << "Name: " << peopleInfo[j].name << endl;
				}
			}
		}
	return 0;
}
