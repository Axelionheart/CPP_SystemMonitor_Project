#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

#include "system_info.h"
#include "cpu_info.h"
#include "process_info.h"

class LinuxParser : public SystemInfo, public CPUInfo, public ProcessInfo
{
public:
// Paths
    const std::string kProcDirectory{"/proc/"};
    const std::string kCmdlineFilename{"/cmdline"};
    const std::string kCpuinfoFilename{"/cpuinfo"};
    const std::string kStatusFilename{"/status"};
    const std::string kStatFilename{"/stat"};
    const std::string kUptimeFilename{"/uptime"};
    const std::string kMeminfoFilename{"/meminfo"};
    const std::string kVersionFilename{"/version"};
    const std::string kOSPath{"/etc/os-release"};
    const std::string kPasswordPath{"/etc/passwd"};
    const int kProcessUptimeIndex = 22;
    const int kProcessCpuUtilizationIndex = 14;

// ProcessInfo implementation
    float MemoryUtilization() override;
    long UpTime() override;
    std::vector<int> Pids() override;
    int TotalProcesses() override;
    int RunningProcesses() override;
    std::string OperatingSystem() override;
    std::string Kernel() override;

// CPUInfo implementation
    std::vector<float> CpuUtilization() override;
    float CpuUtilization(int pid) override;

// ProcessInfo implementation
    std::string Command(int pid) override;
    std::string Ram(int pid) override;
    std::string Uid(int pid) override;
    std::string User(std::string uid) override;
    long int UpTime(int pid) override;

private:
    struct MemoryData
    {
        float mem_total = -1, mem_free = -1;
    };

    bool IsMemoryDataCollected(MemoryData& memory) const;
    std::vector<long> CpuTimes(const int pid);
}; 

#endif