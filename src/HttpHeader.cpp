#include "HttpHeader.h"
#include "Common.h"

HttpHeader::HttpHeader()
{
}


HttpHeader::~HttpHeader()
{
}

string HttpHeader::GetHost()
{
	map<string, string>::iterator iter = Item.find("HOST");
	if (iter == Item.end()) {
		return "";
	}

	return Item["HOST"];
}