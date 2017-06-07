#pragma once
#include "Common.h"
class HttpWorker
{
public:
	HttpWorker();
	~HttpWorker();

	bool Run(string req, stringstream &res);

protected:
	bool doTest(string uri, string requestBody, stringstream &res);
};

