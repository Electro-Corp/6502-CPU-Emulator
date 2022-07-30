/*
6502 CPU Emulator
Hex : https://gist.github.com/bit-hack/3be16a5333a50732d3eee85c962157a7
*/
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdint>
#include <vector>

unsigned int reg_A = 0x00;
unsigned int reg_X = 0x00;
unsigned int reg_P = 0x00;
unsigned int reg_S = 0x00;
int reg_PC;

int flag_Z = 0;
int broke = 0;
int memory[64000];
unsigned short opcode;

//int data[] = {0xa9, 0xff, 0x8d, 0x02, 0x60};
//int data[] = {0xa9, 0x01, 0x8d, 0x00 ,0x02,0xa9,0xff,0x8d,0x00,0x08};
//int data[] = {0xa9, 0x01, 0x8d, 0x00, 0x02, 0xa9, 0x05, 0x8d, 0x01, 0x02, 0xa9, 0x08, 0x8d, 0x02, 0x02};

//int data[] = {0xa9, 0xc0, 0xaa, 0xe8, 0x69, 0xc4};

//MORE COMMANDS
int startaddr = 248;
//int data[] = {0xa2,0x08,0xca,0x8e,0x00,0x02,0xe0,0x03,0xd0,0xf8,0x8e,0x01,0x02,0x00};

int opcodes[] = {0xa9,0x8d,0xa2,0x8e,0xaa,0xe8,0xca,0x69,0xe0,0xd0};
///0xa9       LDA        #          SZ         2          2
///0x8d       STA        abs                   4          3
///0xa2       LDX        #          SZ         2          2
///0x8e       STX        abs                   4          3
///0xaa       TAX                   SZ         2          1
///0xe8       INX                   SZ         2          1
///0xca       DEX                   SZ         2          1
///0x69       ADC        #          SVZC       2          2
///0xe0       CPX        #          SZC        2          2
///0xd0       BNE        rel                   2/1*       2
int isopcode(int value);
void loadData();
void dumpMemory();
/*int main(){
    loadData();
    //dumpMemory();
    int i;
    //for(i=0;i<sizeof(data)/ sizeof(data[0]);i++){
    i = 0;
    while(broke == 0){
      i++;
      std::cout<<"AT: "<<memory[startaddr+i]<<std::endl;
      switch (memory[startaddr+i]){
        //LDA
        case 0xa9:
          std::cout<<"LDA COMMAND; VALUE: "<<data[i+1]<<std::endl;
          while(isopcode(memory[startaddr+i]) != 1){
            reg_A = reg_A+memory[startaddr+i];
            i++;
          }
          i = i - 1;
          break;
        //LDX
        case 0xa2:
          std::cout<<"LDX COMMAND; VALUE: "<<data[i+1]<<std::endl;
          i++;
          while(isopcode(memory[startaddr+i]) != 1){
                        
            reg_X = reg_X + memory[startaddr+i];
            i++;
          }
          i = i - 1;          
          break;
        //STA
        case 0x8d:{
          int addr;
          while(isopcode(memory[startaddr+i]) != 1 || i>62918){
            if(i+1>sizeof(data)/ sizeof(data[0])){
              break;
            }
            std::cout<<"BOI: "<<memory[startaddr+i]<<std::endl;
            addr = addr+memory[startaddr+i];
            i++;
          }
          std::cout<<"STA COMMAND; ADDR: "<<addr<<std::endl;
          memory[addr] = reg_A;
          std::cout<<memory[addr]<<std::endl;
          i++;
          }
          break;
        //STX      
        case 0x8e:{
          int addr;
          //addr = 0x00;
          i++;
          while(isopcode(memory[startaddr+i]) != 1 || i>62918){
           if(i+1>sizeof(data)/ sizeof(data[0])){
              break;
            }
            addr = addr+memory[startaddr+i];
            i++;
          }
          std::cout<<"STX COMMAND; ADDR: "<<addr<<std::endl;
          memory[addr] = reg_X;
          std::cout<<memory[addr]<<std::endl;
          //i++;
          }
          break;
        //BNE
        case 0xd0:{}
          int addr;
          //addr = 0x00;
          i++;
          while(isopcode(memory[startaddr+i]) != 1 || i>62918){
           if(i+1>sizeof(data)/ sizeof(data[0])){
              break;
            }
            addr = addr+memory[startaddr+i];
            i++;
          }
          std::cout<<"BNE COMMAND; ADDR: "<<addr<<std::endl;
          if(flag_Z == 0){
            startaddr = addr;
            i = 0;
          }
          break;
        case 0xaa:{}
          std::cout<<"TAX COMMAND"<<std::endl;
          reg_X = reg_A;
          break;
        //increment X
        case 0xe8:
          std::cout<<"INX COMMAND"<<std::endl;
          reg_X = reg_X + 1;
          break;
        //decrement x
        case 0xca:
          std::cout<<"DEX COMMAND"<<std::endl;
          reg_X = reg_X - 1;
          break;
        //ADC
        case 0x69:{
          int realdata = data[i+1];
          std::cout<<"ADC COMMAND: VALUE: "<<realdata<<std::endl;
          reg_A = realdata + reg_A;
          i++;
          }
          break;
        //CPX
        case 0xe0:{
          int realdata = data[i+1];
          std::cout<<"CPX COMMAND; ADDR: "<<realdata<<std::endl;
          if(reg_X = memory[realdata]){
            flag_Z = 1;
          }else{
            flag_Z = 0;
          }
          }
          break;
        case 0x00:{
          broke = 1;
        }
        // default:
        //   std::cout<<"Unrecognized"<<std::endl;
        //   break;
      }
      std::cout<<"A REGISTER: "<<reg_A<<std::endl;
      std::cout<<"X REGISTER: "<<reg_X<<std::endl;
      std::cout<<"Z FLAG: "<<flag_Z<<std::endl;
      std::cout<<"=============================="<<std::endl;
    }
  dumpMemory();
}*/
int main(){
  loadData();
  dumpMemory();
  
}
int isopcode(int value){
  int i;
  int isopcodereal = 0;
  for(i=0;i<sizeof(opcodes)/sizeof(opcodes[0]);i++){
    if(value == opcodes[i]){
      isopcodereal = 1;
      break;
    }
  }
  return isopcodereal;
}
void loadData(){
  int i;
  for(i=0;i<64000;i++){
    memory[i] = 0xea;  
  }
  // std::ifstream file;
  // file.open("/home/runner/6502-CPU-Emulator/test.bin",std::ios::in|std::ios::binary);
  // int size = 1;
  // std::vector<uint8_t> memblock(size);
  // file.seekg(0, std::ios::beg);
  // file.read(reinterpret_cast<char*>(memblock.data()), size); 

  FILE* file = fopen("/home/runner/6502-CPU-Emulator/test.bin", "rb");
  char buf[8];
  for (i=0;i<64000;i++){
    fread(buf, 1, 8, file);
  }
  
  // for(i=0;i<sizeof(data) / sizeof(data[0]);i++){
  //   // char full[20];
  //   // while(isopcode(memory[i+startaddr]) != 1){
  //   //   full[]
  //   // }
  //   memory[i+startaddr] = data[i];
  //   std::cout<<data[i]<<std::endl;
  // }
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
