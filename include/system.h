#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <memory>

#include "process.h"
#include "processor.h"
#include "linux_parser.h"

class System 
{

public:
  Processor& Cpu();                   
  std::vector<Process>& Processes();  
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  std::string Kernel();               
  std::string OperatingSystem();      

 private:
  LinuxParser parser_;
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::string operating_system_;
  std::string kernel_ ;
  int memory_utilization_ = -1;
};

#endif