#ifndef _UBOONE_DATATYPES_COMMON_H
#define _UBOONE_DATATYPES_COMMON_H  1

#include <map>
#include <cstring>
#include <string>
#include <sys/time.h>

#include "constants.h"

/* These and the following string definitions are crate-type, also
 * known as the "system designator*.*/
enum  SystemDesignator {
    TRIGGER_SYSTEM = 0,
    TPC_SYSTEM,
    PMT_SYSTEM,
    VETO_SYSTEM,
    TEST_SYSTEM,
    AUX_SYSTEM,
    LASER_SYSTEM,
      TPC_SN_SYSTEM,
};

/* These strings are used to describe each crate type in
 the 2nd field of the crate.inde*x file */

const std::map<int, std::string> systemDesignatorToString
= {{ SystemDesignator::TRIGGER_SYSTEM, "TRIGGER" },
   { SystemDesignator::TPC_SYSTEM, "TPC" },
   { SystemDesignator::PMT_SYSTEM, "PMT" },
   { SystemDesignator::VETO_SYSTEM, "VETO"},
   { SystemDesignator::TEST_SYSTEM, "TEST"},
   { SystemDesignator::AUX_SYSTEM, "AUX" },
   { SystemDesignator::LASER_SYSTEM, "LASER" },
   { SystemDesignator::TPC_SN_SYSTEM, "TPCSN" },
 };

const std::map<const std::string, SystemDesignator> stringToSystemDesignator
= {{"TRIGGER", SystemDesignator::TRIGGER_SYSTEM },
  { "TPC", SystemDesignator::TPC_SYSTEM },
  { "PMT", SystemDesignator::PMT_SYSTEM },
  { "VETO", SystemDesignator::VETO_SYSTEM},
  { "TEST", SystemDesignator::TEST_SYSTEM},
  { "AUX", SystemDesignator::AUX_SYSTEM },
  { "LASER", SystemDesignator::LASER_SYSTEM },
  { "TPCSN", SystemDesignator::TPC_SN_SYSTEM },
 };

typedef SystemDesignator SystemDesignator_t;

std::string demangle(const std::type_info  &type_info) noexcept;

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#define SET_BIT(var,pos) ((var) |= (1<<(pos)))

#endif //_UBOONE_DATATYPES_COMMON_H

