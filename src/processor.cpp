#include <string>
#include <fstream>
#include <numeric>

#include "processor.h"

using std::string;
using std::stof;

float Processor::Utilization() 
{ 
  cpu_times_ = parser_.CpuUtilization();

  const float idle_time = GetIdleTime();
  const float total_time = GetTotalTime();
  
  const float delta_idle_time = idle_time - prev_idle_time_;
  const float delta_total_time = total_time - prev_total_time_;

  prev_total_time_= total_time;
  prev_idle_time_ = idle_time;

  return 1.0 - delta_idle_time/delta_total_time;
}

float Processor::GetIdleTime() const
{
   return cpu_times_[idle_time_index];
}

float Processor::GetTotalTime() const
{
  return std::accumulate(cpu_times_.begin(),cpu_times_.end(),0);
}