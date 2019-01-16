#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

/******************************************************
* This program uses the "candy.txt" file to           *
* calculate 3 different optimal solutions for         *
* candy bags based on the weight of the candy,        *
* and on its "yumminess" quality.                     *
*                                                     *
* Written for Dr. Brian Dean at Clemson University.   *
******************************************************/

const int N = 16;
const int T = 1000;

int weight[N];
int value[N];
bool used[N] = {0};
int bestsofar = 0;
int best = 0;
int bag1 = 0;
int bag2 = 0;
int bag3 = 0;
int extrabag = 0;

//Reads in the candy.txt input file
void read_file()
{
  //Open file
  ifstream fin("candy.txt");
  int w, v;
  int i = 0;

  //Read in values
  while(fin >> w >> v)
  {
    weight[i] = w;
    value[i] = v;
    i++;
  }

  //Close file
  fin.close();
}

//Sorts the arrays by lowest to highest tastiness
void sort_by_values()
{
  for (int c = 0 ; c < (N - 1); c++)
  {
    for (int d = 0 ; d < N - c - 1; d++)
    {
      if (value[d] > value[d+1])
      {
        swap(value[d], value[d+1]);
        swap(weight[d], weight[d+1]);
      }
    }
  }
}

//Resets the array that says if a candy has been used or not
void reset_used()
{
  for(int i=0; i<N; i++)
  {
    used[i] = false;
  }
}

//Greedy function
int greedy()
{
  int greed = 0;
  int bag1 = 0;
  int bag2 = 0;
  int bag3 = 0;

  for(int i=N-1; i>=0; i--)
  {
    if(bag1+weight[i] < 2000 && used[i] != true)
    {
      bag1 += weight[i];
      used[i] = true;
      greed += value[i];
    }
  }
  for(int i=N-1; i>=0; i--)
  {
    if(bag2+weight[i] < 2000 && used[i] != true)
    {
      bag2 += weight[i];
      used[i] = true;
      greed += value[i];
    }
  }
  for(int i=N-1; i>=0; i--)
  {
    if(bag3+weight[i] < 2000 && used[i] != true)
    {
      bag3 += weight[i];
      used[i] = true;
      greed += value[i];
    }
  }

  return greed;
}

//Randomizes the candies' order
void randomize_arrays()
{
  for (int i=0; i<N; i++)
  {
    int temp = rand() % (i+1);
    swap(weight[i], weight[temp]);
    swap(value[i], value[temp]);
  }
}

//More refined search
int refinement()
{
  int best = 0;

  //  Makes 1000 attempts at finding an
  //  optimal solution
  for(int i=0; i<T; i++)
  {
    //Randomize the order of the candies
    randomize_arrays();
    //  Greedily place all the candies in an
    //  attempt to find a better solution
    int temp = greedy();
    //  Reset the used values for the next
    //  attempt at a greedy solution
    reset_used();
    //  If the trial is better than the previous
    //  best solution, make that the new best solution
    if(temp > best)
      best = temp;
  }

  return best;
}

int exhaustive(int test)
{
  //Base case
  if(test == N)
  {
    if(best > bestsofar)
      bestsofar = best;
    return bestsofar;
  }

  /*********************************************
  *  Recursively test all possible placements  *
  *  of candy in the bags to find the most     *
  *  optimal solution                          *
  *********************************************/

  if(bag1+weight[test] <= 2000)
  {
    bag1 += weight[test];
    used[test] = true;
    best += value[test];
    exhaustive(test+1);
    best -= value[test];
    bag1 -= weight[test];
    used[test] = false;
  }
  if(bag2+weight[test] <= 2000)
  {
    bag2 += weight[test];
    used[test] = true;
    best += value[test];
    exhaustive(test+1);
    best -= value[test];
    bag2 -= weight[test];
    used[test] = false;
  }
  if(bag3+weight[test] <= 2000)
  {
    bag3 += weight[test];
    used[test] = true;
    best += value[test];
    exhaustive(test+1);
    best -= value[test];
    bag3 -= weight[test];
    used[test] = false;
  }
  if(!used[test])
  {
    extrabag += weight[test];
    used[test] = true;
    exhaustive(test+1);
    used[test] = false;
    extrabag-= weight[test];
  }

  //Return the solution found in this test case
  return bestsofar;
}

int main()
{
  read_file();
  sort_by_values();
  cout << "Greedy:     " << greedy() << endl;
  cout << "Refinement: " << refinement() << endl;
  reset_used();
  cout << "Exhaustive: " << exhaustive(0) << endl;

  return 0;
}
