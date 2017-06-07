#include "HttpResponse.h"
#include "Common.h"


HttpResponse::HttpResponse()
{
}


HttpResponse::~HttpResponse()
{
}

string HttpResponse::Make(string version, string host, string uri, string body)
{
	stringstream ss;

	// 3. send static header
	ss << version << " " << 200 << " OK" << "\r\n";

	ss << "Content-Length: " << body.length() << "\r\n";
	ss << "Content-Type: text/html" << "\r\n";
	ss << "Connection: close" << "\r\n\r\n";
	ss << body;

	return ss.str();
}

string HttpResponse::MakeError(string version, string host, string uri, int code, string msg)
{
	stringstream ss;

	ss << version << " " << code << " " << getHttpMsg(code) << "\r\n";

	ss << "Content-Length: " << msg.length() << "\r\n";
	ss << "Content-Type: text" << "\r\n";
	ss << "Connection: close" << "\r\n\r\n";
	ss << msg;

	return ss.str();
}

string HttpResponse::getHttpMsg(int code)
{
	switch(code)
	{
		case 100: return "Continue";
		case 101: return "Switching Protocols";
		case 102: return "Processing";
		case 200: return "OK";
		case 201: return "Created";
		case 202: return "Accepted";
		case 203: return "Non-Authoritative Information";
		case 204: return "No Content";
		case 205: return "Reset Content";
		case 206: return "Partial Content";
		case 207: return "Multi-Status";
		case 300: return "Multiple Choices";
		case 301: return "Moved Permanently";
		case 302: return "Found";
		case 303: return "See Other";
		case 304: return "Not Modified";
		case 305: return "Use Proxy";
		case 307: return "Temporary Redirect";
		case 400: return "Bad Request";
		case 401: return "Unauthorized";
		case 402: return "Payment Required";
		case 403: return "Forbidden";
		case 404: return "Not Found";
		case 405: return "Method Not Allowed";
		case 406: return "Not Acceptable";
		case 407: return "Proxy Authentication Required";
		case 408: return "Request Timeout";
		case 409: return "Conflict";
		case 410: return "Gone";
		case 411: return "Length Required";
		case 412: return "Precondition Failed";
		case 413: return "Request Entity Too Large";
		case 414: return "Request-URI Too Long";
		case 415: return "Unsupported Media Type";
		case 416: return "Requested Range Not Satisfiable";
		case 417: return "Expectation Failed";
		case 422: return "Unprocessable Entity";
		case 423: return "Locked";
		case 424: return "Failed Dependency";
		case 426: return "Upgrade Required";
		case 500: return "Internal Server Error";
		case 501: return "Not Implemented";
		case 502: return "Bad Gateway";
		case 503: return "Service Unavailable";
		case 504: return "Gateway Timeout";
		case 505: return "HTTP Version Not Supported";
		case 506: return "Variant Also Negotiates";
		case 507: return "Insufficient Storage";
		case 509: return "Bandwidth Limit Exceeded";
		case 510: return "Not Extended";
	}

	return "Bad Request";
}