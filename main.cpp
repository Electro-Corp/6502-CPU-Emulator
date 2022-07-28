/*
INSTRUCTION SET REFRENCE: https://sites.google.com/site/6502asembly/6502-instruction-set/6502-instruction-set-by-alphabetical-order
*/
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
int reg_Acc = 0x00;
int reg_X = 0x00;
int reg_Y = 0x00;
// auto reg_X_index;
// auto reg_Y_index;
// auto reg_stack_pointer;

int line = 0;
void loadvaluereg(int value);
void loadvalueX(int value);
void loadvalueY(int value);
std::string getCommand(std::string fullCommand);
std::string getValue(std::string fullCommand);
void dumpMemory();
//const size_t fixedListSize(60000);

//std::list<int> memoryvalues(fixedListSize);
//std::list<int>::iterator memint;
int memory[60000];
int main(int args, char **argv){
  std::list <std::string> asmcodes;
  asmcodes.push_back("lda #$ff");
  asmcodes.push_back("sta $6002");
  asmcodes.push_back("ldx #$0a");
  asmcodes.push_back("stx $6000");
  std::string command;
  std::cout<<"CPU Execution Start"<<std::endl;
  for(std::list<std::string>::iterator i = asmcodes.begin(); i != asmcodes.end();i++){
    command = getCommand(*i);
    std::cout<<"Current Command: "<<command<<std::endl;
    std::string value = getValue(*i);
    value.erase (std::remove(value.begin(), value.end(), '$'), value.end());
    value.erase (std::remove(value.begin(), value.end(), '#'), value.end());
    
    //value  = value.erase(std::remove(value.begin(), value.end(), '$'), value.end());
    if(command == "lda"){
      value = "0x" + value;
      std::cout<<"lda instruction: "<< value <<std::endl;
      int ldafinal = std::stoi(value, 0, 16);
      loadvaluereg(ldafinal);
    }
     if(command == "ldx"){
      value = "0x" + value;
      std::cout<<"ldx instruction: "<< value <<std::endl;
      int ldxfinal = std::stoi(value, 0, 16);
      loadvalueX(ldxfinal);
    }
     if(command == "ldy"){
      value = "0x" + value;
      std::cout<<"ldy instruction: "<< value <<std::endl;
      int ldyfinal = std::stoi(value, 0, 16);
      loadvalueY(ldyfinal);
    }
    if(command == "sta"){
      std::cout<<"sta instruction: "<< value <<std::endl;
      int finalval = std::stoi(value, 0, 16);
      memory[finalval] = reg_Acc;
    }
    if(command == "stx"){
      std::cout<<"stx instruction: "<< value <<std::endl;
      int finalval = std::stoi(value, 0, 16);
      memory[finalval] = reg_X;
    }
    if(command == "sty"){
      std::cout<<"sty instruction: "<< value <<std::endl;
      int finalval = std::stoi(value, 0, 16);
      memory[finalval] = reg_Y;
    }
    std::cout<<"Accelerator register: "<<std::hex<<reg_Acc<<std::endl;
    std::cout<<"X register: "<<std::hex<<reg_X<<std::endl;
    std::cout<<"Y register: "<<std::hex<<reg_Y<<std::endl;
    std::cout<<"================================="<<std::endl;
  }
  dumpMemory();
  return 0;
}
void loadvaluereg(int value){
  reg_Acc = value;
}
void loadvalueX(int value){
  reg_X = value;
}
void loadvalueY(int value){
  reg_Y = value;
}
std::string getCommand(std::string fullCommand){
  if (fullCommand.find("lda") != std::string::npos) {
      return "lda";
  }
  if (fullCommand.find("ldx") != std::string::npos) {
      return "ldx";
  }
  if (fullCommand.find("ldy") != std::string::npos) {
      return "ldy";
  }
  if (fullCommand.find("sta") != std::string::npos) {
      return "sta";
  }
  if (fullCommand.find("stx") != std::string::npos) {
      return "stx";
  }
  if (fullCommand.find("sty") != std::string::npos) {
      return "sty";
  }
}
std::string getValue(std::string fullCommand){
  return fullCommand.substr(fullCommand.find(" ") + 1);
}
void dumpMemory(){
	std::ofstream dumpFile;
	dumpFile.open("/home/$USERNAME/6502log", std::ios::app);
	if(dumpFile.is_open()){
	for (int i = 0; i < 60000;i++){
		//std::cout<<"WRITING: "<<i<<std::endl;
		dumpFile << (memory[i])<<std::endl;
	}}
	else{
		std::cout<<"Error dumping memory, file is not open. Error occured"<<std::endl;
	}
	dumpFile.close();
}
