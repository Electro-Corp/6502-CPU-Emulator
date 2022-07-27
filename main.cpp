#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>

int reg_Acc = 0x00;
// auto reg_X_index;
// auto reg_Y_index;
// auto reg_stack_pointer;

int line = 0;
void loadvalue(int value);
std::string getCommand(std::string fullCommand);
std::string getValue(std::string fullCommand);
std::list<int> memory;
int main(int args, char **argv){
  std::list <std::string> asmcodes;
  asmcodes.push_back("lda #$ff");
  asmcodes.push_back("sta $6002");
  std::string command;
  std::cout<<"CPU Execution Start"<<std::endl;
  for(std::list<std::string>::iterator i = asmcodes.begin(); i != asmcodes.end();i++){
    command = getCommand(*i);
    std::cout<<"Current Command: "<<command<<std::endl;
    std::string value = getValue(*i);
    value.erase (std::remove(value.begin(), value.end(), '$'), value.end());
    value.erase (std::remove(value.begin(), value.end(), '#'), value.end());
    
   // value  = value.erase(std::remove(value.begin(), value.end(), '$'), value.end());
    if(command == "lda"){
      value = "0x" + value;
      std::cout<<"lda instruction: "<< value <<std::endl;
      int ldafinal = std::stoi(value, 0, 16);
      loadvalue(ldafinal);
    }
    if(command == "sta"){
      std::cout<<"sta instruction: "<< value <<std::endl;
      int finalval = std::stoi(value, 0, 16);
      memory.insert(reg_Acc,finalval);
    }
    std::cout<<"Accelerator register: "<<std::hex<<reg_Acc<<std::endl;
  }
  return 0;
}
void loadvalue(int value){
  reg_Acc = value;
}
std::string getCommand(std::string fullCommand){
  if (fullCommand.find("lda") != std::string::npos) {
      return "lda";
  }
}
std::string getValue(std::string fullCommand){
  return fullCommand.substr(fullCommand.find(" ") + 1);
}