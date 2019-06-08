#ifndef __ASCIITURTLE_H
#define __ASCIITURTLE_H

#include "ASCIICanvas.h"

enum direction_t {UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3};

class AsciiTurtle
{
private:
  AsciiCanvas* canvas;
  int row;
  int col;
  direction_t facing;
  bool pendown;
  char brush;
public:
  //Initializes the turtle with or without a Canvas
  AsciiTurtle(AsciiCanvas* = nullptr);
  //Initializes the turtle at a given row and column on a Canvas, facing a direction, with the pen up or down, and ready to print a given character
  AsciiTurtle(AsciiCanvas*, int, int, direction_t, bool, char = '*');

  //Simple getters and setters
  AsciiCanvas* getCanvas() { return canvas; }
  void setCanvas(AsciiCanvas* c) { canvas = c; }
  char getBrushCharacter() const { return brush; }
  void setBrushCharacter(char c) { brush = c; }

  //Functions controlling the movement of the turtle
  //Should have no effect if canvas == nullptr
  void penUp();
  void penDown();
  void turnLeft();
  void turnRight();
  void forward(int spaces = 1); //stop early if running off the edge of canvas
};


#endif