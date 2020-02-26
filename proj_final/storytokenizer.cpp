#include "storytokenizer.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

StoryTokenizer::StoryTokenizer(string text, int num)
{   
    string end = "</tw-storydata";
    string delim1 = "<tw-passagedata";
    string delim2 = "</tw-passagedata>";

    story = text.substr(text.find(delim1), text.find(end) - text.find(delim1));
    pass_num = num;
 
    int first = story.find(delim1);
    int last = story.find(delim2);

    while(story != "") // Keeps going until it reaches the end of the passages
    {   
 
        first = story.find(delim1);
        last = story.find(delim2);
        int end_of_last = last + delim2.length();

        string token = story.substr(first, end_of_last);
        split.push_back(token);
        
        story = story.substr(end_of_last, story.size() - end_of_last);
  
        // Added because the last story string of escape.html is not empty, it's a lot of white space
        if (story.find(delim1) == std::string::npos)  
            story = "";
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

string PassageToken::getName()
{
    string delim1 = "name=\"";
    string delim2 = "\" tags";
    story = str.at(num); // Gets the current passage to tokenize

    if (num >= str.size())
    {
        return name; // Returns empty string there are no more passages

    } else
    {
        unsigned int first = story.find(delim1); //Position of delim1
        unsigned int last = story.find(delim2); // Position of delim2
        unsigned int end_of_first = first + delim1.length(); // Position of first letter of the name
        unsigned int end_of_last = last - end_of_first; // Length of the name

        name = story.substr(end_of_first, end_of_last);
    }

    return name;  
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
