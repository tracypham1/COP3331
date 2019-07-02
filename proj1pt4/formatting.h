#ifndef __FORMATTING_H
#define __FORMATTING_H

#include <string>
#include <vector>
#include <unordered_map>
#include "storytokenizer.h"
using namespace std;

class Formatting
{
    private:
        unordered_map<string, string> variables;
    public:
        Formatting();
        //void link(string text, int print); 
        //void link(string);
        //void goTo(string text, int print);
        //void goTo(string text);
        //void set(string text, int print);
        //void set(string text);
        //void iF(string text, int print);
        //void iF(string text);
        //void elseIF(string text, int print);
        //void elseIF(string text);
        //void Else(int print);
        //void Else();
        void text(string text, int print);
        //void text(string text); 
        //void block(string text, int print);
        //void block(string text);
};

#endif