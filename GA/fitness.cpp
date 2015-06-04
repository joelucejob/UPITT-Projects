/*
 * fitness.cpp
 *      Author: Joseph
 */
#include <iostream>
#include "main.h"
#include "fitness.h"
using namespace std;

void setScore(schedule** g, int** score, int gNum, int n)
{
	score[gNum][n] = score[gNum][n] + calcFitness(g, gNum, n);
}

int calcFitness(schedule** g, int gNum, int n)
{
	int score = 0;	//collective score of the schedule

	for (int i = 0; i <= 26; i++)
	{
		score = score + checkMedia(g[gNum][n].s[i]);
		score = score + checkSize(g[gNum][n].s[i]);
	}
	score = score + checkTimeRoom(g[gNum][n]);
	score = score + checkProfessorTime(g[gNum][n]);
	return score;
}

int checkMedia(chromosome s)
{
	int badScore = -50;	//if a course requires a room with media and doesn't get it
	int goodScore = 20;	//if a course requires a room with media and does get it

	//if course requires a media
	if (courseMedia[s.course])
	{
		//if course requiring media has a room without media
		if (roomMedia[s.room] == false)
		{
			//cout << "bad" << endl;
			return badScore;
		}
		//if course requiring media does get media
		else
		{
			//cout << "good" << endl;
			return goodScore;
		}
	}
	//cout << "ok" << endl;
	return 0;
}

int checkSize(chromosome s)
{
	int badScore = -70;	//if a course's room is not large enough
	int goodScore = 20;	//if a course's room is large enough

	//if course's room is big enough
	if (courseSize[s.course] <= roomSize[s.room])
	{
		//cout << "good" << endl;
		return goodScore;
	}
	else
		//cout << "bad" << endl;
		return badScore;
}

int checkTimeRoom(schedule sch)
{
	int badScore = -300;
	int superBadScore = -600;
	int count = 0;

	for (int i=0; i<maxCourses; i++)
	{
		for (int j=(i+1); j<maxCourses; j++)
		{
			//check if same time
			if (sch.s[i].time == sch.s[j].time)
			{
				//see if rooms match
				if (sch.s[i].room == sch.s[j].room)
				{
					count++;
					if (count >= 3)
					{
						return superBadScore;
					}
				}
			}
		}
	}
	if (count != 0)
	{
		return badScore;
	}
	return 0;
}

int checkProfessorTime(schedule sch)
{
	int badScore = -300;

	for (int i=0; i<maxCourses; i++)
	{
		for (int j=(i+1); j<maxCourses; j++)
		{
			//check if same professor
			if(professorData[sch.s[i].course] == professorData[sch.s[j].course])
			{
				//check if same time
				if(sch.s[i].time == sch.s[j].time)
				{
					return badScore;
				}
			}
		}
	}
	return 0;
}
