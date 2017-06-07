#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <stdio.h>
#include <time.h>

typedef enum _LOGLEVEL {
	NONE,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	CRITICAL
} LOGLEVEL;

extern LOGLEVEL g_logLevel;

const std::string currentDateTime();
const std::string levelString(int lvl);

#define Logger(lvl) std::cout << currentDateTime() << "[" << levelString(lvl) << "] " 
