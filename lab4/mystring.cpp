//class that stores a (null-terminated) char*, length, and implements all of the member functions in header file
#include "mystring.h"
#include <string>
#include <cstring>

//Default constructor: empty string
MyString::MyString(){
    str = " ";
    cout << "Default constructor:" << str << len << endl;
}

//const char* constructor:  initializes data members appropriately
MyString::MyString(const char* s){ 
    str = *s;
        cout << "string constructor:" << str << len << endl;

}

//Copy constructor:  prints "Copy constructor" and endl in addition to making a copy
MyString::MyString(const MyString& copy){
    cout << "Copy constructor" << endl;
    len = copy.len;
    for(int i = 0; i < len; i++)
        str[i] = copy.str[i];
}

//Move constructor:  prints "Move constructor" and endl in addition to moving data
MyString::MyString(MyString&& move){
    cout << "Move constructor" << endl;
    if(this != &move){
        delete str;
        str = move.str;
        move.str = nullptr;
    }
    len = move.len;
}

//Move assignment operator:  prints "Move assignment" and endl in addition to moving data
//what is this?
const MyString& MyString::operator=(MyString&& move){
    if(this != &move){
        delete str;
        str = move.str;
        move.str = nullptr;
    }
    len = move.len;

    return *this;
}

//Copy assignment operator:  prints "Copy assignment" and endl in addition to making a copy
const MyString& MyString::operator=(const MyString& rhs){
    cout << "Copy assignment" << endl;
    len = rhs.len;
    str = rhs.str;
    
    return *this;
}


//Destructor
MyString::~MyString(){
    delete[] str;
}

//Array index overload (ex: str[2]) should be able to read or write the character in this position.  Don't test for out-of-bounds indices.
char& MyString::operator[](int i){
    return str[i];
}

//Concatenation (+) operator:  returns the concatenation of this string with the other.  Does not modify either object.
MyString MyString::operator+(const MyString& rhs) const{
    MyString temp;
    
    temp.len = len + rhs.len;
    temp.str = strcat(str, rhs.str); //cant concat str + str

    return temp;
}

//Print function that works with cout
ostream& operator<<(ostream& out, const MyString& rhs){
    //called cout << Mystring object;
    out << rhs.str;
    return out;
}

https://learn.zybooks.com/zybook/USFCOP3331HendrixSummer2019/chapter/19/section/5

https://learn.zybooks.com/zybook/USFCOP3331HendrixSummer2019/chapter/19/section/8

https://learn.zybooks.com/zybook/USFCOP3331HendrixSummer2019/content-explorer?searchTerm=char*file:///C:/Users/17277/Downloads/L5-MoreClasses.long.pdf






    


