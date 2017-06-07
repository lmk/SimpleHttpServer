#include "Logger.h"
#include "Common.h"

LOGLEVEL g_logLevel = DEBUG;

const std::string currentDateTime()
{
	time_t     now = time(0);
	char       buf[100];
	strftime(buf, sizeof(buf), "[%H:%M:%S]", localtime(&now));

	return buf;
}

const std::string levelString(int lvl)
{
	const std::string slevel[] = { "", "DBUG", "INFO", "WARN", "ERRR", "CRIT" };

	if (0 < lvl &&  lvl < 6) {
		return slevel[lvl];
	}

	return "";
}