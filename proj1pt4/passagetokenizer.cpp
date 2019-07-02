#include "passagetokenizer.h"
#include <iostream>
using namespace std;

PassageTokenizer::PassageTokenizer(string pass, int num)
{   
    passage = pass; 
    part_num = num;
    
    int first, last, end_of_last;
    string delim1 = "(";
    string delim2 = ")";
    string delim3 = "[[";
    string delim4 = "]]";
    string delim5 = "[";
    string delim6 = "]";
    string temp;

    // While loop for initializing the string vector parts
    // Terminates when the passage string has been completely tokenized of parts and is now empty
    while(passage != "")
    {   
        if (passage.find(delim1) == 0) // If statement to find commands
        {
            first = passage.find(delim1);
            last = passage.find(delim2);
            end_of_last = last + 1;

            // Gets the part as a substring then adds it to the vector
            temp = passage.substr(first, end_of_last);
            parts.push_back(temp);
            
            // Deletes the part that we stored in temp from passage
            passage = passage.substr(end_of_last, passage.size() - end_of_last);

        } else if (passage.find(delim3) == 0) // Else if statement to find links
        {
            first = passage.find(delim3);
            last = passage.find(delim4);
            end_of_last = last + 2;

            temp = passage.substr(first, end_of_last);
            parts.push_back(temp);
            
            passage = passage.substr(end_of_last, passage.size() - end_of_last);

        } else if(passage.find(delim5) == 0) // Else if statement to find blocks
        {
            first = passage.find(delim5);
            last = passage.find(delim6);
            end_of_last = last + 1;

            temp = passage.substr(first, end_of_last);

            passage = passage.substr(end_of_last, passage.size() - end_of_last);
            
            // If statement for Passage 5, makes sure last ] isn't dropped
            if (passage.find(delim6) == 0)
            {
                temp += delim6; 
                parts.push_back(temp);
                passage = passage.substr(1, passage.size());

            } else
                parts.push_back(temp);

        } else if (passage.find(delim3) != 0) // Else if statement to find text
        {
            first = 0;
            last = passage.find(delim3);
            
            // If [[ is found, add the part to the vector and modify passage as normal
            if (last != std::string::npos)
            {
                temp = passage.substr(first, last);
                parts.push_back(temp);
                passage = passage.substr(last, passage.size() - last);

            } else // If [[ is not found, then the rest of the passage is text
            {
                temp = passage.substr(first, passage.size());
                parts.push_back(temp);
                passage = "";
            }
        }
        
    }
    
}

bool PassageTokenizer::hasNextPart()
{
    if (part_num < parts.size()) 
    {
        next_part = true;
        part_num++;

    } else
        next_part = false;

    return next_part;
}

PartToken PassageTokenizer::nextPart()
{
    PartToken part(parts, part_num - 1);

    return part;
}

PartToken::PartToken(vector<string> p, int n)
{
    prts = p;
    num = n;
}

string PartToken::getText()
{
    if (num >= prts.size()) // If there are no more parts return empty string
        return "";
    else
        return prts.at(num);
}

token_t PartToken::getType()
{
    token_t type;

    string set = "(set:";
    string link = "[[";
    string cif = "(if:";
    string elseif = "(else-if:";
    string celse = "(else:";
    string goTo = "(go-to:";
    string block = "[";

    if (num < prts.size()) // If there are no more parts, type is TEXT
    {
        // If else statements to determine the type of part
        if (prts.at(num).find(set) == 0)
            type = SET;
        else if (prts.at(num).find(link) == 0)
            type = LINK;
        else if (prts.at(num).find(cif) == 0)
            type = IF;
        else if (prts.at(num).find(elseif) == 0)
            type = ELSEIF;
        else if (prts.at(num).find(celse) == 0)
            type = ELSE;
        else if (prts.at(num).find(goTo) == 0)
            type = GOTO;
        else if (prts.at(num).find(block) == 0)
            type = BLOCK;
        else
            type = TEXT;
    } else
        type = TEXT;

    return type;    
}