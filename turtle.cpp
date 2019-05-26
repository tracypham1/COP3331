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
    cout << "Pen up";
    break;
  case PEN_DOWN:
    cout << "Pen down";
    break;
  case TURN_LEFT:
    cout << "Turn left";
    break;
  case TURN_RIGHT:
    cout << "Turn right";
    break;
  case FORWARD:
    cout << "Forward " << mov.dist;
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
  currMove.type = UNKNOWN;
  currMove.dist = 0;
  string input = " ";
  in >> input;

  //stop if type DNE
  if(input == " ")
    return currMove;

  //assign the move_t variable to return.
  if(input == "PU")
      currMove.type = PEN_UP;
  else if(input == "PD")
      currMove.type == PEN_DOWN;
  else if(input == "TL")
      currMove.type = TURN_LEFT;
  else if(input == "TR")
      currMove.type = TURN_RIGHT;
  else if(input == "F"){
      currMove.type = FORWARD;
      in >> currMove.dist;
  }

  return currMove;
}

void makeMove(move_t mov)
{
  //TODO:  update the turtle status and canvas based on the given move
  int startRow, startCol;
  const int END_ROW = canvas.size();
  const int END_COL = canvas[0].size();
  int i, j;

  switch(mov.type){
    case PEN_UP:
      turtle.pendown = false;
      break;
    case PEN_DOWN:
      turtle.pendown = true;
      break;
    case TURN_LEFT:
      turtle.facing = LEFT;
      break;
    case TURN_RIGHT:
      turtle.facing = RIGHT;
      break;
    case FORWARD:

    /**************if pen is down operations
      //only change values if pen is down
      if(turtle.pendown){
        //add the distance to row if facing L or R
        if(turtle.facing == RIGHT){
          //if the move distance is within canvas
          if(turtle.loc.col+mov.dist <= canvas[0].size)
            for(startCol = turtle.loc.col; startCol < mov.dist; startCol++)
              canvas[turtle.loc.row][startCol] = "*";
          //if the move distance goes out of grid: stop loop at end
          else{
            for(startCol = turtle.loc.col; startCol < canvas[i].size; startCol++)
              canvas[turtle.loc.row][startCol] = "*";
          }
          
        }
        else if(turtle.facing == LEFT){
          //if the move distance is within canvas
          if(turtle.loc.col-mov.dist >= 0)
            for(startCol = turtle.loc.col; startCol < mov.dist; startCol--)
              canvas[turtle.loc.row][startCol] = "*";
          //if the move distance goes out of grid: stop loop at end
          else{
            for(startCol = turtle.loc.col; startCol < canvas[i].size; startCol--)
              canvas[turtle.loc.row][startCol] = "*";
          }
        }

        //add distance to col if facing U or D
        
end of pen deown*******************/

      //if statement pt.2

      //the grid starts at (0, 0)
      if(mov.type == PEN_DOWN){
        //switch controls movement based on direction pointing to 
        switch(turtle.facing)
        case UP:
          for(i = turtle.loc.row, j = turtle.loc.col; (i < turtle.loc.row+move.dist) || (i < 0); i++){
            canvas[i][j] = "*";
          }
          turtle.loc.row = i;

          break;
        case DOWN:
          for(i = turtle.loc.row, j = turtle.loc.col; (i < turtle.loc.row+move.dist) || (i < END_ROW); i++){
            canvas[i][j] = "*";
          }
          turtle.loc.row = i;

          break;
        case RIGHT:
          for(i = turtle.loc.row, j = turtle.loc.col; (j < turtle.loc.col+move.dist) || (j < END_COL); j++){
            canvas[i][j] = "*";
          }
          turtle.loc.col = j;
        
          break;
        case LEFT:
          for(i = turtle.loc.row, j = turtle.loc.col; (j < turtle.loc.col-move.dist) || (j < 0); j--){
            canvas[i][j] = "*";
          }
          turtle.loc.col = j;

          break;
        default:
          return;
        
      }

      else{
        //change the status of the turtle w same logic
        switch(turtle.facing){
        case UP:
          turtle.loc.row += mov.dist;
          break;
        case DOWN:
          turtle.loc.row -= mov.dist;
          break;
        case RIGHT:
          turtle.loc.col += mov.dist;
          break;
        case LEFT:
          turtle.loc.col -= mov.dist;
          break;
        }
      }
    default:
      break;
  }//end big switch
  
  //if the current row and col > grid's row and col
  //set the loc to the appropriate edge
  //account for negatives




}//end function

int main()
{
  //TODO:  initialize turtle

  //TODO:  open input.txt
  ifstream in;
  in.open("input.txt");
  if(in.fail()){
    cout << "Failed to open.";
    return 1;
  }

  //TODO:  get canvas size and build the canvas
  int rows, cols;
  in >> rows >> cols;

  //TODO:  get moves from input.txt
  move_t nextMove;
  nextMove = getMove(in);

  //make moves
  while(nextMove.type != UNKNOWN){
    makeMove(nextMove);
  }

  //Print final result
  printCanvas();

  //close file
  in.close();

  return 0;
}