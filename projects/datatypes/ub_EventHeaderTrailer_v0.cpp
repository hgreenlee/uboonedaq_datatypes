#include "ub_EventHeaderTrailer_v0.h"

using namespace gov::fnal::uboone::datatypes;

std::string ub_EventHeader::debugInfo()const noexcept
{
    std::ostringstream os;
    os << "Object " << demangle(typeid(this)) << "."<< std::endl;
    os << std::hex << std::setfill('0') << std::setw(8);
    os << "  RAW["<< raw_data << "]" << std::endl;
    return os.str();
}

std::string ub_EventTrailer::debugInfo()const noexcept
{
    std::ostringstream os;
    os << "Object " << demangle(typeid(this)) << "."<< std::endl;
    os << std::hex << std::setfill('0') << std::setw(8);
    os << "  RAW["<< raw_data << "]" << std::endl;
    return os.str();
}
