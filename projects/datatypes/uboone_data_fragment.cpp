#include "uboone_data_fragment.h"
#include "uboone_data_utils.h"
#include <sstream>

using namespace gov::fnal::uboone::datatypes;

datatypes_exception::datatypes_exception(std::string const& message, std::string const& name)
    :_name(name), _message(message)
{
    std::stringstream out;
    out << " " << _name << " Message: " << _message <<".";
    _message = out.str();
}

const char * datatypes_exception::what () const throw ()
{
    return _message.c_str();
}

datatypes_exception::~datatypes_exception() noexcept
{

}

bool ub_fragment_header::compare(ub_fragment_header const& header, bool do_rethrow) const throw(datatypes_exception)
{
    try {
        if(total_fragment_wordcount!=header.total_fragment_wordcount)
            throw datatypes_exception(make_compare_message("data_transmission_header", "total_fragment_wordcount", total_fragment_wordcount,header.total_fragment_wordcount));

        if(fragment_format_version!=header.fragment_format_version)
            throw datatypes_exception(make_compare_message("data_transmission_header", "fragment_format_version", fragment_format_version,header.fragment_format_version));

        if(is_fragment_complete!=header.is_fragment_complete)
            throw datatypes_exception(make_compare_message("data_transmission_header", "is_fragment_complete", is_fragment_complete,header.is_fragment_complete));

        if(raw_fragment_wordcount!=header.raw_fragment_wordcount)
            throw datatypes_exception(make_compare_message("data_transmission_header", "raw_fragment_wordcount", raw_fragment_wordcount,header.raw_fragment_wordcount));

        if(raw_fragment_beginning_word_offset!=header.raw_fragment_beginning_word_offset)
            throw datatypes_exception(make_compare_message("data_transmission_header", "raw_fragment_beginning_word_offset", raw_fragment_beginning_word_offset,header.raw_fragment_beginning_word_offset));

        if(md5hash!=header.md5hash)
            throw datatypes_exception(make_compare_message("data_transmission_header", "md5hash", md5hash,header.md5hash));
    } catch(datatypes_exception &ex) {
        std::cerr << ex.what();
        if(do_rethrow)
            throw;
        else
            return false;
    } catch(...) {
        std::cerr << "Unknown exception in  ub_fragment_header::compare()";
        if(do_rethrow)
            throw datatypes_exception("Unknown exception in  ub_fragment_header::compare()");
        else
            return false;
    }
    return true;
}


void ub_fragment_header::calculateMD5hash(unsigned char const* addr, std::size_t bytes) noexcept {
    MD5(addr, bytes , md5hash);
}

bool ub_fragment_header::verifyMD5hash(unsigned char const* addr, std::size_t bytes) const noexcept {
    unsigned char md5hash_[MD5_DIGEST_LENGTH];
    MD5(addr, bytes , md5hash_);
    return std::equal(std::begin(md5hash), std::end(md5hash), std::begin(md5hash_));
}