#include "ub_ChannelHeaderTrailer_v0.h"

using namespace gov::fnal::uboone::datatypes;	

std::string ub_ChannelHeader::debugInfo()const
{
	std::ostringstream os;
	os << "Object " << demangle(typeid(this)) << "."<< std::endl;
	os << std::hex << std::setfill('0') << std::setw(2);
	os << "  Channel[" << channel_number<< "], Marker["  << header_mark;
	os << "], RAW["<< std::setw(4)<< channel_mark << "]" << std::endl;
	return os.str();
}

std::string ub_ChannelTrailer::debugInfo()const
{
	std::ostringstream os;
	os << "Object " << demangle(typeid(this))<< "."<< std::endl;
	os << std::hex << std::setfill('0') << std::setw(2);
	os << "  Channel[" << channel_number<< "], Marker["  << trailer_mark;
	os << "], RAW["<< std::setw(4)<< channel_mark << "]" << std::endl;
	return os.str();
}
