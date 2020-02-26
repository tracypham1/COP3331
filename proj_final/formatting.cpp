#include "formatting.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <iterator>
using namespace std;

Formatting::Formatting()
{
    variables.insert(make_pair("hello", false));
}

void Formatting::text(string text, int print)
{
    cout << '"' << text << '"' << endl; // Prints quotes around text
}

void Formatting::set(string text, int print)
{
    
    string delim1 = "$";
    string delim2 = " to ";

    int first = text.find(delim1);
    int last = text.find(delim2);
    int end_of_last = last - first;

    // Gets the variable to be created as a substring
    string var = text.substr(first, end_of_last);

    // Checks if the variable is true or false then adds the variable and it's value to the map
    if(text.find("true") != std::string::npos)
        variables.emplace(var, true);
    else
        variables.emplace(var, false);

    // Checks if variable was already added and updates its value
    if(variables.count(var) == 1)
    {
        if(text.find("true") != std::string::npos)
            variables.at(var) = true;
        else
            variables.at(var) = false;
    }

    unordered_map<string, bool>::iterator it; 
    it = variables.find(var); // Finds the variable in the map
    
    // Prints the variable and its value
    if(it->second == 1) 
        cout << "Set: var=" << it->first << ", value=true" << endl;
    else
        cout << "Set: var=" << it->first << ", value=false" << endl;

}

void Formatting::link(string text, int print)
{
    string delim1 = "[[";
    string delim2 = "]]";
    string delim3 = "-&gt;";
    string display, target;

    int first = text.find(delim1);
    int last = text.find(delim2);
    int gt = text.find(delim3);
    int end_of_first = first + delim1.length();

    // Checks if -&gt; was in the link
    if (gt != std::string::npos)
    {
        int gt_left = gt - end_of_first;
        int gt_right = last - (gt + delim3.length());

        display = text.substr(end_of_first, gt_left); // Display becomes substring to the left of -&gt;
        target = text.substr(gt + delim3.length(), gt_right); // Target becomes substring to the right of -&gt;

    } else // If -&gt; is not in the link, display and target are what's in the double brackets
    {
       int end_of_last = last - end_of_first;

       display = text.substr(end_of_first, end_of_last);
       target = display;
    }

    // Prints out what the link displays and what it links too
    cout << "Link: display=" << display << ", target=" << target << endl;
}

void Formatting::goTo(string text, int print)
{
    string delim1 = "&quot;";
    string delim2 = "&quot;)";

    int first = text.find(delim1);
    int last = text.find(delim2);
    int end_of_first = first + delim1.length();
    int end_of_last = last - end_of_first;

    string go = text.substr(end_of_first, end_of_last); // Gets passage name between the &quot's

    cout << "Goto: target=" << go << endl; // Prints out go-to's target 
}


void Formatting::iF(string text, int print)
{
    
    string delim1 = "$";
    string delim2 = " is ";

    int first = text.find(delim1);
    int last = text.find(delim2);
    int end_of_last = last - first;
    string var = text.substr(first, end_of_last);
    
    if(text.find("true") != std::string::npos)
        cout << "If: var=" << var << ", value=true" << endl;
    else
        cout << "If: var=" << var << ", value=false" << endl;
}

//is else-if in the input all lowercase?
void Formatting::elseIF(string text, int print)
{
    string delim1 = "$";
    string delim2 = " is ";

    int first = text.find(delim1);
    int last = text.find(delim2);
    int end_of_last = last - first;
    string var = text.substr(first, end_of_last);
    
    if(text.find("true") != std::string::npos)
        cout << "Else-if: var=" << var << ", value=true" << endl;
    else
        cout << "Else-if: var=" << var << ", value=false" << endl;
}

//else never appear in middle of text right?
//bc that causes an error...
void Formatting::Else(int print)
{
    cout << "Else" << endl; //too ez
}

void Formatting::block(string text, int print)
{
    int first, last, end_of_last;

    string delim1 = "(";
    string delim2 = ")";
    string delim3 = "[[";
    string delim4 = "]]";
    string delim5 = "[";
    string delim6 = "]";

    string temp;

    while(text != "") // While loop to parse through a block
    {
        if(text.find(delim5) == 0) // Else if statement to find the start of blocks
        {   
            first = text.find(delim5);

            // Checks if text starts with a link or a block or both since [ is apart of [[
            if (text.find(delim3) != text.find(delim5)) 
            {
                temp = text.substr(first, 1);
                text = text.substr(1, text.size() - 1);
                cout << "START BLOCK" << endl; // Prints to signify the start of a block

            } else 
            {   
                // Removes first [ 
                text = text.substr(1, text.size() - 1);

                if (text.find(delim3) == 0) // If [[ is still found then print START BLOCK for the removed [
                {
                    cout << "START BLOCK" << endl; // Prints to signify the start of a block
                    first += 1;
                }

                last = text.find(delim4);
                end_of_last = last + 2;

                temp = text.substr(first, end_of_last);
                this->link(temp, print); // Passes temp the link function
                            
                text = text.substr(end_of_last, text.size() - end_of_last);
            } 
            

        } else if(text.find(delim6) == 0) // Else if statement to find the end of blocks
        {
            first = text.find(delim6);

            temp = text.substr(first, 1);
            cout << "END BLOCK" << endl; // Prints to signify the end of a block

            text = text.substr(1, text.size() - 1);

        } else if (text.find(delim1) == 0) // If statement to find commands
        {
            first = text.find(delim1);
            last = text.find(delim2);
            end_of_last = last + 1;

            // Gets the part as a substring 
            temp = text.substr(first, end_of_last);

            // Passes temp to the function that matches temp's type
            if (temp.find("(set:") == 0)
                this->set(temp, print);
            else if(temp.find("(go-to:") == 0)
                this->goTo(temp, print);
            else if(temp.find("(if:") == 0)
                this->iF(temp, print);
            else if(temp.find("else-if:") == 0) 
                this->elseIF(temp, print);
            else if(temp.find("(else:") == 0)
                this->Else(print);
     
            // Deletes the part that we stored in temp from text
            text = text.substr(end_of_last, text.size() - end_of_last);

        }  else if (text.find(delim3) == 0) // Else if statement to find links
        {
            first = text.find(delim3);
            last = text.find(delim4);
            end_of_last = last + 2;
            
            temp = text.substr(first, end_of_last);
            this->link(temp, print); // Passes temp the link function
                    
            text = text.substr(end_of_last, text.size() - end_of_last);
            
        } else // Else  statement to find text
        {
            first = 0;
            int last_link = text.find(delim3); // Finds links 
            int last_cmd = text.find(delim1);  // Finds commands
            int last_block = text.find(delim6); // Finds the end of the block

            // Changes the value of last_link and last_cmd if there are no links or commands 
            if (last_link == std::string::npos)
                last_link = 100000000;

            if (last_cmd == std::string::npos)
                last_cmd = 100000000;

            // If else statements to determine if a link, command, or end of block comes first
            // Temp will hold the text up to the beginning of the link, command, or end of block
            if (last_cmd < last_block && last_cmd < last_link)
            {
                temp = text.substr(first, last_cmd);
                text = text.substr(last_cmd, text.size() - last_cmd);

            } else if (last_link < last_block && last_link < last_cmd)
            {
                temp = text.substr(first, last_link);
                text = text.substr(last_link, text.size() - last_link);

            } else if (last_block != std::string::npos)
            {
                temp = text.substr(first, last_block);
                text = text.substr(last_block, text.size() - last_block);
            }
            
            this->text(temp,print); // Passes temp to the text function 
        }
    } 
    
}

void Formatting::text(string text)
{
    cout << text; // Prints text
}

void Formatting::set(string text)
{
    
    string delim1 = "$";
    string delim2 = " to ";

    int first = text.find(delim1);
    int last = text.find(delim2);
    int end_of_last = last - first;

    // Gets the variable to be created as a substring
    string var = text.substr(first, end_of_last);

    // Checks if the variable is true or false then adds the variable and it's value to the map
    if(text.find("true") != std::string::npos)
        variables.emplace(var, true);
    else
        variables.emplace(var, false);

    // Checks if variable was already added and updates its value
    if(variables.count(var) == 1)
    {
        if(text.find("true") != std::string::npos)
            variables.at(var) = true;
        else
            variables.at(var) = false;
    }

}

string Formatting::link(string text)
{
    string delim1 = "[[";
    string delim2 = "]]";
    string delim3 = "-&gt;";
    string display, target;

    int first = text.find(delim1);
    int last = text.find(delim2);
    int gt = text.find(delim3);
    int end_of_first = first + delim1.length();

    // Checks if -&gt; was in the link
    if (gt != std::string::npos)
    {
        int gt_left = gt - end_of_first;
        int gt_right = last - (gt + delim3.length());

        display = text.substr(end_of_first, gt_left); // Display becomes substring to the left of -&gt;
        target = text.substr(gt + delim3.length(), gt_right); // Target becomes substring to the right of -&gt;

    } else // If -&gt; is not in the link, display and target are what's in the double brackets
    {
       int end_of_last = last - end_of_first;

       display = text.substr(end_of_first, end_of_last);
       target = display;
    }

    links.push_back(display); 
    this->text(display); // Passes the link to be displayed to text so it can be printed out

    return target; // Returns the target passage
} 

string Formatting::goTo(string text)
{
    string delim1 = "&quot;";
    string delim2 = "&quot;)";

    int first = text.find(delim1);
    int last = text.find(delim2);
    int end_of_first = first + delim1.length();
    int end_of_last = last - end_of_first;

    string go = text.substr(end_of_first, end_of_last); // Gets passage name between the &quot's

    return go; // Returns the target passage
}


void Formatting::iF(string text)
{
    
    string delim1 = "$";
    string delim2 = " is ";
    string delim3 = ")";
    bool val;

    int first = text.find(delim1);
    int last = text.find(delim2);
    int end_of_last = last - first;
    int begin_val = last + delim2.size();
    int end_val = text.size() - begin_val;

    string var = text.substr(first, end_of_last); // Gets the variable name
    string value = text.substr(begin_val, end_val - 1); // Gets the conditional value 

    unordered_map<string, bool>::iterator it; 
    it = variables.find(var);

    // Initializes val so we can compare the value in the if command to the value in the map
    if (value == "true") 
        val = true; 
    else
        val = false;

    // If the conditional value matches the variable's map value, the if command is true
    if(it->second == val) 
    {
        test = true;
        call_else = 1;
    }
    else 
    {
        test = false;
        call_else = 0;
    }
} 

void Formatting::elseIF(string text)
{
    string delim1 = "$";
    string delim2 = " is ";
    string delim3 = ")";
    bool val;

    int first = text.find(delim1);
    int last = text.find(delim2);
    int end_of_last = last - first;
    int begin_val = last + delim2.size();
    int end_val = text.size() - begin_val;
    
    string var = text.substr(first, end_of_last);
    string value = text.substr(begin_val, end_val - 1);

    unordered_map<string, bool>::iterator it; 
    it = variables.find(var);

    // Initializes val so we can compare the value in the if command to the value in the map
    if (value == "true")
        val = true;
    else
        val = false;

    // If the conditional value matches the variable's map value, the if command is true
    if(it->second == val)
    {
        test = true;
        call_else = 1;
    }
    else 
    {
        test = false;
        call_else = 0;
    }
}

void Formatting::Else()
{
    test = true;
    call_else = 0;
}

void Formatting::block(string t)
{
        t = t.substr(1, t.size() - 2); // Removes the block brackets for tokenizing 
        
        string temp; 

        PassageTokenizer pt(t); // Construct PassageTokenizer object 

        while (pt.hasNextPart()) // While loop to go through each part in the current passage
        {   
            PartToken stok = pt.nextPart(); // Construct PartToken object
            
            switch (stok.getType()) // Switch statement to call functions that match the part type
            {
            case LINK:
                temp = this->link(stok.getText());
                link_target.push_back(temp); 
                break; 
            case SET:
                this->set(stok.getText());
                break;
            case GOTO:
                temp = this->goTo(stok.getText());
                break;
            case IF:
                this->iF(stok.getText());
                break;
            case ELSEIF:
                this->elseIF(stok.getText());
                break; 
            case ELSE: 
                if (call_else < 1)
                    this->Else();
                else 
                {
                    test = false;
                    call_else = 0;
                }
                break; 
            case BLOCK:
                if (test == true)              
                       this->block(stok.getText());             
                break; 
            case TEXT:
                this->text(stok.getText());
                break; 
            default:
                cout << "  Unknown token: " << endl;
            }
            
            if (stok.getType() == GOTO) // Ignores everything after go-to command is found
            {
                unordered_map<string, string>::iterator it; 
                it = pass.find(temp); // Looks for the target passage

                name = temp; // Name is initialized to the target passsage's name
                story = it->second; // Story is initialized to the target passage's passage
                
                links.clear(); // Clear vectors for next passage
                link_target.clear();

                nestedGOTO = true;
                
                break;
            } 
        }
    
}