#include "HttpWorker.h"
#include "HttpHeader.h"
#include "HttpReqParser.h"
#include "HttpResponse.h"

HttpWorker::HttpWorker()
{
}

HttpWorker::~HttpWorker()
{
}

bool HttpWorker::Run(string req, stringstream &res)
{
	// 1. parsing
	HttpReqParser parser;
	string resultMsg = parser.Parse(req);

	HttpHeader reqHeader = parser.GetHeader();
	string reqBody = parser.GetBody();

	// 2. route method
	stringstream resBody;

	if (reqHeader.Path.compare("/test") == 0) {
		doTest(reqHeader.Path, reqBody, resBody);
	}
	else {
		Logger(INFO) << "Unknown path: " << reqHeader.Path << endl;
		res << HttpResponse::MakeError(reqHeader.Version, reqHeader.GetHost(), reqHeader.Path, 404, resBody.str());
		return true;
	}

	// 4. send body
	if (resultMsg.length() == 0) {
		res << HttpResponse::Make(reqHeader.Version, reqHeader.GetHost(), reqHeader.Path, resBody.str());
	}
	else {
		res << HttpResponse::MakeError(reqHeader.Version, reqHeader.GetHost(), reqHeader.Path, 500, resultMsg);
	}

	return true;
}

bool HttpWorker::doTest(string uri, string requestBody, stringstream &res)
{
	res << "Hello World!" << endl;

	return true;
}
