#include <string>

class ProcessInfo
{
public:
    virtual std::string Command(int pid) = 0;
    virtual std::string Ram(int pid) = 0;
    virtual std::string Uid(int pid) = 0;
    virtual std::string User(std::string uid) = 0;
    virtual long int UpTime(int pid) = 0;
};