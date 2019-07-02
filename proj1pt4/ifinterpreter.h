#ifndef __IFINTERPRETER_H
#define __IFINTERPRETER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "storytokenizer.h"
#include "formatting.h"
using namespace std;

class IFInterpreter : public Formatting
{
    private:
        vector<PassageToken*> passage;
        unordered_map<string, string> pass;
    public:
        IFInterpreter(string filename);
        void print();
        void play();
};

#endif