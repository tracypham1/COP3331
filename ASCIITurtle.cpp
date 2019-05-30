//contain the implementation of the turtle graphics function
#include "ASCIITurtle.h"
#include <iostream>
using namespace std;

//Initializes the turtle at a given row and column on a Canvas, facing a 
//direction, with the pen up or down, and ready to print a given character
AsciiTurtle::AsciiTurtle(AsciiCanvas* canvas, int startRow, int startCol, direction_t f, bool p, char ast){
    row = startRow;
    col = startCol;
    //set facing based on 'f'
    if (f == 0 ) { facing = UP; }
    else if (f == 1) { facing = LEFT; }
    else if (f == 2) { facing = DOWN; }
    else if (f == 3) { facing = RIGHT; }

    if(p == true) { penDown(); }
    else if(p == false) { penUp(); }

    setBrushCharacter(ast);
    setCanvas(canvas);

}

//Functions controlling the movement of the turtle
//Should have no effect if canvas == nullptr
void AsciiTurtle::penUp() { pendown = false; }

void AsciiTurtle::penDown() { pendown = true; }

void AsciiTurtle::turnLeft(){
    if(facing == DOWN) { facing = RIGHT; }
    else if (facing == RIGHT) { facing = UP; }
    else if (facing == UP) { facing = LEFT; }
    else if (facing == LEFT) { facing = DOWN; }
}

void AsciiTurtle::turnRight(){
    if(facing == DOWN) { facing = LEFT; } 
    else if (facing == LEFT) { facing = UP; }
    else if (facing == UP) { facing = RIGHT; }
    else if (facing == RIGHT) { facing = DOWN; } 
}

void AsciiTurtle::forward(int spaces){

    const int LAST_ROW = canvas->getRows()-1;
    const int LAST_COL = canvas->getCols()-1;

    if(facing == UP){
        if(row < spaces)
          spaces = row;
        if(pendown){
          for(int i = 0; i <= spaces; i++){
            //canvas[row-i][col] = brush;
            canvas->set(row-i, col, brush);
          } 
        }
        row -= spaces;
      }
    else if(facing == LEFT){
        if(col < spaces)
          spaces = col;
        if(pendown){
          for(int i = 0; i <= spaces; i++){
            //canvas[row][col-i] = brush;
            canvas->set(row, col - i, brush);
          }
        }
        col -= spaces;
      }
    else if(facing == DOWN){
        if(row + spaces > LAST_ROW)
          spaces = LAST_ROW - row;
        if(pendown){
          for(int i = 0; i <= spaces; i++){
            //canvas[row+i][col] = brush;
            canvas->set(row+i, col, brush);
          }
        }
        row += spaces;
      }
    else if(facing == RIGHT){
        if(col + spaces > LAST_COL)
          spaces = LAST_COL - col;
        if(pendown){
          for(int i = 0; i <= spaces; i++){
            //canvas[row][col+i] = brush;
            canvas->set(row, col+i, brush);
          }
        }
        col += spaces;
      }
}