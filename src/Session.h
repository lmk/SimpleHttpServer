#pragma once

#include <memory>
#include <string>

class Session
{
public:
	Session(int fd);
	~Session();

	std::string Read();
	int Write(std::string);

private:
	int _fd;
};

//typedef std::shared_ptr<Session> SessionPtr;
//typedef std::auto_ptr<Session> SessionPtr;
