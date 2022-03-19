#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <cassert>
#include <chrono>
#include <ostream>
#include <string>
#include <vector>
#include <cstdint>

#include "types.h"

namespace Frogboard {

std::string engine_info();
std::string compiler_info();
void start_logger(const std::string& fname);



}

#endif

