#include "GritVMBase.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <sstream>

class GritVM : public GritVMInterface {
private:
  std::vector<long> dataMem;
  std::list<Instruction> instructMem;
  std::list<Instruction>::iterator currentInstruct;
  STATUS machineStatus;
  long accumulator;
public:
  GritVM();
  STATUS load(const std::string filename, const std::vector<long> &initialMemory);
  STATUS run();
  std::vector <long> getDataMem();
  STATUS reset();
};
