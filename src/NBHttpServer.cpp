#include "NBHttpServer.h"
#include <pthread.h>
#include <signal.h>

NBHttpServer *NBHttpServer::_instance = NULL;
HttpServer *NBHttpServer::_httpServer = NULL;
bool NBHttpServer::_isRunning = false;
pthread_mutex_t NBHttpServer::_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t NBHttpServer::_thread = 0;
NBHttpServer::NBHttpServer()
{
	_httpServer = new HttpServer();
}

NBHttpServer *NBHttpServer::getInstance()
{
	if (!_instance) {
		_instance = new NBHttpServer();
	}

	return _instance;
}

NBHttpServer::~NBHttpServer()
{
	pthread_mutex_destroy(&_mutex);
}

void NBHttpServer::Init(int poolSize)
{
	if (isRunning()) return;

	_httpServer->Init(poolSize, isRunning);
}

void NBHttpServer::Start() 
{
	if (isRunning()) return;

	pthread_create(&_thread, NULL, RunHttpServer, NULL);
}

void NBHttpServer::Stop()
{
	setRunStat(false);
	
	sleep(1);
	pthread_kill(_thread, 0);
}

bool NBHttpServer::isRunning()
{
	bool result;

	pthread_mutex_lock(&_mutex);
	result = _isRunning;
	pthread_mutex_unlock(&_mutex);

	//Logger(INFO) << "result:" << result << endl;

	return result;
}

void NBHttpServer::setRunStat(bool stat)
{
	pthread_mutex_lock(&_mutex);
	_isRunning = stat;
	pthread_mutex_unlock(&_mutex);
}

void* NBHttpServer::RunHttpServer(void* data) 
{
	setRunStat(true);
	_httpServer->Run();

	return NULL;
}