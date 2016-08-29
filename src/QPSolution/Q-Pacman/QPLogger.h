#pragma once

#include "SimpleLogger.h"

#include <fstream>
#include <string>

//Minimal need so I'll just code one on the fly.
class QPLogger : public ProtoEng::SimpleLogger
{
public:
	QPLogger(std::string info_path = "", std::string warning_path = "", std::string error_path = "");
	QPLogger();
	~QPLogger();

	//Kill masks bits if stream are not open, return modified mask
	uint16_t setMask(uint16_t mask);
	uint16_t getMask() const;

private:
	//Virtual Implementation
	virtual void custom_log(const std::string& message, uint16_t lvl) const override;

	std::string getPrefix() const;

	mutable std::ofstream info;
	mutable std::ofstream warning;
	mutable std::ofstream error;

	uint16_t mask;

};