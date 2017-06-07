#pragma once
#include <string>
class HttpResponse
{
public:
	HttpResponse();
	~HttpResponse();

	static std::string Make(std::string version, std::string host, std::string uri, std::string body);
	static std::string MakeError(std::string version, std::string host, std::string uri, int code, std::string msg);
	static std::string getHttpMsg(int code);
};

