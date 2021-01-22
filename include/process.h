#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "linux_parser.h"

class Process 
{
 public:
  Process(int pid);
  int Pid();                               
  std::string User();                      
  std::string Command();                   
  float CpuUtilization();                  
  std::string Ram();                       
  float UpTime();                       
  bool operator<(Process& p);  

 private:
  int pid_ = 0;
};

#endif