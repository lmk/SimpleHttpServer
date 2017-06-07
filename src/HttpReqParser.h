#pragma once
#include <string>
#include "HttpHeader.h"

class HttpReqParser
{
public:
	HttpReqParser();
	~HttpReqParser();

	std::string Parse(std::string source);
	std::string GetBody();

	HttpHeader GetHeader();

private:
	HttpHeader _header;
	std::string _body;
};

