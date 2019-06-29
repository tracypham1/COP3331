#include <iostream>
#include <fstream>
#include "storytokenizer.h"
using namespace std;

const string INPUT_FILE = "input1.txt";

int main()
{
  string line, story;
  int passnum = 0;

  //Open input.txt for reading
  ifstream in(INPUT_FILE);
  if (!in.is_open())
  {
    cout << "Couldn't open " << INPUT_FILE << " for reading!\n";
    return 1;
  }

  //Read in the story from input.txt
  getline(in, line);
  while (in && line != "</html>")
  {
    story += line + '\n';
    getline(in, line);
  }

  //Construct the StoryTokenizer object
  StoryTokenizer st(story);

  //Iterate through all of the PassageTokens in the story
  while (st.hasNextPassage())
  {
    PassageToken passtok = st.nextPassage();
    cout << "Passage " << ++passnum 
         << " (" << passtok.getName() << "):  " << endl 
         << '\"' << passtok.getText() << '\"' << endl;
  }

  return 0;
}

