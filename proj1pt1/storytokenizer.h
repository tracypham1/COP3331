#ifndef STORY_TOKENIZER_H
#define STORY_TOKENIZER_H

#include "passagetokenizer.h"

class StoryTokenizer{
private:
    bool nextPass;
    string anime;

public:
    StoryTokenizer(); //makes use of passageTokenizer functions
    StoryTokenizer(string s) { anime = s; } //set this story string to 'anime'
    bool hasNextPassage() { return nextPass; }
    PassageToken nextPassage(); 
    
};


#endif

//destructor?