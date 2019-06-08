#include <iostream>
#include <vector>
using namespace std;

#include "mystring.h"

int main()
{
  //Test basic constructors and printing
  MyString test1, test2("The quick brown fox jumps over the lazy dog ");

  cout << "String 1:  \"" << test1 << '"' << endl;
  cout << "String 2:  \"" << test2 << '"' << endl;

  //Test [] operator
  cout << "Char #41:  " << test2[40] << endl;
  test2[40] = 'h';
  cout << "Changing char #41 to 'h':  " << test2 << endl;

  //Test copy constructor and assignment
  MyString test3 = test2;
  test2[40] = 'd';
  cout << "Copy:  " << test3 << endl;
  test1 = test3 = test2;
  cout << "Changing char #41 back:  " << test3 << endl;

  //Test + and move assignment
  vector<MyString> vec;
  vec.reserve(10);
  vec.push_back(test1); //Calls copy constructor
  for (int i = 1; i < test1.size(); i++)
    if (test1[i - 1] == ' ')
      vec.emplace_back(&test1[i]);
  
  MyString test5;
  cout << "Calling move assignment * " << vec.size() << ':' << endl;
  for (int i = 0; i < vec.size(); i++)
    test5 = test5 + vec[i];
  cout << test5 << endl;

  return 0;
}