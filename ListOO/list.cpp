#include <iostream>
#include <string.h>
#include <fstream>
#include "list.h"

using namespace std;

int list::AddItem(rec r)
{
   	rec *ptr;
   	rec *new_ptr = new rec;
	ptr = this -> first;	
        *new_ptr = r;

        //check if empty
        if (this -> first == NULL)
        {
                this -> first = new_ptr;
                this -> last = new_ptr;
                return 1;
        }

   	//Check for same ids
   	while (ptr)
   	{
      		if (strcmp(ptr -> id, new_ptr -> id) == 0)
      		{
         		return 0;
      		}
      		ptr = ptr -> next;
   	}

   	if (strcmp(new_ptr -> lastname, this -> first -> lastname) < 0)
   	{
      		new_ptr -> next = this -> first;
      		this -> first -> prev = new_ptr;
      		this -> first = new_ptr;
   	}
	
	//insert into end
   	else if (strcmp(last -> lastname, new_ptr -> lastname) < 0)
   	{
      		new_ptr -> prev = this -> last;
      		this -> last -> next = new_ptr;
      		this -> last = new_ptr;
   	}
   	
	//insert into middle
	else
   	{
      		//find position to insert
      		ptr = this -> first;
      		while (ptr)
      		{
         		if (strcmp(ptr -> lastname, new_ptr -> lastname) < 0)
         		{
            		ptr = ptr -> next;
         		}
         		else
         		{
            			break;
         		}
      		}
      		new_ptr -> next = ptr;
      		new_ptr -> prev = ptr -> prev;
      		ptr -> prev -> next = new_ptr;
      		ptr -> prev = new_ptr;
   	}
   	return 1;
}

int list::DeleteItem(char* delid)
{
   	rec *ptr;
        int found = 1;
	ptr = this -> first;

	//check if list is emmpty
   	if (ptr == NULL)
   	{
      		return 0;
   	}

	//delete from front of list
   	if (strcmp(delid, ptr -> id) == 0)
   	{
      		// check to see if only one record
      		if (this -> first == this -> last)
      		{
         		this -> first = NULL;
         		this -> last = NULL;
         		delete ptr;
      		}
      		else
      		{
         		this -> first = this -> first -> next;
         		this -> first -> prev = NULL;
         		delete ptr;
      		}
   	}

	//delete from back of list
   	else if (strcmp(delid, ptr -> id) == 0)
   	{
      		ptr = this -> last;
      		this -> last = this -> last -> prev;
      		this -> last -> next = NULL;
      		delete ptr;
   	}

	//delete from the middle
   	else
   	{
      		found = 0;
      		while (ptr)
      		{
			//move pointer if not matched
         		if (strcmp(delid, ptr -> id) < 0)
         		{
            			ptr = ptr -> next;
         		}
         		else if (strcmp(ptr -> id, delid) == 0)
         		{
            			ptr -> prev -> next = ptr -> next;
            			if (ptr -> next)
            			{
               				ptr -> next -> prev = ptr -> prev;
            			}
            			delete ptr;
				found = 1;
            			break;
         		}
         		else
         		{
            			return 0;
         		}
      		}
	}
   	return found;
}

//Prints the list
void list::PrintList(int order)
{
        rec *current;

        if (order == 0 && first != NULL)
        {
                current = first;
                while(current != NULL)
                {
                        cout << current -> id << " ";
			cout.flush();
                        cout << current -> firstname << " ";
                        cout.flush();
                        cout << current -> lastname << " ";
                        cout.flush();
                        for(int i = 0; i < 10; i++)
                        {
                                cout << current -> a[i] << " ";
                        }
			cout.flush();
			cout << current -> prev << " ";
                        cout.flush();
			cout << current << " ";
                        cout << current -> next << " " << endl;
                        current = current -> next;
                }
        }
        else if(last != NULL)
        {
                current = last;
                while (current != NULL)
                {
                        cout << current -> id << " ";
                        cout.flush();
                        cout << current -> firstname << " ";
                        cout.flush();
                        cout << current -> lastname << " ";
                        cout.flush();
                        for(int i = 0; i < 10; i++)
                        {
                                cout << current -> a[i] << " ";
                        }
                        cout.flush();
			cout << current -> prev << " ";
                        cout.flush();
                        cout << current << " ";
                        cout << current -> next << " " << endl;
                        current = current -> prev;
                }
        }
}

//Reads the data from the given two files
int list::ReadData(char* k_file, char* a_file )
{
	ifstream key_file;
	ifstream ans_file;
	char key_buf[100], ans_buf[100];
	rec key_rec_buf[100], ans_rec_buf[100], tempIDrec, tempANSrec;
	int i = 0, j = 0, k = 0, x = 0, y = 0, z = 0, temp_num;
	rec *fPtr, *lPtr, *tempPtr;

        //open the key file
        key_file.open(k_file, ios :: in);
        if (key_file.fail())
        {
		key_file.close();
                return 0;
        }

        //open the answers file
        ans_file.open(a_file, ios :: in);
        if (ans_file.fail())
        {
		key_file.close();
		ans_file.close();
                return 0;
        }

	//removes the old list
	fPtr = first;
	lPtr = last;
	while (fPtr != lPtr)
	{
		tempPtr = lPtr;
		lPtr = tempPtr -> prev;
		lPtr -> next = NULL;
		tempPtr -> prev = NULL;
		delete tempPtr;
	}
	delete fPtr;
	first = NULL;
	last = NULL;

	// read the key file and adds them into buffers
	while (!key_file.eof())
	{
		//gets record from key file and saves them into buffer
		key_file >> key_buf;
		tempIDrec.id = new char[strlen(key_buf) + 1];
		strcpy(tempIDrec.id, key_buf);
		key_file >> tempIDrec.firstname;
		key_file >> tempIDrec.lastname;
		key_rec_buf[i].id = tempIDrec.id;
		strcpy(key_rec_buf[i].firstname, tempIDrec.firstname);
                strcpy(key_rec_buf[i].lastname, tempIDrec.lastname);
		//cout << key_rec_buf[i].id << endl;
		//cout << key_rec_buf[i].firstname << " " << key_rec_buf[i].lastname << endl;
		i++;
	}

	// read the answers file and adds them into buffers
	while (!ans_file.eof())
	{
		//get record from answers file and saves them into buffer
		ans_file >> ans_buf;
		tempANSrec.id = new char[strlen(ans_buf) + 1];
		strcpy(tempANSrec.id, ans_buf);
		ans_rec_buf[j].id = tempANSrec.id;
                for (z = 0; z < 10; z++)
		{
			ans_file >> temp_num;
			ans_rec_buf[j].a[z] = temp_num;
			//cout << ans_rec_buf[j].a[z]; 			
		}
		//cout << endl;
		//cout << ans_rec_buf[j].id << endl;
                j++;
	}

	//Adds the correct buffers into the real list
	for (x = 0; x < i; x ++)
	{
		for(y = 0; y < j; y++)
		{
			//check the two buffers if there are matching IDs
        		if (strcmp(key_rec_buf[x].id, ans_rec_buf[y].id) == 0)
        		{
				//cout << key_rec_buf[x].id << " " << ans_rec_buf[y].id << endl;
                		// copy the answers to questions
                        	for (int k = 0; k < 10; k++)
                        	{
                        		key_rec_buf[x].a[k] = ans_rec_buf[y].a[k];
                        	}
				AddItem(key_rec_buf[x]);
			}
		}
	}
	key_file.close();
	ans_file.close();
	return 1;
}

int list::WriteData(char *k_file, char *a_file)
{
	ofstream key_file;
	ofstream ans_file;
	rec *rPtr;
	rPtr = first;
	int i;

	//opens the answers and key files
        key_file.open(k_file);
	if (key_file.fail())
	{
		return 0;
	}
	ans_file.open(a_file);
	if (ans_file.fail())
	{
		key_file.close();
		return 0;
	}
	while(rPtr)
	{
		//Copy into new key file
		key_file << rPtr -> id << " ";
		key_file << rPtr -> firstname << " ";
		key_file << rPtr -> lastname << " " << endl;

		//Copy into new answers file
                ans_file << rPtr -> id << " ";
                for (i = 0; i < 10; i++)
                {
                        ans_file << rPtr -> a[i] << " ";
                }
		ans_file << endl;

		//Move to next node on the list
		rPtr = rPtr -> next;
	}

	//Closes both files
	key_file.close();
	ans_file.close();
	return 1;
}

//Rec constructor
rec::rec(char* i, char* fn, char* ln, int* a)
{
	//set ID
	this -> id = new char[strlen(i) + 1];
	strcpy (this -> id, i);
	//set first and last names
	strcpy (this -> firstname, fn);
	strcpy (this -> lastname, ln);
	
	//set answers
	for (int i = 0; i < 10; i++)
	{
		this -> a[i] = a[i];
	}
	this -> prev = NULL;
	this -> next = NULL;
}

//Rec copy constructor
rec::rec(const rec& r)
{
	//Copy all info
	this -> id = new char[strlen(r.id) + 1];
	strcpy (this -> id, r.id);
	strcpy (this -> firstname, r.firstname);
	strcpy (this -> lastname, r.lastname);
	for (int i = 0; i < 10; i++)
	{
		this -> a[i] = r.a[i];
	}
}

//Set Data
void rec::SetData (char* id_in, char *fn, char* ln, int *ans_in)
{
	//set ID
	this -> id = new char[strlen(id_in) + 1];
	strcpy (this -> id, id_in);
 	this -> id[strlen(id_in) + 1] = NULL;
 	
	//set first and last names
 	strcpy (this -> firstname, fn);
 	strcpy (this -> lastname, ln);
 	
	//set answers
 	for (int i = 0; i < 10; ++i)
 	{
		this -> a[i] = ans_in[i];
	}
}

//Rec destructor
rec::~rec()
{
	if(this -> id)
	{
		delete[] this -> id;
	}
}

//List constructor
list::list ()
{
	this -> first = NULL;
	this -> last = NULL;
}

//Default rec constructor
rec::rec()
{
        //Clears id, first/last name and answers
	this -> id = NULL;
	for (int i = 0; i < 15; ++i)
	{
		this -> firstname[i] = NULL;
		this -> lastname[i] = NULL;
 	}
	for (int i = 0; i < 10; ++i)
	{
		this -> a[i] = -1;
	}
	this -> prev = NULL;
	this -> next = NULL;
}

//Rec operator
void rec::operator= (const rec& r)
{

	//Copys id, first/last name and answers
	this -> id = new char[strlen(r.id) + 1];
	strcpy (this -> id, r.id);
	strcpy (this -> firstname, r.firstname);
	strcpy (this -> lastname, r.lastname);
	for (int i = 0; i < 10; ++i)
	{
		this -> a[i] = r.a[i];
	}
}

//Rec print()
void rec::Print()
{
	cout << this -> id << " " << 
		this -> firstname << " " << 
		this -> lastname << " ";
	for (int i=0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	//prints addresses
	cout << this -> prev << " " << this << " " << this -> next << endl;
}

//List Operator
void list::operator= (list& list_in)
{
	rec temp_rec;
	rec *rPtr, *fPtr, *lPtr, *tempPtr;
	rPtr = list_in.first;

	//clear old list
	fPtr = first;
        lPtr = last;
        while (fPtr != lPtr)
        {
                tempPtr = lPtr;
                lPtr = tempPtr -> prev;
                lPtr -> next = NULL;
                tempPtr -> prev = NULL;
                delete tempPtr;
        }
        delete fPtr;
        first = NULL;
        last = NULL;

	//copy list
	while (rPtr)
	{
		temp_rec.SetData(rPtr -> id, rPtr -> firstname, rPtr -> lastname, rPtr -> a);
		AddItem(temp_rec);
		rPtr = rPtr -> next;
	}
	delete rPtr;
}
