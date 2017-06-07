#pragma once
#include <string>
#include <map>

class HttpHeader
{
public:
	HttpHeader();
	~HttpHeader();

	std::string Method;
	std::string Path;
	std::string Version;

	std::map<std::string, std::string> Item;

	std::string GetHost();
};

