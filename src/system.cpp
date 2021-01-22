#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::sort;

Processor& System::Cpu(){ return cpu_; }

vector<Process>& System::Processes()
{ 
    processes_.clear();
    auto processes_pid = LinuxParser::Pids();

    for (auto& pid : processes_pid)
    {
       processes_.emplace_back(Process(pid));     
    }

    sort(processes_.begin(), processes_.end());

    return processes_;     
}

std::string System::Kernel() 
{ 
    if(kernel_.length() > 0)
        return kernel_;

    kernel_ = LinuxParser::Kernel();   
    return kernel_;
}

float System::MemoryUtilization()
{ 
    return LinuxParser::MemoryUtilization();
}

std::string System::OperatingSystem()
{ 
    if(operating_system_.length() > 0)
        return operating_system_;
    
    operating_system_ = LinuxParser::OperatingSystem();
    return operating_system_;    
} 

int System::RunningProcesses() 
{ 
    return LinuxParser::RunningProcesses();
}

int System::TotalProcesses() 
{  
    return LinuxParser::TotalProcesses();
}

long int System::UpTime() 
{ 
    return LinuxParser::UpTime();
}