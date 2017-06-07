#include "HttpReqParser.h"
#include "Common.h"


HttpReqParser::HttpReqParser()
{
}


HttpReqParser::~HttpReqParser()
{
}

static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

// success to return empty string
string HttpReqParser::Parse(string source)
{
	// header 
	istringstream iss(source);
	string s;

	// method
	if (!getline(iss, s, ' ')) {
		return "Error parsing method";
	};
	_header.Method = s;

	// path
	if (!getline(iss, s, ' ')) {
		return "Error parsing path";
	};
	_header.Path = s;

	// version
	if (!getline(iss, s, '\r')) {
		return "Error parsing version";
	};
	_header.Version = s;

	// headers...
	_header.Item.clear();

	while (getline(iss, s, '\r')) {
		if (s.length() == 1) break;  // only '\n' end header
		istringstream isline(s);

		if (!getline(isline, s, ':')) {
			s = "Error parsing header: ";
			s.append(isline.str());
			return s;
		}
		string key = s.substr(1); // erase '\n'

		if (!getline(isline, s, '\r')) {
			s = "Error parsing header: ";
			s.append(isline.str());
			return s;
		}

		transform(key.begin(), key.end(), key.begin(), ::toupper);
		_header.Item[key] = trim(s);
	}

	// body
	std::size_t found = source.find("\r\n\r\n");
	if (found + 4 < source.length()) {
		_body = source.substr(found+4);
	}

	return "";
}

std::string HttpReqParser::GetBody()
{
	return _body;
}

HttpHeader HttpReqParser::GetHeader()
{
	return _header;
}
