#ifndef __STORYTOKENIZER_H
#define __STORYTOKENIZER_H

#include <cstring>
#include <string>
#include <vector>
#include "passagetokenizer.h"
using namespace std;

class PassageToken
{
    private:
        string name;
        string passage;
        string story;
        vector<string> str;
        int num;
    public:
        PassageToken(vector<string>, int);
        const char* getName();
        string getText();
};

class StoryTokenizer
{
    private:
        string story;
        string token;
        vector<string> split;
        int pass_num;
        bool next_pass;
    public:
        StoryTokenizer(string, int = 0);
        bool hasNextPassage();
        PassageToken nextPassage();
};

#endif