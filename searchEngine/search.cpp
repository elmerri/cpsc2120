#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include "search.h"

using namespace std;

//Hashes the element to a particular point in the table
int hashh(string s, int table_size)
{
  //Hashes string to the table for easy access later
  unsigned int i, h = 0;
  for (i=0; i<s.length(); i++)
    h = (h * 2917 + (unsigned int)s[i]) % table_size;
  return h;
}

Page **allocate_table_p(int psize)
{
  int i;
  
  cout << "Allocating page table..." << endl;

  //Creates a table of Pages
  Page **table = new Page *[psize];
  for (i=0; i<psize; i++)
  {
    table[i] = NULL;
  }

  return table;
}

Word **allocate_table_k(int ksize)
{
  int i, j;

  cout << "Allocating word table..." << endl;
  
  //Creates a table of Words
  Word **table = new Word *[ksize];
  for (i = 0; i < ksize; i++)
  {
    table[i] = NULL;
  }

  return table;
}

void read_input(void)
{
  string w;
  int pages = 0, words = 0;
  
  ifstream fin;

  //Opens file to collect input
  fin.open("webpages.txt");
  while (fin >> w)
  {
    if(w == "NEWPAGE")
    {
      pages++;
    }
    else if((w[0] == 'h') && (w[1] == 't') && (w[2] == 't') && (w[3] == 'p'))
    {
      //Skips over extra URLs
    }
    else
    {
      words++;
    }
  }

  //Set global variables
  psize = pages;
  ksize = words;

  //Create tables based on the number of main links and keywords
  search_table = allocate_table_p(psize);
  word_table = allocate_table_k(ksize);
  //Print out size of tables
  cout << "Page table size = " << pages << endl;
  cout << "Keyword table size = " << words << endl;

  //Close file
  fin.close();

}

void insert_elements(void)
{
  ifstream fin;
  int h, hw;
  string word, mainpage, w;

  fin.open("webpages.txt");

  cout << "Inserting elements into their respective tables..." << endl;

  while(fin >> w)
  {
    //If the string denotes a new webpage, set up a new Page at the hash of the URL
    if(w == "NEWPAGE")
    {
      fin >> mainpage;
      h = hashh(mainpage, psize);
      search_table[h] = new Page(mainpage, NULL, search_table[h]);
    }
    else if((w[0] == 'h') && (w[1] == 't') && (w[2] == 't') && (w[3] == 'p'))
    {
      //Ignores extra links
    }
    else
    {
      word = w;
      //Inserts the keywords in a linked list for that page
      search_table[h]->keyword = new Key(word, search_table[h]->keyword);

      hw = hashh(word, ksize);

      //Hashing words and their corresponding links into the word table
      if(word_table[hw] == NULL)
      {
        word_table[hw] = new Word(mainpage, NULL);
      }
      else
      {
        word_table[hw] = new Word(mainpage, word_table[hw]);
      }
    }
  }

  fin.close();
}

void find(string word)
{
  //Hash word to find location in table
  int h = hashh(word, ksize);

  cout << endl << "Searching!" << endl << endl;

  cout << "Webpages found: " << endl;

  //If it's not null, print out all links associated with the search query
  while(word_table[h] != NULL)
  {
    cout << word_table[h]->w << endl;
    word_table[h] = word_table[h]->next;
  }
}

int main()
{
  read_input();
  insert_elements();

  string input;

  cout << "Please enter your search term: " << endl;
  cin >> input;

  find(input);

  return 0;
}

