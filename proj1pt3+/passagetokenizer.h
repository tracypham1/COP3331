#ifndef PASSAGE_TOKENIZER_H
#define PASSAGE_TOKENIZER_H

#include <string>
#include <iostream>
using namespace std;

enum toktype_t { LINK, BLOCK, TEXT, GOTO, SET, IF, ELSEIF, ELSE };

class PartToken{
private:
    string text; //holds command of the body 
    toktype_t type;
public:
    PartToken(string = " ", toktype_t = TEXT);
    void setType(toktype_t t) { type = t; }
    void setText(string t) { text = t; }
    toktype_t getType() const { return type; }
    string getText() const { return text; }

};

class PassageTokenizer{
private:
    string text; //holds the body part of a line
    bool nextPt;
public:
    PassageTokenizer(string t = " ");
    bool hasNextPart() const { return nextPt; }
    PartToken nextPart();
};


#endif