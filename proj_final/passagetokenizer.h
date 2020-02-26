#ifndef __PASSAGETOKENIZER_H
#define __PASSAGETOKENIZER_H

#include <string>
#include <vector>
using namespace std;

enum token_t {LINK, GOTO, SET, IF, ELSEIF, ELSE, BLOCK, TEXT};

class PartToken
{
    private:
        vector<string> prts;
        int num;
    public:
        PartToken(vector<string>, int);
        string getText();
        token_t getType();

};

class PassageTokenizer
{
    private:
        string passage;
        vector<string> parts;
        bool next_part;
        int part_num;
    public:
        PassageTokenizer(string, int = 0);
        bool hasNextPart();
        PartToken nextPart();

};

#endif