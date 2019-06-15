#ifndef STORY_TOKENIZER_H
#define STORY_TOKENIZER_H

#include "passagetokenizer.h"

class StoryTokenizer{
private:
    //assume theres always content to read, so set nextPass to true in constructors
    bool nextPass;
    string anime;

public:
    StoryTokenizer() { nextPass = true; } //makes use of passageTokenizer functions
    StoryTokenizer(string s); //set this story string to 'anime'
    bool hasNextPassage() { return nextPass; }
    PassageToken nextPassage(); 
    
};


#endif

//destructor?