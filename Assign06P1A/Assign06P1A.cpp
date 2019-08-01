// NAME: Cody Wright
// DATE: 3/12/2019
// LAST MODIFIED: 3/12/2019
// FILE: Assign06P1A.cpp
// ABSTRACT: A practice program for recursion implementing a function
//           that finds the lowest index of the smallest negative value

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int LowIndexMinNeg(const int a[], int size);
void SeedRand();
int BoundedRandomInt(int lowerBound, int upperBound);
void ShowArray(const int a[], int size);
void DebugShowCase(int whichCase, int totalCasesToDo,
                   const int caseValues[], int caseSize);

int main()
{
   int testCasesToDo = 900000,
       testCasesDone = 0,
       loSize = 0,
       hiSize = 20,
       loValue = -9,
       hiValue = 9;
   int numInts,
       used,
       intCount,
       limnO2B,
       limn,
       newInt;
   int *intArr = 0;

   // SeedRand(); // disabled for reproducible result

   do
   {
      ++testCasesDone;
      limnO2B = -999;
      numInts = BoundedRandomInt(loSize, hiSize);
      if (numInts > 0) intArr = new int [numInts];
      used = 0;
      for (intCount = 0; intCount < numInts; ++intCount)
      {
         newInt = BoundedRandomInt(loValue, hiValue);
         if (newInt < 0)
            if (limnO2B == -999 || newInt < intArr[limnO2B])
               limnO2B = used;
         intArr[used++] = newInt;
      }

      limn = LowIndexMinNeg(intArr, used);

      if (limn != limnO2B)
      {
         cout << "Incorrect limn ..." << endl;
         cout << "test_case: " << testCasesDone << endl;
         cout << "array: ";
         ShowArray(intArr, used);
         cout << "limn expected: " << limnO2B << endl;
         cout << "limn returned: " << limn << endl;
         exit(EXIT_FAILURE);
      }

      if (testCasesDone < 10)
      {
         DebugShowCase(testCasesDone, testCasesToDo, intArr, used);
         cout << "limn_returned--> " << limn
              << " == " << limnO2B << " <--limn_ought2b" << endl;
      }
      else // uncomment next line to show array involved in every case
//          DebugShowCase(testCasesDone, testCasesToDo, intArr, used);
      if (testCasesDone % 30000 == 0)
      {
         cout << "================================" << endl;
         clog << "testing case " << testCasesDone
              << " of " << testCasesToDo << endl;
         clog << "================================" << endl;
         cout << "array: ";
         ShowArray(intArr, used);
         cout << "limn returned: " << limn << "\tlimn ought2b: " << limnO2B << endl;
      }
      delete [] intArr;
      intArr = 0;
   }
   while (testCasesDone < testCasesToDo);
   cout << "================================" << endl;
   cout << "test program terminated normally" << endl;
   cout << "================================" << endl;

   return EXIT_SUCCESS;
}

/////////////////////////////////////////////////////////////////////
// Function to seed the random number generator
// PRE:  none
// POST: The random number generator has been seeded.
/////////////////////////////////////////////////////////////////////
void SeedRand()
{
   srand( (unsigned) time(NULL) );
}

/////////////////////////////////////////////////////////////////////
// Function to generate a random integer between
// lowerBound and upperBound (inclusive)
// PRE:  lowerBound is a positive integer.
//       upperBound is a positive integer.
//       upperBound is larger than lowerBound
//       The random number generator has been seeded.
// POST: A random integer between lowerBound and upperBound
//       has been returned.
/////////////////////////////////////////////////////////////////////
int BoundedRandomInt(int lowerBound, int upperBound)
{
   return ( rand() % (upperBound - lowerBound + 1) ) + lowerBound;
}

void ShowArray(const int a[], int size)
{
   for (int i = 0; i < size; ++i)
      cout << a[i] << "  ";
   cout << endl;
}

void DebugShowCase(int whichCase, int totalCasesToDo,
                   const int caseValues[], int caseSize)
{
   cout << "test case " << whichCase
        << " of " << totalCasesToDo << endl;
   cout << "array: ";
   ShowArray(caseValues, caseSize);
}

/////////////////////////////////////////////////////////////////////
// Function searches for the "smallest negative value" in a given
// (unsorted) array of integers a of size n
// PRE:  n is a non-negative integer.
// POST: Lowest index of the smallest negative value is returned
//       if found, else value -999 is returned 
/////////////////////////////////////////////////////////////////////
int LowIndexMinNeg(const int a[], int n)
{  // concise variable names were specified in assignment specifications
   if (n < 0)
   {
      cout<<"Invalid array size"<<endl;
      return -999;
   }
   if (n == 0)
      return -999;
   if (n == 1 && a[0] >= 0)
      return -999;
   if (n == 1) // a[0] < 0 implicit
      return 0;
   int minIndexTheRest = LowIndexMinNeg(a, n - 1);
   if (a[n - 1] < 0 && a[n - 1] < a[minIndexTheRest])
      return n - 1;
   else
      return minIndexTheRest;
}
