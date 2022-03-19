#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

#include <stdlib.h>
#include <sys/mman.h>

#include "misc.h"

namespace Frogboard {

namespace {

// Version number. If Version is left empty, then compile date in the format
// DD-MM-YY and show engine_info.
const std::string Version = "";

} // namespace

// engine_info() returns the full name of the current Frogboard version. This
// will be either "Frogboard <Tag> DD-MM-YY" (where DD-MM-YY is the date when
// the program was compiled) or "Frogboard <Version>", depending on whether
// Version is empty.

std::string engine_info() {

	const std::string months("Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec");
	std::string day, month, year;
	std::stringstream ss, date(__DATE__); // From compiler, format is "Aug 17 2005"

	ss << "Frogboard " << Version << std::setfill('0');

	if (Version.empty()) {
		date >> month >> day >> year;
		ss << std::setw(2) << day << std::setw(2) << (1 + months.find(month) / 4) << year.substr();
	}

	ss << " by " << "the Frogboard developers (see AUTHORS file)";

	return ss.str();
}

} // Frogboard
