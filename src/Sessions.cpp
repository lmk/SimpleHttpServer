#include "Common.h"
#include "Sessions.h"

Sessions::Sessions()
{
	_size = 0;
}

Sessions::~Sessions()
{
	Release();
}

void Sessions::Init(int size)
{
	_size = size;
	Release();
}

bool Sessions::Add(int fd)
{
	int s;

	if (_size <= (int)_fd_list.count(s)) return false;

	_fd_list[fd] = new Session(fd);

	return true;
}

bool Sessions::Remove(int fd)
{
	map<int, Session*>::iterator iter = _fd_list.find(fd);
	if (iter == _fd_list.end()) {
		return false;
	}

	delete _fd_list[fd];
	_fd_list.erase(fd);
	close(fd);

	return true;
}

vector<int> Sessions::GetAllFd()
{
	vector<int> v;
	for (map<int, Session*>::iterator it = _fd_list.begin(); it != _fd_list.end(); ++it) {
		v.push_back(it->first);
	}

	return v;
}

void Sessions::FD_SET_All(fd_set* fs)
{
	for (map<int, Session*>::iterator it = _fd_list.begin(); it != _fd_list.end(); ++it) {
		FD_SET(it->first, fs);
	}
}

Session *Sessions::Get(int fd)
{
	map<int, Session*>::iterator iter = _fd_list.find(fd);
	if (iter == _fd_list.end()) {
		return NULL;
	}

	return _fd_list[fd];
}

void Sessions::Release()
{
	for (map<int, Session*>::iterator it = _fd_list.begin(); it != _fd_list.end(); ++it) {
		delete _fd_list[it->first];
	}
}