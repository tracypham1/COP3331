#include "ASCIICanvas.h"
#include <iostream>

AsciiCanvas::AsciiCanvas(int rows, int cols, char init)
{
  if (rows > 0)
    nrows = rows;
  else
    nrows = 1;
  if (cols > 0)
    ncols = cols;
  else
    ncols = 1;

  canvas.resize(nrows);
  for (int i = 0; i < nrows; i++)
    for (int j = 0; j < ncols; j++)
      canvas[i].push_back(init);
}

void AsciiCanvas::print() const
{
  for (int i = 0; i < nrows; i++)
  {
    for (int j = 0; j < ncols; j++)
      cout << canvas[i][j];
    cout << endl;
  }
}
