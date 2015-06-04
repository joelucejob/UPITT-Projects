/*
 * main.h
 *      Author: Joseph
 */
	const int maxCourses = 27;

	/* 0-Hagerich
	 * 1-Bilitski
	 * 2-Smigla
	 * 3-IM
	 * 4-Federick
	 * 5-Ferencek
	 * 6-Thomson
	 * 7-Darling
	 * 8-Hinder
	 */

	const int professorData[] = {0,1,1,1,0,0,2,3,3,4,
								5,5,5,6,6,6,7,7,7,1,
								1,8,8,8,0,0,2};

	const bool courseMedia[] = {false, true, true, true, true, true, true, false, false, false,
						 false, false, false, false, false, false, true, true, true, true,
						 true, false, false, false, true, true, true};

	const int courseSize[] = {20,20,20,15,20,20,35,35,35,35,
				   40,50,60,40,50,60,45,40,35,15,
				   15,30,35,30,20,20,20};

	const int roomSize[] = {30,50,40,20,30,35,40,45,100};

	const bool roomMedia[] = {true, true, false, false, true, false, false ,false, true};
/*
	const char* courseName[] = {"cs015",
								"cs456",
								"cs456",
								"cs1783",
								"cs455",
								"cs455",
								"cs455",
								"cs015",
								"cs015",
								"cs015",
								"cs015",
								"math001",
								"math001",
								"math001",
								"math002",
								"math002",
								"math002",
								"soc100",
								"soc100",
								"soc100",
								"cs047",
								"cs047",
								"psy200",
								"psy200",
								"psy200",
								"cs045",
								"cs045",
								"cs045"};
*/
	struct chromosome {
		int course;		//CRN
		int time;		//period
		int room;		//index number for room data
	};

	struct schedule {
		chromosome s[maxCourses];	//a schedule
	};

	chromosome createChromosome(int);
	void printChromosome(schedule**, int, int, int);
	void printSchedule(schedule*, int);
	void printScore(int);
