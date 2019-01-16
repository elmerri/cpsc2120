#include <iostream>
#include <cstdlib>

using namespace std;

int N;
bool board[100][100] = {0};

bool can_place(int col, int row)
{
  int i, j;

  for(i=row; i>=0; i--)
  {
    if(board[i][col])
      return false;
  }
  for(i=row, j=col; i>=0 && j>=0; i--, j--)
  {
    if(i>=0 && i < N)
      if(board[i][j])
        return false;
  }
  for(i=row, j=col;j<N && j>=0; i--, j++)
  {
    if(i>=0 && i < N)
      if(board[i][j])
        return false;
  }

  return true;
}

void print()
{
  for(int i=0; i<N; i++)
  {
    for(int j=0; j<N; j++)
      cout << board[i][j] << " ";
    cout << endl;
  }
}

int check_row(int row)
{
  int total = 0;

  //base case
  if(row == N)
  {
    total += 1;
    return total;
  }

  for(int i=0; i<N; i++)
  {
    if(can_place(i, row))
    {
      board[row][i] = true;
      total += check_row(row+1);
      board[row][i] = false;
    }
  }

  return total;
}

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    cout << "Invalid input!" << endl;
    return 1;
  }

  N = atoi(argv[1]);

  int total = 0;

  total += check_row(0);

  cout << "Number of solutions: " << total << endl;

  return 0;
}
