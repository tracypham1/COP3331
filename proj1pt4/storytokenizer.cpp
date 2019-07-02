#include "storytokenizer.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;

StoryTokenizer::StoryTokenizer(string text, int num)
{
    story = text;
    pass_num = num;
    
    istringstream iss(story);
    string delim1 = "<tw-passagedata";

    getline(iss, token); // Gets each line of text stopping when it reaches endl
    while(iss && token != "</tw-storydata>") // Keeps going until it reaches the end of the passages
    {   
        unsigned int d1 = token.find(delim1);

        if (d1 == 0) // If the line of text starts with delim1 it is a passage
            split.push_back(token); // Add the passage to the string vector

        getline(iss, token); // Gets the next line of text
    }
}

bool StoryTokenizer::hasNextPassage()
{
    // If pass_num is greater than the size of the vector, there are no more passages
    if (pass_num < split.size()) 
    {
        next_pass = true;
        pass_num++;

    } else
        next_pass = false;

    return next_pass;
}

PassageToken StoryTokenizer::nextPassage()
{
    PassageToken passage(split, pass_num - 1);

    return passage;
}

PassageToken::PassageToken(vector<string> s, int n)
{
    str = s; // Copies the vector from StoryTokenizer
    num = n; // Copies the current passage number 
}

const char* PassageToken::getName()
{
    string delim1 = "name=\"";
    string delim2 = "\" tags";
    story = str.at(num); // Gets the current passage to tokenize

    if (num >= str.size())
    {
        return name.c_str(); // Returns empty string there are no more passages

    } else
    {
        unsigned int first = story.find(delim1); //Position of delim1
        unsigned int last = story.find(delim2); // Position of delim2
        unsigned int end_of_first = first + delim1.length(); // Position of first letter of the name
        unsigned int end_of_last = last - end_of_first; // Length of the name

        name = story.substr(end_of_first, end_of_last);
    }

    return name.c_str();  
}

string PassageToken::getText()
{
    char delim1 = '>';
    string delim2 = "</tw-passagedata>";
    story = str.at(num); // Test

    if (num >= str.size())
        {
            return passage; // Returns empty string there are no more passages
            
        } else
        {
            unsigned int first = story.find(delim1);
            unsigned int last = story.find(delim2);
            unsigned int end_of_first = first + 1; // Plus 1 because the length of char is 1
            unsigned int end_of_last = last - end_of_first;

            passage = story.substr(end_of_first, end_of_last);
        }

    return passage;
}
