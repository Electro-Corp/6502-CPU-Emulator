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

//int data[] = {0xa9, 0xff, 0x8d, 0x02, 0x60};
//int data[] = {0xa9, 0x01, 0x8d, 0x00 ,0x02,0xa9,0xff,0x8d,0x00,0x08};
//int data[] = {0xa9, 0x01, 0x8d, 0x00, 0x02, 0xa9, 0x05, 0x8d, 0x01, 0x02, 0xa9, 0x08, 0x8d, 0x02, 0x02};

int data[] = {0xa9, 0xc0, 0xaa, 0xe8, 0x69, 0xc4};

std::list<int> opcodes = {0xa9,0x8d};

void loadData();
void dumpMemory();
int main(){
    loadData();
    int i;
    for(i=0;i<sizeof(data)/ sizeof(data[0]);i++){
      switch (data[i]){
        case 0xa9:
          std::cout<<"LDA COMMAND; VALUE: "<<data[i+1]<<std::endl;
          reg_A = data[i+1];
          i++;
          break;
        case 0x8d:{
          int addr = data[i+1]+data[i+2];
          std::cout<<"STA COMMAND; ADDR: "<<addr<<std::endl;
          memory[addr] = reg_A;
          std::cout<<memory[addr]<<std::endl;
          i++;
          }
          break;
          
        case 0xaa:{}
          std::cout<<"TAX COMMAND"<<std::endl;
          reg_X = reg_A;
          break;
        case 0xe8:
          std::cout<<"INX COMMAND"<<std::endl;
          reg_X = reg_X + 1;
          break;
        case 0x69:
          int realdata = data[i+1]+data[i+2];
          reg_A = realdata + reg_A;
          i++;
          break;
        // default:
        //   std::cout<<"Unrecognized"<<std::endl;
        //   break;
      }
      std::cout<<"A REGISTER: "<<reg_A<<std::endl;
      std::cout<<"=============================="<<std::endl;
    }
  dumpMemory();
}
void loadData(){
  int i;
  for(i=0;i<sizeof(data) / sizeof(data[0]);i++){
    //memory[i] = data[i];
    std::cout<<data[i]<<std::endl;
  }
}
void dumpMemory(){
	std::ofstream dumpFile;
	dumpFile.open("/home/runner/6502-CPU-Emulator/6502log", std::ios::app);
  std::cout<<"Dumping memory, please wait..."<<std::endl;
	if(dumpFile.is_open()){
	for(int i=0;i<sizeof(memory) / sizeof(memory[0]);i++){
		dumpFile << memory[i]<<std::endl;
	  }
  }
	else{
		std::cout<<"Error dumping memory, file is not open. Error occured"<<std::endl;
	}
  std::cout<<"Finished."<<std::endl;
	dumpFile.close();
}
