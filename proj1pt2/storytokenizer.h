#ifndef STORY_TOKENIZER_H
#define STORY_TOKENIZER_H

#include "passagetokenizer.h"

class PassageToken{
private:
    string text; //holds line of the story
    string name;
public:
    PassageToken();
    void setName(string n) { name = n; }
    void setText(string t) { text = t; }
    string getName() const { return name; }
    string getText() const { return text; } 
    

};

class StoryTokenizer{
private:
    //assume theres always content to read, so set nextPass to true in constructors
    bool nextPass;
    string story;

public:
    StoryTokenizer() { nextPass = true; story = " "; } //makes use of passageTokenizer functions
    StoryTokenizer(string s); //set this story string to 'story'
    bool hasNextPassage() { return nextPass; }
    PassageToken nextPassage(); 
    
};


#endif
