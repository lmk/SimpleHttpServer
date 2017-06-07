#pragma once
#include "Common.h"
#include "Session.h"

class Sessions
{
public:
	Sessions();
	~Sessions();

	void Init(int size);
	bool Add(int fd);
	bool Remove(int fd);
	Session *Get(int fd);
	vector<int> GetAllFd();
	void FD_SET_All(fd_set* fs);
	void Release();

private:
	int _size;  // maxinum session
	map<int, Session*> _fd_list;
};

//typedef std::shared_ptr<Sessions> SessionsPtr;
//typedef std::auto_ptr<Sessions> SessionsPtr;