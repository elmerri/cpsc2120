#ifndef SEARCH_H
#define SEARCH_H
#include <string>

using namespace std;

struct Link
{
  string l;
  Link *next;

  Link(string l_, Link *n) { l = l_; next = n; }
  Link() { l = ""; next = NULL; }
};

struct Key
{
  string k;
  Key *next;

  Key(string k_, Key *n) { k = k_; next = n; }
  Key() { k = ""; next = NULL; }
};

struct Page 
{
  string mainpage;
  Key *keyword;
  double weight;
  double new_weight;

  Page( string p, Key *k, Page *n ) { mainpage = p; keyword = k; }
  Page() { mainpage = ""; keyword = NULL; }
};

struct Word
{
  string w;
  Word *next;

  Word(string word, Word *n) { w = word; next = n; }
  Word() { w = ""; next = NULL; }
};

Page **search_table;
Word **word_table;
int psize;
int ksize;

#endif
