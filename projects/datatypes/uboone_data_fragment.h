#ifndef _UBOONE_DATATYPES_DATAFRAGMENT_H
#define _UBOONE_DATATYPES_DATAFRAGMENT_H  1

#include <fstream>
#include <vector>

#define EVENTTRAILER 0xe0000000
#define EVENTHEADER  0xffffffff

namespace gov {
namespace fnal {
namespace uboone {
namespace datatypes {

#if 0
  #include "DAQdata/Fragment.hh" 
  typedef artdaq::RawDataType raw_data_type;
  typedef artdaq::Fragment    raw_data_containter;
#else
  typedef uint16_t raw_data_type;
  template <class T,class Alloc = std::allocator<T>> using raw_data_containter = std::vector<T, Alloc>;
#endif
}  // end of namespace datatypes
}  // end of namespace uboone
}  // end of namespace fnal
}  // end of namespace gov

#endif //_UBOONE_DATATYPES_DATAFRAGMENT_H

