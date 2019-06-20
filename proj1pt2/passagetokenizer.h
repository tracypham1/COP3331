#ifndef PASSAGE_TOKENIZER_H
#define PASSAGE_TOKENIZER_H

#include <string>
#include <iostream>
using namespace std;

enum toktype_t { LINK, BLOCK, TEXT, GOTO, SET, IF, ELSEIF, ELSE };

class PassageToken{
private:
    string name;
    string text;
public:
    PassageToken(); //intitalize name and text to " "
    string getName() const { return name; } //when used?
    string getText() const { return text; } 
    void setName(string n) { name = n; }
    void setText(string t) { text = t; }

};

//writing PartToken stuff in here for now
//will these text members be confused?
class PartToken{
private:
    toktype_t type;
    string text; //hold text to the part 
public:
    PartToken(string = " ", toktype_t = TEXT);
    toktype_t getType() const { return type; }
    string getText() const { return text; } //gets text of the one part

};

//gets passage from above and tokenizes the text using PartToken
class PassageTokenizer{
private:
    string text; //holds the entire passage line
    bool nextPt;
public:
    PassageTokenizer(string t = " "); //holds the passage part of story line
    PartToken nextPart(string); //gets the PartToken data part from passage: type and text and sets it, one at a time
    //remember to redefine text if nextPt = true

    string getText() const;
    bool hasNextPart() const { return nextPt; }
};


#endif