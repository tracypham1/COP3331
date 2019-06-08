#ifndef __MYSTRING_H
#define __MYSTRING_H

#include <iostream>
using namespace std;

class MyString
{
  friend ostream& operator<<(ostream&, const MyString&);
private:
  char* str;
  int len;
public:
  MyString();
  MyString(const char*);
  
  MyString(const MyString&);
  MyString(MyString&&);
  const MyString& operator=(const MyString&);
  const MyString& operator=(MyString&&);
  ~MyString();

  int size() const { return len; }
  char& operator[](int);
  MyString operator+(const MyString&) const;
};

ostream& operator<<(ostream&, const MyString&);

#endif