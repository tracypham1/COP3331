//class that stores a (null-terminated) char*, length, and implements all of the member functions in header file
#include "mystring.h"
#include <string>
#include <cstring>

//Default constructor: empty string
MyString::MyString(){
    str = new char[2]; 
    str[0] = '\0'; 
    len = strlen(str);
}

//const char* constructor:  initializes data members appropriately
MyString::MyString(const char* s){ 
    //len = strlen(s);
    //using the string library was not prohibited, but just in cases
    //proof of concept for finding length of a char* pointer, cstring
    len = 0;
    for(int i = 0; s[i] != '\0'; i++)
        len++;

    str = new char[len+1];
    int i;
    for(i = 0; i < len; i++)
        str[i] = s[i];
    str[i] = '\0';
}

//Copy constructor:  prints "Copy constructor" and endl in addition to making a copy
MyString::MyString(const MyString& copy){
    cout << "Copy constructor" << endl;
    len = copy.len;
    str = new char[len+1];

    //the copy constructor does not call the copy assignment
    int i;
    for(i = 0; i < len; i++)
        str[i] = copy.str[i];
    str[i] = '\0';
}

//Copy assignment operator:  prints "Copy assignment" and endl in addition to making a copy
//you can't call the = operator overload bc the object has not been created yet
const MyString& MyString::operator=(const MyString& rhs){
    cout << "Copy assignment" << endl;
    len = rhs.len;
    delete[] str;
    str = new char[len+1];
    
    int i;
    for(i = 0; i < rhs.len; i++)
        str[i] = rhs.str[i];
    str[i] = '\0';
    
    return *this;
}

//Concatenation (+) operator:  returns the concatenation of this string with the other.  Does not modify either object.
MyString MyString::operator+(const MyString& rhs) const{
    MyString temp;

    temp.len = len + rhs.len;
    
    temp.str = new char[temp.len];
    for(int i = 0; i < len; i++)
        temp.str[i] = str[i];

    for(int j = 0; j < rhs.len; j++)
        temp.str[len + j] = rhs.str[j];

    temp.str[len+rhs.len] = '\0';
    return temp; 
}

//Move constructor:  prints "Move constructor" and endl in addition to moving data
MyString::MyString(MyString&& move){
    cout << "Move constructor" << endl;
    if(this != &move){
        len = move.len;
        delete[] str;
        str = new char[len+1];
        str = move.str;
        move.str = nullptr;
    }
}

//Move assignment operator:  prints "Move assignment" and endl in addition to moving data
const MyString& MyString::operator=(MyString&& rhs){
    cout << "Move assignment" << endl;
    len = rhs.len;

    delete[] str;
    str = new char[len];
    int i;
    for(i = 0; i < len; i++)
        str[i] = rhs.str[i];
    str[i] = '\0';
  
    rhs.str = nullptr;
    return *this;
}

//Destructor
MyString::~MyString(){
    delete[] str;
}

//Array index overload (ex: str[2]) should be able to read or write the character in this position.  Don't test for out-of-bounds indices.
//just char is for reading char& is for writing as well 
char& MyString::operator[](int i){
    return str[i];
}

//Print function that works with cout
ostream& operator<<(ostream& out, const MyString& rhs){
    return out << rhs.str;
}







    


