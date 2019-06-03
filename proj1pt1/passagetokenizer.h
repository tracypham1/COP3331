#ifndef PASSAGE_TOKENIZER_H
#define PASSAGE_TOKENIZER_H

#include <string>
#include <iostream>
using namespace std;

class PassageToken{
private:
    string name;
    string text;
public:
    PassageToken(); //intitalize name and text to " "
    string getName() const { return name; }
    string getText() const { return text; }
    void setName(string n) { name = n; }
    void setText(string t) { text = t; }

};

#endif