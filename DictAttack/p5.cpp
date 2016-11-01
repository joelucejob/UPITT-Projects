#include <iostream>
#include <crypt.h>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

int main()
{
	const char* salt = "elxmCxPd";
	char* pw;
	char* pwHash;
	const char* hash = "e1W5x/LmQ9kyU";
	string tempStr;

	ifstream dictFile;
	dictFile.open ("wordlist.txt");
	if (dictFile.is_open())
	{
		while (dictFile >> tempStr)
		{
			pw = new char[tempStr.size()+1];
			pw[tempStr.size()] = 0;
			memcpy(pw, tempStr.c_str(), tempStr.size());
			pwHash = crypt(pw, salt);
                        cout << tempStr << "   " << pw << "   " << pwHash << endl;					
			if (strcmp(pwHash, hash) == 0)
			{
				cout << "Password found!" << endl;
				break;
			}
		}
	}	
	else
	{
		cout << "File not found!" << endl;
	}
	dictFile.close();
}
