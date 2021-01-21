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
  long int UpTime();                       
  bool operator<(Process const& a);  

 private:
  LinuxParser parser_;
  int pid_ = 0;
  float cpu_utilization_ = 0.0;
  std::string user_name_;
  std::string comandline_args_;
};

#endif