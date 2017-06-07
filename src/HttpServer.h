#pragma once
#include "Sessions.h"

typedef bool(*funcIsConitnuePtr)();

class HttpServer
{
public:
	HttpServer();
	~HttpServer();

	void Init(int poolSize, funcIsConitnuePtr func);
	void Run();

private:
	int _poolSize;
	unsigned short _listenPort;
	Sessions sessions;
	funcIsConitnuePtr _IsConitnue;

	int listenPort();
};

