#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//Declare structs and enums
enum direction_t {UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3};
enum command_t {PEN_UP, PEN_DOWN, TURN_LEFT, TURN_RIGHT, FORWARD, UNKNOWN};
typedef struct
{
  int row;
  int col;
} coord_t;

typedef struct
{
  bool pendown;
  direction_t facing;
  coord_t loc;
} status_t;

typedef struct
{
  command_t type;
  unsigned int dist;
} move_t;

//Global variables
//Not good style, but avoids syntax we haven't discussed yet
vector<vector<char>> canvas;
status_t turtle;


//Initializes a blank canvas of the given size
void buildCanvas(coord_t size)
{
  canvas.resize(size.row);
  for (int i = 0; i < size.row; i++)
    for (int j = 0; j < size.col; j++)
      canvas[i].push_back(' ');
}

void printStatus()
{
  cout << "You are at (" << turtle.loc.row << ", " << turtle.loc.col << "), facing ";
  switch (turtle.facing)
  {
  case UP:
    cout << "up";
    break;
  case DOWN:
    cout << "down";
    break;
  case LEFT:
    cout << "left";
    break;
  case RIGHT:
    cout << "right";
    break;
  default:
    cout << "the wrong direction";
  }
  cout << ".  The pen is " << (turtle.pendown? "down.":"up.") << endl;
}

void printMove(move_t mov)
{
  switch (mov.type)
  {
  case PEN_UP:
    cout << " Pen up ";
    break;
  case PEN_DOWN:
    cout << " Pen down ";
    break;
  case TURN_LEFT:
    cout << " Turn left ";
    break;
  case TURN_RIGHT:
    cout << " Turn right ";
    break;
  case FORWARD:
    cout << " Forward " << mov.dist;
    break;
  default:
    break;
  }
}

void printCanvas()
{
  for (int i = 0; i < canvas.size(); i++)
  {
    for (int j = 0; j < canvas[i].size(); j++)
      cout << canvas[i][j];
    cout << endl;
  }
}

//We'll discuss reference parameters (&) later in class
//Just treat it as a normal ifstream for now (no extra syntax to pass in an ifstream argument)
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
  int startRow, startCol;
  const int LAST_ROW = canvas.size()-1;
  const int LAST_COL = canvas[0].size()-1;
  int i, j;

  switch(mov.type){
    case PEN_UP:
      turtle.pendown = false;
      break;
    case PEN_DOWN:
      turtle.pendown = true;
      break;
    case TURN_LEFT:
      if(turtle.facing == UP)
        turtle.facing = LEFT;
      else if(turtle.facing == LEFT)
        turtle.facing = DOWN;
      else if(turtle.facing == DOWN)
        turtle.facing = RIGHT;
      else if(turtle.facing == RIGHT)
        turtle.facing = UP;
      break;
    case TURN_RIGHT:
      if(turtle.facing == UP)
        turtle.facing = RIGHT;
      else if(turtle.facing == RIGHT)
        turtle.facing = DOWN;
      else if(turtle.facing == DOWN)
        turtle.facing = LEFT;
      else if(turtle.facing == LEFT)
        turtle.facing = UP;
      break;
    case FORWARD:
      if(turtle.facing == UP){
        if(turtle.loc.row < mov.dist)
          mov.dist = turtle.loc.row;
        if(turtle.pendown){
          for(int i = 0; i <= mov.dist; i++){
            canvas[turtle.loc.row-i][turtle.loc.col] = '*';
          }
        }
        turtle.loc.row -= mov.dist;
      }
      else if(turtle.facing == LEFT){
        if(turtle.loc.col < mov.dist)
          mov.dist = turtle.loc.col;
        if(turtle.pendown){
          for(int i = 0; i <= mov.dist; i++){
            canvas[turtle.loc.row][turtle.loc.col-i] = '*';
          }
        }
        turtle.loc.col -= mov.dist;
      }
      else if(turtle.facing == DOWN){
        if(turtle.loc.row + mov.dist > canvas.size()-1)
          mov.dist = canvas.size()-1 - turtle.loc.row;
        if(turtle.pendown){
          for(int i = 0; i <= mov.dist; i++){
            canvas[turtle.loc.row+i][turtle.loc.col] = '*';
          }
        }
        turtle.loc.row += mov.dist;
      }
      else if(turtle.facing == RIGHT){
        if(turtle.loc.col + mov.dist > canvas[0].size()-1)
          mov.dist = canvas[0].size()-1 - turtle.loc.col;
        if(turtle.pendown){
          for(int i = 0; i <= mov.dist; i++){
            canvas[turtle.loc.row][turtle.loc.col+i] = '*';
          }
        }
        turtle.loc.col += mov.dist;
      }
      break; //end of case FORWARD
    default:
      break;
  }//end big switch
}//end function

int main()
{
  //TODO:  initialize turtle
  turtle.pendown = false;
  turtle.facing = DOWN;
  turtle.loc.row = 0;
  turtle.loc.col = 0;

  string file;
  cout << "Enter file: ";
  cin >> file;

  //TODO:  open input.txt
  ifstream in;
  in.open(file);
  if(in.fail()){
    cout << "Failed to open.";
    return 1;
  }

  //TODO:  get canvas size and build the canvas
  coord_t size;
  in >> size.row >> size.col;
  buildCanvas(size);

  //TODO:  get moves from input.txt
  while(!in.eof()){
    move_t nextMove;
    nextMove = getMove(in);
    printMove(nextMove);
    cout << endl;

    //make moves
    if(nextMove.type != UNKNOWN)
      makeMove(nextMove);
  }

  //Print final result
  printCanvas();

  //close file
  in.close();

  return 0;
}