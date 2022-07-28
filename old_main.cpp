//https://sites.google.com/site/6502asembly/6502-instruction-set/6502-instruction-set-by-alphabetical-order
//https://www.pagetable.com/c64ref/6502/
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#define MEMORY 10000
//registers
int reg_Acc = 0x00;
int reg_X = 0x00;
int reg_Y = 0x00;

int line = 0;
//function defs
void loadvaluereg(int value);
void loadvalueX(int value);
void loadvalueY(int value);
std::string getCommand(std::string fullCommand);
std::string getValue(std::string fullCommand);
void dumpMemory();
//memory
int memory[600000];
//stuff
int ishex = 0;
int isaddr = 0;
int main(int args, char **argv){
  std::list <std::string> asmcodes;
  // asmcodes.push_back("lda #$ff");
  // asmcodes.push_back("sta $6002");
  // asmcodes.push_back("ldx #$0a");
  // asmcodes.push_back("stx $6000");
  // asmcodes.push_back("and $ff");
  // asmcodes.push_back("lda #$ff");
  // asmcodes.push_back("sta $6002");
  // asmcodes.push_back("adc #$0a");
  // asmcodes.push_back("lda #$0a");
  // asmcodes.push_back("sta $1");
  /*
LDA #$c0  ;Load the hex value $c0 into the A register
TAX       ;Transfer the value in the A register to X
INX       ;Increment the value in the X register
ADC #$c4  ;Add the hex value $c4 to the A register
BRK       ;Break - we're done
    */
  asmcodes.push_back("LDA #$c0");
  asmcodes.push_back("TAX");
  asmcodes.push_back("INX");
  asmcodes.push_back("ADC #$c4");
  asmcodes.push_back("BRK");
  //asmcodes.push_back("sta $0202");

  //asmcodes.push_back("jmp $3000");
  std::string command;
  int c;
  //for(c = 0;c!=10000-asmcodes.size();c++){
  //  asmcodes.push_back("nop");
 // }

  

  std::cout<<"CPU Execution Start"<<std::endl;
  for(std::list<std::string>::iterator i = asmcodes.begin(); i != asmcodes.end() ;i++){
    command = getCommand(*i);
    std::cout<<"Current Command: "<<command<<std::endl;
    std::string value = getValue(*i);
    if(value.find("$") != std::string::npos){isaddr = 1;}else{isaddr = 0;};
    if(value.find("#") != std::string::npos){ishex = 1;}else{ishex = 0;};
    value.erase (std::remove(value.begin(), value.end(), '$'), value.end());
    value.erase (std::remove(value.begin(), value.end(), '#'), value.end());
    if(command == "lda"){
      value = "0x" + value;
      std::cout<<"lda instruction: "<< value <<std::endl;
      int ldafinal = std::stoi(value, 0, 16);
      if(isaddr == 1 && ishex != 1){
        ldafinal = memory[ldafinal];
      }
      loadvaluereg(ldafinal);
    }
     if(command == "ldx"){
      value = "0x" + value;
      std::cout<<"ldx instruction: "<< value <<std::endl;
      int ldxfinal = std::stoi(value, 0, 16);
       if(isaddr == 1 && ishex != 1){
        ldxfinal = memory[ldxfinal];
      }
      loadvalueX(ldxfinal);
    }
     if(command == "ldy"){
      value = "0x" + value;
      std::cout<<"ldy instruction: "<< value <<std::endl;
      int ldyfinal = std::stoi(value, 0, 16);
      if(isaddr == 1 && ishex != 1){
        ldyfinal = memory[ldyfinal];
      }
      loadvalueY(ldyfinal);
    }
    if(command == "sta"){
      std::cout<<"sta instruction: "<< value <<std::endl;
      int finalval = std::stoi(value, 0, 16);
      if(isaddr == 1 && ishex != 1){
        finalval = memory[finalval];
      }
      memory[finalval] = reg_Acc;
      std::cout<<"Memory writtin: "<<memory[finalval]<<std::endl;
    }
    if(command == "stx"){
      std::cout<<"stx instruction: "<< value <<std::endl;
      int finalval = std::stoi(value, 0, 16);
      if(isaddr == 1 && ishex != 1){
        finalval = memory[finalval];
      }
      memory[finalval] = reg_X;
    }
    if(command == "sty"){
      std::cout<<"sty instruction: "<< value <<std::endl;
      int finalval = std::stoi(value, 0, 16);
      if(isaddr == 1 && ishex != 1){
        finalval = memory[finalval];
      }
      memory[finalval] = reg_Y;
    }
    if(command == "adc"){
      std::cout<<"adc instruction: "<<value<<std::endl;
      int finalval = std::stoi(value, 0, 16);
      if(isaddr == 1 && ishex != 1){
        finalval = memory[finalval];
      }
      reg_Acc = reg_Acc + finalval;
    }
    if(command == "and"){
      std::cout<<"and instruction: "<<value<<std::endl;
      
      int finalval = std::stoi(value, 0, 16);
      if(isaddr == 1 && ishex != 1){
        finalval = memory[finalval];
      }
      if(reg_Acc == finalval){
      	reg_Acc = 1;
      }else{
      	reg_Acc = 0;
      }
    }
    if(command == "tax"){
      
      reg_X = reg_Acc;
    }
    if(command == "jmp"){
      std::cout<<"jmp instruction: "<<value<<std::endl;
      int finalval = std::stoi(value, 0, 16);
     if(isaddr == 1 && ishex != 1){
        finalval = memory[finalval];
      }
      i =  asmcodes.begin();
      if(asmcodes.size() > finalval){
        std::advance(i,finalval);
      }
    }
    if(command == "nop"){
      std::cout<<"No operation"<<std::endl;
    }
    if(command == "inx"){
      reg_X = reg_X + 1;
    }
    if(command == "brk"){
      break;
    }
    std::cout<<"Accelerator register: "<<std::hex<<reg_Acc<<std::endl;
    std::cout<<"X register: "<<std::hex<<reg_X<<std::endl;
    std::cout<<"Y register: "<<std::hex<<reg_Y<<std::endl;
    //std::cout<<"Value was adress: "<<(ishex+isaddr)/2  <<std::endl;
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
  transform(fullCommand.begin(), fullCommand.end(), fullCommand.begin(), ::tolower);
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
  if (fullCommand.find("adc") != std::string::npos) {
      return "adc";
  }
  if (fullCommand.find("and") != std::string::npos) {
      return "and";
  }
  if (fullCommand.find("jmp") != std::string::npos) {
      return "jmp";
  }
  if (fullCommand.find("nop") != std::string::npos) {
      return "nop";
  }
  if (fullCommand.find("tax")!= std::string::npos) {
      return "tax";
  }
  if (fullCommand.find("inx")!= std::string::npos) {
      return "inx";
  }
  if (fullCommand.find("brk")!= std::string::npos) {
      return "brk";
  }
  
}
std::string getValue(std::string fullCommand){
  return fullCommand.substr(fullCommand.find(" ") + 1);
}
void dumpMemory(){
	std::ofstream dumpFile;
	dumpFile.open("/home/runner/6502-CPU-Emulator/6502log", std::ios::app);
  std::cout<<"Dumping memory, please wait..."<<std::endl;
	if(dumpFile.is_open()){
	for (int i = 0; i < 60000;i++){
		//std::cout<<"WRITING: "<<i<<std::endl;
		dumpFile << (memory[i])<<std::endl;
	}}
	else{
		std::cout<<"Error dumping memory, file is not open. Error occured"<<std::endl;
	}
  std::cout<<"Finished."<<std::endl;
	dumpFile.close();
}
