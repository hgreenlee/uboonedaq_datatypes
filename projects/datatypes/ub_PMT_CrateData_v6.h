#ifndef _UBOONE_TYPES_MARKEDPMTRATEDATA_V6_H
#define _UBOONE_TYPES_MARKEDPMTRATEDATA_V6_H 1


#include "ub_MarkedRawCrateData.h"

#include "ub_PMT_CardData_v6.h"
#include "uboone_data_fragment_metadata.h"

namespace gov {
namespace fnal {
namespace uboone {
namespace datatypes {

class ub_PMT_CrateData_v6 final: public ub_MarkedRawCrateData<ub_PMT_CardData_v6> {
public:
    typedef ub_PMT_CardData_v6::ub_CrateHeader ub_CrateHeader_t;
    ub_PMT_CrateData_v6(ub_RawData const rawdata, bool initializeHeaderFromRawData=false);
    bool compare(ub_PMT_CrateData_v6 const & crate_data, bool do_rethrow=false) const throw(datatypes_exception);

    ub_PMT_CrateData_v6() = delete;
    ub_PMT_CrateData_v6& operator=(ub_PMT_CrateData_v6 const &) = delete;
    
    static constexpr auto typeName="TPC";
};


}  // end of namespace datatypes
}  // end of namespace uboone
}  // end of namespace fnal
}  // end of namespace gov


#endif //_UBOONE_TYPES_MARKEDPMTRATEDATA_V6_H
