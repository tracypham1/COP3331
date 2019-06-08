#ifndef __ASCIICANVAS_H
#define __ASCIICANVAS_H

#include <vector>
using namespace std;

class AsciiCanvas
{
private:
  int nrows;
  int ncols;
  vector<vector<char>> canvas;
public:
  //Initialize a canvas of a given size, with an optional fill character
  AsciiCanvas(int rows, int cols, char init = ' ');

  //Return a character on the canvas
  char get(int row, int col) const { return canvas[row][col]; }
  //Change a character on the canvas
  void set(int row, int col, char ch) { canvas[row][col] = ch; }

  //Simple getters
  int getRows() const { return nrows; }
  int getCols() const { return ncols; }

  //Print the canvas to the console
  void print() const;
};

#endif