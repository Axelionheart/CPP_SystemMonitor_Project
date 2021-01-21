#include <string>

class CPUInfo
{
public:

enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};

virtual std::vector<float> CpuUtilization() = 0;
virtual float CpuUtilization(int pid) = 0 ;
};