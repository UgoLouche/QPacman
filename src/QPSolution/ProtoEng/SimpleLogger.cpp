#include "SimpleLogger.h"

ProtoEng::SimpleLogger::~SimpleLogger()
{
}

void ProtoEng::SimpleLogger::log(const std::string& message, uint16_t lvl) const
{
	custom_log(message, lvl);
}
