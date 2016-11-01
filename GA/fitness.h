/*
 * fitness.h
 *      Author: Joseph
 */
void setScore(schedule**, int**, int, int);
int calcFitness(schedule**, int, int);
int checkMedia(chromosome);
int checkSize(chromosome);
int checkTimeRoom(schedule);
int checkProfessorTime(schedule sch);
