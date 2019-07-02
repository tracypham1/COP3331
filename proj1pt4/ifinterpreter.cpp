#include "ifinterpreter.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
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
        PassageToken* ptr = &passtok; 

        passage.push_back(ptr); // Add PassageToken* to vector pass
        pass.insert(make_pair(passtok.getName(), passtok.getText())); // Maps the name and text together
    }

}

void IFInterpreter::print()
{
    int pass_num = 0;

    //check vector<PassageToken*> passage initialized correctly in constructor
    while(pass_num < passage.size()){
        cout << "passage name at " << pass_num+1 << ": " << passage.at(pass_num)->getName << endl;
    }

/*************    
    // Goes through each element of vector passage
    while(pass_num < passage.size()) 
    {
        cout << "Passage: " << passage.at(pass_num)->getName() << endl; // Prints passage name

        PassageTokenizer pt(passage.at(pass_num)->getText()); // Construct PassageTokenizer object

        while (pt.hasNextPart()) // While loop to go through each part in the current passage
        {
            PartToken stok = pt.nextPart(); // Construct PartToken object

            switch (stok.getType()) // Switch statement to call functions that match the part type
            {
            /*********
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
                cout << "  Unknown token: ";
            }
        }
     
        pass_num++; // Increments pass_num to go to the next vector element
    }
*********************/

}
