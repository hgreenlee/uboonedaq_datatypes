#ifndef _UBOONETYPES_CONSTANTS_H
#define _UBOONETYPES_CONSTANTS_H

namespace gov {
namespace fnal {
namespace uboone {
namespace datatypes {

  //Readout options for levels of detail in the data readout/readin.
  enum {
    IO_GRANULARITY_CRATE,
    IO_GRANULARITY_CARD,
    IO_GRANULARITY_CHANNEL
  };
  
  //Crate types.
  enum ub_SEBFragmentType{
    TPC_TRIGGERED,
    TPC_CONTINUOUS,
    PMT_TRIGGERED,
    PMT_CONTINUOUS,
    TRIGGER,
    LASER   
  };

namespace constants
{
/*
  enum VERSION{
    v6_00_00 = 6,
    v5_00_00 = 5
  };
*/
  const int VERSION = 5; // A dB query eventually. // NJT: shouldn't this match major version number for datatypes package?
    // ... other related constants

} // namespace constants


}
}
}
}

#endif // _UBOONETYPES_CONSTANTS_H
