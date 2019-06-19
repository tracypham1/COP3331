#include "GritVM.hpp"
#include "GritVMBase.cpp"

GritVM::GritVM() { //default constructor that sets the machine status to WAITING and AC to 0 when created
  accumulator = 0;
  machineStatus = WAITING;
}

STATUS GritVM::load(const std::string filename, const std::vector<long> &initialMemory) { //method for loading files
  std::ifstream myFile; std::istringstream iss;
  std::string fullInstruction;
  myFile.open(filename);
  int i = 0;

  if(!myFile.is_open()) {
    throw "File could not be opened";
  }

  while(!myFile.eof()) { //while loop that extracts lines from the file and parses them
    std::getline(myFile, fullInstruction);
    if(fullInstruction.empty() || fullInstruction[0] == '#') { //if string is empty or the line starts with '#' skip
      continue;
    }
    Instruction temp = GVMHelper::parseInstruction(fullInstruction); //assign the return struct to temp
    if(temp.operation == UNKNOWN_INSTRUCTION) { //if the instruction is unknown, set machine status to errored
      reset();
      machineStatus = ERRORED;
      break;
    }
    instructMem.push_back(temp);
    machineStatus = READY;
  }

  if(instructMem.empty()) { //if size of list is 0, set status to waiting
    machineStatus = WAITING;
  }
  dataMem = initialMemory;
  return machineStatus;
}


STATUS GritVM::run() { //method for running programs
  bool stopGritVM;
  int j = 0;
  currentInstruct = instructMem.begin();
  if(machineStatus == READY) {
    machineStatus = RUNNING;
  }

    while(currentInstruct != instructMem.end()) {
      std::cout << "Instruction " << j++ << ": " << GVMHelper::instructionToString(currentInstruct->operation) << " " << currentInstruct-> argument << std::endl;
      switch(currentInstruct->operation) { //cases (thank God for the STL library)
          case CLEAR:
            accumulator = 0;
            currentInstruct++;
            break;
          case AT:
            accumulator = dataMem[currentInstruct->argument];
            currentInstruct++;
            break;
          case SET:
            dataMem[currentInstruct->argument] = accumulator;
            std:: cout << dataMem[0] << " " << dataMem[1] << " " << dataMem[2] << std::endl;
            currentInstruct++;
            break;
          case INSERT:
            dataMem.insert(dataMem.begin() + currentInstruct->argument, accumulator);
            currentInstruct++;
            break;
          case ERASE:
            dataMem.erase(dataMem.begin() + currentInstruct->argument);
            currentInstruct++;
            break;
          case ADDCONST:
            accumulator += currentInstruct->argument;
            currentInstruct++;
            break;
          case SUBCONST:
            accumulator -= currentInstruct->argument;
            currentInstruct++;
            break;
          case MULCONST:
            accumulator *= currentInstruct->argument;
            currentInstruct++;
            break;
          case DIVCONST:
            accumulator /= currentInstruct->argument;
            currentInstruct++;
            break;
          case ADDMEM:
            accumulator += dataMem[currentInstruct->argument];
            currentInstruct++;
            break;
          case SUBMEM:
            accumulator -= dataMem[currentInstruct->argument];
            currentInstruct++;
            break;
          case MULMEM:
            accumulator *= dataMem[currentInstruct->argument];
            currentInstruct++;
            break;
          case DIVMEM:
            accumulator /= dataMem[currentInstruct->argument];
            currentInstruct++;
            break;
          case JUMPREL:
            std::advance(currentInstruct, currentInstruct->argument);
            break;
          case JUMPZERO:
            if(accumulator == 0) {
              std::advance(currentInstruct, currentInstruct->argument);
            }
            else {
              currentInstruct++;
            }
            break;
          case JUMPNZERO:
            if(accumulator != 0) {
              std::advance(currentInstruct, currentInstruct->argument);
            }
            else {
              currentInstruct++;
            }
            break;
          case NOOP:
            currentInstruct++;
            break;
          case HALT:
            stopGritVM = true;
            machineStatus = HALTED;
            break;
          case OUTPUT:
            currentInstruct++;
            break;
          case CHECKMEM:
            if(dataMem.size() < currentInstruct->argument/2) {
              stopGritVM = true;
              machineStatus =  ERRORED;
            }
            else {
              currentInstruct++;
            }
            break;
          case UNKNOWN_INSTRUCTION:
            throw "Should not appear in normal flow";
            break;
      }
      if(stopGritVM) {
        break;
      }
    }
  return machineStatus;
}


std::vector <long> GritVM::getDataMem() { //returns the vecotr dataMem
  return dataMem;
}

STATUS GritVM::reset() { //method to rest AC, List and dataMem
  accumulator = 0;
  instructMem.clear();
  dataMem.clear();
  machineStatus = WAITING;
  return machineStatus;
}
