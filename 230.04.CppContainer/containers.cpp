/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 04: Contaiers
 * 3. Assignment Description:
 *      Work with a list and a vector
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/


#include "testContainers.h"
#include <string>
#include <list>
using namespace std;

list<string> arrayToList(string a[], int num)
{
   // create list
   list<string> l;
   for (int i = 0; i < num; ++i)
   {
      // add the element to the list
      l.push_back(a[i]);
   }
   return l;
}

/*****************************
 * ARRAY TO LIST BACKWARDS
 *****************************/
list<string> arrayToListBackwards(string a[], int num)
{
   // create list
   list<string> l;
   // iterate backwards
   for (int i = num - 1; i >= 0; --i)
   {
      // add the element to the list
      l.push_back(a[i]);
   }
   return l;
}

/*****************************
 * LIST TO VECTOR
 *****************************/
vector<string> listToVector(const list<string> & l)
{
   // create vector
   vector<string> vec;
   // create an iterator for the list
   auto iter = l.begin();
   for (int i = 0; i < l.size(); ++i)
   {
      // add the element to the vector
      vec.push_back(*iter);
      ++iter;
   }
   return vec;
}

/*****************************
 * LIST TO VECTOR BACKWARDS
 *****************************/
vector<string> listToVectorBackwards(const list<string>& l)
{
   // create vector
   vector<string> vec;
   // create a reverse iterator for the list
   auto revIter = l.rbegin();
   // iterate backwards
   for (int i = 0; i < l.size(); ++i)
   {
      // add the element to the vector
      vec.push_back(*revIter);
      ++revIter;
   }
   return vec;
}

/*****************************
 * FIND ELEMENT IN VECTOR
 *****************************/
bool findElementInVector(const vector<string> & vec, const string& element)
{
   for (const auto& item : vec)
   {
      if (item == element)
         return true;
   }
   return false;
}

/*****************************
 * MAIN
 *****************************/
int main()
{
   TestCollection().run();
   return 0;
}
