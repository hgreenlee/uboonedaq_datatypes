#ifndef _UBOONETYPES_EVENTRECORD_H
#define _UBOONETYPES_EVENTRECORD_H


#include <assert.h>
#include <numeric>
#include <atomic>
#include "evttypes.h"
#include "constants.h"
#include "boostSerialization.h"
#include "raw_data_access.h"

#include "ub_FEMBeamTriggerOutput.h"

/***
    The ub_EventRecord is meant to house all of the components of the
    final data format as it leaves the assembler and is written to
    disk. The data will be written as a boost binary_archive, so
    we may version different pieces accordingly. Along with all the
    (independently) serialized headers, we have a map that pairs
    crate headers and crate data.
 ***/


namespace gov {
namespace fnal {
namespace uboone {
namespace datatypes {

using namespace gov::fnal::uboone::datatypes;

class ub_EventRecord final {

public:
    typedef raw_data_container<raw_data_type>   raw_fragment_data_t;
    typedef raw_fragment_data_t::value_type      fragment_value_type_t;

    typedef std::tuple<raw_fragment_data_t,
            std::unique_ptr<ub_RawData>,
            std::unique_ptr<tpc_crate_data_t>> tpc_crate_data_tuple_t;
    typedef std::map<int,tpc_crate_data_tuple_t> tpc_seb_map_t;

    typedef std::map<int,tpc_crate_data_t const&> tpc_map_t;
    
    typedef std::tuple<raw_fragment_data_t,
            std::unique_ptr<ub_RawData>,
            std::unique_ptr<sn_crate_data_t>> tpc_sn_crate_data_tuple_t;
    typedef std::map<int,tpc_sn_crate_data_tuple_t> tpc_sn_seb_map_t;

    typedef std::map<int,tpc_sn_crate_data_t const&> tpc_sn_map_t;

    typedef std::tuple<raw_fragment_data_t,
            std::unique_ptr<ub_RawData>,
            std::unique_ptr<pmt_crate_data_t>> pmt_crate_data_tuple_t;
    typedef std::map<int,pmt_crate_data_tuple_t> pmt_seb_map_t;

    typedef std::map<int,pmt_crate_data_t const&> pmt_map_t;

    typedef std::tuple< raw_fragment_data_t,
                        std::unique_ptr<ub_RawData>,
                        std::unique_ptr<trig_crate_data_t> > trig_crate_data_tuple_t;
    typedef std::map<int,trig_crate_data_tuple_t> trig_seb_map_t;
    typedef std::map<int,trig_crate_data_t const&> trig_map_t;

    typedef std::map<int,ub_LaserData> laser_map_t;

    typedef std::vector<raw_fragment_data_t const*> fragment_references_t;

    static const uint8_t DAQ_version_number = gov::fnal::uboone::datatypes::constants::DATATYPES_VERSION;

    ub_EventRecord();
    ~ub_EventRecord();

    global_header_t& getGlobalHeader() noexcept;
    void setGlobalHeader (global_header_t const& header) noexcept;

    void addFragment(raw_fragment_data_t & fragment) throw(datatypes_exception,data_size_exception);
    void addFragment_TPC_or_LASER(raw_fragment_data_t & fragment) throw(datatypes_exception,data_size_exception);
    void addFragment_PMT_or_TRIG(raw_fragment_data_t & fragment) throw(datatypes_exception,data_size_exception);
    void addFragment_SN(raw_fragment_data_t & fragment) throw(datatypes_exception,data_size_exception);

    trigger_counter_t const& getTriggerCounter() noexcept;
    void setTriggerCounter( trigger_counter_t const& ) noexcept;
    void resetTriggerCounter() noexcept;
    trig_data_t const& getTriggerData() noexcept;
    bool passesSoftwarePrescale( std::map< uint16_t, float> const&, uint16_t, double ) noexcept; 

    void addSWTriggerOutput( ub_FEMBeamTriggerOutput const& ) noexcept;
    std::vector<ub_FEMBeamTriggerOutput> const& getSWTriggerOutputVector() noexcept;
    
    std::string debugInfo()const noexcept;
    

    bool compare(ub_EventRecord const& event_record, bool do_rethrow) const throw(datatypes_exception);
    void gps_sign_adjust (int&, int&);
    
    const tpc_map_t     getTPCSEBMap() const noexcept;
    const tpc_sn_map_t  getTpcSnSEBMap() const noexcept;
    const pmt_map_t     getPMTSEBMap() const noexcept;
    const trig_map_t    getTRIGSEBMap() const noexcept;
    laser_map_t const&  getLASERSEBMap() const noexcept;

    std::size_t getFragmentCount() const noexcept;
    void updateDTHeader() throw (datatypes_exception);
    
    void setGPSTime(ub_GPS_Time const& gps_time) noexcept;
    void setTriggerBoardClock(ub_TriggerBoardClock const& trigger_board_time) noexcept;
    void setLocalHostTime(ub_LocalHostTime const& localhost_time) noexcept;

    void setGPSEVTTime(ub_GPS_Time const& gps_time) noexcept;
    void setTriggerBoardEVTClock(ub_TriggerBoardClock const& trigger_board_time) noexcept;
    
    void setBeamRecord(ub_BeamRecord const& beam_record) noexcept;
    
    ub_GPS_Time const& GPSTime() const noexcept;    
    ub_TriggerBoardClock const& TriggerBoardClock() const noexcept;
    ub_GPS_Time const& GPSEVTTime() const noexcept;    
    ub_TriggerBoardClock const& TriggerBoardEVTClock() const noexcept;
    ub_LocalHostTime const& LocalHostTime() const noexcept;
    
    ub_BeamRecord const& beamRecord()const noexcept;
    ub_BeamRecord& beamRecord() noexcept;

    void markAsIncompleteEvent() noexcept;
    void setCrateSerializationMask(uint16_t mask) throw (datatypes_exception);
    
    //do your custom out-of-class specialization if needed
    template <typename EVENTFRAGMENTPTR_TYPE>
            void releaseFragmentsAs( EVENTFRAGMENTPTR_TYPE*  );
    
    static int getEventRecordVersion() noexcept;
private:
    void  getFragments(fragment_references_t& fragments) const noexcept;
private:
    ub_event_header    _bookkeeping_header;
    ub_event_trailer   _bookkeeping_trailer;
    global_header_t    _global_header;
    trig_data_t        _trigger_data;
    trigger_counter_t  _trigger_counter;
    tpc_seb_map_t      _tpc_seb_map;
    tpc_sn_seb_map_t   _tpc_sn_seb_map;
    pmt_seb_map_t      _pmt_seb_map;
    trig_seb_map_t     _trigger_seb_map;
    laser_map_t        _laser_seb_map;

    ub_BeamRecord        _beam_record;

    std::vector< ub_FEMBeamTriggerOutput > _swtrigger_output_vector;
    
    mutable std::atomic<uint16_t> _crate_serialization_mask={0xFFFF};
    static int eventRecordVersion;

#define UNUSED(x) (void)(x)
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        UNUSED(version);
        
        //BEGIN SERIALIZE RAW EVENT FRAGMENT DATA
        fragment_references_t fragments;
        getFragments(fragments);
        
        auto bookkeeping_header=_bookkeeping_header;
        
        if(_bookkeeping_header.event_fragment_count!=fragments.size()){
            bookkeeping_header.is_event_complete=false;
            bookkeeping_header.event_fragment_count=fragments.size();
        }
        
        assert(bookkeeping_header.event_fragment_count==fragments.size());
        assert(bookkeeping_header.raw_event_fragments_wordcount==std::accumulate(
        fragments.begin(),fragments.end(),0u,[](size_t total, raw_fragment_data_t const* fragment) {
            return total+fragment->size()*sizeof(fragment_value_type_t);
        }));

        // write bookkeeping info
        ar.save_binary(&bookkeeping_header,ub_event_header_size);

        // write raw fragmetns with crate headers
        for(auto const& fragment : fragments) {
            std::size_t size {fragment->size()};
            ar.save_binary(&size, sizeof(std::size_t)) ;
            ar.save_binary(fragment->data(),size*sizeof(fragment_value_type_t));
        }
        //END SERIALIZE RAW EVENT FRAGMENT DATA

        // write remaining event details

	if(version>=11){
	  ar << _global_header;
	  ar << _trigger_counter;
	  ar << _laser_seb_map;
	  ar << _swtrigger_output_vector;
	}
	else if(version>=9){
	  ar << _global_header;
	  ar << _trigger_counter;
	  ar << _laser_seb_map;
	}
	else if(version>=8){
	  ar << _global_header;
	  ar << _laser_seb_map;
	}
        else if(version>0)
        {
            ar << _global_header;
            //ar << _beam_record;
        }
        //this must be the last step
        ar.save_binary(&_bookkeeping_trailer,ub_event_trailer_size);
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        UNUSED(version);
        
        eventRecordVersion=version;
        
        //BEGIN SERIALIZE RAW EVENT FRAGMENT DATA
        // read bookkeeping info
        ar.load_binary(&_bookkeeping_header,ub_event_header_size);
        if(_bookkeeping_header.mark_E974!=UBOONE_EHDR)
            throw datatypes_exception("Invalid header marker");
            
        assert(_bookkeeping_header.mark_E974==UBOONE_EHDR);
        // write raw fragmetns with crate headers
        std::size_t frag_number{_bookkeeping_header.event_fragment_count};
        while(frag_number--)
        {
            raw_fragment_data_t fragment;
            std::size_t size;
            ar.load_binary(&size,sizeof(std::size_t)) ;
            fragment.resize(size);
            ar.load_binary(fragment.data(),fragment.size()*sizeof(fragment_value_type_t));
            addFragment(fragment);
        }
        fragment_references_t fragments;
        getFragments(fragments);
        assert(_bookkeeping_header.raw_event_fragments_wordcount==std::accumulate(
        fragments.begin(),fragments.end(),0u,[](size_t total, raw_fragment_data_t const* fragment) {
            return total+fragment->size()*sizeof(fragment_value_type_t);
        }));
        //END SERIALIZE RAW EVENT FRAGMENT DATA

        // write remaining event details
	if(version>=11){
	  ar >> _global_header;
	  ar >> _trigger_counter;
	  ar >> _laser_seb_map;
	  ar >> _swtrigger_output_vector;
	}
	else if(version>=9){
	  ar >> _global_header;
	  ar >> _trigger_counter;
	  ar >> _laser_seb_map;
	}
	else if(version>=8){
	  ar >> _global_header;
	  ar >> _laser_seb_map;
	}
        else if(version>0)
        {
            ar >> _global_header;
            //ar << _beam_record;
        }

        //this must be the last step
        ar.load_binary(&_bookkeeping_trailer,ub_event_trailer_size);
        
        if(_bookkeeping_trailer.mark_974E!=UBOONE_ETLR)
            throw datatypes_exception("Invalid trailer marker");
            
        assert(_bookkeeping_trailer.mark_974E==UBOONE_ETLR);
    }
    BOOST_SERIALIZATION_SPLIT_MEMBER()

};

}  // end of namespace datatypes
}  // end of namespace uboone
}  // end of namespace fnal
}  // end of namespace gov

// This MACRO must be outside any namespaces.
BOOST_CLASS_VERSION(gov::fnal::uboone::datatypes::ub_EventRecord, gov::fnal::uboone::datatypes::constants::DATATYPES_VERSION)

#endif /* #ifndef BOONETYPES_H */
