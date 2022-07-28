/*
6502 CPU Emulator
*/
#include <iostream>
#include <string>
#include <list>
#include <fstream>

int reg_A = 0x00;
int reg_X = 0x00;
int reg_P = 0x00;
int reg_S = 0x00;
int reg_PC;

int memory[64000];
unsigned short opcode;

int data[] = {0xa9, 0xff, 0x8d, 0x02, 0x60};

void loadData();
void dumpMemory();
int main(){
    loadData();
    int i;
    for(i=0;i<sizeof(data)/ sizeof(data[0]);i++){
      switch (data[i]){
        case 0xa9:
          std::cout<<"LDA COMMAND"<<std::endl;
          reg_X = data[i+1];
          i++;
          break;
        case 0x8d:
          std::cout<<"STA COMMAND"<<std::endl;
          memory[data[i+1]] = reg_X;
          std::cout<<memory[data[i+1]]<<std::endl;
          i++;
        default:
          std::cout<<"Unrecognized"<<std::endl;
          break;
      }
    }
  dumpMemory();
}
void loadData(){
  int i;
  for(i=0;i<sizeof(data) / sizeof(data[0]);i++){
    memory[i] = data[i];
    std::cout<<&data[i]<<std::endl;
  }
}
void dumpMemory(){
	std::ofstream dumpFile;
	dumpFile.open("/home/runner/6502-CPU-Emulator/6502log", std::ios::app);
  std::cout<<"Dumping memory, please wait..."<<std::endl;
	if(dumpFile.is_open()){
	for (int i = 0; i<sizeof(data) / sizeof(data[0]);i++){
		dumpFile << (memory[i])<<std::endl;
	}}
	else{
		std::cout<<"Error dumping memory, file is not open. Error occured"<<std::endl;
	}
  std::cout<<"Finished."<<std::endl;
	dumpFile.close();
}
