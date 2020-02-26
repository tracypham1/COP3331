#include "passagetokenizer.h"
#include <iostream>
#include <cstddef>
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

            if(passage.find("[[[") == 0) // Added for escape.html
            {
                last = passage.find("]]]");
                end_of_last = last + 3;

                temp = passage.substr(first, end_of_last);
                passage = passage.substr(end_of_last, passage.size() - end_of_last);

            } else
            {
                temp = passage.substr(first, end_of_last);
                passage = passage.substr(end_of_last, passage.size() - end_of_last);
            }
            parts.push_back(temp);
             
        } else if(passage.find(delim5) == 0) // Else if statement to find blocks
        {
            last = passage.find(delim6);
            end_of_last = last + 1;
            
            temp = passage.substr(first, end_of_last);
            passage = passage.substr(end_of_last, passage.size() - end_of_last); 
            
            // If statement that makes sure last ] isn't dropped
            if (passage.find(delim6) == 0)
            {   
                while (passage.find(delim6) == 0)
                {
                    temp += delim6; 
                    passage = passage.substr(1, passage.size());
                }
                while (passage.find(delim6) == 1)
                {
                    temp = temp + " " + delim6; 
                    passage = passage.substr(2, passage.size());
                }
                while (passage.find(delim6) == 2)
                {
                    temp = temp + "\n" + delim6; 
                    passage = passage.substr(3, passage.size());
                }
                while (passage.find(delim6) == 24) 
                {
                    temp += "\n";
                    temp += "(set: $end8 to true)\n";
                    temp += delim6;
                    passage = passage.substr(25, passage.size());
                }
                parts.push_back(temp);
                
            } else
                parts.push_back(temp); 

        } else // Else statement to find text
        {   
            first = 0;
            int link = passage.find(delim3); // Finds links 
            int set = passage.find("(set:"); // Finds set commands
            int goTo = passage.find("(go-to"); // Finds go-to commands
            int If = passage.find("(if:"); // Finds if commands
            int Else = passage.find("(else"); // Finds else-if and else commands
            int block = passage.find(delim5); // Finds the end of the block
            
            // Changes the value if there are no links or commands
            if (link == std::string::npos)
                link = 100000000;
            if (set == std::string::npos)
                set = 100000000;
            if (goTo == std::string::npos)
                goTo = 100000000;
            if (If == std::string::npos)
                If = 100000000;
            if (Else == std::string::npos)
                Else = 100000000;
            if (block == std::string::npos)
                block = 100000000;   

            // If else statements to determine if a link, command, or end of block comes first
            // Temp will hold the text up to the beginning of the link, command, or end of block
            if (set < block && set < link && set < goTo && set < If && set < Else)
            {
                temp = passage.substr(first, set);
                parts.push_back(temp);
                passage = passage.substr(set, passage.size() - set);

            } else if (goTo < block && goTo < link && goTo < set && goTo < If && goTo < Else)
            {
                temp = passage.substr(first, goTo);
                parts.push_back(temp);
                passage = passage.substr(goTo, passage.size() - goTo);
            } else if (If < block && If < link && If < set && If < goTo && If < Else)
            {
                temp = passage.substr(first, If);
                parts.push_back(temp);
                passage = passage.substr(If, passage.size() - If);

            } else if (Else < block && Else < link && Else < set && Else < If && Else < goTo)
            {
                temp = passage.substr(first, Else);
                parts.push_back(temp);
                passage = passage.substr(Else, passage.size() - Else);

            } else if (link <= block && link < set && link < goTo && link < If && link < Else)
            {
                temp = passage.substr(first, link);
                parts.push_back(temp);
                passage = passage.substr(link, passage.size() - link);
            } 
            else if (block < link && block < set && block < goTo && set < If && set < goTo)
            {
                temp = passage.substr(first, block);
                parts.push_back(temp);
                passage = passage.substr(block, passage.size() - block);

            } else
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
        else if (prts.at(num).find("[[[") == 0) // Added for escape.html
            type = BLOCK;
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

