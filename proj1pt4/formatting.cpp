#include "formatting.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

Formatting::Formatting(){
    variables.insert(make_pair("hello", "world"));
}

void Formatting::text(string text, int print){
    cout << '"' << text << '"' << endl;
}