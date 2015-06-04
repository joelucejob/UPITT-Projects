#include <iostream>
#include "list.h"
#include <string.h>  // <string>

    using namespace std;

int main (void)
{
   int choice, printorder;
   char idbuf[100];
   char fnamebuf[15];
   char lnamebuf[15];
   int  ansbuf [10];
   char key[100];
   char ans[100];
   rec r;
   list mylist;

  ///////////////////////////

   // Extra test stuff /////

   // - get this stuff working last

   // comment this section out until the first milestone is working

    // YOUR FINAL VERSION SUBMITTED MUST HAVE THIS SECTION WORKING

   //  Be sure this section executes when you turn it in

   //////////////////////////


    int tarr[10] = {4,4,3,3,2,2,1,1,0,0};

    rec  rec1;

    rec  rec2( (char*)"1992", (char*)"Hank", (char*)"Chigla", (int*)tarr);

    rec2.Print();

    cout << endl;

    cout << "------  Rec 1 2 3 -----------" << endl;

    rec1 = rec2;

    rec1.SetData((char*)"888a", (char*)"Jerry", (char*)"Malega", (int*)tarr);

    rec rec3(rec1);

    rec1.Print();

    cout << endl;

    rec2.Print();

    cout << endl;

    rec3.Print();

    cout << "------ Rec 3-----------" << endl;

    rec3.SetData((char*)"xxxx", (char*)"Mr", (char*)"Beepers", (int*)tarr);

    rec3.Print();



    cout << mylist.AddItem ( rec1 ) ;

    cout << mylist.AddItem ( rec2 ) ;

    cout << "---------- mylist ----------"<< endl;

    mylist.PrintList (0);


    list myotherlist;

    myotherlist = mylist;


    cout << myotherlist.DeleteItem((char*)"xxxx") ;

    rec rec4 ((char*)"16", (char*)"Larry", (char*)"Orlando", (int*)tarr);

    cout << mylist.AddItem( rec4) ;

    cout << "#######  mylist ########"
<< endl;


    mylist.PrintList(0);

    cout << "###### myotherlist ########"
<< endl;

    myotherlist.PrintList(0);


   //////////////////////////

   // End Extra test stuff //

   //////////////////////////


   do
   {
      cout << "Enter your choice\n1 Add, 2 Delete, 3 Print, 4 Read, 5 Write, 0 quit ";

      cin >> choice;

       switch ( choice )
 {
          case 1:  //AddItem
             cout << "\nEnter ID ";
             cin >> idbuf;

             cout << "\nFirst Name ";
             cin >> fnamebuf;

             cout << "\nLast Name ";
             cin >> lnamebuf;

             cout << "\nAnswers ";
             for ( int i = 0; i < 10; ++i)
             {
                cin >> ansbuf[i];
             }

             r.SetData ( idbuf, fnamebuf, lnamebuf, ansbuf );

             if ( mylist.AddItem ( r ) )
             {
                cout << "\nSuccess!\n";
             }
             else
             {
                cout << "\nItem failed to be added\n";
             }
             break;

          case 2:  //Delete
             cout << "\nEnter id :";
             cin >> idbuf;
             if ( mylist.DeleteItem ( idbuf ) )
             {
                cout << "\nDelete OK\n";
             }
             break;

          case 3: // Print
            cout << "Enter order 0 - Ascending, 1 - Descending\n";
            cin >> printorder;
            mylist.PrintList (printorder);
            break;

          case 4: // ReadData
            cout << "Enter key file name:\n";
            cin >> key;
            cout << "Enter answer file name:\n";
            cin >> ans;
            if ( mylist.ReadData( key, ans ) )
            {
               cout << "\nReadData Success\n";
            }
            else
            {
               cout << "\nReadData Failed\n";
            }
            break;
          case 5: // WriteData
            cout << "Enter key file name:\n";
            cin >> key;
            cout << "Enter answer file name:\n";
            cin >> ans;
            if ( mylist.WriteData( key, ans ) )
            {
               cout << "\nWriteData Success\n";
            }
            else
            {
               cout << "\nWriteData Failed\n";
            }
            break;
          case 0:  // quit

          default: // bad  choice
             break;
       } // end switch
   }
   while ( choice );// end do while

   return 0;
}  // end main
