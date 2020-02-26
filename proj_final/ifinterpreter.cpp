#include "ifinterpreter.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <iterator>
using namespace std;

IFInterpreter::IFInterpreter(string filename)
{
    string line, story;

    // Opens input.html for reading
    ifstream in(filename);
    if (!in.is_open())
        cout << "Couldn't open " << filename << " for reading!\n";

    // Read in the story from input.html
    getline(in, line);
    while (in && line != "</html>")
    {
        story += line + '\n';
        getline(in, line);
    }

    // Construct StoryTokenizer object
    StoryTokenizer st(story);

    //Iterate through all of the passages in the story
    while (st.hasNextPassage())
    {
        PassageToken passtok = st.nextPassage(); // Construct PassageToken object
        PassageToken* ptr = new PassageToken(passtok);

        passage.push_back(ptr); // Add PassageToken* to vector pass
        pass.insert(make_pair(passtok.getName(), passtok.getText())); // Maps the name and text together
    }

}

void IFInterpreter::print()
{
    int pass_num = 0;

    // Goes through each element of vector passage
    while(pass_num < passage.size()) 
    {
        cout << "Passage " << passage.at(pass_num)->getName() << ":" << endl; // Prints passage name
        
        PassageTokenizer pt(passage.at(pass_num)->getText()); // Construct PassageTokenizer object

        while (pt.hasNextPart()) // While loop to go through each part in the current passage
        {   
            PartToken stok = pt.nextPart(); // Construct PartToken object

            switch (stok.getType()) // Switch statement to call functions that match the part type
            {
            case LINK:
                link(stok.getText(), pass_num);
                break;
            case SET:
                set(stok.getText(), pass_num);
                break;
            case GOTO:
                goTo(stok.getText(), pass_num);
                break;
            case IF:
                iF(stok.getText(), pass_num);
                break;
            case ELSEIF:
                elseIF(stok.getText(), pass_num);
                break;
            case ELSE:
                Else(pass_num);
                break;
            case BLOCK:
                block(stok.getText(), pass_num);
                break;
            case TEXT:
                text(stok.getText(), pass_num);
                break;
            default:
                cout << "  Unknown token: " << endl;
            }
        }
     
        pass_num++; // Increments pass_num to go to the next vector element
    }

}

void IFInterpreter::play()
{   
    story = passage.at(0)->getText(); // Initializes to the first passage 
    name = passage.at(0)->getName(); // Initializes to the name of the first passage
    string temp;
    int option;
    bool last_pass = false;
    call_else = 0;

    // Terminates when it reaches a passage that contains no links
    while(last_pass == false) 
    {   
        PassageTokenizer pt(story); // Construct PassageTokenizer object

        if(story.find("[[") == std::string::npos) // Checks for the final passage with no links
            last_pass = true; 

        nestedGOTO = false;

        while (pt.hasNextPart() && nestedGOTO == false) // While loop to go through each part in the current passage
        {   
            PartToken stok = pt.nextPart(); // Construct PartToken object
            
            switch (stok.getType()) // Switch statement to call functions that match the part type
            {
            case LINK:
                temp = link(stok.getText());
                link_target.push_back(temp); 
                break; 
            case SET:
                set(stok.getText());
                break;
            case GOTO:
                temp = goTo(stok.getText());
                break;
            case IF:
                iF(stok.getText());
                break;
            case ELSEIF:
                elseIF(stok.getText());
                break; 
            case ELSE:
                if(call_else < 1)
                    Else(); 
                else
                {
                    test = false;
                    call_else = 0;
                }
                break;
            case BLOCK:
                if (test == true)             
                    block(stok.getText());
                break; 
            case TEXT:
                text(stok.getText());
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

                break;
            }

            // For escape.html; there is a go-to command in a passage with no links
            if (nestedGOTO == true)
                last_pass = false; // Causes the outer loop to continue even though there are no links
        }
        cout << endl << endl;
        
         if (links.size() != 0) // If statements that deals with printing out and selecting links
        {
            for(int i = 0; i < links.size(); i++) // For loop that prints numbered list of links
                cout << i + 1 << ") " << links.at(i) << endl;

            cout << endl << "Select an option: "; // Prompts user to select one of the links
            cin >> option;

            while(option > links.size() || option < 1) // If statement for invalid link selection
            {
                cout << "Invalid option. Please select a valid option: ";
                cin >> option;
            }

            cout << endl << endl;
            
            temp = link_target.at(option - 1);

            unordered_map<string, string>::iterator it; 
            it = pass.find(temp); // Looks for the links target passage

            name = temp; // Name is initialized to the target passsage's name
            story = it->second; // Story is initialized to the target passage's passage

            links.clear(); // Clear vectors for next passage
            link_target.clear();
        } 

    }
}