#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "linux_parser.h"

class Processor 
{
 public:
  float Utilization();  

 private:
  float GetIdleTime() const;
  float GetTotalTime() const;

  const int idle_time_index = 3;
  float prev_idle_time_ = 0;
  float prev_total_time_ = 0;
  std::vector<float> cpu_times_;
};

#endif