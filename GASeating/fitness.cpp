/*
 * fitness.cpp
 *      Author: Joseph
 */
#include <iostream>
#include "main.h"
#include "fitness.h"
#include <cmath>
using namespace std;

int calcFitness(generation gen, person* person, int pop, int tNum, int sNum)
{
	int score = 0;
	int count;

	//check if not enough seats
	for (int t=0; t<tNum; t++)
	{
		count=0;
		for (int i=0; i<pop; i++)
		{
			if (gen.list[i].tableIndex == t)
			{
				count++;
			}
		}
		if (count > sNum)
		{
			score = score - 5000;
		}
		else
		{
			score = score + 5000;
		}
	}

	for (int i=0; i<pop; i++)
	{
		for (int j=1; j<pop; j++)
		{
			//check if two people are in the same table
			if (gen.list[i].tableIndex == gen.list[j].tableIndex)
			{
				//if people are 5 years of age apart
				if (abs(float(person[i].age - person[j].age)) <= 5)
				{
					score = score + 500;
				}
				//if people are 20 years of age apart
				if (abs(float(person[i].age - person[j].age)) >= 20)
				{
					score = score - 1000;
				}
				//if people have the same profession
				if (person[i].profession == person[j].profession)
				{
					score = score + 2000;
				}
				//check if likes match
				for (int x=0; x<person[i].likeCount; x++)
				{
					for (int y=0; y<person[j].likeCount; y++)
					{
						if (person[i].likes[x] == person[j].likes[y])
						{
							score = score + 1000;
						}
					}
				}
				//check if dislikes match
				for (int x=0; x<person[i].dislikeCount; x++)
				{
					for (int y=0; y<person[j].dislikeCount; y++)
					{
						if (person[i].dislikes[x] == person[j].dislikes[y])
						{
							score = score + 1000;
						}
					}
				}
				//check if likes match dislikes
				for (int x=0; x<person[i].likeCount; x++)
				{
					for (int y=0; y<person[j].dislikeCount; y++)
					{
						if (person[i].likes[x] == person[j].dislikes[y])
						{
							score = score - 1000;
						}
					}
				}
				//check if with the right person
				for(int x=0; x<person[i].withCount; x++)
				{
					if (person[i].with[x] == person[j].name)
					{
						score = score + 10000;
					}
				}
			}
		}
	}
	return score;
}
