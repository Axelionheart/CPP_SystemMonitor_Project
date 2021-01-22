#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid){};

int Process::Pid() { return pid_; }

float Process::CpuUtilization() 
{ 
    return LinuxParser::CpuUtilization(pid_); 
}

string Process::Command() 
{ 
    return LinuxParser::Command(pid_);
}

string Process::Ram() 
{ 
    string memory_in_kb = LinuxParser::Ram(pid_); 
    int memory_in_mb = stoi(memory_in_kb) / 1000;

    return to_string(memory_in_mb);
}

string Process::User() 
{  
    std::string uid = LinuxParser::Uid(pid_);
    return LinuxParser::User(uid);
}

float Process::UpTime() 
{ 
    return LinuxParser::UpTime(pid_) / sysconf(_SC_CLK_TCK); 
}

bool Process::operator<(Process& process)  
{ 
   return  CpuUtilization() > process.CpuUtilization(); 
}