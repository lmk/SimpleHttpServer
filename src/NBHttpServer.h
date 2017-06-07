#pragma once

#include <pthread.h>
#include "HttpServer.h"


class NBHttpServer
{
public:
	static NBHttpServer *getInstance();
	~NBHttpServer();

	void Init(int poolSize);
	void Start();
	void Stop();

private:
	NBHttpServer();
	static bool isRunning();
	static void setRunStat(bool stat);
	static void* RunHttpServer(void* data);

	static NBHttpServer *_instance;

	static HttpServer *_httpServer;
	static bool _isRunning;
	static pthread_mutex_t _mutex;
	static pthread_t _thread;

};

