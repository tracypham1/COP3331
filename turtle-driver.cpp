//contains the main function that constructs and uses ASCIICanvas and ASCIITurtle 
//objects in order to generate the turtle graphics commands in input.txt

#include "ASCIITurtle.h"
#include <fstream>
#include <iostream>
using namespace std;

//Global Varibales
AsciiCanvas* c;
AsciiTurtle turtle(c, 0, 0, DOWN, false);

enum command_t {PEN_UP, PEN_DOWN, TURN_LEFT, TURN_RIGHT, FORWARD, UNKNOWN};

typedef struct
{
  command_t type;
  unsigned int dist;
} move_t;

move_t getMove(ifstream& in)
{
  //TODO:  write code to read in the move_t from in
  
  move_t currMove;
  string input = " ";
  in >> input;

  //assign the move_t variable to return
  if(input == "PU")
    currMove.type = PEN_UP;
  else if(input == "PD")
    currMove.type = PEN_DOWN;
  else if(input == "TL")
    currMove.type = TURN_LEFT;
  else if(input == "TR")
    currMove.type = TURN_RIGHT;
  else if(input == "F"){
    currMove.type = FORWARD;
    in >> currMove.dist;
    if(currMove.dist<0){
      currMove.type = UNKNOWN;
    }
  }
  else
    currMove.type = UNKNOWN;

  return currMove;
}

void makeMove(move_t mov)
{
  //TODO:  update the turtle status and canvas based on the given move
  switch(mov.type){
    case PEN_UP:
      turtle.penUp();
      break;
    case PEN_DOWN:
      turtle.penDown();
      break;
    case TURN_LEFT:
      turtle.turnLeft();
      break;
    case TURN_RIGHT:
      turtle.turnRight();
      break;
    case FORWARD:
      turtle.forward(mov.dist);
      break; 
    default:
      break;
    
  }//end switch
}//end function

int main(){

    //open the file
    ifstream in;
    in.open("input.txt");
    if(in.fail()){
        cout << "Failed to open.";
        return 1;
    }

    //get info and build canvas
    int nrow, ncol;
    in >> nrow >> ncol;
    AsciiCanvas canvas(nrow, ncol);
    c = &canvas;
    turtle.setCanvas(c);

    //get moves from 'in' file stream
    while(!in.eof()){
        move_t nextMove = getMove(in);
        
        //make moves
        if(nextMove.type != UNKNOWN){
            makeMove(nextMove);
        }
    }

    //print final canvas
    canvas.print(); //c->print(); 

    in.close();
    return 0;
}