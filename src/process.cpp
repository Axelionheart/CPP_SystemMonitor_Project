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
    cpu_utilization_ = parser_.CpuUtilization(pid_);
    return cpu_utilization_; 
}

string Process::Command() 
{ 
    return parser_.Command(pid_);
}

string Process::Ram() 
{ 
    string memory_in_kb = parser_.Ram(pid_); 
    int memory_in_mb = stoi(memory_in_kb) / 1000;

    return to_string(memory_in_mb);
}

string Process::User() 
{  
    std::string uid = parser_.Uid(pid_);
    user_name_ = parser_.User(uid);
    return user_name_;
}

long int Process::UpTime() 
{ 
    return parser_.UpTime(pid_) / sysconf(_SC_CLK_TCK); 
}

bool Process::operator<(Process const& process)  
{ 
   return  cpu_utilization_ <  process.cpu_utilization_; 
}