#include "QPLogger.h"
#include "const.h"

#include <ctime>

QPLogger::QPLogger(std::string info_path, std::string warning_path, std::string error_path)
{
	if (info_path != "")
		info.open(info_path, std::ostream::app);

	if (warning_path != "")
		warning.open(warning_path, std::ostream::app);

	if (error_path != "")
		error.open(error_path, std::ostream::app);

	setMask(NONE);
}

QPLogger::QPLogger() : QPLogger("", "", "")
{
}

QPLogger::~QPLogger()
{
	log(CLOSING_STR, ALL);

	if (info.is_open()) info.close();
	if (warning.is_open()) warning.close();
	if (error.is_open()) error.close();
}

uint16_t QPLogger::setMask(uint16_t mask)
{
	if (!info.is_open()) mask = mask & ~INFO;
	if (!warning.is_open()) mask &= mask & ~WARNING;
	if (!error.is_open()) mask &= mask & ~ERROR;

	this->mask = mask;

	return mask;
}

uint16_t QPLogger::getMask() const
{
	return mask;
}

void QPLogger::custom_log(const std::string& message, uint16_t lvl) const
{
	std::string prefix = getPrefix();

	if (lvl & INFO & mask)
		info << prefix << " :: " << message << "\n";

	if (lvl & WARNING & mask)
		warning << prefix << " :: " << message << "\n";

	if (lvl & ERROR & mask)
		error << prefix << " :: " << message << "\n";
}

std::string QPLogger::getPrefix() const
{
	time_t raw = time(&raw);
	return std::string(ctime(&raw), 24);
}
