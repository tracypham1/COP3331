#ifndef STORY_TOKENIZER_H
#define STORY_TOKENIZER_H

#include "passagetokenizer.h"

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
