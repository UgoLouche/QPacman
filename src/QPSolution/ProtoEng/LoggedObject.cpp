#include "LoggedObject.h"

#include "SimpleLogger.h"

ProtoEng::LoggedObject::LoggedObject()
	: logger(NULL)
{
}

ProtoEng::LoggedObject::LoggedObject(SimpleLogger * logger)
	: LoggedObject()
{
	linkLogger(logger);
}

ProtoEng::LoggedObject::~LoggedObject()
{
}

void ProtoEng::LoggedObject::linkLogger(SimpleLogger * logger)
{
	this->logger = logger;
	infoLog("New object linked");
}

 void ProtoEng::LoggedObject::log(const std::string& message, uint16_t lvl) const
{
	if (logger != NULL) logger->log(custom_log_header() + message, lvl);
}

 void ProtoEng::LoggedObject::infoLog(const std::string& message) const
{
	log(message, SimpleLogger::INFO);
}

 void ProtoEng::LoggedObject::warnLog(const std::string& message) const
{
	 log(message, SimpleLogger::WARNING);
}

 void ProtoEng::LoggedObject::errLog(const std::string& message) const
{
	 log(message, SimpleLogger::ERROR);
}

 std::string ProtoEng::LoggedObject::custom_log_header() const
{
	return  "";
}
