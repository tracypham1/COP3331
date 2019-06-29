#include "storytokenizer.h"

PassageToken::PassageToken() : name(" "), text(" ") { /*...*/ }

StoryTokenizer::StoryTokenizer(string s){ 
    story = s;
    nextPass = true; 
}

//get the line from story and use find, substr, and at from <string> 
PassageToken StoryTokenizer::nextPassage(){
    PassageToken passage;

    //use character to find name of the PassageToken
    //start is the index of n, +6 is the start of the name
    string n(""); 
    size_t start = story.find("pid=");
    if(start != std::string::npos)
        for(int i = start + 14; story.at(i) != '"'; i++)
            n += story.at(i);
    passage.setName(n);

    //use certain character to find test of the PassageToken
    //start is redefined as the index of a char+constant to determine beginning of text
    string t("");
    int j;
    //this method means the text cannot contain '<'
    start = story.find("position");
    if(start != std::string::npos)
        for(j = start + 19; story.at(j) != '<'; j++)
            t += story.at(j); 
    passage.setText(t);

    //Note: only works if the distance from p in position is the same from first character of text
    //this strat sets name and text as " " if the occurance is not found

    //if there is a next passage, remove this passage from the story
    size_t nextOccur = story.find("pid=", start); //start refers to middle of the last passage defined above

    if(nextOccur == std::string::npos) 
        nextPass = false;
    else{ 
        nextPass = true;
        size_t end = story.find("</body>");
        story = story.substr(j, end); //redefine giant story string
    }   
   
    return passage;
}
