#include "storytokenizer.h"

StoryTokenizer::StoryTokenizer(string s){ 
    anime = s;
    nextPass = true; 
}

PassageToken StoryTokenizer::nextPassage(){
    //get the line from anime and use string functions find, substr, at from <string>
    //to episode.setName(n) and episode.setText(t)
    PassageToken episode;
    size_t start;
    size_t end = anime.find("</body>");

    string n("");
    //start is the index of n, +6 is the start of the name
    start = anime.find("pid=");
    if(start != std::string::npos)
        for(int i = start + 14; anime.at(i) != '"'; i++)
            n += anime.at(i);
    episode.setName(n);

    string t("");
    //start is the index of t, +6 is the start of the text
    //this method means the text cannot contain '<'
    int j;
    start = anime.find("position");
    if(start != std::string::npos)
        for(j = start + 19; anime.at(j) != '<'; j++)
            t += anime.at(j); 
    episode.setText(t);

    //Note: only works if the distance from p in position is the same from first character of text
    //this strat sets name and text as " " if the occurance is not found

    //if both name and text == " ", no nextPass
    //...actually check for next occurance, so we dont print an empty passage
    //understand the thing about start+1 here, the second occurance or whatever >> start parameter is where to start searching
    size_t nextOccurN;
    nextOccurN = anime.find("pid=", start);
    if(nextOccurN == std::string::npos) 
        nextPass = false;
    else{ 
        nextPass = true;
        anime = anime.substr(j, end);
    }   
    //gotta change where anime starts each time
    //redefine anime string

    return episode;
}
