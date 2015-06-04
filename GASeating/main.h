/*
 * main.h
 */
#include <string>
using namespace std;

	struct person {
		string name;
		int age;
		string profession;
		string* likes;
		string* dislikes;
		string* with;
		int likeCount = 0;
		int dislikeCount = 0;
		int withCount = 0;
	};

	struct chromosome {
		int tableIndex;
	};

	struct generation {
		chromosome* list;
		int fitness;
	};
