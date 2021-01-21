#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;

string Format::ElapsedTime(long seconds)
{ 
    int minutes, hours;
    minutes = seconds / 60;
    seconds = seconds % 60;
    hours = minutes / 60;
    minutes = minutes % 60;

    std::stringstream stream;

    stream << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << 
    std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    
    return stream.str();
}
