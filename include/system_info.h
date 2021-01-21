#include <string>
#include <vector>

class SystemInfo
{
public:
    virtual float MemoryUtilization() = 0;
    virtual long UpTime() = 0;
    virtual std::vector<int> Pids() = 0;
    virtual int TotalProcesses() = 0;
    virtual int RunningProcesses() = 0;
    virtual std::string OperatingSystem() = 0;
    virtual std::string Kernel() = 0;
};