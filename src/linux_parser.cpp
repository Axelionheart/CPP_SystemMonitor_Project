#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unistd.h>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() 
{
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel() 
{
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) 
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() 
{
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() 
{ 
  string line, key, value;
  MemoryData memory_data = {};

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line) && !IsMemoryDataCollected(memory_data)) 
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value) 
      {
        if(key == "MemTotal:") 
        {
          memory_data.mem_total = stof(value);
          break;
        }
        
        if(key == "MemFree:")
        {
          memory_data.mem_free = stof(value); 
          break;
        }
      }
    }
  }  

  return memory_data.mem_free / memory_data.mem_total;  
}

bool LinuxParser::IsMemoryDataCollected(MemoryData& data) const
{
  if(data.mem_free < 0)
    return false;

  if(data.mem_total < 0)
    return false;

  return true;
}

long LinuxParser::UpTime() 
{ 
  string line, key, value;
  long uptime = 0;

  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) 
  {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      linestream >> uptime;
  }  

  return uptime;
}

std::vector<float> LinuxParser::CpuUtilization() 
{
   std::vector<float> cpu_times = {};
   std::ifstream filestream(kProcDirectory + kStatFilename);
   std::string line, time;

    if(filestream.is_open())
    {
      filestream.ignore(5, ' '); // Skip the 'cpu' prefix.
      std::getline(filestream, line);
      std::istringstream linestream(line);

      while(linestream >> time)
        cpu_times.push_back(std::stof(time));
      
    }  

    return cpu_times;
}

float LinuxParser::CpuUtilization(int pid) 
{ 
   std::vector<long> cpu_times = CpuTimes(pid);

   long utime = cpu_times[0];
   long stime = cpu_times[1];
   long cutime = cpu_times[2];
   long cstime = cpu_times[3];

   long start_time = UpTime(pid);
   long system_uptime = UpTime();

   long total_process_time = utime + stime;
   total_process_time = total_process_time + cutime + cstime;

   long seconds = system_uptime - (start_time / sysconf(_SC_CLK_TCK)) ;

   return 100 * ((total_process_time / sysconf(_SC_CLK_TCK)) / seconds);
}

std::vector<long> LinuxParser::CpuTimes(const int pid)
{
   string line, value;
   int value_count = 1;
   std::vector<long> cpu_times = {};

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line) && !(value_count > 18)) 
    {
      std::istringstream linestream(line);
      while (linestream >> value) 
      {
        if(value_count == 18)
          break;
          
        if(value_count >= kProcessCpuUtilizationIndex) 
        {
          cpu_times.emplace_back(std::stol(value));
        }
        ++value_count;
      }
    }
  }
  return cpu_times;
}

int LinuxParser::TotalProcesses() 
{ 
  string line, key, value;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value) 
      {
        if(key == "processes") 
        {
          return stoi(value);
        }
      }
    }
  }
  return 0;
}

int LinuxParser::RunningProcesses() 
{ 
  string line, key, value;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value) 
      {
        if(key == "procs_running") 
        {
          return stoi(value);
        }
      }
    }
  }
  return 0;
}

string LinuxParser::Command(int pid) 
{ 
  string line;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) 
  {
    std::getline(filestream, line);    
    std::istringstream linestream(line);     
    return linestream.str();
  }
  return string{}; 
}

string LinuxParser::Ram(int pid) 
{ 
  string line, key, value;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value) 
      {
        if(key == "VmSize:") 
        {
          return value;
        }
      }
    }
  }
  return string{};
}

string LinuxParser::Uid(int pid) 
{ 
  string line, key, value;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while (linestream >> key >> value) 
      {
        if(key == "Uid:") 
        {
          return value;
        }
      }
    }
  }
  return string{};
}

string LinuxParser::User(string uid)
{ 
  string name, variable, Uid, line;

  std::ifstream filestream(kPasswordPath);

  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> name >> variable >> Uid) 
      {
        if(Uid == uid) 
        {
          return name;
        }
      }
    }
  }
  return string{};
}

long int LinuxParser::UpTime(int pid) 
{ 
   string line, value;
   int value_count = 1;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) 
  {
    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      while (linestream >> value) 
      {
        if(value_count == kProcessUptimeIndex) 
        {
          return std::stol(value);
        }
        ++value_count;
      }
    }
  }
  return 0;
}